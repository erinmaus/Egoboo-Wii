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

#include <cassert>
#include <cstdlib>

#include "PooledAllocator.hpp"

Adventure::PooledAllocator::PooledAllocator(Allocator* base, AllocatorSizeType blockSize, AllocatorSizeType blockCount, const char* name)
	: base(base), name(name)
{
	ASSERT(blockSize >= MinBlockSize);
	
	size = blockSize;
	count = blockCount;
	
	void* memory = base->Allocate(blockSize * blockCount);
	
	if (memory)
	{
		blocks = (BlockInfo*)memory;
		reserved = (count / sizeof(BlockInfo)) / (size / MinBlockSize);
		
		// Always reserved one block
		// A value of zero only occurs when the reserved count is less than
		// one block in size
		if (reserved == 0)
			reserved = 1;
		
		ASSERT(reserved < blockCount);
		
		TRACE(DEBUG_ALLOCATOR_CRITICAL, "Reserved %d blocks for %d block entries in %s pool", reserved, count / size, name);
		
		Reset();
		
		pool = (char*)memory + reserved * size;
		end = (char*)memory + count * size;
	}
}

Adventure::PooledAllocator::~PooledAllocator()
{
	base->Deallocate(blocks);
}

void* Adventure::PooledAllocator::Allocate(AllocatorSizeType request)
{
	unsigned int blockIndex = 0;
	AllocatorSizeType blockCount;
	bool blockFree = false;
	
	TRACE(DEBUG_ALLOCATOR_CRITICAL, "Request to allocate %ld bytes from %s pool...", request, name);
	
	// Find the first available free block in the block info array
	while (blockIndex < GetAvailableBlockCount())
	{
		BlockInfo info = blocks[blockIndex];
		blockCount = info & SizeMask;
		blockFree = !(info & AllocatedFlag);
		
		if (blockFree && blockCount * size >= request)
		{
			TRACE(DEBUG_ALLOCATOR, "Found block at %d index with %d bytes free", blockIndex, blockCount * size);
			break;
		}
#ifdef ADVENTURE_DEBUG
		else
		{
				TRACE(DEBUG_ALLOCATOR, "Block index %d [0x%lx]: %s [%d bytes]",
					blockIndex,
					info,
					blockFree ? "insufficient size" : "already allocated",
					blockCount * size);
				
				ASSERT(blockCount > 0);
		}
#endif
		
		blockIndex += blockCount;
		blockFree = false;
	}
	
	// All memory is allocated and therefore the block request cannot be fulfilled
	if (!blockFree || blockCount * size < request)
	{
		TRACE(DEBUG_ALLOCATOR_CRITICAL, "No available blocks found");
		
		return NULL;
	}
	
	unsigned int blocksRequested = ((request + (size - 1)) & ~(size - 1)) / size;
	
	// This can happen when a requested size in bytes is less than the block size in bytes
	if (blocksRequested == 0)
	{
		TRACE(DEBUG_ALLOCATOR, "Block requested adjusted to 1");
		blocksRequested = 1;
	}
		
	// A block request cannot be over SizeMask in size, else the size
	// stored in the block info would be invalid
	if (blocksRequested > SizeMask)
	{
		TRACE(DEBUG_ALLOCATOR_CRITICAL, "Requested too much memory (%d bytes)", request);
		
		return NULL;
	}
	
	// Set the memory as allocated
	blocks[blockIndex] = (blocksRequested & SizeMask) | AllocatedFlag;
	
	// Mark the first free block after this block request as unallocated
	// An unallocated block has the AllocatedFlag unset and has a valid
	// SizeMask
	unsigned int nextBlockIndex = blockIndex + blocksRequested;
	
	TRACE(DEBUG_ALLOCATOR, "Next block index: %d", nextBlockIndex);
	
	// As long as the next block is within bounds, set it
	if (nextBlockIndex < GetAvailableBlockCount() && nextBlockIndex != 0)
	{
		blocks[nextBlockIndex] = blockCount - blocksRequested;
		TRACE(DEBUG_ALLOCATOR, "Next block data: 0x%lx", blocks[nextBlockIndex]);
	}
	
	TRACE(DEBUG_ALLOCATOR_CRITICAL, "Allocated %p (%ld bytes) at block index %d [0x%lx]", (char*)pool + blockIndex * size, blocksRequested * size, blockIndex, blocks[blockIndex]);
	
	// Return the block of memory
	return (char*)pool + blockIndex * size;
}

