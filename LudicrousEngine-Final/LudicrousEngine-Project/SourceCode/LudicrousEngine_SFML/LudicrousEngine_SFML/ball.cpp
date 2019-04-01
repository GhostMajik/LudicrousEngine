#pragma once
#include "ball.h"

float magnitude(const sf::Vector2f &v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float distance(const sf::Vector2f &v, const sf::Vector2f &w)
{
	return magnitude(v - w);
}

float angle(const sf::Vector2f &v)
{
	if (v.x == 0)
	{
		if (v.y < 0) return 270;
		return 90;
	}

	float angle = atan(v.y / v.x) * 180 / PI;       
	if (v.x < 0) angle += 180;
	else if (v.y < 0) angle += 360;              

	return angle;
}

float dot(const sf::Vector2f &v, const sf::Vector2f &w)
{
	return v.x*w.x + v.y*w.y;
}

void set_magnitude(sf::Vector2f &v, float len)
{
	float curr = magnitude(v);
	if (curr == 0) v = sf::Vector2f(0, len);
	else v *= len / curr;
}

void set_vector_angle(sf::Vector2f &v, float ang)
{
	float curr = magnitude(v);
	v.x = curr * cos(ang*PI / 180);
	v.y = curr * sin(ang*PI / 180);
}

sf::Vector2f proj(const sf::Vector2f &v, const sf::Vector2f &w)
{
	if (dot(w, w) == 0)
	{
		handle_error(0);
		return v;
	}
	return dot(w, v) / dot(w, w) * w;
}


Wall::Wall()
{
	*this = Wall(sf::Vector2f(20, 20), sf::Vector2f(30, 30), thDefault, wcDefault);
}

Wall::Wall(sf::Vector2f p1, sf::Vector2f p2)
{
	*this = Wall(p1, p2, thDefault, wcDefault);
}

Wall::Wall(sf::Vector2f p1, sf::Vector2f p2, float th)
{
	*this = Wall(p1, p2, th, wcDefault);
}

Wall::Wall(sf::Vector2f p1, sf::Vector2f p2, float th, sf::Color c)
{
	pt1 = p1;
	pt2 = p2;

	if (th < 0) thickness = -th;
	else if (th == 0) thickness = thDefault;
	else thickness = th;

	fill_color = c;

	update_vectors();
}

Wall::Wall(sf::Vector2f p1, const Wall& w)
{
	*this = Wall(p1, p1 + w.v_l, w.thickness, w.fill_color);
}

Wall::Wall(sf::Vector2f p1, sf::Vector2f p2, const Wall& w)
{
	*this = Wall(p1, p2, w.thickness, w.fill_color);
}

void Wall::update_vectors()
{
	v_l = pt2 - pt1;

	v_th = sf::Vector2f(0, thickness);
	if (magnitude(v_l) > 0) set_vector_angle(v_th, angle(v_l) + 90);
}

sf::RectangleShape Wall::get_rectangleShape() const
{
	sf::RectangleShape rect(sf::Vector2f(get_length(), 2 * thickness));
	rect.setOrigin(0, thickness);
	rect.setPosition(pt1);
	rect.setRotation(angle(v_l));
	rect.setFillColor(fill_color);

	return rect;
}

void Wall::set_points(sf::Vector2f p1, sf::Vector2f p2)
{
	pt1 = p1;
	pt2 = p2;

	update_vectors();
}

void Wall::set_thickness(float th)
{
	if (th < 0) thickness = -th;
	else if (th == 0) thickness = thDefault;
	else thickness = th;

	set_magnitude(v_th, thickness);
}

sf::Vector2f Wall::relative_coordinates(const sf::Vector2f &pt) const
{
	sf::Vector2f rel = pt - pt1;
	return sf::Vector2f(dot(rel, v_l) / magnitude(v_l), dot(rel, v_th) / thickness);
}

bool Wall::contains(const sf::Vector2f &pt) const
{
	sf::Vector2f coords = relative_coordinates(pt);

	return (coords.x >= 0 && coords.x <= get_length() && coords.y >= -thickness && coords.y <= thickness);
}

sf::Vector2f Wall::nearest_corner(const sf::Vector2f &rel_pt) const
{
	if (rel_pt.x <= get_length() / 2)
	{
		if (rel_pt.y >= 0) return pt1 + v_th;
		else return pt1 - v_th;
	}
	else
	{
		if (rel_pt.y >= 0) return pt2 + v_th;
		else return pt2 - v_th;
	}

}


Ball::Ball()
{
	*this = Ball(sf::Vector2f(50, 50), sf::Vector2f(50, 50));
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel)
{
	*this = Ball(pos, vel, rDefault, cDefault, dDefault);
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, float r)
{
	*this = Ball(pos, vel, r, cDefault, dDefault);
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, float r, sf::Color c)
{
	*this = Ball(pos, vel, r, c, dDefault);
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, float r, sf::Color c, float dens)
{
	if (r < 0) r = -r;               
	if (r > MAX_RADIUS) r = MAX_RADIUS;
	if (dens < 0) dens = -dens;

	position = pos;
	velocity = vel;
	radius = r;

	if (get_speed() > MAX_SPEED) set_speed(MAX_SPEED);

	fill_color = c;
	density = dens;

	mass = dens * 4.0 / 3.0 * PI * r*r*r;
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, float r, Material mat)
{
	

	switch (mat)
	{
	case WOOD:
		*this = Ball(pos, vel, r, sf::Color::Magenta, 0.70);
		break;

	case STONE:
		*this = Ball(pos, vel, r, sf::Color::White, 2.00);
		break;

	case IRON:
		*this = Ball(pos, vel, r, sf::Color::Black, 7.87);
		break;

	case GOLD:
		*this = Ball(pos, vel, r, sf::Color::Yellow, 19.32);
		break;

	case DEF:
	default:
		*this = Ball(pos, vel, r, sf::Color::Green, dDefault);
		break;
	}
}

Ball::Ball(sf::Vector2f pos, float spd, float ang)
{
	*this = Ball(pos, spd, ang, rDefault, cDefault, dDefault);
}

Ball::Ball(sf::Vector2f pos, float spd, float ang, float r)
{
	*this = Ball(pos, spd, ang, r, cDefault, dDefault);
}

Ball::Ball(sf::Vector2f pos, float spd, float ang, float r, sf::Color c)
{
	*this = Ball(pos, spd, ang, r, c, dDefault);
}

Ball::Ball(sf::Vector2f pos, float spd, float ang, float r, sf::Color c, float dens)
{
	float velx = spd * cos(ang*PI / 180);
	float vely = spd * sin(ang*PI / 180);

	*this = Ball(pos, sf::Vector2f(velx, vely), r, c, dens);
}

Ball::Ball(sf::Vector2f pos, float spd, float ang, float r, Material mat)
{
	float velx = spd * cos(ang*PI / 180);
	float vely = spd * sin(ang*PI / 180);

	*this = Ball(pos, sf::Vector2f(velx, vely), r, mat);
}

Ball::Ball(sf::Vector2f pos, const Ball &b)
{
	*this = Ball(pos, b.velocity, b.radius, b.fill_color, b.density);
}

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel, const Ball &b)
{
	*this = Ball(pos, vel, b.radius, b.fill_color, b.density);
}

