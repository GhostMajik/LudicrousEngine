#pragma once
#include <SFML/Graphics.hpp>

struct AABB
{
	sf::Vector2f bLeft;
	sf::Vector2f tRight;
};

class PhysicsRBody
{
public:
	PhysicsRBody(float mass, float bounciness, bool obeysGravity);
	~PhysicsRBody();

	void SetObeysGravity(bool obey);

	void SetMaxVelocity(sf::Vector2f maxVelocity);
	sf::Vector2f GetCurrentVelocity();
	void SetCurrentVelocity(sf::Vector2f currentVelocity);

	inline float GetMass() { return this->mass; }
	inline void SetMass(float value) { this->mass = value; }
	inline float GetBounciness() { return this->bounciness; }
	inline void SetBounciness(float value) { this->bounciness = value; }
	AABB GetAABB();
	void SetAABB();

	void Integrate(float dT);
	void AddForce(sf::Vector2f force);
	bool IsGrounded();

	void Awake();
	void Update();

private:
	sf::Sprite sprite;
	sf::IntRect rectShape;

	void LoadContent();

	float mass;					
	float bounciness;			
	bool obeysGravity;
	sf::Vector2f gravity;		

	sf::Vector2f maxVelocity;	

	sf::Vector2f currentVelocity; 

	bool grounded;

	sf::Vector2f totalForces;

	AABB aabb;

};
