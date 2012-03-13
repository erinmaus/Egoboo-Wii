#include <cstdio>
#include <fat.h>

#include "FileSystem.hpp"

Adventure::FileSystem::FileSystem()
{
	fatInitDefault();

#ifdef ADVENTURE_DEBUG
	{
		remove(ADVENTURE_DEBUG_OUTPUT);
	}
#endif

	TRACE(DEBUG_SYSTEM, "Initialized file system");
}