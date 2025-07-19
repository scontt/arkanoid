#include "GameElement.h"

class Brick : GameElement {
private:
	int _brickWidth, _brickHeight, _brickLevel;
public:
	Brick(int level);
	bool isHit(int ballX, int ballY);

	int width();
	int height();
};