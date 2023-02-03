#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

#ifndef M_PIF
# define M_PIF	3.14159265358979323846f
#endif


struct Vec2
{
	Vec2(float _x = 0, float _y = 0) : x{ _x }, y{ _y } {};
	//Vec2(int _x, int _y) : x{(float)_x}, y{(float)_y} {};
	Vec2(sf::Vector2f _v) : x{ _v.x }, y{ _v.y } {};
	float x;
	float y;

	Vec2 operator+ (Vec2 other) { return Vec2(other.x + x, other.y + y); }
	Vec2 operator- (Vec2 other) { return Vec2(other.x - x, other.y - y); }
	Vec2 operator+= (Vec2 other) { x += other.x; y += other.y; return *this; }
	Vec2 operator-= (Vec2 other) { x -= other.x; y -= other.y; return *this; }
	Vec2 operator* (Vec2 other) const { return Vec2(x * other.x, y * other.y); }


	Vec2 operator* (float _m) const { return Vec2(x * _m, y * _m); }
	Vec2 operator/ (float _m) { return Vec2(x / _m, y / _m); }

	operator sf::Vector2f() const { return sf::Vector2f(x, y);  }

	float length() const { return sqrt(x*x + y*y); };

	static const Vec2 nullV;
	static const Vec2 UP;
	static const Vec2 DOWN;
	static const Vec2 LEFT;
	static const Vec2 RIGHT;
};

std::ostream& operator<< (std::ostream& out, const Vec2& obj);

std::ostream& operator<< (std::ostream& out, const Vec2&& obj);

float angleBetween(Vec2 target, Vec2 base);