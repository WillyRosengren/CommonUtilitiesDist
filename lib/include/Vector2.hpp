#pragma once

#include <math.h>
#include <ostream>

namespace Tga
{
	template <typename T>
	class Vector2;
}

namespace CommonUtilities
{
	template <typename T>
	class Vector3;

	template <typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2();
		Vector2(const T& aX, const T& aY);
		Vector2(const Vector2<T>& aVector) = default;
		Vector2<T>& operator=(const Vector2<T>& aVector) = default;
		~Vector2() = default;
		template<class TargetType>
		Vector2<TargetType> ToType() const;
		Tga::Vector2<T> ToTga() const;
		Vector2<T> operator-() const;
		T LengthSqr() const;
		T Length() const;
		Vector2<T> GetNormalized() const;

		void Normalize();
		T Dot(const Vector2<T>& aVector) const;
		Vector3<T> ToXY0() const;
	};
	template <typename T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar);
	template <typename T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector);
	template <typename T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar);
	template <typename T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	void operator*=(Vector2<T>& aVector, const T& aScalar);
	template <typename T>
	void operator/=(Vector2<T>& aVector, const T& aScalar);
	template <typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector2<T>& aVector);
	template <typename T>
	bool operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1);
	template <typename T>
	bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1);

	template <typename T>
	inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template <typename T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY)
	{
		x = aX;
		y = aY;
	}

	template<typename T>
	template<class TargetType>
	inline Vector2<TargetType> Vector2<T>::ToType() const
	{
		return { static_cast<TargetType>(x),static_cast<TargetType>(y) };
	}

	template<typename T>
	inline Tga::Vector2<T> Vector2<T>::ToTga() const
	{
		return Tga::Vector2<T>( x, y);
	}

	template<class T>
	inline Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2<T>{ -x, -y};
	}

	template<typename T>
	inline T Vector2<T>::LengthSqr() const
	{
		return (x * x + y * y);
	}

	template<typename T>
	inline T Vector2<T>::Length() const
	{
		return static_cast<T>(std::sqrt(x * x + y * y));
	}

	template<typename T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = Length();

		if (length == 0) return Vector2{};

		Vector2 normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		return normalized;
	}

	template<typename T>
	inline void Vector2<T>::Normalize()
	{
		T length = Length();

		if (length == 0)
		{
			x = 0;
			y = 0;
			return;
		}

		x = x / length;
		y = y / length;
	}

	template<typename T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return (aVector.x * x) + (aVector.y * y);
	}

	template<typename T>
	inline Vector3<T> Vector2<T>::ToXY0() const
	{
		return Vector3<T>(x, y, 0);
	}

	template<typename T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> addVector;
		addVector.x = aVector0.x + aVector1.x;
		addVector.y = aVector0.y + aVector1.y;
		return addVector;
	}

	template<typename T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> subVector;
		subVector.x = aVector0.x - aVector1.x;
		subVector.y = aVector0.y - aVector1.y;
		return subVector;
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> mulVector;
		mulVector.x = aVector0.x * aVector1.x;
		mulVector.y = aVector0.y * aVector1.y;
		return mulVector;
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		return mulVector;
	}

	template<typename T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		Vector2<T> mulVector;
		mulVector.x = aVector.x * aScalar;
		mulVector.y = aVector.y * aScalar;
		return mulVector;
	}

	template<typename T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T> { (aVector.x / aScalar), (aVector.y / aScalar)};
	}

	template<typename T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x = aVector0.x + aVector1.x;
		aVector0.y = aVector0.y + aVector1.y;
	}

	template<typename T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x = aVector0.x - aVector1.x;
		aVector0.y = aVector0.y - aVector1.y;
	}

	template<typename T>
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x * aScalar;
		aVector.y = aVector.y * aScalar;
	}

	template<typename T>
	void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x / aScalar;
		aVector.y = aVector.y / aScalar;
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& aStream, const Vector2<T>& aVector)
	{
		aStream << "(" << aVector.x << ", " << aVector.y << ")";
		return aStream;
	}
	template<typename T>
	bool operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return aVector0.x == aVector1.x &&
			aVector0.y == aVector1.y;
	}
	template<typename T>
	bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}
}
