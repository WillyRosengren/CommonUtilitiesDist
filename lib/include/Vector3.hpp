#pragma once

#include <math.h>
#include <ostream>

namespace Tga
{
	template <typename T>
	class Vector3;
}

namespace CommonUtilities
{
	template <typename T>
	class Vector3
	{
	public:
		T x; 
		T y;
		T z;

		Vector3();
		Vector3(const T& aX, const T& aY, const T& aZ);
		Vector3(const Vector3<T>& aVector) = default;
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		~Vector3() = default;
		template<class TargetType>
		Vector3<TargetType> ToType() const;
		Tga::Vector3<T> ToTga() const;
		Vector3<T> operator-() const;
		T LengthSqr() const;
		T Length() const;
		Vector3<T> GetNormalized() const;

		void Normalize();
		T Dot(const Vector3<T>& aVector) const;
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};
	
	template <typename T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar);
	template <typename T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector);
	template <typename T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar);
	template <typename T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	void operator*=(Vector3<T>& aVector, const T& aScalar);
	template <typename T>
	void operator/=(Vector3<T>& aVector, const T& aScalar);
	template <typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector3<T>& aVector);
	
	template <typename T>
	bool operator==(const Vector3<T>& aVector0, const Vector3<T>& aVector1);
	template <typename T>
	bool operator!=(const Vector3<T>& aVector0, const Vector3<T>& aVector1);

	template <typename T>
	inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template <typename T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<typename T>
	template<class TargetType>
	inline Vector3<TargetType> Vector3<T>::ToType() const
	{
		return {static_cast<TargetType>(x),static_cast<TargetType>(y), static_cast<TargetType>(z)};
	}

	template<typename T>
	inline Tga::Vector3<T> Vector3<T>::ToTga() const
	{
		return Tga::Vector3<T>({ x, y, z });
	}

	template<class T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		return Vector3<T>{ -x, -y, -z };
	}

	template<typename T>
	inline T Vector3<T>::LengthSqr() const
	{
		return  (x * x + y * y + z * z);
	}

	template<typename T>
	inline T Vector3<T>::Length() const
	{
		return static_cast<T>(std::sqrt(x * x + y * y + z * z));
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		T length = Length();

		if (length == 0) return Vector3{};

		Vector3 normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		normalized.z = z / length;
		return normalized;
	}

	template<typename T>
	inline void Vector3<T>::Normalize()
	{
		T length = Length();

		if (length == 0)
		{
			x = 0;
			y = 0;
			z = 0;
			return;
		}

		x = x / length;
		y = y / length;
		z = z / length;
	}

	template<typename T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return (aVector.x * x) + (aVector.y * y) + (aVector.z * z);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		Vector3<T> cross;
		cross.x = (y * aVector.z) - (z * aVector.y);
		cross.y = (z * aVector.x) - (x * aVector.z);
		cross.z = (x * aVector.y) - (y * aVector.x);

		return cross;
	}

	template<typename T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> addVector;
		addVector.x = aVector0.x + aVector1.x;
		addVector.y = aVector0.y + aVector1.y;
		addVector.z = aVector0.z + aVector1.z;
		return addVector;
	}

	template<typename T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> subVector;
		subVector.x = aVector0.x - aVector1.x;
		subVector.y = aVector0.y - aVector1.y;
		subVector.z = aVector0.z - aVector1.z;
		return subVector;
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> mulVector;
		mulVector.x = aVector0.x * aVector1.x;
		mulVector.y = aVector0.y * aVector1.y;
		mulVector.z = aVector0.z * aVector1.z;
		return mulVector;
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		mulVector.z = aVector.z * aScalar;
		return mulVector;
	}

	template<typename T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		Vector3<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		mulVector.z = aVector.z * aScalar;
		return mulVector;
	}

	template<typename T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> DivVector;
		DivVector.x = aVector.x / aScalar;
		DivVector.y = aVector.y / aScalar;
		DivVector.z = aVector.z / aScalar;
		return DivVector;
	}

	template<typename T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x = aVector0.x + aVector1.x;
		aVector0.y = aVector0.y + aVector1.y;
		aVector0.z = aVector0.z + aVector1.z;
	}

	template<typename T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x = aVector0.x - aVector1.x;
		aVector0.y = aVector0.y - aVector1.y;
		aVector0.z = aVector0.z - aVector1.z;
	}

	template<typename T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x * aScalar;
		aVector.y = aVector.y * aScalar;
		aVector.z = aVector.z * aScalar;
	}

	template<typename T>
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x / aScalar;
		aVector.y = aVector.y / aScalar;
		aVector.z = aVector.z / aScalar;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector3<T>& aVector)
	{
		aStream << "(" << aVector.x << ", " << aVector.y << ", " << aVector.z << ")";
		return aStream;
	}

	template<typename T>
	bool operator==(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return (aVector0.x == aVector1.x) && (aVector0.y == aVector1.y) && (aVector0.z == aVector1.z);
	}

	template<typename T>
	bool operator!=(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

}
