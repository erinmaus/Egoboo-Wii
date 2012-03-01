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

#ifndef ADVENTURE_SYSTEM_INTERFACE_HPP_
#define ADVENTURE_SYSTEM_INTERFACE_HPP_

#include <string>

namespace Adventure
{
	class IDisplay;
	
	class ISystem
	{
		public:
			virtual ~ISystem() = 0;
			
			virtual IDisplay& GetDisplay() = 0;
			virtual const IDisplay& GetDisplay() const = 0;
			
			virtual bool SetApplicationPath(const std::string& path) = 0;
			virtual const std::string& GetApplicationPath() const = 0;
			
			virtual bool Initialize() = 0;
	};
}

#endif
