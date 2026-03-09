#pragma once

#include <math.h>
#include <ostream>

namespace Tga
{
	template <typename T>
	class Vector4;
}

namespace CommonUtilities
{
	template <typename T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4();
		Vector4(const T& aX, const T& aY, const T& aZ, const T& aW);
		Vector4(const Vector4<T>& aVector) = default;
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;
		~Vector4() = default;
		template<class TargetType>
		Vector4<TargetType> ToType() const;
		Tga::Vector4<T> ToTga() const;
		Vector4<T> operator-() const;
		T LengthSqr() const;
		T Length() const;
		Vector4<T> GetNormalized() const;

		void Normalize();
		T Dot(const Vector4<T>& aVector) const;
	};
	template <typename T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar);
	template <typename T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector);
	template <typename T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar);
	template <typename T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	void operator*=(Vector4<T>& aVector, const T& aScalar);
	template <typename T>
	void operator/=(Vector4<T>& aVector, const T& aScalar);
	template <typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector4<T>& aVector);
	template <typename T>
	bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	bool operator!=(const Vector4<T>& aVector0, const Vector4<T>& aVector1);
	template <typename T>
	inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template <typename T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<typename T>
	template<class TargetType>
	inline Vector4<TargetType> Vector4<T>::ToType() const
	{
		return { static_cast<TargetType>(x),static_cast<TargetType>(y), static_cast<TargetType>(z), static_cast<TargetType>(w) };
	}

	template<typename T>
	inline Tga::Vector4<T> Vector4<T>::ToTga() const
	{
		return Tga::Vector4<T>({ x, y, z, w });
	}

	template<class T>
	inline Vector4<T> Vector4<T>::operator-() const
	{
		return Vector4<T>{ -x, -y, -z, -w };
	}

	template<typename T>
	inline T Vector4<T>::LengthSqr() const
	{
		return  (x * x + y * y + z * z + w * w);
	}

	template<typename T>
	inline T Vector4<T>::Length() const
	{
		return static_cast<T>(std::sqrt(x * x + y * y + z * z + w * w));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = Length();

		if (length == 0) return Vector4{};

		Vector4 normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		normalized.z = z / length;
		normalized.w = w / length;

		return normalized;
	}

	template<typename T>
	inline void Vector4<T>::Normalize()
	{
		T length = Length();

		if (length == 0)
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
			return;
		}

		x = x / length;
		y = y / length;
		z = z / length;
		w = w / length;
	}

	template<typename T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return (aVector.x * x) + (aVector.y * y) + (aVector.z * z) + (aVector.w * w);
	}

	template<typename T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> addVector;
		addVector.x = aVector0.x + aVector1.x;
		addVector.y = aVector0.y + aVector1.y;
		addVector.z = aVector0.z + aVector1.z;
		addVector.w = aVector0.w + aVector1.w;

		return addVector;
	}

	template<typename T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> subVector;
		subVector.x = aVector0.x - aVector1.x;
		subVector.y = aVector0.y - aVector1.y;
		subVector.z = aVector0.z - aVector1.z;
		subVector.w = aVector0.w - aVector1.w;

		return subVector;
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> mulVector;
		mulVector.x = aVector0.x * aVector1.x;
		mulVector.y = aVector0.y * aVector1.y;
		mulVector.z = aVector0.z * aVector1.z;
		mulVector.w = aVector0.w * aVector1.w;

		return mulVector;
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		mulVector.z = aVector.z * aScalar;
		mulVector.w = aVector.w * aScalar;

		return mulVector;
	}

	template<typename T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		Vector4<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		mulVector.z = aVector.z * aScalar;
		mulVector.w = aVector.w * aScalar;

		return mulVector;
	}

	template<typename T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> DivVector;
		DivVector.x = aVector.x / aScalar;
		DivVector.y = aVector.y / aScalar;
		DivVector.z = aVector.z / aScalar;
		DivVector.w = aVector.w / aScalar;

		return DivVector;
	}

	template<typename T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x = aVector0.x + aVector1.x;
		aVector0.y = aVector0.y + aVector1.y;
		aVector0.z = aVector0.z + aVector1.z;
		aVector0.w = aVector0.w + aVector1.w;

	}

	template<typename T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x = aVector0.x - aVector1.x;
		aVector0.y = aVector0.y - aVector1.y;
		aVector0.z = aVector0.z - aVector1.z;
		aVector0.w = aVector0.w - aVector1.w;

	}

	template<typename T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x * aScalar;
		aVector.y = aVector.y * aScalar;
		aVector.z = aVector.z * aScalar;
		aVector.w = aVector.w * aScalar;

	}

	template<typename T>
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x / aScalar;
		aVector.y = aVector.y / aScalar;
		aVector.z = aVector.z / aScalar;
		aVector.w = aVector.w / aScalar;

	}
	template<typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector4<T>& aVector)
	{
		aStream << "(" << aVector.x << ", " << aVector.y << ", " << aVector.z << ", " << aVector.w << ")";
		return aStream;
	}
	template<typename T>
	bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return (aVector0.x == aVector1.x &&
			aVector0.y == aVector1.y &&
			aVector0.z == aVector1.z &&
			aVector0.w == aVector1.w);
	}
	template<typename T>
	bool operator!=(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}
}
