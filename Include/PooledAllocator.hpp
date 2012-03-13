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
			PooledAllocator(Allocator* base, AllocatorSizeType blockSize, AllocatorSizeType blockCount, const char* name = "anonymous");
			~PooledAllocator();
			
			void* Allocate(AllocatorSizeType request);
			void Clear(void* memory, AllocatorSizeType request);
			void Flush(void* memory, AllocatorSizeType request);
			void Deallocate(void* memory);
			
			// Marks all memory as free
			void Reset();
			
			// Gets a value indicating if the pool is valid
			inline bool IsValid() const { return pool != NULL; }
			
			// Gets the size of a block, in bytes
			inline int GetBlockSize() const { return size; }
			
			// Gets the reserved block count
			inline int GetReservedBlockCount() const { return reserved; }
			
			// Gets the maximum amount of blocks, excluding the reserved portion
			inline AllocatorSizeType GetTotalBlockCount() const { return count; }
			
			// Gets the amount of non-reserved blocks
			// Note: This does not indicate the true memory usage. In fact, it will only be correct in an empty pool!
			inline AllocatorSizeType GetAvailableBlockCount() const { return (count - reserved); }
			
			// Gets the maximum amount of memory available for use in bytes
			// Note: This does not indicate true memory usage, simply the potential; use GetMemoryUsage() for that
			inline AllocatorSizeType GetAvailableMemory() const
			{
				return GetAvailableBlockCount() * size;
			}
			
			// Gets the amount of memory, rounded to the nearest block, allocated
			// The value is in bytes
			AllocatorSizeType GetMemoryUsage() const;
			
			enum
			{
				// A flag that indicates the block of memory is allocated
				AllocatedFlag = 0x80000000,
				
				// Size indicates the amount of blocks allocated or unallocated
				// Therefore, the resulting value in bytes is (blocks[i] & SizeMask) * size
				SizeMask = 0x00FFFFFF
			};
			
			typedef unsigned int BlockInfo;
			
			static const BlockInfo NullBlockInfo = 0;
			
			static const AllocatorSizeType MinBlockSize = 32;
			
		private:
			Allocator* base;
			const char* name;
			
			void* pool;
			void* end;
			
			AllocatorSizeType reserved;
			BlockInfo* blocks;
			
			AllocatorSizeType size;
			AllocatorSizeType count;
	};
}

#endif
