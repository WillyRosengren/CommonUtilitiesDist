#pragma once
#include <windows.h>
#include <bitset>
namespace CommonUtilities
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		bool UpdateEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		bool IsKeyDown(const int aKeyCode) const;
		bool IsKeyPressed(const int aKeyCode) const;
		bool IsKeyReleased(const int aKeyCode) const;

		bool UpdateMouseInput(UINT aMessage);
		const POINT GetMouseDelta();
		const POINT GetMousePosition();
		const int GetScrollDelta();
		void UpdateInput();

	private:
		std::bitset<256> myCurrentState;
		std::bitset<256> myPreviousState;
		std::bitset<256> myTentativeState;

		POINT myPreviousMousePos;
		POINT myTentativeMousePoint;
		POINT myCurrentMousePoint;

		int myScrollDelta;
	};
}
