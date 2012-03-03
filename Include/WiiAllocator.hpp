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

#ifndef ADVENTURE_WII_ALLOCATOR_HPP_
#define ADVENTURE_WII_ALLOCATOR_HPP_

#include <cstdlib>
#include <cstring>
#include <malloc.h>
#include <ogc/cache.h>

#include "Allocator.hpp"

namespace Adventure
{
	class WiiAllocator : public Allocator
	{
		public:
			static AllocatorSizeType RoundSize(AllocatorSizeType value, AllocatorSizeType round = 32)
			{
				return (value + (round - 1)) & ~(round - 1);
			}
			
			void* Allocate(AllocatorSizeType size)
			{
				return memalign(32, RoundSize(size));
			}
			
			void Clear(void* memory, AllocatorSizeType size)
			{
				if (memory)
					memset(memory, 0, RoundSize(size));
			}
			
			void Flush(void* memory, AllocatorSizeType size)
			{
				if (memory)
					DCFlushRange(memory, RoundSize(size));
			}
			
			void Deallocate(void* memory)
			{
				free(memory);
			}
	};
}

#endif
