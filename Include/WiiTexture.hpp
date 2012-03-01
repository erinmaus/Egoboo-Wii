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

#ifndef ADVENTURE_WII_TEXTURE_HPP_
#define ADVENTURE_WII_TEXTURE_HPP_

#include <ogc/gx.h>

#include "ITexture.hpp"

namespace Adventure
{
	class WiiDisplay;
	
	class WiiTexture : public ITexture
	{
		public:
			WiiTexture(WiiDisplay& display);
			~WiiTexture();
			
			bool SetData(const void * data, int width, int height, Format format, Quality quality);
			
			inline int GetWidth() const { return width; };
			inline int GetHeight() const { return height; };
			inline Format GetFormat() const { return format; };
			inline Quality GetQuality() const { return quality; };
			
			bool Bind();
		
		private:
			WiiDisplay& display;
			
			GXTexObj textureObject;
			void * textureData;
			
			int width, height;
			Format format;
			Quality quality;
	};
}

#endif
