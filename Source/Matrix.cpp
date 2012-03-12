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
#include <cstring>

#include "Matrix.hpp"
#include "Vector3.hpp"

Adventure::Matrix::Matrix()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0.0f;
}

Adventure::Matrix::Matrix(const float other[16])
{
	for (int i = 0; i < 16; i++)
		matrix[i] = other[i];
}

Adventure::Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	Set(0, 0, m11);
	Set(0, 1, m12);
	Set(0, 2, m13);
	Set(0, 3, m14);
	
	Set(1, 0, m21);
	Set(1, 1, m22);
	Set(1, 2, m23);
	Set(1, 3, m24);
	
	Set(2, 0, m31);
	Set(2, 1, m32);
	Set(2, 2, m33);
	Set(2, 3, m34);
	
	Set(3, 0, m41);
	Set(3, 1, m42);
	Set(3, 2, m43);
	Set(3, 3, m44);
}

Adventure::Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < 16; i++)
		matrix[i] = other.matrix[i];
}

void Adventure::Matrix::ToFloat16(float array[16]) const
{
	memcpy(array, matrix, sizeof(float) * 16);
}

Adventure::Matrix& Adventure::Matrix::operator *=(const Matrix& other)
{
	for (int i = 0; i < 4; i++)
	{
		float a = Get(i, 0), b = Get(i, 1), c = Get(i, 2), d = Get(i, 3);
		
		Set(i, 0, a * other.Get(0, 0) + b * other.Get(1, 0) + c * other.Get(2, 0) + d * other.Get(3, 0));
		Set(i, 1, a * other.Get(0, 1) + b * other.Get(1, 1) + c * other.Get(2, 1) + d * other.Get(3, 1));
		Set(i, 2, a * other.Get(0, 2) + b * other.Get(1, 2) + c * other.Get(2, 2) + d * other.Get(3, 2));
		Set(i, 3, a * other.Get(0, 3) + b * other.Get(1, 3) + c * other.Get(2, 3) + d * other.Get(3, 3));
	}
	
	return *this;
}

