#include "GameScreen.h"
#include "Brick.h"
#include "Drawer.h"

#include <windows.h>
#include <iterator>

GameScreen::GameScreen() {}

int GameScreen::_screenXbrickCount = 0;
int GameScreen::_screenYbrickCount = 0;

int GameScreen::_screenHeight = 0;
int GameScreen::_screenWidth = 0;
int GameScreen::_halfHeight;
int GameScreen::_halfWidth;

GameScreen::GameScreen(int width, int height) {
	GameScreen::_screenHeight = height;
	GameScreen::_screenWidth = width;
	int a = Brick::width();

	GameScreen::_screenXbrickCount = width / Brick::width();
	GameScreen::_screenYbrickCount = height / Brick::height() / 3;

	GameScreen::_halfHeight = height / 2;
	GameScreen::_halfWidth = width / 2;
}

void GameScreen::Fill(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::list<Brick>& bricks) {
	std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		Drawer::DrawBrick(hWnd, ps, hdc, brick);
	}
}

void GameScreen::Clear(HWND hWnd, HDC hdc, PAINTSTRUCT ps, RECT clearRect) {
	/*std::list<Brick>::iterator brick;
	for (brick = bricks.begin(); brick != bricks.end(); brick++)
	{
		Drawer::EraseBrick(hWnd, ps, hdc, *brick);
	}*/

	Drawer::EraseBrick(hWnd, ps, hdc, clearRect);
}

int GameScreen::width() { return _screenWidth; }
int GameScreen::height() { return _screenHeight; }
int GameScreen::halfWidth() { return GameScreen::_halfWidth; }
int GameScreen::halfHeight() { return GameScreen::_halfHeight; }


int x = 0;
int y = 0;