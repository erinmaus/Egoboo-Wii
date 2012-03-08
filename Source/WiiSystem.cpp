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

const std::string Adventure::WiiSystem::DefaultApplicationPath = "sd:/adventure/";

Adventure::WiiSystem::WiiSystem()
{
	applicationPath = DefaultApplicationPath;
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

bool Adventure::WiiSystem::SetApplicationPath(const std::string& path)
{
	applicationPath = path;
	
	return true;
}

const std::string& Adventure::WiiSystem::GetApplicationPath() const
{
	return applicationPath;
}

bool Adventure::WiiSystem::SetArguments(int count, const char** arguments)
{
	applicationArguments.clear();
	
	for (int i = 0; i < count; i++)
		applicationArguments.push_back(arguments[i]);
	
	// Set the application path from applicationArguments[0]
	std::string path = applicationArguments[0].substr(0, applicationArguments[0].find_last_of("/"));
	
	return SetApplicationPath(path);
}

std::string Adventure::WiiSystem::BuildPath(const std::string& path) const
{
	return applicationPath + path;
}

bool Adventure::WiiSystem::Initialize()
{
	if (!fatInitDefault())
		return false;

#ifdef ADVENTURE_DEBUG
	{
		remove(ADVENTURE_DEBUG_OUTPUT);
	}
#endif
	TRACE(DEBUG_SYSTEM, "Initialized FAT.");
	
	if (!display.Initialize())
		return false;
	TRACE(DEBUG_SYSTEM, "Initialized display.");
	
	return true;
}
