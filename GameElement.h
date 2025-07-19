class GameElement {
protected:
	int sizeX;
	int sizeY;
	const int RGB = 3;

public:
	GameElement() {
		sizeX = 35;
		sizeY = 18;
	}

	int getSizeX() const { return sizeX; }
	int getSizeY() const { return sizeY; }
};