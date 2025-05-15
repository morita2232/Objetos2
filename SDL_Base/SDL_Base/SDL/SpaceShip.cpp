#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* rend, InputManager* inputManager):GameObject(rend, new Vector2Int(0, 0), new Vector2Int(30, 40)) {

	input = inputManager;

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
	const float SCREEN_WIDTH = 800.0f;
	const float SCREEN_HEIGHT = 600.0f;

	//Calcular dirección desde la rotación
	float radians = (zRotation - 90.0f) * (M_PI / 180.0f);
	direction = Vector2(cos(radians), sin(radians));


	//Aplicar aceleración si la flecha de arriba está presionada
	if (input->GetKey(SDLK_UP, HOLD)) {
		velocity += direction * accelerationFactor * dt;
	}

	//Aplicar drag lineal al movimiento lineal
	velocity = velocity * pow(linearDrag, dt);

	//Aplicar rotación si están la flecha izquierda o derecha presionadas
	float angularSpeed = 540.f;

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
	const float maxAngularVelocity = 180.f;
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

	//Wrap de pantalla
	if (position.x < -sizeToClamp.x) position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH) position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT) position.y = -sizeToClamp.y;
}
