#include <stdio.h>
#include <list>
#include <string>
#include <iterator>
#include <cstdlib>

#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "GameScreen.h"
#include "BallVectorDirection.h"
#include "PlatformVectorDirection.h"

Ball::Ball() : GameElement() {
	_width = sizeX / 3;
	_height = sizeY;
}

Ball::Ball(float x, float y, float startSpeed) : GameElement() {
	_width = sizeY;
	_height = sizeY;

	_x = x;
	_y = y;

	_speed = startSpeed;
}

void Ball::Move(float deltaTime) {
	_x += _dx * deltaTime;
	_y += _dy * deltaTime;
}

bool Ball::IsFell(int gameScreenHeight) {
	return _y + width() > gameScreenHeight;
}

int Ball::x() const { return _x; }
int Ball::y() const { return _y; }
int Ball::dx() const { return _dx; }
int Ball::dy() const { return _dy; }

int Ball::radius() const { return _radius; }
int Ball::width() const { return _width; }
int Ball::height() const { return _height; }

float Ball::speed() const { return _speed; }