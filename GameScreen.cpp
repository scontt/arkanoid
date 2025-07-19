#include "GameScreen.h"
#include "Brick.h"

void GameScreen::Fill(Brick brick) {
	for (size_t i = 0; i < screenXbrickSize; i++)
	{
		for (size_t i = 0; i < screenYbrickSize; i++)
		{
			bricks.push_back(brick);
		}
	}
}