#include "Object.h"

std::deque<GObject*> GObject::colidable;
std::vector<GObject*> GObject::allList;
float GObject::pxlByMtr = 50;

void GObject::updateC(float deltaT, std::deque<GObject*>::iterator i)
{
	/*for (i; i != end(colidable); i++)
	{
		if(dynamic_cast<Physical>)
	}*/
}