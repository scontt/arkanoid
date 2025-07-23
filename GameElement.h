#pragma once

class GameElement {
protected:
	static const int sizeX = 80;
	static const int sizeY = 18;

public:
	GameElement() {}

	static int getSizeX() { return sizeX; }
	static int getSizeY() { return sizeY; }
};