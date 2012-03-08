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

#ifndef ADVENTURE_DEBUG_HPP_
#define ADVENTURE_DEBUG_HPP_

#define DEBUG_GENERAL 0x01
#define DEBUG_ALLOCATOR 0x02
#define DEBUG_ALLOCATOR_CRITICAL 0x04
#define DEBUG_SYSTEM 0x08
#define DEBUG_RENDERING_LOW 0x10
#define DEBUG_RENDERING_HIGH 0x20
#define DEBUG_ASSERT 0x40
#define DEBUG_FILE_LOADING 0x80

#ifndef NDEBUG

#define ADVENTURE_DEBUG
#define ADVENTURE_DEBUG_OUTPUT "sd:/Adventure.txt"
#define TRACE(module, ...) _adventure_trace(module, __VA_ARGS__)
#define ASSERT(statement) _adventure_assert(#statement, __FILE__, __LINE__, statement)

void _adventure_trace(int module, const char* format, ...);
void _adventure_assert(const char* statement, const char* filename, int line, bool result);

#else
#define TRACE(module, ...)
#define ASSERT(statement)
#endif
#endif
