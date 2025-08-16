#include <windows.h>
#include "Brick.h"
#include "Platform.h"
#include "Ball.h"
//#include "Brick.h"

#pragma once

class Drawer {
public:
	static void DrawBrick(HDC, Brick*);
	static void DrawPlatform(HDC, Platform);
	static void DrawBall(HDC, Ball);
	static void DrawTrail(Gdiplus::Graphics&, Ball);

	static void ErasePlatform(HDC, Platform);
	static void EraseBall(HDC, Ball);
	static void EraseBrick(HDC, RECT);
};