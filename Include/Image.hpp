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

#ifndef ADVENTURE_IMAGE_HPP_
#define ADVENTURE_IMAGE_HPP_

#include <string>

namespace Adventure
{
	class Allocator;
	class File;
	class ITexture;
	class IDisplay;
	
	namespace Image
	{
		enum ImageIdentifier
		{
			Bmp,
			Tga,
			Png,
			Unknown
		};
		
		// Attempts to determine the identifier from extension
		ImageIdentifier IdentifierFromExtension(const std::string& extension);
		
		// Loads an image of the provided type from a file
		ITexture* LoadFromFile(File& file, ImageIdentifier identifier, IDisplay& display, Allocator* scratch);
		
		// Loads a TGA from a file
		ITexture* LoadTgaFromFile(File& file, IDisplay& display, Allocator* scratch);
		
		// Loads a BMP from a file
		ITexture* LoadBmpFromFile(File& file, IDisplay& display, Allocator* scratch);
	}
}

#endif
