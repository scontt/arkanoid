#pragma once

class Point {
private:
	float _x, _y;

public:
	Point(float x, float y) {
		_x = x;
		_y = y;
	}

	float x() const { return _x; }
	float y() const { return _y; }
};