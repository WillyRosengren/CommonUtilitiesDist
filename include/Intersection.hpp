#pragma once
#include "Vector3.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"
#include <limits>

namespace CommonUtilities
{
	template <typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint);

	template <typename T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint);

	template <typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay);

	template <typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay);
}
namespace CommonUtilities
{
	template <typename T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint)
	{
		const T epsilon = static_cast<T>(1e-6);
		T rayPlaneAlignment = aPlane.GetNormal().Dot(aRay.GetDirection());

		if (std::abs(rayPlaneAlignment) < epsilon)
		{
			if (std::abs(aPlane.GetNormal().Dot(aRay.GetOrigin() - aPlane.GetPointOnPlane())) < epsilon)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		T rayDistance = (aPlane.GetPointOnPlane() - aRay.GetOrigin()).Dot(aPlane.GetNormal()) / rayPlaneAlignment;
		if (rayDistance < 0)
		{
			return false;
		}
		outIntersectionPoint = aRay.GetOrigin() + aRay.GetDirection() * rayDistance;
		return true;
	}

	template<typename T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint)
	{
		Vector3<T> closestPoint;

		closestPoint.x = std::max(aAABB3D.GetMin().x, std::min(aSphere.GetCenter().x, aAABB3D.GetMax().x));
		closestPoint.y = std::max(aAABB3D.GetMin().y, std::min(aSphere.GetCenter().y, aAABB3D.GetMax().y));
		closestPoint.z = std::max(aAABB3D.GetMin().z, std::min(aSphere.GetCenter().z, aAABB3D.GetMax().z));

		Vector3<T> diff = closestPoint - aSphere.GetCenter();
		T squaredDistance = diff.Dot(diff);

		if (squaredDistance <= aSphere.GetRadius() * aSphere.GetRadius())
		{
			outIntersectionPoint = closestPoint;
			return true;
		}

		return false;
	}

	template<typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{
		const Vector3<T> rayOrigin = aRay.GetOrigin();
		const Vector3<T> rayDirection = aRay.GetDirection();

		T tEnter = std::numeric_limits<T>::lowest();
		T tExit = std::numeric_limits<T>::max();

		if (rayDirection.x == T(0))
		{
			if (rayOrigin.x < aAABB.GetMin().x || rayOrigin.x > aAABB.GetMax().x)
			{
				return false;
			}
		}
		else
		{
			T t1 = (aAABB.GetMin().x - rayOrigin.x) / rayDirection.x;
			T t2 = (aAABB.GetMax().x - rayOrigin.x) / rayDirection.x;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}

			tEnter = std::max(tEnter, t1);
			tExit = std::min(tExit, t2);

			if (tEnter > tExit)
			{
				return false;
			}
		}
		if (rayDirection.y == T(0))
		{
			if (rayOrigin.y < aAABB.GetMin().y || rayOrigin.y > aAABB.GetMax().y)
			{
				return false;
			}
		}
		else
		{
			T t1 = (aAABB.GetMin().y - rayOrigin.y) / rayDirection.y;
			T t2 = (aAABB.GetMax().y - rayOrigin.y) / rayDirection.y;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tEnter = std::max(tEnter, t1);
			tExit = std::min(tExit, t2);
			if (tEnter > tExit)
			{
				return false;
			}
		}
		if (rayDirection.z == T(0))
		{
			if (rayOrigin.z < aAABB.GetMin().z || rayOrigin.z > aAABB.GetMax().z)
			{
				return false;
			}
		}
		else
		{
			T t1 = (aAABB.GetMin().z - rayOrigin.z) / rayDirection.z;
			T t2 = (aAABB.GetMax().z - rayOrigin.z) / rayDirection.z;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tEnter = std::max(tEnter, t1);
			tExit = std::min(tExit, t2);
			if (tEnter > tExit)
			{
				return false;
			}
		}

		if (tExit < 0)
		{
			return false;
		}

		return true;
	}

	template<typename T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> originToCenter = aSphere.GetCenter() - aRay.GetOrigin();
		T distanceAlongRay = originToCenter.Dot(aRay.GetDirection());
		
		if(distanceAlongRay < 0)
		{
			return false;
		}

		T squaredDistanceToRay = originToCenter.Dot(originToCenter) - (distanceAlongRay * distanceAlongRay);

		if(squaredDistanceToRay > aSphere.GetRadius() * aSphere.GetRadius())
		{
			return false;
		}

		return true;
	}
	
}