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

#ifndef ADVENTURE_EFFECT_INTERFACE_HPP_
#define ADVENTURE_EFFECT_INTERFACE_HPP_

#include "Color.hpp"
#include "Vector3.hpp"

namespace Adventure
{
	class IEffect
	{
		public:
			virtual ~IEffect() { }
			
			// Applies an effect, such as lighting or enchantment
			// This method returns a color for a vertex
			virtual Color Apply(const Vector3& vertexPosition, const Vector3& vertexNormal) = 0;
	};
}

#endif
