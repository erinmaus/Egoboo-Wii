// This file is part of Egoboo-Wii.
//
// Egoboo-Wii is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Egoboo-Wii is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Egoboo-Wii.  If not, see <http:// www.gnu.org/licenses/>.

#include <algorithm>
#include <cctype>

#include "Color.hpp"
#include "File.hpp"
#include "IDisplay.hpp"
#include "Image.hpp"
#include "ITexture.hpp"

Adventure::Image::ImageIdentifier Adventure::Image::IdentifierFromExtension(const std::string& extension)
{
	std::string e = extension;
	std::transform(e.begin(), e.end(), e.begin(), tolower);
	
	if (e == "bmp")
		return Bmp;
	else if (e == "tga")
		return Tga;
	else if (e == "png")
		return Png;
	
	return Unknown;
}

Adventure::ITexture* Adventure::Image::LoadFromFile(File& file, ImageIdentifier identifier, IDisplay& display)
{
	switch(identifier)
	{
		case Tga:
			return LoadTgaFromFile(file, display);
		
		case Bmp:
		case Png:
		default:
			return NULL;
	}
}

#include <fstream>

Adventure::ITexture* Adventure::Image::LoadTgaFromFile(File& file, IDisplay& display)
{
	file.GetStream().seekg(2, std::ios::beg);
	
	File::UInt8 type;
	file.Read(type);
	
	if (type != 2) // Type 2 indicates a BGRA image
		return NULL;
	
	file.GetStream().seekg(11, std::ios::beg);
	
	File::UInt16 width, height;
	file.Read(width);
	file.Read(height);
	
	int pixels = width * height;
	
	file.GetStream().seekg(16, std::ios::beg);
	
	File::UInt8 bits;
	file.Read(bits);
	
	if (bits < 24)
		return NULL;
	
	file.GetStream().seekg(18, std::ios::beg);
	
	Color* pixelData = new Color[pixels];
	
	for (int i = 0; i < pixels; i++)
	{
		// BGRA format
		file.Read(pixelData[i].Blue);
		file.Read(pixelData[i].Green);
		file.Read(pixelData[i].Red);
		
		if (bits == 32)
			file.Read(pixelData[i].Alpha);
		else
			pixelData[i].Alpha = Color::MaxChannelValue;
	}
	
	ITexture* texture = display.CreateTexture();
	
	if (texture == NULL)
	{
		delete[] pixelData;
		return NULL;
	}
	
	texture->SetData(pixelData, width, height, ITexture::Rgba8, ITexture::Point);
	
	delete[] pixelData;
		
	return texture;
}
