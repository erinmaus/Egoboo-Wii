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

#ifndef ADVENTURE_STANDARD_HPP_
#define ADVENTURE_STANDARD_HPP_

#include <map>
#include <string>
#include <vector>

#include "StdAllocator.hpp"

namespace Adventure
{
	template <typename T>
	struct Vector
	{
		typedef std::vector<T, StdAllocator<T> > Type;
	};
	
	template <typename Key, typename T>
	struct Map
	{
		typedef std::map<Key, T, std::less<Key>, StdAllocator<T> > Type;
	};
	
	typedef std::basic_string<char, std::char_traits<char>, StdAllocator<char> > String;
}

#endif
