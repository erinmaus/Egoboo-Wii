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

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <network.h>

#ifdef ADVENTURE_DEBUG

#define DEBUG_LEVEL (DEBUG_GENERAL | DEBUG_ALLOCATOR | DEBUG_ALLOCATOR_CRITICAL | DEBUG_SYSTEM | DEBUG_RENDERING_LOW | DEBUG_RENDERING_HIGH | DEBUG_ASSERT | DEBUG_FILE_LOADING)
//#define DEBUG_LEVEL (DEBUG_GENERAL | DEBUG_ASSERT)

FILE* _adventure_log = NULL;

void _adventure_close_log()
{
	if (_adventure_log != NULL)
		fclose(_adventure_log);
}

void _adventure_trace(int module, const char* format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	
	if (DEBUG_LEVEL & module)
	{
		if (_adventure_log == NULL)
		{
			_adventure_log = fopen(ADVENTURE_DEBUG_OUTPUT, "w");
			
			if (_adventure_log == NULL)
				abort();
			else
			{
				atexit(&_adventure_close_log);
			}
		}
		
		vfprintf(_adventure_log, format, arguments);
		fprintf(_adventure_log, "\n");
		fflush(_adventure_log);
	}
	
	va_end(arguments);
}

void _adventure_assert(const char* statement, const char* filename, int line, bool result)
{
	if (!result)
	{
		_adventure_trace(DEBUG_ASSERT, "Assertion failed %s:%d: %s", filename, line, statement);
		exit(1);
	}
}

#endif
