#include "Platform.h"
#include "GameElement.h"

Platform::Platform() : GameElement() {
	
}

void Platform::Move(int _x) {
	x = _x - width / 2;
}