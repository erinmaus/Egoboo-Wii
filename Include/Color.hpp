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

#ifndef ADVENTURE_COLOR_HPP_
#define ADVENTURE_COLOR_HPP_

namespace Adventure
{
	struct Color
	{
		public:
			typedef unsigned char Channel;
			
			Color();
			Color(Channel red, Channel green, Channel blue, Channel alpha = MaxChannelValue);
			Color(float red, float green, float blue, float alpha = 1.0f);
			explicit Color(unsigned int color);
			Color(const Color& other);
			
			static const Channel MaxChannelValue = 255;
			static const Channel MinChannelValue = 0;
			
			Channel Red;
			Channel Green;
			Channel Blue;
			Channel Alpha;
	};
}

#endif
