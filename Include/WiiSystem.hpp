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

#ifndef ADVENTURE_SYSTEM_WII_HPP_
#define ADVENTURE_SYSTEM_WII_HPP_

#include "Standard.hpp"

#include "ISystem.hpp"
#include "WiiDisplay.hpp"

namespace Adventure
{
	class Allocator;
	
	class WiiSystem : public ISystem
	{
		public:
			WiiSystem();
			~WiiSystem();
			
			IDisplay& GetDisplay();
			const IDisplay& GetDisplay() const;
			
			bool SetApplicationPath(const String& path);
			const String& GetApplicationPath() const;
			
			String BuildPath(const String& path) const;
			
			bool SetArguments(int count, const char** arguments);
			
			bool Initialize();
			
			static const char* DefaultApplicationPath;
		
		private:
			String applicationPath;
			Vector<String>::Type applicationArguments;
			
			WiiDisplay display;
			Allocator* allocator;
	};
}

#endif
