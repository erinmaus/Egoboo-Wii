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
