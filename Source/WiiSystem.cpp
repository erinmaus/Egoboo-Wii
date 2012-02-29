#include "WiiSystem.hpp"

Adventure::WiiSystem::DefaultApplicationPath = "sd://adventure/";

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
}

const std::string& Adventure::WiiSystem::GetApplicationPath() const
{
	return applicationPath;
}

bool Adventure::WiiSystem::Initialize()
{
	if (!display.Initialize())
		return false;
}
