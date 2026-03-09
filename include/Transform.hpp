#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Matrix4x4;

	template <typename T>
	class Transform
	{
	public:
		Transform();
		Transform(const Vector3<T>& aPosition, const Vector3<T>& aRotation, const Vector3<T>& aScale);
		Transform(const Transform<T>& aTransform) = default;
		
		void SetPositionRotationScale(const Vector3<T>& aPosition, const Vector3<T>& aRotation, const Vector3<T>& aScale);

		Transform<T>& operator=(const Transform<T>& aTransform) = default;
		Transform<T> operator*(const Transform<T>& aTransform) const;
		Transform<T>& operator*=(const Transform<T>& aTransform);

		const Vector3<T>& GetPosition() const;
		const Vector3<T>& GetRotation() const;
		const Vector3<T>& GetScale() const;

		Vector3<T> GetLocalForward() const;
		Vector3<T> GetLocalRight() const;
		Vector3<T> GetLocalUp() const;
		
		void SetPosition(const Vector3<T>& aPosition);
		void SetRotation(const Vector3<T>& aRotation);
		void SetScale(const Vector3<T>& aScale);

		void Translate(const Vector3<T>& aTranslation);
		void TranslateForward(T aDistance);
		void TranslateRight(T aDistance);
		void TranslateUp(T aDistance);

		void Rotate(const Vector3<T>& aRotation);
		void ScaleBy(const Vector3<T>& aScale);

		void LookAt(const Vector3<T>& aTarget, const Vector3<T>& aUp = Vector3<T>(0, 1, 0));

		Matrix4x4<T> GetMatrix() const;
		Matrix4x4<T> GetRotationMatrix() const;
		Matrix4x4<T> GetInverseMatrix() const;

		Vector3<T> TransformPoint(const Vector3<T>& aPoint) const;
		Vector3<T> InverseTransformPoint(const Vector3<T>& aPoint) const;
		Vector3<T> TransformVector(const Vector3<T>& aVector) const;
		Vector3<T> InverseTransformVector(const Vector3<T>& aVector) const;

		static Transform<T> Identity();
		void SetIdentity();

	private:
		Vector3<T> myPosition;
		Vector3<T> myRotation; // radians
		Vector3<T> myScale;

		mutable Matrix4x4<T> myCachedMatrix;
		mutable bool myIsDirty = true;

		void SetDirty() { myIsDirty = true; }
		void SetClean() const { myIsDirty = false; }
		void RecalculateMatrix() const;
	};
	
	template<typename T>
	inline Transform<T>::Transform()
	{
		SetPositionRotationScale(Vector3<T>(0, 0, 0), Vector3<T>(0, 0, 0), Vector3<T>(1, 1, 1));
	}
	
	template<typename T>
	inline Transform<T>::Transform(const Vector3<T>& aPosition, const Vector3<T>& aRotation, const Vector3<T>& aScale)
	{
		SetPositionRotationScale(aPosition, aRotation, aScale);
	}

	template<typename T>
	inline void Transform<T>::SetPositionRotationScale(const Vector3<T>& aPosition, const Vector3<T>& aRotation, const Vector3<T>& aScale)
	{
		myPosition = aPosition;
		myRotation = aRotation;
		myScale = aScale;
		SetDirty();
	}

	template<typename T>
	inline Transform<T> Transform<T>::operator*(const Transform<T>& aTransform) const
	{
		Transform<T> result;
		result.myScale = myScale * aTransform.myScale;
		result.myRotation = myRotation + aTransform.myRotation;
		
		Vector3<T> scaledPosition = myScale * aTransform.myPosition;
		Vector4<T> position4 = Vector4<T>(scaledPosition.x, scaledPosition.y, scaledPosition.z, static_cast<T>(1));
		Vector4<T> rotatedPosition = GetRotationMatrix() * position4;

		result.myPosition = myPosition + Vector3<T>(rotatedPosition.x, rotatedPosition.y, rotatedPosition.z);
		
		return result;
	}

	template<typename T>
	inline Transform<T>& Transform<T>::operator*=(const Transform<T>& aTransform)
	{
		*this = *this * aTransform;
		return *this;
	}

	template<typename T>
	inline const Vector3<T>& Transform<T>::GetPosition() const
	{
		return myPosition;
	}

	template<typename T>
	inline const Vector3<T>& Transform<T>::GetRotation() const
	{
		return myRotation;
	}

	template<typename T>
	inline const Vector3<T>& Transform<T>::GetScale() const
	{
		return myScale;
	}

	template<typename T>
	inline Vector3<T> Transform<T>::GetLocalForward() const
	{
		Matrix4x4<T> rotationMatrix = GetRotationMatrix();
		return Vector3<T>(rotationMatrix(3, 1), rotationMatrix(3, 2), rotationMatrix(3, 3));
	}

	template<typename T>
	inline Vector3<T> Transform<T>::GetLocalRight() const
	{
		Matrix4x4<T> rotationMatrix = GetRotationMatrix();
		return Vector3<T>(rotationMatrix(1, 1), rotationMatrix(1, 2), rotationMatrix(1, 3));
	}

	template<typename T>
	inline Vector3<T> Transform<T>::GetLocalUp() const
	{
		Matrix4x4<T> rotationMatrix = GetRotationMatrix();
		return Vector3<T>(rotationMatrix(2, 1), rotationMatrix(2, 2), rotationMatrix(2, 3));
	}

	template<typename T>
	inline void Transform<T>::SetPosition(const Vector3<T>& aPosition)
	{
		myPosition = aPosition;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::SetRotation(const Vector3<T>& aRotation)
	{
		myRotation = aRotation;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::SetScale(const Vector3<T>& aScale)
	{
		myScale = aScale;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::Translate(const Vector3<T>& aTranslation)
	{
		myPosition += aTranslation;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::TranslateForward(T aDistance)
	{
		myPosition += GetLocalForward() * aDistance;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::TranslateRight(T aDistance)
	{
		myPosition += GetLocalRight() * aDistance;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::TranslateUp(T aDistance)
	{
		myPosition += GetLocalUp() * aDistance;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::Rotate(const Vector3<T>& aRotation)
	{
		myRotation += aRotation;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::ScaleBy(const Vector3<T>& aScale)
	{
		myScale.x *= aScale.x;
		myScale.y *= aScale.y;
		myScale.z *= aScale.z;
		SetDirty();
	}
	
	template<typename T>
	inline void Transform<T>::LookAt(const Vector3<T>& aTarget, const Vector3<T>& aUp)
	{
		Vector3<T> forward = (aTarget - myPosition).GetNormalized();
		Vector3<T> right = aUp.Cross(forward).GetNormalized();
		Vector3<T> up = forward.Cross(right);

		Matrix4x4<T> rotationMatrix;
		rotationMatrix(1, 1) = right.x;		rotationMatrix(1, 2) = right.y;		rotationMatrix(1, 3) = right.z;		rotationMatrix(1, 4) = static_cast<T>(0);
		rotationMatrix(2, 1) = up.x;		rotationMatrix(2, 2) = up.y;		rotationMatrix(2, 3) = up.z;		rotationMatrix(2, 4) = static_cast<T>(0);
		rotationMatrix(3, 1) = forward.x;	rotationMatrix(3, 2) = forward.y;	rotationMatrix(3, 3) = forward.z;	rotationMatrix(3, 4) = static_cast<T>(0);

		T clampedY = std::clamp(rotationMatrix(3, 1), static_cast<T>(-1), static_cast<T>(1));
		myRotation.x = std::atan2(-rotationMatrix(3, 2), rotationMatrix(3, 3));
		myRotation.y = std::asin(clampedY);
		myRotation.z = std::atan2(-rotationMatrix(2, 1), rotationMatrix(1, 1));
		SetDirty();
	}
	
	template<typename T>
	inline Matrix4x4<T> Transform<T>::GetMatrix() const
	{
		return myIsDirty ? (RecalculateMatrix(), myCachedMatrix) : myCachedMatrix;
	}
	
	template<typename T>
	inline Matrix4x4<T> Transform<T>::GetRotationMatrix() const
	{
		Matrix4x4<T> rotationX = Matrix4x4<T>::CreateRotationAroundX(myRotation.x);
		Matrix4x4<T> rotationY = Matrix4x4<T>::CreateRotationAroundY(myRotation.y);
		Matrix4x4<T> rotationZ = Matrix4x4<T>::CreateRotationAroundZ(myRotation.z);

		return rotationZ * rotationY * rotationX;
	}
	
	template<typename T>
	inline Matrix4x4<T> Transform<T>::GetInverseMatrix() const
	{	
		return myIsDirty ? (RecalculateMatrix(), myCachedMatrix.GetFastInverse()) : myCachedMatrix.GetFastInverse();
	}
	
	template<typename T>
	inline Vector3<T> Transform<T>::TransformPoint(const Vector3<T>& aPoint) const
	{
		return GetMatrix() * Vector4<T>(aPoint.x, aPoint.y, aPoint.z, static_cast<T>(1));
	}
	
	template<typename T>
	inline Vector3<T> Transform<T>::InverseTransformPoint(const Vector3<T>& aPoint) const
	{
		return GetInverseMatrix() * Vector4<T>(aPoint.x, aPoint.y, aPoint.z, static_cast<T>(1));
	}
	
	template<typename T>
	inline Vector3<T> Transform<T>::TransformVector(const Vector3<T>& aVector) const
	{
		return GetMatrix() * Vector4<T>(aVector.x, aVector.y, aVector.z, static_cast<T>(0));
	}
	
	template<typename T>
	inline Vector3<T> Transform<T>::InverseTransformVector(const Vector3<T>& aVector) const
	{
		return GetInverseMatrix() * Vector4<T>(aVector.x, aVector.y, aVector.z, static_cast<T>(0));
	}
	
	template<typename T>
	inline Transform<T> Transform<T>::Identity()
	{
		return Transform<T>();
	}
	
	template<typename T>
	inline void Transform<T>::SetIdentity()
	{
		SetPositionRotationScale(Vector3<T>(0, 0, 0), Vector3<T>(0, 0, 0), Vector3<T>(1, 1, 1));
	}
	
	template<typename T>
	inline void Transform<T>::RecalculateMatrix() const
	{
		Matrix4x4<T> scaleMatrix;
		scaleMatrix(1, 1) = myScale.x;
		scaleMatrix(2, 2) = myScale.y;
		scaleMatrix(3, 3) = myScale.z;
		Matrix4x4<T> rotationX = Matrix4x4<T>::CreateRotationAroundX(myRotation.x);
		Matrix4x4<T> rotationY = Matrix4x4<T>::CreateRotationAroundY(myRotation.y);
		Matrix4x4<T> rotationZ = Matrix4x4<T>::CreateRotationAroundZ(myRotation.z);
		Matrix4x4<T> translationMatrix;
		translationMatrix(4, 1) = myPosition.x;
		translationMatrix(4, 2) = myPosition.y;
		translationMatrix(4, 3) = myPosition.z;
		myCachedMatrix = scaleMatrix * (rotationX * rotationY * rotationZ) * translationMatrix;
		SetClean();
	}
}