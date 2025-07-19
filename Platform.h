#include "GameElement.h"

class Platform : public GameElement {
public:
	const static int width = 100;
	const static int height = 15;
	const static int hitbox = 5;

	int x, y;

	Platform();
	void Move(int x);
	void Draw();
};