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

#ifndef ADVENTURE_ELEMENT_ARRAY_HPP_
#define ADVENTURE_ELEMENT_ARRAY_HPP_

#include <cassert>

#include "Allocator.hpp"
#include "Color.hpp"

namespace Adventure
{
	// Compressed vertex/UV and normal types
	typedef short int CompressedElement;
	typedef short int CompressedNormalElement;
	
	typedef int ElementShiftType;
	
	template <typename TBaseType, typename TConversionType, ElementShiftType TShift>
	struct ElementConverter
	{
		public:
			typedef TBaseType BaseType;
			typedef TConversionType ConversionType;
			
			static const ElementShiftType ConversionFactor = 1 << TShift;
			
			inline ConversionType Convert(const BaseType& baseValue) const
			{
				return (ConversionType)(baseValue * ConversionFactor);
			}
	};
	
	template <>
	struct ElementConverter <Color, Color, 0>
	{
		public:
			typedef Color BaseType;
			typedef Color ConversionType;
			
			static const ElementShiftType ConverisonFactor = 1;
			
			inline Color Convert(const Color& other) const
			{
				return other;
			}
	};
	
	typedef ElementConverter<float, float, 0> NullElementConverter;
	typedef ElementConverter<float, CompressedElement, 7> CompressedElementConverter;
	typedef ElementConverter<float, CompressedNormalElement, 14> CompressedNormalElementConverter;
	typedef ElementConverter<Color, Color, 0> ColorElementConverter;
	
	typedef ElementConverter<int, unsigned short, 0> NullLargeIndexConverter;
	typedef ElementConverter<int, unsigned char, 0> NullSmallIndexConverter;
	
	typedef unsigned short ElementArrayCount;
	typedef unsigned long int ElementArrayLength;
	
	template <typename TConverter, int TElementMembers>
	class ElementArray
	{
		public:
			typedef TConverter ConverterType;
			typedef typename ConverterType::BaseType BaseType;
			typedef typename ConverterType::ConversionType ElementType;
			typedef Allocator<ElementType> AllocatorType;
			
			// The amount of members in an element
			// This number must be between 1 and 4, inclusive
			// Otherwise there is a high chance for fatal data corruption
			static const int ElementMembers = TElementMembers;
			
			// The stride between elements
			static const unsigned char ElementStride = sizeof(ElementType) * ElementMembers;
			
			ElementArray(ElementArrayCount count, AllocatorType& allocator)
				: allocator(allocator)
			{
				assert(ElementMembers >= 1 && ElementMembers <= 4);
				
				elementCount = count;
				
				elements = allocator.Allocate(elementCount, count * ElementMembers);
			}
			
			~ElementArray()
			{
				allocator.Deallocate(elements);
			}
			
			// Gets a pointer to the underlying array
			const ElementType* GetElements() const { return elements; }
			
			// Gets the total element count
			ElementArrayCount GetElementCount() const { return elementCount; }
			
			// Locks the element array
			// Note: Any stored data is lost
			bool Lock()
			{
				assert(IsValid());
				assert(!IsLocked());
				
				allocator.Clear(elements, elementCount * ElementMembers);
			}
			
			// Unlocks the element array
			bool Unlock()
			{
				assert(IsValid());
				assert(IsLocked());
				
				allocator.Flush(elements, elementCount * ElementMembers);
			}
			
			inline bool IsValid() const { return elements != NULL; }
			inline bool IsLocked() const { return isLocked; }
			
			// Buffers data
			// The function called should match the ElementMembers constant
			bool Buffer(const BaseType& x)
			{
				assert(ElementMembers == 1);
				assert(IsValid());
				assert(IsLocked());
				
				elements[lockedOffset++] = converter.Convert(x);
			}
			
			bool Buffer(const BaseType& x, const BaseType& y)
			{
				assert(ElementMembers == 2);
				assert(IsValid());
				assert(IsLocked());
				
				elements[lockedOffset++] = converter.Convert(x);
				elements[lockedOffset++] = converter.Convert(y);
			}
			
			bool Buffer(const BaseType& x, const BaseType& y, const BaseType& z)
			{
				assert(ElementMembers == 3);
				assert(IsValid());
				assert(IsLocked());
				
				elements[lockedOffset++] = converter.Convert(x);
				elements[lockedOffset++] = converter.Convert(y);
				elements[lockedOffset++] = converter.Convert(z);
			}
			
			bool Buffer(const BaseType& x, const BaseType& y, const BaseType& z, const BaseType& w)
			{
				assert(ElementMembers == 4);
				assert(IsValid());
				assert(IsLocked());
				
				elements[lockedOffset++] = converter.Convert(x);
				elements[lockedOffset++] = converter.Convert(y);
				elements[lockedOffset++] = converter.Convert(z);
				elements[lockedOffset++] = converter.Convert(w);
			}
			
		private:
			ElementArray(const ElementArray<ConverterType, ElementMembers>& other) { }
			
			AllocatorType& allocator;
			ConverterType converter;
			
			bool isLocked;
			int lockedOffset;
			
			ElementType* elements;
			ElementArrayCount elementCount;
	};
	
	typedef ElementArray<NullElementConverter, 3> Vector3Array;
	typedef ElementArray<CompressedElementConverter, 3> CompressedVector3Array;
	
	typedef ElementArray<NullElementConverter, 2> Vector2Array;
	typedef ElementArray<CompressedElementConverter, 2> CompressedVector2Array;
	
	typedef ElementArray<NullElementConverter, 3> NormalArray;
	typedef ElementArray<CompressedNormalElementConverter, 3> CompressedNormalArray;
	
	typedef ElementArray<ColorElementConverter, 1> ColorArray;
	
	// An index array for a model
	// Composed of position, normal, material, and UV indices (4)
	typedef ElementArray<NullLargeIndexConverter, 4> ModelIndexArray;
	
	// An index for a particle or billboard sprite
	// Composed of position, color, and UV indices
	// Large indices are used for a large particle cloud
	typedef ElementArray<NullLargeIndexConverter, 3> ParticleIndexArray;
	
	// An index for a sprite
	// Composed of position, color, and UV indices
	// Generally only one quad is drawn per sprite; hence small indices
	typedef ElementArray<NullSmallIndexConverter, 3> SpriteIndexArray;
};

#endif
