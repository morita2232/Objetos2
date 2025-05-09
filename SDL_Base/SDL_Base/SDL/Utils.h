#pragma once

class Vector2 {

public:
	float x;
	float y;

	Vector2() { x = 0; y = 0; }
	Vector2(float _x, float _y) { x = _x; y = _y; }

	Vector2 operator +(Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}

};

class Vector2Int {

public:
	int x;
	int y;

	Vector2Int() { x = 0; y = 0; }
	Vector2Int(int _x, int _y) { x = _x; y = _y; }

	Vector2Int operator +(Vector2Int& other) {
		return Vector2Int(x + other.x, y + other.y);
	}

};