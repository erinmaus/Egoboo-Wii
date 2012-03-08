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

#ifndef ADVENTURE_POOLED_ALLOCATOR_HPP_
#define ADVENTURE_POOLED_ALLOCATOR_HPP_

#include <cstdlib>

#include "Allocator.hpp"

namespace Adventure
{
	class PooledAllocator : public Allocator
	{
		public:
			// Block count and block size should be multiples of two
			// Note: this method reserves some blocks for internal use
			PooledAllocator(Allocator* base, AllocatorSizeType blockSize, int blockCount);
			~PooledAllocator();
			
			void* Allocate(AllocatorSizeType request);
			void Clear(void* memory, AllocatorSizeType request);
			void Flush(void* memory, AllocatorSizeType request);
			void Deallocate(void* memory);
			
			// Marks all memory as free
			void Reset();
			
			inline bool IsValid() const { return pool != NULL; }
			
			inline int GetBlockSize() const { return size; }
			
			// Gets the reserved block count
			inline int GetReservedBlockCount() const { return reserved; }
			
			// Maximum capacity, including reserved blocks, in blocks
			inline AllocatorSizeType GetCapacity() const { return count; }
			
			// Maximum capacity, excluding reserved blocks, in blocks
			inline AllocatorSizeType GetSize() const { return (count - reserved); }
			
			// Gets the amount of memory, rounded to the nearest block, allocated
			// The value is in bytes
			AllocatorSizeType GetMemoryUsage() const;
			
			enum
			{
				// A flag that indicates the block of memory is allocated
				AllocatedFlag = 0x80000000,
				
				// Size indicates the amount of blocks allocated or unallocated
				// Therefore, the resulting value is (blocks[i] & SizeMask) * size
				SizeMask = 0x0000FFFF
			};
			
			typedef int BlockInfo;
			
			static const BlockInfo NullBlockInfo = 0;
			
		private:
			Allocator* base;
			
			void* pool;
			void* end;
			
			int reserved;
			BlockInfo* blocks;
			
			AllocatorSizeType size;
			int count;
	};
}

#endif
