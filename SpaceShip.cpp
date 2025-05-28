#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* rend, InputManager* inputManager):GameObject(rend, Vector2Int(0, 0), Vector2Int(30, 40)){

	input = inputManager;

	lives = 3;

	position = Vector2(SCREENW / 2.0f, SCREENH / 2.0f);

	//Velocidad actual
	velocity = Vector2(0, 0);

	//Direccion en la que apunta la nave
	direction = Vector2(0, 0);

	//Intensidad de aceleracion
	accelerationFactor = 400.0f;

	//Resistencia del movimiento
	linearDrag = 0.90f;

	//Resistencia de la rotacion
	angularDrag = 0.95f;

	//Velocidad maxima
	maxSpeed = 250.0f;

	//Velocidad de rotacion
	angularVelocity = 0.0f;

}

void SpaceShip::Update(float dt) {

	//Constantes de pantalla para el wraparound
	const float SCREEN_WIDTH = SCREENW;
	const float SCREEN_HEIGHT = SCREENH;

	//Calcular dirección desde la rotación
	float radians = (zRotation - NINENTYDGS) * (M_PI / ONEEIGHTYDGS);
	direction = Vector2(cos(radians), sin(radians));


	//Aplicar aceleración si la flecha de arriba está presionada
	if (input->GetKey(SDLK_UP, HOLD)) {
		velocity += direction * accelerationFactor * dt;
	}

	//Aplicar drag lineal al movimiento lineal
	velocity = velocity * pow(linearDrag, dt);

	//Aplicar rotación si están la flecha izquierda o derecha presionadas
	float angularSpeed = ANGULARSPD;

	if (input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity += angularSpeed * dt;
	}

	if (input->GetKey(SDLK_LEFT, HOLD)) {
		angularVelocity -= angularSpeed * dt;
	}

	//Aplicar drag angular si no se esta girando
	if (!input->GetKey(SDLK_LEFT, HOLD) && !input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity *= pow(angularDrag, dt);
	}

	//Limitar rotacion maxima
	const float maxAngularVelocity = ONEEIGHTYDGS;
	if (angularVelocity > maxAngularVelocity)
		angularVelocity = maxAngularVelocity;
	else if (angularVelocity < -maxAngularVelocity)
		angularVelocity = -maxAngularVelocity;

	//Limitar velocidad lineal
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed) {
		velocity = (velocity * (1.0f / speed)) * maxSpeed;
	}

	//Actualizar posición y rotación
	position += velocity * dt;
	zRotation += angularVelocity * dt;

	// --- Lógica de respawn/parpadeo ---
	if (respawning) {
		respawnTimer += dt;
		blinkTimer += dt;

		// Alternar visibilidad para el efecto parpadeo
		if (blinkTimer >= blinkInterval) {
			visible = !visible;
			blinkTimer = 0.0f;
		}

		// Fin del estado de respawn
		if (respawnTimer >= respawnDuration) {
			respawning = false;
			visible = true;
		}
	}


	//Wrap de pantalla
	if (position.x < -sizeToClamp.x) position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH) position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT) position.y = -sizeToClamp.y;
}

void SpaceShip::Render(SDL_Renderer* renderer) {
	if (!visible) {

		return;
	}


	GameObject::Render(renderer);
}

void SpaceShip::StartRespawn() {
	respawning = true;
	respawnTimer = 0.0f;
	blinkTimer = 0.0f;
	visible = false;

	// Reposicionar en el centro de la pantalla
	position = Vector2(SCREENW / 2.0f, SCREENH / 2.0f);

	// Reiniciar movimiento
	velocity = Vector2(0, 0);
	angularVelocity = 0.0f;

	// Reiniciar rotación
	zRotation = 0.0f;
}

bool SpaceShip::IsRespawning() const {
	return respawning;
}