Ball::Ball(sf::Vector2f pos, float spd, float ang, const Ball &b)
{
	*this = Ball(pos, spd, ang, b.radius, b.fill_color, b.density);
}

float Ball::get_speed() const
{
	return magnitude(velocity);
}

float Ball::get_angle() const
{
	return angle(velocity);
}

sf::CircleShape Ball::get_circleShape() const
{
	sf::CircleShape circ(radius, 24);
	circ.setPosition(position.x - radius, position.y - radius);     
	circ.setFillColor(fill_color);
	return circ;
}

void Ball::set_position(sf::Vector2f pos)
{
	position = pos;
}

void Ball::set_position(float a, float b)
{
	position = sf::Vector2f(a, b);
}

void Ball::set_velocity(sf::Vector2f vel)
{
	velocity = vel;
	float spd = get_speed();
	if (spd > MAX_SPEED) set_speed(MAX_SPEED);
}

void Ball::set_velocity(float a, float b)
{
	set_velocity(sf::Vector2f(a, b));
}

void Ball::set_radius(float r)
{
	if (r < 0) r = -r;
	if (r > MAX_RADIUS) r = MAX_RADIUS;
	radius = r;
	mass = density * 4.0 / 3.0 * PI * r*r*r;
}

void Ball::set_speed(float sp)
{
	if (sp > MAX_SPEED) sp = MAX_SPEED;
	else if (sp < -MAX_SPEED) sp = -MAX_SPEED;

	set_magnitude(velocity, sp);
}

