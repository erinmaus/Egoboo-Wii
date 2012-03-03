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

#ifndef ADVENTURE_ALLOCATOR_HPP_
#define ADVENTURE_ALLOCATOR_HPP_

namespace Adventure
{
	typedef unsigned long AllocatorSizeType;
	
	class Allocator
	{
		public:
			virtual ~Allocator() { }
			
			// Allocates memory
			virtual void* Allocate(AllocatorSizeType size) = 0;
			
			// Clears a range of memory
			// Note: a value of NULL should result in a NOP
			virtual void Clear(void* memory, AllocatorSizeType size) = 0;
			
			// Flushes a range of memory
			// Note: a value of NULL should result in a NOP
			virtual void Flush(void* memory, AllocatorSizeType size) = 0;
			
			// Deallocates memory
			// Note: a value of NULL should result in a NOP
			virtual void Deallocate(void* memory) = 0;
	};
}

#endif
