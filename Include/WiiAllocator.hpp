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
#include <malloc.h>
#include <ogc/cache.h>

#include "Allocator.hpp"

namespace Adventure
{
	template <typename TType>
	class WiiAllocator : Allocator<TType>
	{
		public:
			typedef TType AllocatorDataType;
			
			AllocatorSizeType RoundSize(AllocatorSizeType value, AllocatorSizeType round)
			{
				return (value + (round - 1)) & ~(round - 1);
			}
			
			AllocatorDataType* Allocate(AllocatorSizeType count)
			{
				return memalign(32, RoundSize(count * sizeof(AllocatorDataType)));
			}
			
			void Clear(AllocatorDataType* memory, AllocatorSizeType count)
			{
				if (memory)
					memset(memory, 0, RoundSize(count * sizeof(AllocatorDataType)));
			}
			
			void Flush(AllocatorDataType* memory, AllocatorSizeType count)
			{
				if (memory)
					DCFlushRange(memory, RoundSize(count * sizeof(AllocatorDataType)));
			}
			
			void Deallocate(AllocatorDataType* memory)
			{
				free(memory);
			}
	};
}

#endif
