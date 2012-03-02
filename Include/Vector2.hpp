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

#ifndef ADVENTURE_Vector2_HPP_
#define ADVENTURE_Vector2_HPP_

namespace Adventure
{
	struct Vector2
	{
		public:
			Vector2();
			Vector2(float x, float y);
			Vector2(const Vector2& other);
			
			// Operations
			Vector2& operator +=(const Vector2& other);
			Vector2& operator +=(float other);
			
			Vector2& operator -=(const Vector2& other);
			Vector2& operator -=(float other);
			
			Vector2& operator *=(const Vector2& other);
			Vector2& operator *=(float other);
			
			Vector2& operator /=(const Vector2& other);
			Vector2& operator /=(float other);
			
			// Length
			float CalculateLengthSquared() const;
			float CalculateLength() const;
			
			// Normalization
			static Vector2 Normalize(const Vector2& vector);
			
			// Products
			static float Dot(const Vector2& a, const Vector2& b);
			
			// Utilities
			static float Distance(const Vector2& from, const Vector2& to);
		
			// Components of the vector
			float X;
			float Y;
	};
	
	Vector2 operator +(const Vector2& left, const Vector2& right);
	Vector2 operator +(const Vector2& left, float right);
	
	Vector2 operator -(const Vector2& left, const Vector2& right);
	Vector2 operator -(const Vector2& left, float right);
	
	Vector2 operator *(const Vector2& left, const Vector2& right);
	Vector2 operator *(const Vector2& left, float right);
	
	Vector2 operator /(const Vector2& left, const Vector2& right);
	Vector2 operator /(const Vector2& left, float right);
}

#endif
