#include <list>
#include <windows.h>
#include <stdio.h>
#include "Brick.h"
#include <list>

#pragma once

class GameScreen {
private:
	static int screenXbrickCount;
	static int screenYbrickCount;

	static int _screenWidth, _screenHeight, _halfWidth, _halfHeight;

public:
	GameScreen();
	GameScreen(int width, int height);
	void Fill(HWND, HDC, PAINTSTRUCT, std::list<Brick> bricks);
	void Clear();

	static int width();
	static int height();
	static int halfWidth();
	static int halfHeight();
};