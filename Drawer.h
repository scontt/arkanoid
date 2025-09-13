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
	static void DrawBrick(HDC hdc, Brick* brick) {

		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		g.FillRectangle(&brush, brick->x(), brick->y(), brick->width(), brick->height());

		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
		g.DrawRectangle(&pen, brick->x(), brick->y(), brick->width(), brick->height());
	}

	static void DrawBall(HDC hdc, Ball ball) {
		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		g.FillEllipse(&brush, ball.x(), ball.y(), ball.diameter(), ball.diameter());

		/*Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
		g.DrawRectangle(&pen, ball.lastX(), ball.lastY(), ball.width(), ball.height());*/
	}

	static void DrawPlatform(HDC hdc, Platform platform) {
		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0));
		g.FillRectangle(&brush, platform.currentX(), platform.y(), platform.width(), platform.height());

		Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
		g.DrawRectangle(&pen, platform.currentX(), platform.y(), platform.width(), platform.height());
	}

	static void DrawTrail(Gdiplus::Graphics& graphics, Ball ball) {
		float direction = atan2f(ball.dy(), ball.dx());
		Gdiplus::Pen pen(Gdiplus::Color(128, 255, 255, 255), 1.0f);

		/*for (size_t i = 0; i < 5; ++i) {
			Point pos = ball.trail[i];
			float alpha = 255 * (1.0f - static_cast<float>(i) / ball.trail.size());
			pen.SetColor(Gdiplus::Color(static_cast<BYTE>(alpha), 255, 255, 255));

			for (int p = -10 / 2; p <= 10 / 2; ++p) {
				float angle = direction + (p * (3.14159f / 10));
				float px = pos.X + ball.radius() * cosf(angle);
				float py = pos.Y + ball.radius() * sinf(angle);
				graphics.DrawLine(&pen, px - 0.5f, py, px + 0.5f, py);
			}
		}*/
	}


	static void ErasePlatform(HDC hdc, Platform platform) {
		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
		g.FillRectangle(&brush, platform.lastX(), platform.y(), platform.width(), platform.height());
	}

	static void EraseBall(HDC hdc, Ball ball) {
		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
		g.FillRectangle(&brush, ball.x(), ball.y(), ball.diameter(), ball.diameter());
	}

	static void EraseBrick(HDC hdc, RECT clearRect) {
		Gdiplus::Graphics g(hdc);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
		int x = clearRect.left;
		int y = clearRect.top;
		int width = clearRect.right - clearRect.left;
		int height = clearRect.bottom - clearRect.top;
		g.FillRectangle(&brush, x, y, width, height);
	}
};