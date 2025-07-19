#include "Brick.h"
#include <list>

class GameScreen {
private:
	static const int screenXbrickSize = 8;
	static const int screenYbrickSize = 8;

	float screenWidth, screenHeight;
	std::list<Brick> bricks;

public:
	void Fill(Brick brick);
	void Clear();

	float width();
	float height();
};