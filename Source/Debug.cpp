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

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#define DEBUG_LEVEL (DEBUG_GENERAL | DEBUG_ALLOCATOR | DEBUG_SYSTEM | DEBUG_RENDERING_LOW | DEBUG_RENDERING_HIGH | DEBUG_ASSERT | DEBUG_FILE_LOADING)

void _adventure_trace(int module, const char* format, ...)
{
	FILE * log = fopen(ADVENTURE_DEBUG_OUTPUT, "a");
	
	if (log && DEBUG_LEVEL & module)
	{
		va_list arguments;
		va_start(arguments, format);
		
		vfprintf(log, format, arguments);
		fprintf(log, "\n");
		fflush(log);
		
		va_end(arguments);
		
		fclose(log);
	}
}

void _adventure_assert(const char* statement, const char* filename, int line, bool result)
{
	if (!result)
	{
		_adventure_trace(DEBUG_ASSERT, "Assertion failed %s:%d: %s", filename, line, statement);
		abort();
	}
}