void Ball::set_angle(float ang)
{
	set_vector_angle(velocity, ang);
}

bool Ball::is_colliding_with(const Ball &b) const
{
	if (distance(position, b.position) - (radius + b.radius) < 0) return true;
	return false;
}

bool Ball::is_colliding_with(const sf::Vector2f &point) const
{
	if (distance(position, point) < radius) return true;
	return false;
}

bool Ball::is_colliding_with(const Wall &w) const
{
	sf::Vector2f coords = w.relative_coordinates(position);

	if (coords.y <= -w.get_thickness() - radius || coords.y >= w.get_thickness() + radius) return false;
	if (coords.x <= -radius || coords.x >= w.get_length() + radius) return false;

	if (coords.x >= 0 && coords.x <= w.get_length()) return true;
	else if (coords.y >= -w.get_thickness() && coords.y <= w.get_thickness()) return true;
	else
	{
		sf::Vector2f corner = w.nearest_corner(coords);
		if (distance(position, corner) < radius) return true;
	}
	return false;
}

bool Ball::is_colliding_with(const sf::RectangleShape &rect) const
{
	sf::Vector2f rectPos = sf::Vector2f(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
	if (distance(position, rect.getPosition() + rectPos) - (radius + rect.getSize().x / 2) < 0) {
		return true;
	}
	return false;
}

void Ball::bounce(float ang)
{
	float alpha = get_angle();
	float beta = ang + 90;            

	set_angle(2 * beta - alpha);
}

void Ball::bounce_off_wall(const Wall &w)
{
	sf::Vector2f coords = w.relative_coordinates(position);

	if (coords.y <= -w.get_thickness() - radius || coords.y >= w.get_thickness() + radius) return;
	if (coords.x <= -radius || coords.x >= w.get_length() + radius) return;

	if (coords.x >= 0 && coords.x <= w.get_length())                     
	{
		if (!STUTTER_PROTECTION || dot(velocity, w.get_thick_vector()) * coords.y <= 0)
			bounce(angle(w.get_thick_vector()));
	}
	else
	{
		if (coords.y >= -w.get_thickness() && coords.y <= w.get_thickness())     
		{
			if (!STUTTER_PROTECTION || dot(velocity, w.get_length_vector()) * coords.x <= 0)
				bounce(angle(w.get_length_vector()));
		}
		else
		{
			sf::Vector2f corner = w.nearest_corner(coords);

			if (distance(position, corner) < radius)                      
			{
				if (!STUTTER_PROTECTION || dot(velocity, position - corner) <= 0)
					bounce(angle(position - corner));
			}
		}
	}
}

void Ball::update_position(sf::Time dT)
{
	float dt = dT.asSeconds();

	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void collide(Ball &ball1, Ball &ball2)
{
	float m = ball1.mass;
	float n = ball2.mass;

	sf::Vector2f v1 = ball1.velocity;
	sf::Vector2f v2 = ball2.velocity;

	sf::Vector2f x1 = ball1.position;
	sf::Vector2f x2 = ball2.position;

	if (x1 != x2)
	{
		if (!STUTTER_PROTECTION || dot(v2 - v1, x2 - x1) < 0)
		{
			sf::Vector2f pr = proj(v2 - v1, x2 - x1);
			ball1.velocity = v1 + 2 * n / (m + n)*pr;
			ball2.velocity = v2 - 2 * m / (m + n)*pr;
		}
	}
}

void collide(Ball &b, Wall &w)
{
	b.bounce_off_wall(w);
}

void collide(Ball &ball, sf::RectangleShape &rect)
{
	float m1 = ball.mass;
	float m2 = 100;

	sf::Vector2f ballVelocity = ball.velocity;
//	sf::Vector2f playerVelocity = rect.getPosition();

	sf::Vector2f ballPos = ball.position;
	sf::Vector2f playerPos = rect.getPosition();

	if (ballPos != playerPos) {
		if (STUTTER_PROTECTION)
		{
			//sf::Vector2f pr = proj(playerVelocity - ball.velocity, playerPos - ballPos);
			//ball.velocity = ball.velocity + 2 * m2 / (m1 + m2)*pr;
			ball.velocity = ball.velocity * -1.0f;
		}
	}
}

int handle_error(int code)
{
	return code;
}