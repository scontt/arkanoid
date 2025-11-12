#include <windows.h>
#include <gdiplus.h>
#include <string>
#pragma comment(lib, "gdiplus.lib")

#include "Brick.h"
#include "Platform.h"
#include "Ball.h"

#pragma once

static class Drawer {
public:
	static void DrawBrick(Gdiplus::Graphics& g, Brick* brick) {

		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		g.FillRectangle(&brush, brick->x(), brick->y(), brick->width(), brick->height());

		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
		g.DrawRectangle(&pen, brick->x(), brick->y(), brick->width(), brick->height());
	}

	static void DrawBall(Gdiplus::Graphics& g, Ball ball) {
		Gdiplus::SolidBrush brush(Gdiplus::Color(100, 0, 0, 0));
		g.FillEllipse(&brush, ball._x0, ball._y0, ball.diameter(), ball.diameter());

		Gdiplus::Pen pen(Gdiplus::Color(100, 255, 255, 255));
		g.DrawEllipse(&pen, ball._x0, ball._y0, ball.diameter(), ball.diameter());
	}

	static void DrawPlatform(Gdiplus::Graphics& g, Platform platform) {
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		g.FillRectangle(&brush, platform.currentX(), platform.y(), platform.width(), platform.height());

		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
		g.DrawRectangle(&pen, platform.currentX(), platform.y(), platform.width(), platform.height());
	}

	static void DrawPoint(Gdiplus::Graphics& g, int x, int y) {
		Gdiplus::SolidBrush brush(Gdiplus::Color(128, 255, 0, 0));
		g.FillEllipse(&brush, x, y, 2, 2);
	}
};