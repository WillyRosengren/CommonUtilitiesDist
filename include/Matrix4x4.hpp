#pragma once
#include <cmath>
#include <cassert>
#include "Vector4.hpp"
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Matrix3x3;
	
	template <typename T>
	class Matrix4x4
	{
	public:
		// Creates the identity matrix.
		Matrix4x4<T>();
		// Copies the 3x3 matrix into the top left area of the 4x4 matrix.
		Matrix4x4<T>(const Matrix3x3<T>& aMatrix);
		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix) = default;
		//Assignment operator (compiler generated)
		Matrix4x4<T>& operator=(const Matrix4x4<T>& aMatrix) = default;
		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		// Creates a transposed copy of the matrix.
		Matrix4x4<T> GetTranspose() const;
		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(const T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(const T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(const T aAngleInRadians);
		static Matrix4x4<T> CreateFromEulerAngles(const Vector3<T>& aEulerAnglesInRadians);

		Matrix4x4<T> GetFastInverse() const;
		Vector4<T> GetRow(int aRow) const;
		
		Matrix4x4<T> CreateTranslation(const Vector3<T>& aTranslation) const;
		Matrix4x4<T> CreateScale(const Vector3<T>& aScale) const;

	private:
		T m[4][4];
	};

	template<typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T>& operator*=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T>& operator+=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T>& operator-=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	bool operator==(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	bool operator!=(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1);
	template<typename T>
	Matrix4x4<T> operator*(T aScalar, const Matrix4x4<T>& aMatrix);
	template<typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix, T aScalar);
	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix);
	template<typename T>
	Vector4<T> operator*(const Matrix4x4<T>& aMatrix, const Vector4<T>& aVector);
	template<typename T>
	Vector4<T>& operator*=(Vector4<T>& aVector, const Matrix4x4<T>& aMatrix);
	template<typename T>
	Vector4<T>& operator*=(const Matrix4x4<T>& aMatrix, Vector4<T>& aVector);
	
	template<typename T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				if (i == j)
				{
					m[i - 1][j - 1] = static_cast<T>(1);
				}
				else
				{
					m[i - 1][j - 1] = static_cast<T>(0);
				}
			}
		}
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix3x3<T>& aMatrix)
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				m[i - 1][j - 1] = aMatrix(i, j);
			}
		}

		(*this)(1, 4) = static_cast<T>(0);
		(*this)(2, 4) = static_cast<T>(0);
		(*this)(3, 4) = static_cast<T>(0);

		(*this)(4, 1) = static_cast<T>(0);
		(*this)(4, 2) = static_cast<T>(0);
		(*this)(4, 3) = static_cast<T>(0);
		(*this)(4, 4) = static_cast<T>(1);
	}

	template<typename T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 4);
		assert(aColumn >= 1 && aColumn <= 4);
#endif	
		return m[aRow - 1][aColumn - 1];
	}

	template<typename T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 4);
		assert(aColumn >= 1 && aColumn <= 4);
