#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <typename T>
	class Plane
	{
	public:
		Plane();
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);
		void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
		bool IsInside(const Vector3<T>&aPosition) const;
		const Vector3<T>& GetNormal() const;
		const Vector3<T>& GetPointOnPlane() const;

	private:
		Vector3<T> myNormal;
		Vector3<T> myPoint;
	};

	template<typename T>
	inline Plane<T>::Plane()
	{
		myNormal = Vector3<T>();
		myPoint = Vector3<T>();
	}

	template<typename T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		InitWith3Points(aPoint0, aPoint1, aPoint2);
	}

	template<typename T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
	{
		myPoint = aPoint0;
		myNormal = aNormal;
	}

	template<typename T>
	inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		myNormal = (aPoint1 - aPoint0).Cross(aPoint2 - aPoint0);
		myNormal.Normalize();
	}

	template<typename T>
	inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
	{
		myNormal = aNormal;
		myPoint = aPoint;
	}

	template<typename T>
	inline bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if(myNormal == Vector3<T>() && myPoint == Vector3<T>())
		{
			return false;
		}

		return (myNormal.Dot(aPosition - myPoint) <= 0);
	}

	template<typename T>
	inline const Vector3<T>& Plane<T>::GetNormal() const
	{
		return myNormal;
	}

	template<typename T>
	inline const Vector3<T>& Plane<T>::GetPointOnPlane() const
	{
		return myPoint;
	}
}
