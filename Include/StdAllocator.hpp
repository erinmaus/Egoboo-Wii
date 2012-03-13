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

#ifndef ADVENTURE_STD_ALLOCATOR_HPP_
#define ADVENTURE_STD_ALLOCATOR_HPP_

#include <cstddef>
#include <memory>
#include <new>

#include "PooledAllocator.hpp"

namespace Adventure
{
	class StdAllocatorBase
	{
		public:
			static void SetBase(PooledAllocator* allocator)
			{
				ASSERT(allocator);
				ASSERT(!base);
				base = allocator;
			}
			
			static PooledAllocator* GetBase()
			{
				return base;
			}
		
		private:
			static PooledAllocator* base;
	};
	
	template<typename T>
	class StdAllocator
	{
		public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T* const_pointer;
			typedef const T& const_reference;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			
			template<class U>
			struct rebind
			{
				typedef StdAllocator<U> other;
			};
			
			StdAllocator() throw()
			{
			}
			
			StdAllocator(const StdAllocator<T>& other) throw()
			{
			}
			
			template<typename U>
			StdAllocator(const StdAllocator<U>& other) throw()
			{
			}
			
			pointer address(reference x) const
			{
				return &x;
			}
			
			const_pointer address(const_reference x) const
			{
				return &x;
			}
			
			pointer allocate(size_type n, const void* hint = 0)
			{
				pointer data = (pointer)StdAllocatorBase::GetBase()->Allocate(n * sizeof(value_type));
				
				if (data == NULL)
					throw std::bad_alloc();
				
				return data;
			}
			
			void deallocate(pointer p, size_type n)
			{
				StdAllocatorBase::GetBase()->Deallocate(p);
			}
			
			size_type max_size() const throw()
			{
				return StdAllocatorBase::GetBase()->GetAvailableMemory();
			}
			
			void construct(pointer p, const_reference val)
			{
				new ((void*)p) T(val);
			}
			
			void destroy(pointer p)
			{
				((T*)p)->~T();
			}
	};
	
	template<typename T, typename U>
	bool operator ==(const StdAllocator<T>& left, const StdAllocator<U>& right)
	{
		return true;
	}
	
	template<typename T, typename U>
	bool operator !=(const StdAllocator<T>& left, const StdAllocator<U>& right)
	{
		return false;
	}
}

#endif
