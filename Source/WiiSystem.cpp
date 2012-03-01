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

#include "WiiSystem.hpp"

const std::string Adventure::WiiSystem::DefaultApplicationPath = "sd://adventure/";

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

bool Adventure::WiiSystem::Initialize()
{
	if (!display.Initialize())
		return false;
	
	return true;
}
