#pragma once

// --- Configuración general ---
#define FPSNUM 60
#define FTNUM 1.0f
#define HALF 2.f

// --- Pantalla ---
#define SCREENW 800.0f
#define SCREENH 600.0f
#define SCREENLIMIT 10

// --- Movimiento y físicas ---
#define ANGULARSPD 540.0f
#define ONEEIGHTYDGS 180.0f
#define NINENTYDGS 90.0f
#define COOLDOWN 0.2f
#define MAXSPEED 250.0f

// --- Balas / proyectiles ---
#define PROJECTILE_SIZE 8
#define PROJECTILEWANDH 6 // usado para render básico

// --- Asteroides (puntuación) ---
#define SCORE_BIG_ASTEROID 50
#define SCORE_MEDIUM_ASTEROID 30
#define SCORE_SMALL_ASTEROID 20

// --- Enemigos ---
#define SCORE_ENEMY 150
#define ENEMY_SPAWN_INTERVAL 15.0f
#define ENEMYSHIP_SIZE_X 255
#define ENEMYSHIP_SIZE_Y 125

// --- Nave / respawn ---
#define RESPAWN_DURATION 3.0f
#define BLINK_INTERVAL 0.2f
#define INITIAL_POSITION Vector2(SCREENW / 2.0f, SCREENH / 2.0f)

// --- Cálculos ---
#define VELOCITY_RAND rand() % 100 - 50
#define DIRECTION_RAND rand() % 100 - 50


// -------------------- Vector2 --------------------
class Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	float Magnitude() const {
		return sqrt(x * x + y * y);
	}

	Vector2 operator +(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator *(float other) const  {
		return Vector2(x * other, y * other);
	}

	Vector2 operator *(Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}
	
	Vector2& operator +=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}


};

// -------------------- Vector2Int --------------------
class Vector2Int {

public:
	int x;
	int y;

	Vector2Int() { x = 0; y = 0; }
	Vector2Int(int _x, int _y) { x = _x; y = _y; }

	Vector2Int operator +(Vector2Int& other) {
		return Vector2Int(x + other.x, y + other.y);
	}

	Vector2Int& operator=(const Vector2Int& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	bool operator ==(const Vector2Int& other) {
		return x == other.x && y == other.y;
	}

};