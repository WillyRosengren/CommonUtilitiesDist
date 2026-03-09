#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <typename T>
	class Line
	{
	public:
		Line();
		Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);
		void InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal);
		bool IsInside(const Vector2<T>& aPosition) const;
		Vector2<T> GetDirection() const;
		Vector2<T> GetNormal() const;

	private:
		Vector2<T> myDirection;
		Vector2<T> myStartPoint;
	};

	template<typename T>
	inline Line<T>::Line()
	{
		myStartPoint = Vector2<T>(0, 0);
		myDirection = Vector2<T>(0, 0);
	}

	template<typename T>
	inline Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		InitWith2Points(aPoint0, aPoint1);
	}

	template<typename T>
	inline void Line<T>::InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myStartPoint = aPoint0;
		myDirection = aPoint1 - aPoint0;
	}

	template<typename T>
	inline void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myStartPoint = aPoint;
		myDirection = aDirection;
	}

	template<typename T>
	inline void Line<T>::InitWithPointAndNormal(const Vector2<T>& aPoint, const Vector2<T>& aNormal)
	{
		myStartPoint = aPoint;
		myDirection = Vector2<T>(aNormal.y, -aNormal.x);
	}

	template<typename T>
	inline bool Line<T>::IsInside(const Vector2<T>& aPosition) const
	{
		if (myDirection == Vector2<T>(0, 0))
		{
			return false;
		}

		Vector2<T> directionToPoint = aPosition - myStartPoint;
		Vector2<T> normal = GetNormal();

		return normal.Dot(directionToPoint) <= 0;
	}

	template<typename T>
	inline Vector2<T> Line<T>::GetDirection() const
	{
		return myDirection;
	}

	template<typename T>
	inline Vector2<T> Line<T>::GetNormal() const
	{
		return Vector2<T>(-myDirection.y, myDirection.x);
	}
}
