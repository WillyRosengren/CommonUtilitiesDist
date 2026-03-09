#pragma once

#include "Matrix3x3.hpp"
#include "Vector2.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Transform2D
	{
	public:
		Transform2D()
			: myPosition(0, 0)
			, myRotation(0)
			, myScale(1, 1)
			, myIsDirty(true)
		{}

		Transform2D(const Vector2<T>& aPosition, const T aRotation, const Vector2<T>& aScale) 
			: myPosition(aPosition)
			, myRotation(aRotation)
			, myScale(aScale)
			, myIsDirty(true)
		{}
		
		Transform2D(const Transform2D<T>& aTransform) = default;

		void SetPositionRotationScale(const Vector2<T>& aPosition, const T aRotation, const Vector2<T>& aScale)
		{
			myPosition = aPosition;
			myRotation = aRotation;
			myScale = aScale;
			myIsDirty = true;
		}

		Transform2D<T>& operator=(const Transform2D<T>& aTransform) = default;

		const Vector2<T>& GetPosition() const { return myPosition; }
		T GetRotation() const { return myRotation; }
		T GetRotationDegrees() const { return myRotation * static_cast<T>(180 / M_PI); }
		const Vector2<T>& GetScale() const { return myScale; }

		Vector2<T> GetLocalUp() const;
		Vector2<T> GetLocalRight() const;

		void SetPosition(const Vector2<T>& aPosition) { myPosition = aPosition; SetDirty(); }
		void SetRotation(const T aRotation) { myRotation = aRotation; NormalizeRotation(); SetDirty(); }
		void SetRotationDegrees(T aRotationDegrees) { SetRotation(aRotationDegrees * static_cast<T>(M_PI / 180)); }
		void SetScale(const Vector2<T>& aScale) { myScale = aScale; SetDirty(); }

		void Translate(const Vector2<T>& aTranslation) { myPosition += aTranslation; SetDirty(); }
		void TranslateUp(const T aDistance) { myPosition += GetLocalUp() * aDistance; SetDirty(); }
		void TranslateRight(const T aDistance) { myPosition += GetLocalRight() * aDistance; SetDirty(); }


		void Rotate(T aRotation) { myRotation += aRotation; NormalizeRotation(); SetDirty(); }
		void RotateDegrees(T aRotationDegrees) { Rotate(aRotationDegrees * static_cast<T>(M_PI / 180)); }
		void ScaleBy(const Vector2<T>& aScale) { myScale.x *= aScale.x; myScale.y *= aScale.y; SetDirty(); }

		Vector2<T> TransformPoint(const Vector2<T>& aPoint) const;
		Vector2<T> InverseTransformPoint(const Vector2<T>& aPoint) const;

		const Matrix3x3<T>& GetMatrix() const {return myIsDirty ? (RecalculateMatrix(), myCachedMatrix) : myCachedMatrix };

	private:
		Vector2<T> myPosition;
		T myRotation; // radians
		Vector2<T> myScale;

		mutable Matrix3x3<T> myCachedMatrix;
		mutable bool myIsDirty;

		void SetDirty() { myIsDirty = true; }
		void SetClean() const { myIsDirty = false; }
		void RecalculateMatrix() const;
		void NormalizeRotation();
	};


	template<typename T>
	inline Vector2<T> Transform2D<T>::GetLocalUp() const
	{
		T cosRotation = std::cos(myRotation);
		T sinRotation = std::sin(myRotation);

		return Vector2<T>(-sinRotation, cosRotation);
	}

	template<typename T>
	inline Vector2<T> Transform2D<T>::GetLocalRight() const
	{
		T cosRotation = std::cos(myRotation); 
		T sinRotation = std::sin(myRotation);

		return Vector2<T>(cosRotation, sinRotation);
	}

	template<typename T>
	inline Vector2<T> Transform2D<T>::TransformPoint(const Vector2<T>& aPoint) const
	{
		if (myIsDirty)
		{
			RecalculateMatrix();
		}

		Vector3<T> transformedPoint = GetMatrix() * aPoint.ToXY0();
		return Vector2<T>(transformedPoint.x, transformedPoint.y);

	}

	template<typename T>
	inline Vector2<T> Transform2D<T>::InverseTransformPoint(const Vector2<T>& aPoint) const
	{
		if (myIsDirty)
		{
			RecalculateMatrix();
		}

		Vector2<T> point = aPoint - myPosition;

		T cosRotation = std::cos(-myRotation);
		T sinRotation = std::sin(-myRotation);

		Vector2<T> rotatedPoint;
		rotatedPoint.x = point.x * cosRotation - point.y * sinRotation;
		rotatedPoint.y = point.x * sinRotation + point.y * cosRotation;

		rotatedPoint.x /= myScale.x;
		rotatedPoint.y /= myScale.y;

		return rotatedPoint;
	}

	template<typename T>
	inline void Transform2D<T>::RecalculateMatrix() const
	{
		T cosRotation = std::cos(myRotation);
		T sinRotation = std::sin(myRotation);
		
		myCachedMatrix(1, 1) = cosRotation * myScale.x;
		myCachedMatrix(1, 2) = -sinRotation * myScale.y;
		myCachedMatrix(1, 3) = myPosition.x;
		myCachedMatrix(2, 1) = sinRotation * myScale.x;
		myCachedMatrix(2, 2) = cosRotation * myScale.y;
		myCachedMatrix(2, 3) = myPosition.y;
		myCachedMatrix(3, 1) = static_cast<T>(0);
		myCachedMatrix(3, 2) = static_cast<T>(0);
		myCachedMatrix(3, 3) = static_cast<T>(1);
		
		SetClean();
	}

	template<typename T>
	inline void Transform2D<T>::NormalizeRotation()
	{
		myRotation = std::fmod(myRotation, static_cast<T>(2 * M_PI));
		if (myRotation < 0)
		{
			myRotation += static_cast<T>(2 * M_PI);
		}
	}

}