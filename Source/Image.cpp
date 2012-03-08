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
#include <cmath>

#include "Allocator.hpp"
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

Adventure::ITexture* Adventure::Image::LoadFromFile(File& file, ImageIdentifier identifier, IDisplay& display, Allocator* scratch)
{
	switch(identifier)
	{
		case Tga:
			return LoadTgaFromFile(file, display, scratch);
		
		case Bmp:
			return LoadBmpFromFile(file, display, scratch);
			
		case Png:
		default:
			return NULL;
	}
}

Adventure::ITexture* Adventure::Image::LoadBmpFromFile(File& file, IDisplay& display, Allocator* scratch)
{
	struct
	{
		File::UInt8 Type[2];
		File::UInt32 Size;
		File::UInt32 Reserved;
		File::UInt32 Offset;
	} header;
	
	TRACE(DEBUG_FILE_LOADING, "Loading BMP file...");
	
	file.Read(header.Type[0]);
	file.Read(header.Type[1]);
	
	if (header.Type[0] != 'B' || header.Type[1] != 'M')
		return NULL;
	
	file.Read(header.Size);
	file.Read(header.Reserved);
	file.Read(header.Offset);
	
	TRACE(DEBUG_FILE_LOADING, "Loaded header.");
	
	struct
	{
		File::UInt32 Size;
		File::Int32 Width;
		File::Int32 Height;
		File::UInt16 Planes;
		File::UInt16 Bits;
		File::UInt32 Compression;
		File::UInt32 DataSize;
		File::Int32 XPixelsPerMeter;
		File::Int32 YPixelsPerMeter;
		File::UInt32 Colors;
		File::UInt32 ImportantColors;
	} info;
	
	file.Read(info.Size);
	file.Read(info.Width);
	file.Read(info.Height);
	file.Read(info.Planes);
	file.Read(info.Bits);
	
	if (!(info.Bits == 8 || info.Bits == 24))
		return NULL;
		
	TRACE(DEBUG_FILE_LOADING, "BMP is of valid bit depth (8 or 24 bits)");
	
	file.Read(info.Compression);
	file.Read(info.DataSize);
	file.Read(info.XPixelsPerMeter);
	file.Read(info.YPixelsPerMeter);
	file.Read(info.Colors);
	file.Read(info.ImportantColors);
	
	Color* table = NULL;
	if (info.Bits == 8)
	{
		TRACE(DEBUG_FILE_LOADING, "Reading color table...");
		
		table = new(scratch) Color[256];
		
		for (int i = 0; i < 256; i++)
		{
			file.Read(table[i].Blue);
			file.Read(table[i].Green);
			file.Read(table[i].Red);
			table[i].Alpha = Color::MaxChannelValue;
			
			File::UInt8 reserved;
			file.Read(reserved);
		}
		
		TRACE(DEBUG_FILE_LOADING, "Read color table.");
	}
	
	TRACE(DEBUG_FILE_LOADING, "Reading image data...");
	
	int size = header.Size - header.Offset;
	File::UInt8* data = new(scratch) File::UInt8[size];
	file.GetStream().read((char*)data, size);
	
	TRACE(DEBUG_FILE_LOADING, "Read image data.");
	
	Color* pixels = new(scratch) Color[info.Width * abs(info.Height)];
	
	int height = abs(info.Height);
	
	int width = info.Width * info.Bits / 8; // Only 24 and 8 bit formats supported
	int stride = (width + 3) & ~3; // Round to nearest multiple of four
	
	int y = 0;
	
	TRACE(DEBUG_FILE_LOADING, "Converting image data to RGBA...");
	
	while (y < height)
	{
		if (info.Bits == 8)
		{
			for (int i = 0; i < info.Width; i++)
			{
				int index = y * stride + i;
				pixels[index] = table[data[index]];
			}
		}
		else
		{
			for (int i = 0; i < info.Width; i++)
			{
				int index = y * stride + i;
				int dataIndex = y * stride + i * 4;
				pixels[index].Red = data[dataIndex + 2];
				pixels[index].Green = data[dataIndex + 1];
				pixels[index].Blue = data[dataIndex];
				
				pixels[index].Alpha = Color::MaxChannelValue;
			}
		}
		
		y++;
	}
	
	TRACE(DEBUG_FILE_LOADING, "Converted image data.");
	
	Deallocate(table, scratch);
	TRACE(DEBUG_FILE_LOADING, "Deallocated color table.");
	
	Deallocate(data, scratch);
	TRACE(DEBUG_FILE_LOADING, "Deallocated image data.");
	
	ITexture* texture = display.CreateTexture();
	
	if (texture == NULL)
	{
		Deallocate(pixels, scratch);
		return NULL;
	}
	
	texture->SetData(pixels, info.Width, height, ITexture::Rgba8, ITexture::Point);
	
	TRACE(DEBUG_FILE_LOADING, "Texture created and initialize.");
	
	Deallocate(pixels, scratch);
	
	TRACE(DEBUG_FILE_LOADING, "Deallocated final scratch data.");
	
	TRACE(DEBUG_FILE_LOADING, "Loaded BMP file.");
	
	return texture;
}

Adventure::ITexture* Adventure::Image::LoadTgaFromFile(File& file, IDisplay& display, Allocator* scratch)
{
	file.GetStream().seekg(2, std::ios::beg);
	
	File::UInt8 type;
	file.Read(type);
	
	if (type != 2) // Type 2 indicates a regular image
		return NULL;
	
	file.GetStream().seekg(12, std::ios::beg);
	
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
	
	Color* pixelData = new(scratch) Color[pixels];
	
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
		Deallocate(pixelData, scratch);
		return NULL;
	}
	
	texture->SetData(pixelData, width, height, ITexture::Rgba8, ITexture::Point);
	
	Deallocate(pixelData, scratch);
		
	return texture;
}
