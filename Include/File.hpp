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

#ifndef ADVENTURE_FILE_HPP_
#define ADVENTURE_FILE_HPP_

#include <iostream>

namespace Adventure
{
	class File
	{
		public:
			enum Endianness
			{
				BigEndian,
				LittleEndian
			};
			
			typedef unsigned int UInt32;
			typedef int Int32;
			
			typedef unsigned short UInt16;
			typedef short Int16;
			
			typedef unsigned char UInt8;
			typedef char Int8;
			
			File(std::iostream& stream, Endianness host, Endianness file = LittleEndian);
			~File();
			
			static UInt32 Swap(UInt32 value);
			static Int32 Swap(Int32 value);
			
			static UInt16 Swap(UInt16 value);
			static Int16 Swap(Int16 value);
			
			bool Read(UInt32& value);
			bool Read(Int32& value);
			
			bool Read(UInt16& value);
			bool Read(Int16& value);
			
			bool Read(UInt8& value);
			bool Read(Int8& value);
			
			bool Write(UInt32 value);
			bool Write(Int32 value);
			
			bool Write(UInt16 value);
			bool Write(Int16 value);
			
			bool Write(UInt8 value);
			bool Write(Int8 value);
			
			bool IsValid() const;
			
			std::iostream& GetStream();
			const std::iostream& GetStream() const;
		
		private:
			std::iostream& stream;
			Endianness host, file;
	};
}

#endif
