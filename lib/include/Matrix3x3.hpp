#pragma once
#include <cmath>
#include <cassert>
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Matrix4x4;

	template <typename T>
	class Matrix3x3
	{
	public:
		// Creates the identity matrix.
		Matrix3x3<T>();
		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix) = default;
		//Assignment operator (compiler generated)
		Matrix3x3<T>& operator=(const Matrix3x3<T>& aMatrix) = default;
		// Copies the top left 3x3 part of the Matrix4x4.
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);
		// () operator for accessing element (row, column) for read/write or read, 
		//respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		// Creates a transposed copy of the matrix.
		Matrix3x3<T> GetTranspose() const;
		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(const T aAngleInRadians);

		Vector3<T> GetRow(int aRow) const;

	private:
		T m[3][3];
	};

	template<typename T>
	Matrix3x3<T> operator*(T aScalar, const Matrix3x3<T>& aMatrix);
	template<typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix, T aScalar);
	template<typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Matrix3x3<T>& operator+=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Matrix3x3<T>& operator-=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Matrix3x3<T>& operator*=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix);
	template<typename T>
	bool operator==(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);
	template<typename T>
	bool operator!=(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1);

	template<typename T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
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
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				m[i - 1][j - 1] = aMatrix(i, j);
			}
		}
	}

	template<typename T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 3);
		assert(aColumn >= 1 && aColumn <= 3);
#endif	
		return m[aRow - 1][aColumn - 1];
	}

	template<typename T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 3);
		assert(aColumn >= 1 && aColumn <= 3);
#endif
		return m[aRow - 1][aColumn - 1];
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::GetTranspose() const
	{
		Matrix3x3<T> transposedMatrix;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				transposedMatrix(i, j) = m[j - 1][i - 1];
			}
		}
		return transposedMatrix;
	}

	template<typename T>
	inline Vector3<T> Matrix3x3<T>::GetRow(int aRow) const
	{
#ifndef NDEBUG
		assert(aRow >= 1 && aRow <= 3);
#endif 
		return Vector3<T> {m[aRow - 1][0], m[aRow - 1][1], m[aRow - 1][2]};
	}

	template<typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(const T aAngleInRadians)
	{
		Matrix3x3<T> rotationMatrix;
		rotationMatrix(1, 1) = static_cast<T>(1);
		rotationMatrix(1, 2) = static_cast<T>(0);
		rotationMatrix(1, 3) = static_cast<T>(0);

		rotationMatrix(2, 1) = static_cast<T>(0);
		rotationMatrix(2, 2) = std::cos(aAngleInRadians);
		rotationMatrix(2, 3) = std::sin(aAngleInRadians);

		rotationMatrix(3, 1) = static_cast<T>(0);
		rotationMatrix(3, 2) = -std::sin(aAngleInRadians);
		rotationMatrix(3, 3) = std::cos(aAngleInRadians);
		return rotationMatrix;
	}

	template<typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(const T aAngleInRadians)
	{
		Matrix3x3<T> rotationMatrix;
		rotationMatrix(1, 1) = std::cos(aAngleInRadians);
		rotationMatrix(1, 2) = static_cast<T>(0);
		rotationMatrix(1, 3) = -std::sin(aAngleInRadians);

		rotationMatrix(2, 1) = static_cast<T>(0);
		rotationMatrix(2, 2) = static_cast<T>(1);
		rotationMatrix(2, 3) = static_cast<T>(0);

		rotationMatrix(3, 1) = std::sin(aAngleInRadians);
		rotationMatrix(3, 2) = static_cast<T>(0);
		rotationMatrix(3, 3) = std::cos(aAngleInRadians);
		return rotationMatrix;
	}

	template<typename T>
	Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(const T aAngleInRadians)
	{
		Matrix3x3<T> rotationMatrix;
		rotationMatrix(1, 1) = std::cos(aAngleInRadians);
		rotationMatrix(1, 2) = std::sin(aAngleInRadians);
		rotationMatrix(1, 3) = static_cast<T>(0);

		rotationMatrix(2, 1) = -std::sin(aAngleInRadians);
		rotationMatrix(2, 2) = std::cos(aAngleInRadians);
		rotationMatrix(2, 3) = static_cast<T>(0);

		rotationMatrix(3, 1) = static_cast<T>(0);
		rotationMatrix(3, 2) = static_cast<T>(0);
		rotationMatrix(3, 3) = static_cast<T>(1);
		return rotationMatrix;
	}

	template<typename T>
	Matrix3x3<T> operator*(T aScalar, const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				result(i, j) = aMatrix(i, j) * aScalar;
			}
		}
		return result;
	}

	template<typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix, T aScalar)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				result(i, j) = aMatrix(i, j) * aScalar;
			}
		}
		return result;
	}

	template<typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				result(i, j) = aMatrix0(i, j) + aMatrix1(i, j);
			}
		}
		return result;
	}

	template<typename T>
	Matrix3x3<T>& operator+=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				aMatrix0(i, j) += aMatrix1(i, j);
			}
		}
		return aMatrix0;
	}

	template<typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				result(i, j) = aMatrix0(i, j) - aMatrix1(i, j);
			}
		}
		return result;
	}

	template<typename T>
	Matrix3x3<T>& operator-=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				aMatrix0(i, j) -= aMatrix1(i, j);
			}
		}
		return aMatrix0;
	}

	template<typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				result(i, j) = static_cast<T>(0);
				for (int k = 1; k <= 3; ++k)
				{
					result(i, j) += aMatrix0(i, k) * aMatrix1(k, j);
				}
			}
		}
		return result;
	}

	template<typename T>
	Matrix3x3<T>& operator*=(Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		Matrix3x3<T> result = aMatrix0 * aMatrix1;
		aMatrix0 = result;
		return aMatrix0;
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		return Vector3<T>(
			aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1),
			aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2),
			aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3)
		);
	}

	template<typename T>
	bool operator==(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		constexpr T epsilon = static_cast<T>(1e-5);

		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				if (std::abs(aMatrix0(i, j) - aMatrix1(i, j)) > epsilon)
					return false;
			}
		}
		return true;
	}

	template<typename T>
	bool operator!=(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		return !(aMatrix0 == aMatrix1);
	}
}