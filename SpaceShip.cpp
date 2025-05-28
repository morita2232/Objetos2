#include "SpaceShip.h"

//CONSTRUCTOR: inicializa la nave del jugador con valores por defecto
SpaceShip::SpaceShip(SDL_Renderer* rend, InputManager* inputManager)
	: GameObject(rend, Vector2Int(0, 0), Vector2Int(30, 40)) // Sprite inicial
{
	input = inputManager;      // Referencia al gestor de input

	lives = 3;                 // Número de vidas inicial

	// Posicionamos la nave en el centro de la pantalla
	position = INITIAL_POSITION;

	velocity = Vector2(0, 0);         // Velocidad inicial nula
	direction = Vector2(0, 0);        // Dirección inicial
	accelerationFactor = 400.0f;      // Aceleración al pulsar tecla
	linearDrag = 0.90f;               // Resistencia al movimiento lineal
	angularDrag = 0.95f;              // Resistencia al giro
	angularVelocity = 0.0f;           // Velocidad de giro inicial
}

//UPDATE: se ejecuta cada frame, controla movimiento, giro, colisiones y respawn
void SpaceShip::Update(float dt) {

	const float SCREEN_WIDTH = SCREENW;
	const float SCREEN_HEIGHT = SCREENH;

	// Dirección basada en la rotación actual (convertida a radianes)
	float radians = (zRotation - NINENTYDGS) * (M_PI / ONEEIGHTYDGS);
	direction = Vector2(cos(radians), sin(radians));

	// Si se pulsa la flecha hacia arriba, la nave acelera en su dirección actual
	if (input->GetKey(SDLK_UP, HOLD)) {
		velocity += direction * accelerationFactor * dt;
	}

	// Aplicamos resistencia al movimiento (drag)
	velocity = velocity * pow(linearDrag, dt);

	// Control de rotación con flechas izquierda y derecha
	float angularSpeed = ANGULARSPD;
	if (input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity += angularSpeed * dt;
	}
	if (input->GetKey(SDLK_LEFT, HOLD)) {
		angularVelocity -= angularSpeed * dt;
	}

	// Si no se está girando, se aplica el drag angular
	if (!input->GetKey(SDLK_LEFT, HOLD) && !input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity *= pow(angularDrag, dt);
	}

	// Limitamos la velocidad angular máxima
	const float maxAngularVelocity = ONEEIGHTYDGS;
	if (angularVelocity > maxAngularVelocity)
		angularVelocity = maxAngularVelocity;
	else if (angularVelocity < -maxAngularVelocity)
		angularVelocity = -maxAngularVelocity;

	// Limitamos la velocidad lineal máxima
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > MAXSPEED) {
		velocity = (velocity * (1.0f / speed)) * MAXSPEED;
	}

	// Aplicamos el movimiento y la rotación
	position += velocity * dt;
	zRotation += angularVelocity * dt;

	// Lógica de respawn y parpadeo tras perder una vida
	if (respawning) {
		respawnTimer += dt;
		blinkTimer += dt;

		// Hace que la nave parpadee alternando visibilidad
		if (blinkTimer >= BLINK_INTERVAL) {
			visible = !visible;
			blinkTimer = 0.0f;
		}

		// Si termina el tiempo de respawn, vuelve a la normalidad
		if (respawnTimer >= RESPAWN_DURATION) {
			respawning = false;
			visible = true;
		}
	}

	// Wraparound de pantalla: si se sale por un borde, aparece por el contrario
	if (position.x < -sizeToClamp.x) position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH)   position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT)  position.y = -sizeToClamp.y;
}

//RENDER: solo dibuja la nave si está visible (por ejemplo, no en parpadeo de respawn)
void SpaceShip::Render(SDL_Renderer* renderer) {
	if (!visible) return;
	GameObject::Render(renderer);
}

//StartRespawn: inicia el estado de respawn (tras perder vida)
void SpaceShip::StartRespawn() {
	respawning = true;
	respawnTimer = 0.0f;
	blinkTimer = 0.0f;
	visible = false;

	// Reposicionamos al centro de la pantalla
	position = INITIAL_POSITION;

	// Reiniciamos velocidad y rotación
	velocity = Vector2(0, 0);
	angularVelocity = 0.0f;
	zRotation = 0.0f;
}

//IsRespawning: devuelve si la nave está actualmente en respawn
bool SpaceShip::IsRespawning() const {
	return respawning;
}