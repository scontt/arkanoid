class TracePoint {
private:
	int _x, _y;

public:
	TracePoint(int x, int y) {
		_x = x;
		_y = y;
	}

	int x() const { return _x; }
	int y() const { return _y; }
};