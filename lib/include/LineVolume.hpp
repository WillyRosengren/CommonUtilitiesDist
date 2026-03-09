#pragma once
#include <vector>
#include "Line.hpp"

namespace CommonUtilities
{
	template <typename T>
	class LineVolume
	{
	public:
		LineVolume();
		LineVolume(const std::vector<Line<T>>& aLineList);
		void AddLine(const Line<T>& aLine);
		bool IsInside(const Vector2<T>& aPosition) const;

	private:
		std::vector<Line<T>> myLines;
	};

	template<typename T>
	inline LineVolume<T>::LineVolume()
	{
		myLines = std::vector<Line<T>>();
		myLines.push_back(Line<T>());
	}

	template<typename T>
	inline LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLines = aLineList;
	}

	template<typename T>
	inline void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLines.push_back(aLine);
	}

	template<typename T>
	bool LineVolume<T>::IsInside(const Vector2<T>& aPosition) const
	{
		for (size_t i = 0; i < myLines.size(); i++)
		{
			if (myLines[i].IsInside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}

}