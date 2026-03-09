#pragma once
#include <vector>
#include "Vector3.hpp"
#include "Plane.hpp"

namespace CommonUtilities
{
	template <typename T>
	class PlaneVolume
	{
	public:
		PlaneVolume();
		PlaneVolume(const std::vector<Plane<T>>& aPlaneList);
		void AddPlane(const Plane<T>& aPlane);
		bool IsInside(const Vector3<T>& aPosition) const;

	private:
		std::vector<Plane<T>> myPlanes;
	};

	template<typename T>
	inline PlaneVolume<T>::PlaneVolume()
	{
		myPlanes = std::vector<Plane<T>>();
	}

	template<typename T>
	inline PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
	{
		myPlanes = aPlaneList;
	}

	template<typename T>
	inline void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
	{
		myPlanes.push_back(aPlane);
	}

	template<typename T>
	inline bool PlaneVolume<T>::IsInside(const Vector3<T>& aPosition) const
	{
		for (size_t i = 0; i < myPlanes.size(); i++)
		{
			if (myPlanes[i].IsInside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}
}