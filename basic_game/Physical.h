#pragma once

#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <vector>
#include <cmath>

#include "Object.h"
#include "MathEquations.h"

class Physical : public GObject
{
public:
	Physical(Vec2 _pos = Vec2::nullV, Vec2 _size = Vec2::nullV, bool isColidable = false, float _m = 0, Vec2 _v = Vec2::nullV, bool _grav = false)
		: GObject{true, _pos,_size,isColidable }, mass{ _m }, velocity{ _v }, gravity{ _grav }, nvelocity{_v} {};
	//Physical(float m, float _x, float _y) : Physical(m, _x, _y, 0, 0) {};  float xv=0, float yv=0

	Physical(bool col) : Physical(Vec2::nullV,Vec2::nullV,col) {};

	static Vec2 gravityAcc;
	static float gravityAng;
	virtual void updatePP(float deltaT); //predict position
	virtual void updateC(float deltaT, std::deque<GObject*>::iterator);
	virtual void updateP(float deltaT);

	static Vec2 setGravity(Vec2 &&_newG)
	{
		Physical::gravityAng = angleBetween(_newG, Vec2(0, 1));
		return gravityAcc = _newG;
	}

	void addVelocity(Vec2 av)
	{
		velocity += av;
		nvelocity += av;
	}

	bool gravity = false;

	Vec2 velocity;
	Vec2 nvelocity;
//protected:
	float mass;
	float boyancy = 0.42f;//1;//0.40f;
	Vec2 npos;

	bool isLockedX = false;
	bool isLockedY = false;
	
	//bool isColid = 0;
};

//float Physical::gravityAcc = 9.81f;
//std::vector<Physical*> Physical::colidable;

float kineticEnergy(const Physical&);
Vec2 momentum(const Physical&);
float potentialEnergy(const Physical&);

#endif // !PHYSICAL_H