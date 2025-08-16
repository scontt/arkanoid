#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <iterator>

#include "Drawer.h"
#include "Ball.h"
#include "Brick.h"

#pragma comment(lib, "gdiplus.lib")

void Drawer::DrawBrick(HDC hdc, Brick* brick) {
	if (brick->isDestroyed())
		return;

	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillRectangle(&brush, brick->x(), brick->y(), brick->width(), brick->height());

	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
	g.DrawRectangle(&pen, brick->x(), brick->y(), brick->width(), brick->height());
}

void Drawer::DrawBall(HDC hdc, Ball ball) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillEllipse(&brush, ball.x(), ball.y(), ball.width(), ball.height());
}

void Drawer::DrawPlatform(HDC hdc, Platform platform) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillRectangle(&brush, platform.x(), platform.y(), platform.width(), platform.height());

	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
	g.DrawRectangle(&pen, platform.x(), platform.y(), platform.width(), platform.height());
}

void Drawer::DrawTrail(Gdiplus::Graphics& graphics, Ball ball) {
	float direction = atan2f(ball.dy(), ball.dx());
	Gdiplus::Pen pen(Gdiplus::Color(128, 255, 255, 255), 1.0f);
}


void Drawer::ErasePlatform(HDC hdc, Platform platform) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	g.FillRectangle(&brush, platform.x(), platform.y(), platform.width(), platform.height());
}

void Drawer::EraseBall(HDC hdc, Ball ball) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	g.FillRectangle(&brush, ball.x(), ball.y(), ball.width(), ball.height());
}

void Drawer::EraseBrick(HDC hdc, RECT clearRect) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	int x = clearRect.left;
	int y = clearRect.top;
	int width = clearRect.right - clearRect.left;
	int height = clearRect.bottom - clearRect.top;
	g.FillRectangle(&brush, x, y, width, height);
}