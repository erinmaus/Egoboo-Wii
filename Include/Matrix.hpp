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

#ifndef ADVENTURE_MATRIX_HPP_
#define ADVENTURE_MATRIX_HPP_

namespace Adventure
{
	struct Vector3;
	
	struct Matrix
	{
		private:
			float matrix[16];
		
		public:
			Matrix();
			Matrix(const float other[16]);
			Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
			Matrix(const Matrix& other);
			
			// Getter and setter methods
			inline float Get(int row, int column) const
			{
				return matrix[(column << 2) + row];
			}
			
			void Set(int row, int column, float value)
			{
				matrix[(column << 2) + row] = value;
			}
			
			// Mathematical operations (for now, only multiplication is supported)
			Matrix& operator *=(const Matrix& other);
			
			// Determinant
			float CalculateDeterminant() const;
			
			// Transformation
			static Matrix Rotate(const Vector3& axis, float angle);
			static Matrix Translate(const Vector3& translation);
			static Matrix Scale(const Vector3& scale);
			
			// Inverse
			Matrix Invert(const Matrix& matrix);
	};
	
	Matrix operator *(const Matrix& left, const Matrix& right);
}

#endif
