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

#ifndef ADVENTURE_VECTOR3_HPP_
#define ADVENTURE_VECTOR3_HPP_

namespace Adventure
{
	struct Matrix;
	
	struct Vector3
	{
		public:
			Vector3();
			Vector3(float x, float y, float z);
			Vector3(const Vector3& other);
			
			// Operations
			Vector3& operator +=(const Vector3& other);
			Vector3& operator +=(float other);
			
			Vector3& operator -=(const Vector3& other);
			Vector3& operator -=(float other);
			
			Vector3& operator *=(const Vector3& other);
			Vector3& operator *=(float other);
			
			Vector3& operator /=(const Vector3& other);
			Vector3& operator /=(float other);
			
			Vector3 operator -() const;
			
			// Length
			float CalculateLengthSquared() const;
			float CalculateLength() const;
			
			// Normalization
			static Vector3 Normalize(const Vector3& vector);
			
			// Products
			static Vector3 Cross(const Vector3& left, const Vector3& right);
			static float Dot(const Vector3& a, const Vector3& b);
			
			// Utilities
			static float Distance(const Vector3& from, const Vector3& to);
			
			// Transformation
			static Vector3 Transform(const Vector3& vector, const Matrix& matrix);
		
			// Components of the vector
			float X;
			float Y;
			float Z;
	};
	
	Vector3 operator +(const Vector3& left, const Vector3& right);
	Vector3 operator +(const Vector3& left, float right);
	
	Vector3 operator -(const Vector3& left, const Vector3& right);
	Vector3 operator -(const Vector3& left, float right);
	
	Vector3 operator *(const Vector3& left, const Vector3& right);
	Vector3 operator *(const Vector3& left, float right);
	
	Vector3 operator /(const Vector3& left, const Vector3& right);
	Vector3 operator /(const Vector3& left, float right);
}

#endif