#endif	
		return m[aRow - 1][aColumn - 1];
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetTranspose() const
	{
		Matrix4x4<T> transposedMatrix;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				transposedMatrix(i, j) = (*this)(j, i);
			}
		}
		return transposedMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(const T aAngleInRadians)
	{
		Matrix4x4<T> rotationMatrix;

		rotationMatrix(1, 1) = static_cast<T>(1);
		rotationMatrix(1, 2) = static_cast<T>(0);
		rotationMatrix(1, 3) = static_cast<T>(0);
		rotationMatrix(1, 4) = static_cast<T>(0);

		rotationMatrix(2, 1) = static_cast<T>(0);
		rotationMatrix(2, 2) = std::cos(aAngleInRadians);
		rotationMatrix(2, 3) = std::sin(aAngleInRadians);
		rotationMatrix(2, 4) = static_cast<T>(0);

		rotationMatrix(3, 1) = static_cast<T>(0);
		rotationMatrix(3, 2) = -std::sin(aAngleInRadians);
		rotationMatrix(3, 3) = std::cos(aAngleInRadians);
		rotationMatrix(3, 4) = static_cast<T>(0);

		rotationMatrix(4, 1) = static_cast<T>(0);
		rotationMatrix(4, 2) = static_cast<T>(0);
		rotationMatrix(4, 3) = static_cast<T>(0);
		rotationMatrix(4, 4) = static_cast<T>(1);

		return rotationMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(const T aAngleInRadians)
	{
		Matrix4x4<T> rotationMatrix;

		rotationMatrix(1, 1) = std::cos(aAngleInRadians);
		rotationMatrix(1, 2) = static_cast<T>(0);
		rotationMatrix(1, 3) = -std::sin(aAngleInRadians);
		rotationMatrix(1, 4) = static_cast<T>(0);

		rotationMatrix(2, 1) = static_cast<T>(0);
		rotationMatrix(2, 2) = static_cast<T>(1);
		rotationMatrix(2, 3) = static_cast<T>(0);
		rotationMatrix(2, 4) = static_cast<T>(0);

		rotationMatrix(3, 1) = std::sin(aAngleInRadians);
		rotationMatrix(3, 2) = static_cast<T>(0);
		rotationMatrix(3, 3) = std::cos(aAngleInRadians);
		rotationMatrix(3, 4) = static_cast<T>(0);

		rotationMatrix(4, 1) = static_cast<T>(0);
		rotationMatrix(4, 2) = static_cast<T>(0);
		rotationMatrix(4, 3) = static_cast<T>(0);
		rotationMatrix(4, 4) = static_cast<T>(1);

		return rotationMatrix;

	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(const T aAngleInRadians)
	{
		Matrix4x4<T> rotationMatrix;

		rotationMatrix(1, 1) = std::cos(aAngleInRadians);
		rotationMatrix(1, 2) = std::sin(aAngleInRadians);
		rotationMatrix(1, 3) = static_cast<T>(0);
		rotationMatrix(1, 4) = static_cast<T>(0);

		rotationMatrix(2, 1) = -std::sin(aAngleInRadians);
		rotationMatrix(2, 2) = std::cos(aAngleInRadians);
		rotationMatrix(2, 3) = static_cast<T>(0);
		rotationMatrix(2, 4) = static_cast<T>(0);

		rotationMatrix(3, 1) = static_cast<T>(0);
		rotationMatrix(3, 2) = static_cast<T>(0);
		rotationMatrix(3, 3) = static_cast<T>(1);
		rotationMatrix(3, 4) = static_cast<T>(0);

		rotationMatrix(4, 1) = static_cast<T>(0);
		rotationMatrix(4, 2) = static_cast<T>(0);
		rotationMatrix(4, 3) = static_cast<T>(0);
		rotationMatrix(4, 4) = static_cast<T>(1);

		return rotationMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateFromEulerAngles(const Vector3<T>& aEulerAnglesInRadians)
	{
		Matrix4x4<T> rotationX = CreateRotationAroundX(aEulerAnglesInRadians.x);
		Matrix4x4<T> rotationY = CreateRotationAroundY(aEulerAnglesInRadians.y);
		Matrix4x4<T> rotationZ = CreateRotationAroundZ(aEulerAnglesInRadians.z);

		return rotationZ * rotationY * rotationX;

	}

	template<typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> result;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				result(i, j) = static_cast<T>(0);
				for (int k = 1; k <= 4; ++k)
				{
					result(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		return result;
	}

	template<typename T>
	Matrix4x4<T>& operator*=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 * aMatrix1;
		return aMatrix0;
	}

	template<typename T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> result;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				result(i, j) = aMatrix0(i, j) + aMatrix1(i, j);
			}
		}
		return result;
	}

	template<typename T>
	Matrix4x4<T>& operator+=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 + aMatrix1;
		return aMatrix0;
	}

	template<typename T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		Matrix4x4<T> result;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				result(i, j) = aMatrix0(i, j) - aMatrix1(i, j);
			}
		}
		return result;
	}

	template<typename T>
	Matrix4x4<T>& operator-=(Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 - aMatrix1;
		return aMatrix0;
	}

	template<typename T>
	bool operator==(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		constexpr T epsilon = static_cast<T>(1e-5);

		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				if (std::abs(aMatrix0(i, j) - aMatrix1(i, j)) > epsilon)
				{
					return false;
				}
			}
		}
		return true;
	}

	template<typename T>
	bool operator!=(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		return !(aMatrix0 == aMatrix1);
	}

	template<typename T>
	Matrix4x4<T> operator*(T aScalar, const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> result;
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				result(i, j) = aScalar * aMatrix(i, j);
			}
		}
		return result;
	}

	template<typename T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix, T aScalar)
	{
		return aScalar * aMatrix;
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		return Vector4<T>(
			aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1) + aVector.w * aMatrix(4, 1),
			aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2) + aVector.w * aMatrix(4, 2),
			aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3) + aVector.w * aMatrix(4, 3),
			aVector.x * aMatrix(1, 4) + aVector.y * aMatrix(2, 4) + aVector.z * aMatrix(3, 4) + aVector.w * aMatrix(4, 4)
		);
	}

	template<typename T>
	Vector4<T> operator*(const Matrix4x4<T>& aMatrix, const Vector4<T>& aVector)
	{
		return Vector4<T>(
			aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1) + aVector.w * aMatrix(4, 1),
			aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2) + aVector.w * aMatrix(4, 2),
			aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3) + aVector.w * aMatrix(4, 3),
			aVector.x * aMatrix(1, 4) + aVector.y * aMatrix(2, 4) + aVector.z * aMatrix(3, 4) + aVector.w * aMatrix(4, 4)
		);
	}

	template<typename T>
	Vector4<T>& operator*=(Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		aVector = aVector * aMatrix;
		return aVector;
	}

	template<typename T>
	Vector4<T>& operator*=(const Matrix4x4<T>& aMatrix, Vector4<T>& aVector)
	{
		aVector = aMatrix * aVector;
		return aVector;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse() const
	{
		Matrix4x4<T> invers = *this;
		invers = invers.GetTranspose();

		T tx = (*this)(4, 1);
		T ty = (*this)(4, 2);
		T tz = (*this)(4, 3);

		Matrix4x4<T> translationInverse;
		translationInverse(4, 1) = -tx;
		translationInverse(4, 2) = -ty;
		translationInverse(4, 3) = -tz;

		return invers * translationInverse;
	}

	template<typename T>
	inline Vector4<T> Matrix4x4<T>::GetRow(int aRow) const
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 4);
#endif 
		return Vector4<T> {m[aRow - 1][0], m[aRow - 1][1], m[aRow - 1][2], m[aRow - 1][3]};
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateTranslation(const Vector3<T>& aTranslation) const
	{
		Matrix4x4<T> translationMatrix;
		translationMatrix(4, 1) = aTranslation.x;
		translationMatrix(4, 2) = aTranslation.y;
		translationMatrix(4, 3) = aTranslation.z;
		return translationMatrix;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateScale(const Vector3<T>& aScale) const
	{
		Matrix4x4<T> scaleMatrix;
		scaleMatrix(1, 1) = aScale.x;
		scaleMatrix(2, 2) = aScale.y;
		scaleMatrix(3, 3) = aScale.z;
		return scaleMatrix;
	}


}
