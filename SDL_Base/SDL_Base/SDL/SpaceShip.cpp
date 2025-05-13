#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* rend, InputManager* inputManager):GameObject(rend, new Vector2Int(0, 0), new Vector2Int(30, 40)) {

	input = inputManager;

	velocity = Vector2(0, 0);
	acceleration = Vector2(0, 0);
	direction = Vector2(0, 0);

	angularVelocity = 0.f;
	accelerationFactor = 0.25f;
	linearDrag = 0.98f;
	angularDrag = 0.98f;
	maxSpeed = 0.5f;

}

void SpaceShip::Update(float dt) {

	const float SCREEN_WIDTH = 800.0f;
	const float SCREEN_HEIGHT = 600.0f;

	// Wrap horizontal
	if (position.x < -sizeToClamp.x) position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH) position.x = -sizeToClamp.x;

	// Wrap vertical
	if (position.y < -sizeToClamp.y) position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT) position.y = -sizeToClamp.y;

	float radians = zRotation * (M_PI / 180.0f);
	direction = Vector2(cos(radians), sin(radians));

	if (input->GetKey(SDLK_UP, HOLD)) {

		velocity += direction * accelerationFactor * dt;

	}

	velocity = velocity * pow(linearDrag, dt);

	float angularSpeed = 540.f;

	if (input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity += angularSpeed * dt;
	}
	
	if (input->GetKey(SDLK_LEFT, HOLD)) {
		angularVelocity -= angularSpeed * dt;
	}

	if (!input->GetKey(SDLK_LEFT, HOLD) && !input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity *= pow(angularDrag, dt);
	}


	//printf("angularVelocity: %.2f\n", angularVelocity);

	const float maxAngularVelocity = 180.f;
	if (angularVelocity > maxAngularVelocity)
		angularVelocity = maxAngularVelocity;
	else if (angularVelocity < -maxAngularVelocity)
		angularVelocity = -maxAngularVelocity;


	zRotation += angularVelocity * dt;
	position += velocity * dt;

	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

	if (speed > maxSpeed) {
		
		velocity = Vector2(velocity.x / speed, velocity.y / speed) * maxSpeed;

	}

}