#include "Brick.h"

Brick::Brick(int level) : GameElement() {
	_brickHeight = sizeY;
	_brickWidth = sizeX;
	_brickLevel = level;
	unsigned int color[RGB] = { 255, 255, 255 };
}

bool Brick::isHit(int ballX, int ballY) {
	/*if (ballX >= brickX - hitbox && ballX < brickX + width + hitbox) {
		if (ballY >= brickY - hitbox && ballY < brickY + width + hitbox) {
			return true;
		}
	}
	return false;*/
}

int Brick::height() {
	return _brickHeight;
}

int Brick::width() {
	return _brickWidth;
}