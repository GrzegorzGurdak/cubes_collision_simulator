#include "MVec.h"

#include <iostream>

const Vec2 Vec2::nullV = Vec2();
const Vec2 Vec2::UP = Vec2(0,1);
const Vec2 Vec2::DOWN = Vec2(0,-1);
const Vec2 Vec2::LEFT = Vec2(-1,0);
const Vec2 Vec2::RIGHT = Vec2(1,0);

std::ostream& operator<< (std::ostream& out, const Vec2& obj)
{
	return out << "(" << obj.x << ", " << obj.y << ")";
}

std::ostream& operator<< (std::ostream& out, const Vec2&& obj)
{
	return out << "(" << obj.x << ", " << obj.y << ")";
}

float angleBetween(Vec2 target, Vec2 base)
{
	/*if (acos((target.x * base.x + target.y * base.y) / (target.length() * base.length())) < M_PI / 2)
		return asin((target.x * base.y - target.y * base.x) / (target.length() * base.length())) * 90/acos(0);
	//return acos((target.x * base.x + target.y * base.y) / (target.length() * base.length()));
	else 
		return 180 - asin((target.x * base.y - target.y * base.x) / (target.length() * base.length())) * 90 / acos(0);*/

	/*if (asin((target.x * base.y - target.y * base.x) / (target.length() * base.length())) > 0)
		return acos((target.x * base.x + target.y * base.y) / (target.length() * base.length())) * 90 / acos(0);
	//return acos((target.x * base.x + target.y * base.y) / (target.length() * base.length()));
	else
		return 180 + acos((target.x * base.x + target.y * base.y) / (target.length() * base.length())) * 90 / acos(0);*/
	float det = (target.x * base.y - target.y * base.x);
	//std::cout << "det = " << (signbit(det)?'-':'+');
	float dot = (target.x * base.x + target.y * base.y);
	//std::cout << ", dot = " << (signbit(dot) ? '-' : '+') << ", ";
	//if(det>0 && dot > 0) return atan2f(det, dot) * 180 / M_PI;

	//if(dot>0) return atan2f(det, dot) * 180 / M_PI; // det<0

	if (det < 0) return 360 + atan2f(det, dot);// *180.f / M_PIF; // det <0 -180

	return atan2f(det, dot);// *180.f / M_PIF;
}