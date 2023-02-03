#pragma once

#include "Object.h"

class Controller : public GObject
{
public:
	Controller(Vec2 _pos = Vec2::nullV, Vec2 _size = Vec2::nullV)
		: GObject{ _pos,_size,true } {};

	Controller(float _px, float _py, float _sx, float _sy) : Controller(Vec2(_px, _py), Vec2(_sx, _sy)) {};

	void move(Vec2 _tran) { pos += _tran; }
	void addSpeed(Vec2 _av) { velocity += _av; }
	//void update

	Vec2 velocity;
};