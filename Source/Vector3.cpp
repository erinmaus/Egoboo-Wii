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

#include <cmath>

#include "Matrix.hpp"
#include "Vector3.hpp"

Adventure::Vector3::Vector3()
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

Adventure::Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Adventure::Vector3::Vector3(const Vector3& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
}

Adventure::Vector3& Adventure::Vector3::operator +=(const Vector3& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator +=(float other)
{
	X += other;
	Y += other;
	Z += other;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator -=(const Vector3& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator -=(float other)
{
	X -= other;
	Y -= other;
	Z -= other;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator *=(const Vector3& other)
{
	X *= other.X;
	Y *= other.Y;
	Z *= other.Z;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator *=(float other)
{
	X *= other;
	Y *= other;
	Z *= other;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator /=(const Vector3& other)
{
	X /= other.X;
	Y /= other.Y;
	Z /= other.Z;
	
	return *this;
}

Adventure::Vector3& Adventure::Vector3::operator /=(float other)
{
	X /= other;
	Y /= other;
	Z /= other;
	
	return *this;
}

Adventure::Vector3 Adventure::Vector3::operator -() const
{
	return Vector3(-X, -Y, -Z);
}

float Adventure::Vector3::CalculateLengthSquared() const
{
	return X * X + Y * Y + Z * Z;
}

float Adventure::Vector3::CalculateLength() const
{
	return sqrtf(CalculateLengthSquared());
}
	
Adventure::Vector3 Adventure::Vector3::Normalize(const Vector3& vector)
{
	return vector * (1.0f / vector.CalculateLength());
}

Adventure::Vector3 Adventure::Vector3::Cross(const Vector3& left, const Vector3& right)
{
	return Vector3(left.Y * right.Z - left.Z * right.Y, left.Z * right.X - left.X * right.Z, left.X * right.Y - left.Y * right.X);
}

float Adventure::Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

float Adventure::Vector3::Distance(const Vector3& from, const Vector3& to)
{
	return (from - to).CalculateLength();
}

Adventure::Vector3 Adventure::Vector3::Transform(const Vector3& vector, const Matrix& matrix)
{
	return Vector3
	(
		vector.X * matrix.Get(0, 0) + vector.Y * matrix.Get(0, 1) + vector.Z * matrix.Get(0, 2) + matrix.Get(0, 3),
		vector.X * matrix.Get(1, 0) + vector.Y * matrix.Get(1, 1) + vector.Z * matrix.Get(1, 2) + matrix.Get(1, 3),
		vector.X * matrix.Get(2, 0) + vector.Y * matrix.Get(2, 1) + vector.Z * matrix.Get(2, 2) + matrix.Get(2, 3)
	);
}

Adventure::Vector3 Adventure::operator +(const Vector3& left, const Vector3& right)
{
	return Vector3(left) += right;
}

Adventure::Vector3 Adventure::operator +(const Vector3& left, float right)
{
	return Vector3(left) += right;
}

Adventure::Vector3 Adventure::operator -(const Vector3& left, const Vector3& right)
{
	return Vector3(left) -= right;
}

Adventure::Vector3 Adventure::operator -(const Vector3& left, float right)
{
	return Vector3(left) -= right;
}

Adventure::Vector3 Adventure::operator *(const Vector3& left, const Vector3& right)
{
	return Vector3(left) *= right;
}

Adventure::Vector3 Adventure::operator *(const Vector3& left, float right)
{
	return Vector3(left) *= right;
}
