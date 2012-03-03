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

#ifndef ADVENTURE_TEXTURE_INTERFACE_HPP_
#define ADVENTURE_TEXTURE_INTERFACE_HPP_

namespace Adventure
{
	class ITexture
	{
		public:
			virtual ~ITexture() = 0;
			
			enum Format
			{
				// The data is expected to be in a RGBA format
				Rgba8
			};
			
			enum Quality
			{
				// Point quality
				Point,
				
				// Linear quality
				Linear
			};
			
			// Sets the texture data.
			// The data should be freed after this call, generally.
			virtual bool SetData(const void * data, int width, int height, Format format = Rgba8, Quality quality = Point) = 0;
			
			// Binds the texture
			virtual bool Bind() = 0;
			
			// Getters for certain values
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;
			virtual Format GetFormat() const = 0;
			virtual Quality GetQuality() const = 0;
	};
}

#endif
