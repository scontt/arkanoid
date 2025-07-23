#include "Drawer.h"
#include <windows.h>
#include <gdiplus.h>

#include "Ball.h"
#include "Brick.h"

#pragma comment(lib, "gdiplus.lib")

void Drawer::DrawBrick(HWND hWnd, PAINTSTRUCT ps, HDC hdc, Brick brick) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillRectangle(&brush, brick.x(), brick.y(), brick.width(), brick.height());

	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
	g.DrawRectangle(&pen, brick.x(), brick.y(), brick.width(), brick.height());
}

void Drawer::DrawBall(HWND hWnd, PAINTSTRUCT ps, HDC hdc, Ball ball) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillRectangle(&brush, ball.currentX(), ball.currentY(), ball.width(), ball.height());

	/*Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
	g.DrawRectangle(&pen, ball.lastX(), ball.lastY(), ball.width(), ball.height());*/
}

void Drawer::DrawPlatform(HWND hWnd, PAINTSTRUCT ps, HDC hdc, Platform platform) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
	g.FillRectangle(&brush, platform.currentX(), platform.y(), platform.width(), platform.height());

	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
	g.DrawRectangle(&pen, platform.currentX(), platform.y(), platform.width(), platform.height());
}

void Drawer::ErasePlatform(HWND hWnd, PAINTSTRUCT ps, HDC hdc, Platform platform) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	g.FillRectangle(&brush, platform.lastX(), platform.y(), platform.width(), platform.height());
}

void Drawer::EraseBall(HWND hWnd, PAINTSTRUCT ps, HDC hdc, Ball ball) {
	Gdiplus::Graphics g(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	g.FillRectangle(&brush, ball.lastX(), ball.lastY(), ball.width(), ball.height());
}