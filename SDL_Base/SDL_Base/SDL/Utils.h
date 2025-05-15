#pragma once

#define FPSNUM 60
#define FTNUM 1.0f
#define HALF 2.f
#define NINENTYDGS 90.0f
#define ONEEIGHTYDGS 180.0f
#define PROJECTILEWANDH 6
#define SCREENW 800.0f
#define SCREENH 600.0f
#define SCREENLIMIT 10
#define ANGULARSPD 540.0f
#define COOLDOWN 0.2f

class Vector2 {

public:
	float x;
	float y;

	//Constructores
	Vector2() { x = 0; y = 0; }
	Vector2(float _x, float _y) { x = _x; y = _y; }

	//Operador de suma
	Vector2 operator +(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	//Operador de multiplicacion escalar
	Vector2 operator *(float other) const  {
		return Vector2(x * other, y * other);
	}
	
	//Operador de multiplicacion componente a componente
	Vector2 operator *(Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}
	
	//Operdador de suma acumulativa
	Vector2& operator +=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
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