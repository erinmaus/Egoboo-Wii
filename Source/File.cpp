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

#include "File.hpp"

Adventure::File::File(std::iostream& stream, Endianness host, Endianness file)
	: stream(stream)
{
	this->host = host;
	this->file = file;
}

Adventure::File::~File()
{
}

Adventure::File::UInt32 Adventure::File::Swap(UInt32 value)
{
	return (value << 24) | ((value >> 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24);
}

Adventure::File::Int32 Adventure::File::Swap(Int32 value)
{
	return (value << 24) | ((value >> 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24);
}

Adventure::File::UInt16 Adventure::File::Swap(UInt16 value)
{
	return (value >> 8) | (value << 8);
}

Adventure::File::Int16 Adventure::File::Swap(Int16 value)
{
	return (value >> 8) | (value << 8);
}

bool Adventure::File::Read(UInt32& value)
{
	stream.read((char*)&value, sizeof(UInt32));
	
	if (host != file)
		Swap(value);
	
	return stream.good();
}

bool Adventure::File::Read(Int32& value)
{
	stream.read((char*)&value, sizeof(Int32));
	
	if (host != file)
		Swap(value);
	
	return stream.good();
}

bool Adventure::File::Read(UInt16& value)
{
	stream.read((char*)&value, sizeof(UInt16));
	
	if (host != file)
		Swap(value);
	
	return stream.good();
}

bool Adventure::File::Read(Int16& value)
{
	stream.read((char*)&value, sizeof(Int16));
	
	if (host != file)
		Swap(value);
	
	return stream.good();
}

bool Adventure::File::Read(UInt8& value)
{
	value = (UInt8)stream.get();
	
	return stream.good();
}

bool Adventure::File::Read(Int8& value)
{
	value = (UInt8)stream.get();
	
	return stream.good();
}

bool Adventure::File::Write(UInt32 value)
{
	if (host != file)
		Swap(value);
	
	stream.write((char*)&value, sizeof(UInt32));
	
	return stream.good();
}

bool Adventure::File::Write(Int32 value)
{
	if (host != file)
		Swap(value);
	
	stream.write((char*)&value, sizeof(Int32));
	
	return stream.good();
}

bool Adventure::File::Write(UInt16 value)
{
	if (host != file)
		Swap(value);
	
	stream.write((char*)&value, sizeof(UInt16));
	
	return stream.good();
}

bool Adventure::File::Write(Int16 value)
{
	if (host != file)
		Swap(value);
	
	stream.write((char*)&value, sizeof(Int16));
	
	return stream.good();
}

bool Adventure::File::Write(UInt8 value)
{
	stream.put(value);
	
	return stream.good(); 
}

bool Adventure::File::Write(Int8 value)
{
	stream.put(value);
	
	return stream.good();
}

bool Adventure::File::IsValid() const
{
	return stream.good();
}

std::iostream& Adventure::File::GetStream()
{
	return stream;
}

const std::iostream& Adventure::File::GetStream() const
{
	return stream;
}