void Adventure::PooledAllocator::Clear(void* memory, AllocatorSizeType request)
{
	// No further testing is done in this method because the memory pointer
	// can be offset from the original pointer allocated
	ASSERT(memory >= pool && memory < end);
	
	base->Clear(memory, request);
	
	TRACE(DEBUG_ALLOCATOR, "Flushed memory %p", memory);
}

void Adventure::PooledAllocator::Flush(void* memory, AllocatorSizeType request)
{
	// See Clear why no further testing is performed
	ASSERT(memory >= pool && memory < end);
	
	base->Flush(memory, request);
	
	TRACE(DEBUG_ALLOCATOR, "Cleared memory %p", memory);
}

void Adventure::PooledAllocator::Deallocate(void* memory)
{
	ASSERT(memory >= pool && memory < end);
	
	// Find the memory allocation info and mark as unallocated
	unsigned int currentBlockIndex = (int)((char*)memory - (char*)pool) / size;
	
	TRACE(DEBUG_ALLOCATOR, "Deallocating block starting at %p (block %d) from %s pool...", memory, currentBlockIndex, name);
	
	blocks[currentBlockIndex] &= ~AllocatedFlag;
	
	// Merge with the previous block info, if necessary
	if (currentBlockIndex != 0)
	{
		unsigned int previousBlockIndex = currentBlockIndex;
		
		// Since the implementation only keeps track of the distance between
		// the current block and the next, manually go backwards and find
		// the previous block
		while (blocks[previousBlockIndex] == NullBlockInfo && previousBlockIndex > 0)
			previousBlockIndex--;
			
		ASSERT(previousBlockIndex <= currentBlockIndex);
			
		if (previousBlockIndex != currentBlockIndex && !(blocks[previousBlockIndex] & AllocatedFlag))
		{
			TRACE(DEBUG_ALLOCATOR, "Merged previous block %d [0x%lx]", previousBlockIndex, blocks[previousBlockIndex]);
			
			blocks[previousBlockIndex] = blocks[currentBlockIndex] + blocks[previousBlockIndex];
			blocks[currentBlockIndex] = NullBlockInfo;
			
			// Set the current index to the previous, since the current one is now invalid
			currentBlockIndex = previousBlockIndex;
		}
	}
	
	// Merge with the next block info, if necessary
	unsigned int nextBlockIndex = currentBlockIndex + (blocks[currentBlockIndex] & SizeMask);
	
	if (nextBlockIndex < count && !(blocks[nextBlockIndex] & AllocatedFlag))
	{
		TRACE(DEBUG_ALLOCATOR, "Merged next block %d [0x%lx]", nextBlockIndex, blocks[nextBlockIndex]);
		
		blocks[currentBlockIndex] = (blocks[nextBlockIndex] & SizeMask) + (blocks[currentBlockIndex] & SizeMask) + 1;
		blocks[nextBlockIndex] = NullBlockInfo;
	}
#ifdef ADVENTURE_DEBUG
	else
	{
		TRACE(DEBUG_ALLOCATOR, "Did not merge with next block %d [0x%lx]", nextBlockIndex, blocks[nextBlockIndex]);
	}
#endif
	TRACE(DEBUG_ALLOCATOR, "Final block position %d with info 0x%lx", currentBlockIndex, blocks[currentBlockIndex]);
	TRACE(DEBUG_ALLOCATOR, "Deallocated %p", memory);
}

void Adventure::PooledAllocator::Reset()
{
	base->Clear(blocks, GetAvailableBlockCount() * size);
	blocks[0] = count;
}

Adventure::AllocatorSizeType Adventure::PooledAllocator::GetMemoryUsage() const
{
	unsigned int blockIndex = 0;
	AllocatorSizeType allocated = 0;
	
	while (blockIndex < GetAvailableBlockCount())
	{
		BlockInfo info = blocks[blockIndex];
		AllocatorSizeType blockCount = info & SizeMask;
		bool blockFree = info & AllocatedFlag;
		
		if (blockFree)
			allocated += blockCount;
		
		TRACE(DEBUG_ALLOCATOR_CRITICAL, "Block info at index %lu: 0x%lx", blockIndex, info);
		
		ASSERT(blockCount > 0);
		
		blockIndex += blockCount;
	}
	
	return allocated * size;
}
