#include "Physical.h"

#include <iostream>

Vec2 Physical::gravityAcc = Vec2(0,-9.81f);
float Physical::gravityAng = M_PIF;

void Physical::updatePP(float deltaT)
{
	if (gravity) velocity += gravityAcc * deltaT;
	//velocity -= (velocity * velocity) * 0.05f * deltaT; // air drag

	pos += velocity * deltaT;
	npos = pos;

	nvelocity = velocity;
}

void Physical::updateC(float deltaT, std::deque<GObject*>::iterator i)
{
	isLockedX = false;
	isLockedY = false;
	for(i;i != end(colidable); i++)
	{
		constexpr float eps = 0;

		if ((pos.x + size.x > (*i)->pos.x) && (pos.x < (*i)->pos.x + (*i)->size.x) && isHorizBound(this, (*i)))
		{
			if ((npos.y + size.y > (*i)->pos.y) && (npos.y < (*i)->pos.y + (*i)->size.y))
			{
				if ( Physical* ip = dynamic_cast<Physical*>(*i) ) {
					ColisionVy(this, ip);
					if (size.y / 2 + npos.y > (*i)->size.y / 2 + (*i)->pos.y) colisionPosY(this, ip);
					else colisionPosY(ip, this);

					dragAccX(this, ip);
				}

				else {
					isLockedY = true;
					if (size.y / 2 + npos.y > (*i)->size.y / 2 + (*i)->pos.y) npos.y = (*i)->pos.y + (*i)->size.y + eps;
					else npos.y = (*i)->pos.y - size.y - eps;
					nvelocity.y = ColisionV(velocity.y, boyancy);

					dragAccX(this);
				}
			}
		}

		else if ((pos.y + size.y > (*i)->pos.y) && (pos.y < (*i)->pos.y + (*i)->size.y))
		{
			if ((npos.x + size.x > (*i)->pos.x) && (npos.x < (*i)->pos.x + (*i)->size.x))
			{


				if ( Physical* ip = dynamic_cast<Physical*>(*i) ) {
					ColisionVx(this, ip);
					if (size.x / 2 + npos.x > (*i)->size.x / 2 + (*i)->pos.x) colisionPosX(this, ip);
					else colisionPosX(ip, this);

					dragAccX(this, ip);
				}


				else {
					isLockedX = true;
					nvelocity.x = ColisionV(velocity.x, boyancy);
					if (size.x / 2 + npos.x > (*i)->size.x / 2 + (*i)->pos.x) npos.x = (*i)->pos.x + (*i)->size.x + eps;
					else npos.x = (*i)->pos.x - size.x - eps;

					dragAccX(this);
				}
			}
		}

	}
	//pos = npos;
}

void Physical::updateP(float deltaT)
{
	pos = npos;
	velocity = nvelocity;
}

float kineticEnergy(const Physical& ph)
{
	float speed = ph.velocity.length();
	return ph.mass * speed * speed / 2.f;
}

Vec2 momentum(const Physical& ph)
{
	//float speed = ph.velocity.length();
	return Vec2(ph.mass * ph.velocity.x, ph.mass * ph.velocity.y);
}

float potentialEnergy(const Physical& ph)
{
	//float rad = angleBetween(Physical::gravityAcc, Vec2(0, 1));
	//if(ph.pos.x != 0 || ph.pos.y != 0 || rad < 0.0001 || rad > 360 - 0.0001) return ph.mass * Physical::gravityAcc.length() * ph.pos.y;

	//return ph.mass * 9.81 * ph.pos.y;
	float rad = angleBetween(ph.pos, Vec2(0, 1));
	//std::cout << ph.pos.length() * sin(Physical::gravityAng - (rad + M_PIF / 2));
	return ph.mass * Physical::gravityAcc.length() * ph.pos.length() * sin(Physical::gravityAng - ( rad + M_PIF / 2) );
}



/*if (pos.y < 0) {
		pos.y = 0.01;
		if(velocity.y<0) velocity.y = 0;
		//if (pos.y < -0.01) pos.y = -0.005f;
	}
	else if (gravity) velocity.y -= gravityAcc*deltaT;
	pos += velocity * deltaT;*/
	//velocity = velocity;

/*
colision sets speed but did not correct position of second object
*/