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

#ifndef ADVENTURE_MODEL_INTERFACE_HPP_
#define ADVENTURE_MODEL_INTERFACE_HPP_

namespace Adventure
{
	class IModelAnimator;
	
	class IModel
	{
		public:
			virtual ~IModel() { };
			
			virtual IModelAnimator* CreateAnimator() = 0;
			virtual void DestroyAnimator(IModelAnimator* animator) = 0;
	};
}

#endif
