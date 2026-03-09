#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <typename T>
	class Ray
	{
	public:
		Ray();
		Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);
		void InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);
		void InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);
		const Vector3<T>& GetDirection() const;
		const Vector3<T>& GetOrigin() const;
		bool IsInFront(const Vector3<T>& aPosition) const;

	private:
		Vector3<T> myOrigin;
		Vector3<T> myDirection;
	};

	template<typename T>
	inline Ray<T>::Ray()
	{
		myOrigin = Vector3<T>(0, 0, 0);
		myDirection = Vector3<T>(0, 0, 0);
	}

	template<typename T>
	inline Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection.GetNormalized();
	}

	template<typename T>
	inline void Ray<T>::InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myDirection = (aPoint - aOrigin).GetNormalized();
		myOrigin = aOrigin;
	}

	template<typename T>
	inline void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}

	template<typename T>
	inline const Vector3<T>& Ray<T>::GetDirection() const
	{
		return myDirection;
	}

	template<typename T>
	inline const Vector3<T>& Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}
	template<typename T>
	inline bool Ray<T>::IsInFront(const Vector3<T>& aPosition) const
	{
		if(myDirection == Vector3<T>(0,0,0))
		{
			return false;
		}

		Vector3<T> originToPoint = aPosition - myOrigin;
		T dotProduct = myDirection.Dot(originToPoint);
		return dotProduct >= static_cast<T>(0);
	}
}