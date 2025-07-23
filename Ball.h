#include "GameElement.h"
#include "Platform.h"
#include "Brick.h"
#include <windows.h>
#include <stdio.h>
#include <list>
#include "HitStates.h"

#pragma once

class Ball : public GameElement {
private:
	int _ballWidth, _ballHeight;
	int _x1, _y1;
	int _x0, _y0;
	float _speed;
	float xVector, yVector;

public:
	Ball();
	RECT Move(int x, int y);
	void Initialize(float);
	bool IsFell(int gameScreenHeight);
	void CheckPlatformCollition(Platform platform);
	bool CheckBrickCollition(std::list<Brick>& bricks, int vectorSize);
	void CheckWallsColliton();

	int lastX();
	int lastY();
	int currentX();
	int currentY();
	int width();
	int height();
	float speed();
};