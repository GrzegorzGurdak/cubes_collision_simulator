#include "MathEquations.h"
#include "Physical.h"

float ColisionV(float u1, float u2, float m1, float m2, float b)
{
	return (m1 * u1 + m2 * u2 + b * (m2 * u2 - m2 * u1)) / (m1 + m2);
}

void ColisionVx(Physical* that, Physical* other)
{
	that->nvelocity.x = ColisionVsx(that, other);//(that->mass * that->velocity.x + other->mass * other->velocity.x + b * (other->mass * other->velocity.x - other->mass * that->velocity.x)) / (that->mass + other->mass);
	other->nvelocity.x = ColisionVsx(other, that);//(other->mass * other->velocity.x + that->mass * that->velocity.x + b * (that->mass * that->velocity.x - that->mass * other->velocity.x)) / (other->mass + that->mass);
}
void ColisionVy(Physical* that, Physical* other)
{
	that->nvelocity.y = ColisionVsy(that, other);
	other->nvelocity.y = ColisionVsy(other, that);
}

float ColisionVsx(Physical* that, Physical* other)
{
	float b = (that->boyancy + other->boyancy) / 2.f;
	return that->nvelocity.x = (that->mass * that->velocity.x + other->mass * other->velocity.x + b * (other->mass * other->velocity.x - other->mass * that->velocity.x)) / (that->mass + other->mass);
}

float ColisionVsy(Physical* that, Physical* other)
{
	float b = (that->boyancy + other->boyancy) / 2.f;
	return that->nvelocity.y = (that->mass * that->velocity.y + other->mass * other->velocity.y + b * (other->mass * other->velocity.y - other->mass * that->velocity.y)) / (that->mass + other->mass);
}

float ColisionV(float u1, float b)
{
	return -b * u1;
}

bool isHorizBound(GObject* that, GObject* other)		//(Vec2 pos1, Vec2 pos2, Vec2 size1, Vec2 size2)
{
	float disx = that->pos.x + that->size.x - other->pos.x;
	float tmp = other->pos.x + other->size.x - that->pos.x;
	if (abs(tmp) < abs(disx)) disx = tmp;

	float disy = that->pos.y + that->size.y - other->pos.y;
	tmp = other->pos.y + other->size.y - that->pos.y;
	if (abs(tmp) < abs(disy)) disy = tmp;

	return disx > disy;



	/*return abs(that->size.x / 2 + that->pos.x - (other->size.x / 2 + other->pos.x))
			>
			abs(that->size.y / 2 + that->pos.y - (other->size.y / 2 + other->pos.y));*/
}

void dragAccX(Physical* that)
{
	//return (velocity > 0 ? -gravAcc * 0.4f : gravAcc * 0.4f);
	float dragV = 0.4f * abs(that->nvelocity.y);
	if (dragV > abs(that->nvelocity.x)) that->nvelocity.x = 0;
	else if (that->nvelocity.x > 0) that->nvelocity.x -= dragV;
	else that->nvelocity.x += dragV;
}

void dragAccY(Physical* that)
{
	float dragV = 0.4f * abs(that->nvelocity.x);
	if (dragV > abs(that->nvelocity.y)) that->nvelocity.y = 0;
	else if (that->nvelocity.y > 0) that->nvelocity.y -= dragV;
	else that->nvelocity.y += dragV;
	//return (velocity > 0 ? -gravAcc * 0.4f : gravAcc * 0.4f);
	//return 0.4f * that->nvelocity.x;
}

void dragAccX(Physical* that, Physical* other)
{
	//return (velocity > 0 ? -gravAcc * 0.4f : gravAcc * 0.4f);
	float dragV = 0.4f * abs(that->nvelocity.y - other->nvelocity.y);

	if (dragV > abs(that->nvelocity.x - other->nvelocity.x)) that->nvelocity.x = other->nvelocity.x = (other->nvelocity.x * other->mass + other->nvelocity.x * other->mass) / (that->mass + other->mass);
	else if (that->nvelocity.x - other->nvelocity.x > 0) { that->nvelocity.x -= dragV; other->nvelocity.x += dragV; }
	else { that->nvelocity.x += dragV; other->nvelocity.x -= dragV; }
}

void dragAccY(Physical* that, Physical* other)
{
	float dragV = 0.4f * abs(that->nvelocity.x - other->nvelocity.x);

	if (dragV > abs(that->nvelocity.y - other->nvelocity.y)) that->nvelocity.y = other->nvelocity.y = (other->nvelocity.y * other->mass + other->nvelocity.y * other->mass) / (that->mass + other->mass);
	else if (that->nvelocity.y - other->nvelocity.y > 0) { that->nvelocity.y -= dragV; other->nvelocity.y += dragV; }
	else { that->nvelocity.y += dragV; other->nvelocity.y -= dragV; }
	//return (velocity > 0 ? -gravAcc * 0.4f : gravAcc * 0.4f);
	//return 0.4f * that->nvelocity.x;
}

void colisionPosY(Physical* that, Physical* other)
{
	that->npos.y += abs(that->velocity.y) / (abs(that->velocity.y) + abs(other->velocity.y)) * (other->pos.y + other->size.y - that->pos.y);
	other->npos.y = that->npos.y - other->size.y;
}

void colisionPosX(Physical* that, Physical* other)
{
	that->npos.x += abs(that->velocity.x) / (abs(that->velocity.x) + abs(other->velocity.x)) * (other->pos.x + other->size.x - that->pos.x);
	other->npos.x = that->npos.x - other->size.x;
}