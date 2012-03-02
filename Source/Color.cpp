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

#include "Color.hpp"

Adventure::Color::Color()
{
	Red = MinChannelValue;
	Green = MinChannelValue;
	Blue = MinChannelValue;
	Alpha = MaxChannelValue;
}

Adventure::Color::Color(Channel red, Channel green, Channel blue, Channel alpha)
{
	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;
}

Adventure::Color::Color(float red, float green, float blue, float alpha)
{
	Red = red * MaxChannelValue;
	Green = green * MaxChannelValue;
	Blue = blue * MaxChannelValue;
	Alpha = alpha * MaxChannelValue;
}

Adventure::Color::Color(unsigned int color)
{
	Red = (color >> 24) & 0xFF;
	Green = (color >> 18) & 0xFF;
	Blue = (color >> 12) & 0xFF;
	Alpha = color & 0xFF;
}

Adventure::Color::Color(const Color& other)
{
	Red = other.Red;
	Green = other.Green;
	Blue = other.Blue;
	Alpha = other.Alpha;
}
