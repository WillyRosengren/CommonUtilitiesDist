#pragma once
#include <cmath>

namespace CommonUtilities
{
	class MathUtils
	{
	public:

		template<typename T>
		static T Lerp(const T& aStart, const T& aEnd, float aLerpFactor)
		{
			return aStart + (aEnd - aStart) * aLerpFactor;
		}

		template<typename T>
		static T DegreeToRadian(T aDegree)
		{
			return aDegree * static_cast<T>(M_PI / 180);
		}

		template<typename T>
		static T RadianToDegree(T aRadian)
		{
			return aRadian * static_cast<T>(180 / M_PI);
		}
	};
}