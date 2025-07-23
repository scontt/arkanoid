#include <windows.h>
#include "Brick.h"
#include "Platform.h"
#include "Ball.h"

#pragma once

class Drawer {
public:
	static void DrawBrick(HWND, PAINTSTRUCT, HDC, Brick);
	static void DrawPlatform(HWND, PAINTSTRUCT, HDC, Platform);
	static void DrawBall(HWND, PAINTSTRUCT, HDC, Ball);

	static void ErasePlatform(HWND, PAINTSTRUCT, HDC, Platform);
	static void EraseBall(HWND, PAINTSTRUCT, HDC, Ball);
};