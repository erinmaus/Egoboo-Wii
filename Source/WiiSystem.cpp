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

#include <fat.h>

#include "WiiSystem.hpp"

const char* Adventure::WiiSystem::DefaultApplicationPath = "sd:";

Adventure::WiiSystem::WiiSystem()
{
}

Adventure::WiiSystem::~WiiSystem()
{
}

Adventure::IDisplay& Adventure::WiiSystem::GetDisplay()
{
	return display;
}

const Adventure::IDisplay& Adventure::WiiSystem::GetDisplay() const
{
	return display;
}

bool Adventure::WiiSystem::SetApplicationPath(const String& path)
{
	applicationPath = path;
	
	return true;
}

const Adventure::String& Adventure::WiiSystem::GetApplicationPath() const
{
	return applicationPath;
}

bool Adventure::WiiSystem::SetArguments(int count, const char** arguments)
{
	applicationArguments.clear();
	
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			applicationArguments.push_back(arguments[i]);
			
			TRACE(DEBUG_SYSTEM, "Argument %d: %s", i, arguments[i]);
		}
		
		// Set the application path from applicationArguments[0]
		String path = applicationArguments[0].substr(0, applicationArguments[0].find_last_of("/"));
		
		return SetApplicationPath(path);
	}
	
	return false;
}

Adventure::String Adventure::WiiSystem::BuildPath(const String& path) const
{
	return applicationPath + path;
}

bool Adventure::WiiSystem::Initialize()
{
	if (!display.Initialize())
		return false;
	TRACE(DEBUG_SYSTEM, "Initialized display");
	
	return true;
}
