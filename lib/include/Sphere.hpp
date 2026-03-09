#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{

	template <typename T>
	class Sphere
	{
	public:
		Sphere();
		Sphere(const Vector3<T>& aCenter, T aRadius);
		void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius);
		const Vector3<T>& GetCenter() const;
		T GetRadius() const;
		bool IsInside(const Vector3<T>& aPosition) const;

	private:
		Vector3<T> myOrgin;
		T myRadius;
	};

	template<typename T>
	inline Sphere<T>::Sphere()
	{
		myOrgin = Vector3<T>(0, 0, 0);
		myRadius = 0;
	}

	template<typename T>
	inline Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
	{
		myOrgin = aCenter;
		myRadius = aRadius;
	}

	template<typename T>
	inline void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius)
	{
		myOrgin = aCenter;
		myRadius = aRadius;
	}

	template<typename T>
	inline const Vector3<T>& Sphere<T>::GetCenter() const
	{
		return myOrgin;
	}

	template<typename T>
	inline T Sphere<T>::GetRadius() const
	{
		return myRadius;
	}

	template<typename T>
	inline bool Sphere<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if(myRadius <= 0)
		{
			return false;
		}

		Vector3<T> difference = aPosition - myOrgin;
		T distanceSqr = difference.LengthSqr();
		T radiusSqr = myRadius * myRadius;
		return distanceSqr <= radiusSqr;
	}

}