Adventure::Matrix Adventure::Matrix::Rotate(const Vector3& axis, float angle)
{
	float c = cosf(-angle);
	float s = sinf(-angle);
	float t = 1.0 - c;
	
	return Matrix
	(
		t * axis.X * axis.X + c, t * axis.X * axis.Y - s * axis.Z, t * axis.X * axis.Z + s * axis.Y, 0.0f,
		t * axis.X * axis.Y + s * axis.Z, t * axis.Y * axis.Y + c, t * axis.Y * axis.Z - s * axis.X, 0.0f,
		t * axis.X * axis.Z - s * axis.Y, t * axis.Y * axis.Z + s * axis.X, t * axis.Z * axis.Z + c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Adventure::Matrix Adventure::Matrix::Translate(const Vector3& translation)
{
	return Matrix
	(
		1.0f, 0.0f, 0.0f, translation.X,
		0.0f, 1.0f, 0.0f, translation.Y,
		0.0f, 0.0f, 1.0f, translation.Z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Adventure::Matrix Adventure::Matrix::Scale(const Vector3& scale)
{
	return Matrix
	(
		scale.X, 0.0f, 0.0f, 0.0f,
		0.0f, scale.Y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

float Adventure::Matrix::CalculateDeterminant() const
{
	float a1 = Get(0, 0) * Get(1, 1) - Get(0, 1) * Get(1, 0);
	float a2 = Get(0, 0) * Get(1, 2) - Get(0, 2) * Get(1, 0);
	float a3 = Get(0, 0) * Get(1, 3) - Get(0, 3) * Get(1, 0);
	float a4 = Get(0, 1) * Get(1, 2) - Get(0, 2) * Get(1, 1);
	float a5 = Get(0, 1) * Get(1, 3) - Get(0, 3) * Get(1, 1);
	float a6 = Get(0, 2) * Get(1, 3) - Get(0, 3) * Get(1, 2);
	
	float b1 = Get(2, 0) * a4 - Get(2, 1) * a2 + Get(2, 2) * a1;
	float b2 = Get(2, 0) * a5 - Get(2, 1) * a3 + Get(2, 3) * a1;
	float b3 = Get(2, 0) * a6 - Get(2, 2) * a3 + Get(2, 3) * a2;
	float b4 = Get(2, 1) * a6 - Get(2, 2) * a6 + Get(2, 3) * a4;
	
	return -b4 * Get(3, 0) + b3 * Get(3, 1) - b2 * Get(3, 2) + b1 * Get(3, 3);
}

Adventure::Matrix Adventure::Matrix::Invert(const Matrix& matrix)
{
	float d = 1.0f / matrix.CalculateDeterminant();
	Matrix result;

	result.Set(0, 0, (matrix.Get(1, 1) * matrix.Get(2, 2) * matrix.Get(3, 3) + matrix.Get(1, 2) * matrix.Get(2, 3) * matrix.Get(3, 1) + matrix.Get(1, 3) * matrix.Get(2, 1) * matrix.Get(3, 2) - matrix.Get(1, 1) * matrix.Get(2, 3) * matrix.Get(3, 2) - matrix.Get(1, 2) * matrix.Get(2, 1) * matrix.Get(3, 3) - matrix.Get(1, 3) * matrix.Get(2, 2) * matrix.Get(3, 1)) * d);
	result.Set(0, 1, (matrix.Get(0, 1) * matrix.Get(2, 3) * matrix.Get(3, 2) + matrix.Get(0, 2) * matrix.Get(2, 1) * matrix.Get(3, 3) + matrix.Get(0, 3) * matrix.Get(2, 2) * matrix.Get(3, 1) - matrix.Get(0, 1) * matrix.Get(2, 2) * matrix.Get(3, 3) - matrix.Get(0, 2) * matrix.Get(2, 3) * matrix.Get(3, 1) - matrix.Get(0, 3) * matrix.Get(2, 1) * matrix.Get(3, 2)) * d);
	result.Set(0, 2, (matrix.Get(0, 1) * matrix.Get(1, 2) * matrix.Get(3, 3) + matrix.Get(0, 2) * matrix.Get(1, 3) * matrix.Get(3, 1) + matrix.Get(0, 3) * matrix.Get(1, 1) * matrix.Get(3, 2) - matrix.Get(0, 1) * matrix.Get(1, 3) * matrix.Get(3, 2) - matrix.Get(0, 2) * matrix.Get(1, 1) * matrix.Get(3, 3) - matrix.Get(0, 3) * matrix.Get(1, 2) * matrix.Get(3, 1)) * d);
	result.Set(0, 3, (matrix.Get(0, 1) * matrix.Get(1, 3) * matrix.Get(2, 2) + matrix.Get(0, 2) * matrix.Get(1, 1) * matrix.Get(2, 3) + matrix.Get(0, 3) * matrix.Get(1, 2) * matrix.Get(2, 1) - matrix.Get(0, 1) * matrix.Get(1, 2) * matrix.Get(2, 3) - matrix.Get(0, 2) * matrix.Get(1, 3) * matrix.Get(2, 1) - matrix.Get(0, 3) * matrix.Get(1, 1) * matrix.Get(2, 2)) * d);

	result.Set(1, 0, (matrix.Get(1, 0) * matrix.Get(2, 3) * matrix.Get(3, 2) + matrix.Get(1, 2) * matrix.Get(2, 0) * matrix.Get(3, 3) + matrix.Get(1, 3) * matrix.Get(2, 2) * matrix.Get(3, 0) - matrix.Get(1, 0) * matrix.Get(2, 2) * matrix.Get(3, 3) - matrix.Get(1, 2) * matrix.Get(2, 3) * matrix.Get(3, 0) - matrix.Get(1, 3) * matrix.Get(2, 0) * matrix.Get(3, 2)) * d);
	result.Set(1, 1, (matrix.Get(0, 0) * matrix.Get(2, 2) * matrix.Get(3, 3) + matrix.Get(0, 2) * matrix.Get(2, 3) * matrix.Get(3, 0) + matrix.Get(0, 3) * matrix.Get(2, 0) * matrix.Get(3, 2) - matrix.Get(0, 0) * matrix.Get(2, 3) * matrix.Get(3, 2) - matrix.Get(0, 2) * matrix.Get(2, 0) * matrix.Get(3, 3) - matrix.Get(0, 3) * matrix.Get(2, 2) * matrix.Get(3, 0)) * d);
	result.Set(1, 2, (matrix.Get(0, 0) * matrix.Get(1, 3) * matrix.Get(3, 2) + matrix.Get(0, 2) * matrix.Get(1, 0) * matrix.Get(3, 3) + matrix.Get(0, 3) * matrix.Get(1, 2) * matrix.Get(3, 0) - matrix.Get(0, 0) * matrix.Get(1, 2) * matrix.Get(3, 3) - matrix.Get(0, 2) * matrix.Get(1, 3) * matrix.Get(3, 0) - matrix.Get(0, 3) * matrix.Get(1, 0) * matrix.Get(3, 2)) * d);
	result.Set(1, 3, (matrix.Get(0, 0) * matrix.Get(1, 2) * matrix.Get(2, 3) + matrix.Get(0, 2) * matrix.Get(1, 3) * matrix.Get(2, 0) + matrix.Get(0, 3) * matrix.Get(1, 0) * matrix.Get(2, 2) - matrix.Get(0, 0) * matrix.Get(1, 3) * matrix.Get(2, 2) - matrix.Get(0, 2) * matrix.Get(1, 0) * matrix.Get(2, 3) - matrix.Get(0, 3) * matrix.Get(1, 2) * matrix.Get(2, 0)) * d);

	result.Set(2, 0, (matrix.Get(1, 0) * matrix.Get(2, 1) * matrix.Get(3, 3) + matrix.Get(1, 1) * matrix.Get(2, 3) * matrix.Get(3, 0) + matrix.Get(1, 3) * matrix.Get(2, 0) * matrix.Get(3, 1) - matrix.Get(1, 0) * matrix.Get(2, 3) * matrix.Get(3, 1) - matrix.Get(1, 1) * matrix.Get(2, 0) * matrix.Get(3, 3) - matrix.Get(1, 3) * matrix.Get(2, 1) * matrix.Get(3, 0)) * d);
	result.Set(2, 1, (matrix.Get(0, 0) * matrix.Get(2, 3) * matrix.Get(3, 1) + matrix.Get(0, 1) * matrix.Get(2, 0) * matrix.Get(3, 3) + matrix.Get(0, 3) * matrix.Get(2, 1) * matrix.Get(3, 0) - matrix.Get(0, 0) * matrix.Get(2, 1) * matrix.Get(3, 3) - matrix.Get(0, 1) * matrix.Get(2, 3) * matrix.Get(3, 0) - matrix.Get(0, 3) * matrix.Get(2, 0) * matrix.Get(3, 1)) * d);
	result.Set(2, 2, (matrix.Get(0, 0) * matrix.Get(1, 1) * matrix.Get(3, 3) + matrix.Get(0, 1) * matrix.Get(1, 3) * matrix.Get(3, 0) + matrix.Get(0, 3) * matrix.Get(1, 0) * matrix.Get(3, 1) - matrix.Get(0, 0) * matrix.Get(1, 3) * matrix.Get(3, 1) - matrix.Get(0, 1) * matrix.Get(1, 0) * matrix.Get(3, 3) - matrix.Get(0, 3) * matrix.Get(1, 1) * matrix.Get(3, 0)) * d);
	result.Set(2, 3, (matrix.Get(0, 0) * matrix.Get(1, 3) * matrix.Get(2, 1) + matrix.Get(0, 1) * matrix.Get(1, 0) * matrix.Get(2, 3) + matrix.Get(0, 3) * matrix.Get(1, 1) * matrix.Get(2, 0) - matrix.Get(0, 0) * matrix.Get(1, 1) * matrix.Get(2, 3) - matrix.Get(0, 1) * matrix.Get(1, 3) * matrix.Get(2, 0) - matrix.Get(0, 3) * matrix.Get(1, 0) * matrix.Get(2, 1)) * d);

	result.Set(3, 0, (matrix.Get(1, 0) * matrix.Get(2, 2) * matrix.Get(3, 1) + matrix.Get(1, 1) * matrix.Get(2, 0) * matrix.Get(3, 2) + matrix.Get(1, 2) * matrix.Get(2, 1) * matrix.Get(3, 0) - matrix.Get(1, 0) * matrix.Get(2, 1) * matrix.Get(3, 2) - matrix.Get(1, 1) * matrix.Get(2, 2) * matrix.Get(3, 0) - matrix.Get(1, 2) * matrix.Get(2, 0) * matrix.Get(3, 1)) * d);
	result.Set(3, 1, (matrix.Get(0, 0) * matrix.Get(2, 1) * matrix.Get(3, 2) + matrix.Get(0, 1) * matrix.Get(2, 2) * matrix.Get(3, 0) + matrix.Get(0, 2) * matrix.Get(2, 0) * matrix.Get(3, 1) - matrix.Get(0, 0) * matrix.Get(2, 2) * matrix.Get(3, 1) - matrix.Get(0, 1) * matrix.Get(2, 0) * matrix.Get(3, 2) - matrix.Get(0, 2) * matrix.Get(2, 1) * matrix.Get(3, 0)) * d);
	result.Set(3, 2, (matrix.Get(0, 0) * matrix.Get(1, 2) * matrix.Get(3, 1) + matrix.Get(0, 1) * matrix.Get(1, 0) * matrix.Get(3, 2) + matrix.Get(0, 2) * matrix.Get(1, 1) * matrix.Get(3, 0) - matrix.Get(0, 0) * matrix.Get(1, 1) * matrix.Get(3, 2) - matrix.Get(0, 1) * matrix.Get(1, 2) * matrix.Get(3, 0) - matrix.Get(0, 2) * matrix.Get(1, 0) * matrix.Get(3, 1)) * d);
	result.Set(3, 3, (matrix.Get(0, 0) * matrix.Get(1, 1) * matrix.Get(2, 2) + matrix.Get(0, 1) * matrix.Get(1, 2) * matrix.Get(2, 0) + matrix.Get(0, 2) * matrix.Get(1, 0) * matrix.Get(2, 1) - matrix.Get(0, 0) * matrix.Get(1, 2) * matrix.Get(2, 1) - matrix.Get(0, 1) * matrix.Get(1, 0) * matrix.Get(2, 2) - matrix.Get(0, 2) * matrix.Get(1, 1) * matrix.Get(2, 0)) * d);
	
	return result;
}

Adventure::Matrix Adventure::Matrix::Transpose(const Matrix& matrix)
{
	Matrix other;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			other.Set(j, i, matrix.Get(i, j));
		}
	}
	
	return other;
}

Adventure::Matrix Adventure::Matrix::Ortho(float left, float right, float bottom, float top, float near, float far)
{
	float rightLeft = 1.0f / (right - left);
	float topBottom = 1.0f / (top - bottom);
	float farNear = 1.0f / (far - near);
	
	return Matrix
	(
		2.0f * rightLeft, 0.0f, 0.0f, -(right + left) * rightLeft,
		0.0f, 2.0f * topBottom, 0.0f, -(top + bottom) * topBottom, 
		0.0f, 0.0f, -farNear, -(far) * farNear,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Adventure::Matrix Adventure::Matrix::Perspective(float fov, float aspect, float near, float far)
{
	float yMax = near * tanf(0.5f * fov);
	float yMin = -yMax;
	float xMax = yMax * aspect;
	float xMin = yMin * aspect;
	
	return Frustum(xMin, xMax, yMin, yMax, near, far);
}

Adventure::Matrix Adventure::Matrix::Frustum(float left, float right, float bottom, float top, float near, float far)
{
	float x = (2.0f * near) / (right - left);
	float y = (2.0f * near) / (top - bottom);
	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(near) / (far - near);
	float d = -(near * far) / (far - near);

	return Matrix
	(
		x, 0.0f, a, 0.0f,
		0.0f, y, b, 0.0f,
		0.0f, 0.0f, c, d,
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Adventure::Matrix Adventure::Matrix::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 l = Vector3::Normalize(eye - target); // Look
	Vector3 r = Vector3::Normalize(Vector3::Cross(up, l)); // Right
	Vector3 u = Vector3::Normalize(Vector3::Cross(l, r)); // Corrected up
	
	return Matrix
	(
		r.X, r.Y, r.Z, -(eye.X * r.X + eye.Y * r.Y + eye.Z * r.Z),
		u.X, u.Y, u.Z, -(eye.X * u.X + eye.Y * u.Y + eye.Z * u.Z),
		l.X, l.Y, l.Z, -(eye.X * l.X + eye.Y * l.Y + eye.Z * l.Z),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Adventure::Matrix Adventure::operator *(const Matrix& left, const Matrix& right)
{
	return Matrix(left) *= right;
}
