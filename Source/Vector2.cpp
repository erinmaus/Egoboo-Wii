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
#include "Vector2.hpp"

Adventure::Vector2::Vector2()
{
	X = 0.0f;
	Y = 0.0f;
}

Adventure::Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Adventure::Vector2::Vector2(const Vector2& other)
{
	X = other.X;
	Y = other.Y;
}

Adventure::Vector2& Adventure::Vector2::operator +=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator +=(float other)
{
	X += other;
	Y += other;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator -=(const Vector2& other)
{
	X -= other.X;
	Y -= other.Y;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator -=(float other)
{
	X -= other;
	Y -= other;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator *=(const Vector2& other)
{
	X *= other.X;
	Y *= other.Y;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator *=(float other)
{
	X *= other;
	Y *= other;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator /=(const Vector2& other)
{
	X /= other.X;
	Y /= other.Y;
	
	return *this;
}

Adventure::Vector2& Adventure::Vector2::operator /=(float other)
{
	X /= other;
	Y /= other;
	
	return *this;
}

float Adventure::Vector2::CalculateLengthSquared() const
{
	return X * X + Y * Y;
}

float Adventure::Vector2::CalculateLength() const
{
	return sqrtf(CalculateLengthSquared());
}
	
Adventure::Vector2 Adventure::Vector2::Normalize(const Vector2& vector)
{
	return vector * (1.0f / vector.CalculateLength());
}

float Adventure::Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.X * b.X + a.Y * b.Y;
}

float Adventure::Vector2::Distance(const Vector2& from, const Vector2& to)
{
	return (from - to).CalculateLength();
}

Adventure::Vector2 Adventure::operator +(const Vector2& left, const Vector2& right)
{
	return Vector2(left) += right;
}

Adventure::Vector2 Adventure::operator +(const Vector2& left, float right)
{
	return Vector2(left) += right;
}

Adventure::Vector2 Adventure::operator -(const Vector2& left, const Vector2& right)
{
	return Vector2(left) -= right;
}

Adventure::Vector2 Adventure::operator -(const Vector2& left, float right)
{
	return Vector2(left) -= right;
}

Adventure::Vector2 Adventure::operator *(const Vector2& left, const Vector2& right)
{
	return Vector2(left) *= right;
}

Adventure::Vector2 Adventure::operator *(const Vector2& left, float right)
{
	return Vector2(left) *= right;
}
