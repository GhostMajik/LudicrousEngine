#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

const bool STUTTER_PROTECTION = true;     
										
const float PI = 3.1415926535897932;
const float MAX_SPEED = 2000;             
const float MAX_RADIUS = 500;

const sf::Color TAN = sf::Color(150, 130, 50);
const sf::Color GRAY = sf::Color(90, 90, 90);
const sf::Color GLD = sf::Color(255, 225, 40);

const float rDefault = 20;                           
const sf::Color cDefault = sf::Color::Red;           
const float dDefault = 1;                            

const float thDefault = 4;                           
const sf::Color wcDefault = sf::Color::Cyan;         

enum Material { WOOD, STONE, IRON, GOLD, DEF };      

float magnitude(const sf::Vector2f &v);
float distance(const sf::Vector2f &v, const sf::Vector2f &w);
float angle(const sf::Vector2f &v);
float dot(const sf::Vector2f &v, const sf::Vector2f &w);
void set_magnitude(sf::Vector2f &v, float len);
void set_vector_angle(sf::Vector2f &v, float ang);
sf::Vector2f proj(const sf::Vector2f &v, const sf::Vector2f &w);


class Wall
{
private:
	sf::Vector2f pt1;
	sf::Vector2f pt2;

	float thickness;            
								

	sf::Color fill_color;

	sf::Vector2f v_l;           
	sf::Vector2f v_th;          

	void update_vectors();

public:
	Wall();
	Wall(sf::Vector2f p1, sf::Vector2f p2);
	Wall(sf::Vector2f p1, sf::Vector2f p2, float th);
	Wall(sf::Vector2f p1, sf::Vector2f p2, float th, sf::Color c);
	Wall(sf::Vector2f p1, const Wall &w);
	Wall(sf::Vector2f p1, sf::Vector2f p2, const Wall &w);

	float get_length() const { return magnitude(v_l); }
	float get_thickness() const { return thickness; }
	sf::Vector2f get_pt1() const { return pt1; }
	sf::Vector2f get_pt2() const { return pt2; }
	sf::Vector2f get_length_vector() const { return v_l; }
	sf::Vector2f get_thick_vector() const { return v_th; }

	sf::RectangleShape get_rectangleShape() const;

	void set_points(sf::Vector2f p1, sf::Vector2f p2);
	void set_thickness(float th);

	sf::Vector2f relative_coordinates(const sf::Vector2f &pt) const;
	bool contains(const sf::Vector2f &pt) const;
	sf::Vector2f nearest_corner(const sf::Vector2f &rel_pt) const;
};


class Ball
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;

	float radius;               

	sf::Color fill_color;

	float density;            
	float mass;               

public:
	Ball();
	Ball(sf::Vector2f pos, sf::Vector2f vel);
	Ball(sf::Vector2f pos, sf::Vector2f vel, float r);
	Ball(sf::Vector2f pos, sf::Vector2f vel, float r, sf::Color c);
	Ball(sf::Vector2f pos, sf::Vector2f vel, float r, sf::Color c, float dens);
	Ball(sf::Vector2f pos, sf::Vector2f vel, float r, Material mat);

	Ball(sf::Vector2f pos, float spd, float ang);
	Ball(sf::Vector2f pos, float spd, float ang, float r);
	Ball(sf::Vector2f pos, float spd, float ang, float r, sf::Color c);
	Ball(sf::Vector2f pos, float spd, float ang, float r, sf::Color c, float dens);
	Ball(sf::Vector2f pos, float spd, float ang, float r, Material mat);

	Ball(sf::Vector2f pos, const Ball &b);
	Ball(sf::Vector2f pos, sf::Vector2f vel, const Ball &b);
	Ball(sf::Vector2f pos, float spd, float ang, const Ball &b);

	float getx() const { return position.x; }
	float gety() const { return position.y; }
	sf::Vector2f get_position() const { return position; }
	sf::Vector2f get_velocity() const { return velocity; }
	float get_radius() const { return radius; }

	float get_speed() const;
	float get_angle() const;
	virtual sf::CircleShape get_circleShape() const;

	void set_position(sf::Vector2f pos);
	void set_position(float, float);
	void set_velocity(sf::Vector2f vel);
	void set_velocity(float, float);
	void set_radius(float r);
	void set_speed(float sp);
	void set_angle(float ang);

	bool is_colliding_with(const Ball &b) const;
	bool is_colliding_with(const sf::Vector2f &point) const;
	bool is_colliding_with(const Wall &w) const;

	void bounce(float ang);
	void bounce_off_wall(const Wall &w);

	virtual void update_position(sf::Time dT);

	friend void collide(Ball &ball1, Ball &ball2);
	friend void collide(Ball &b, Wall &w);
};

int handle_error(int err_code);