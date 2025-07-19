#include "GameElement.h"

class Ball : public GameElement {
private:
	int ballXsize, ballYsize;
	float speed = 2.0f;
	float _x1 = 0, _y1 = 0; // текущие координаты
	float _x0 = 0, _y0 = 0; // предыдущие координаты
	float xVector = 0, yVector = 0;

public:
	Ball();
	void Move();
	void Initialize(float x0, float y0);
	bool IsFell(float gameScreenHeight);
	int Collide(float );
};