#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template <typename T>
	class AABB3D
	{
	public:
		AABB3D();
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
		const Vector3<T>& GetMin() const;
		const Vector3<T>& GetMax() const;
		bool IsInside(const Vector3<T>& aPosition) const;

	private:
		Vector3<T> myMin;
		Vector3<T> myMax;
	};


	template<typename T>
	inline AABB3D<T>::AABB3D()
	{
		myMin = Vector3<T>(0, 0, 0);
		myMax = Vector3<T>(0, 0, 0);
	}

	template<typename T>
	inline AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template<typename T>
	inline void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template<typename T>
	inline const Vector3<T>& AABB3D<T>::GetMin() const
	{
		return myMin;
	}

	template<typename T>
	inline const Vector3<T>& AABB3D<T>::GetMax() const
	{
		return myMax;
	}
	template<typename T>
	inline bool AABB3D<T>::IsInside(const Vector3<T>& aPosition) const
	{
		return (aPosition.x >= myMin.x && aPosition.x <= myMax.x) &&
			(aPosition.y >= myMin.y && aPosition.y <= myMax.y) &&
			(aPosition.z >= myMin.z && aPosition.z <= myMax.z);
	}
}