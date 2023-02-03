#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <deque>

#include "MVec.h"

class GObject : public sf::Drawable
{
public:
	GObject(bool notBase,Vec2 _pos = Vec2::nullV, Vec2 _size = Vec2::nullV, bool isColidable = false)
		: pos{ _pos }, size{ _size }
	{
		if (isColidable) colidable.push_front(this);
		allList.push_back(this);
	};

	GObject(Vec2 _pos = Vec2::nullV, Vec2 _size = Vec2::nullV, bool isColidable = false)
		: pos{ _pos }, size{_size}
	{
		if (isColidable) colidable.push_back(this);
		allList.push_back(this);

	}; 

	GObject(float _x, float _y, float _xs = 0, float _ys = 0, bool isColidable = false) 
	: GObject{ Vec2(_x,_y), Vec2(_xs,_ys), isColidable } {};

	virtual ~GObject() {}

	static std::deque<GObject*> colidable;
	static std::vector<GObject*> allList;
	static float pxlByMtr;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sf::RectangleShape rect(size * pxlByMtr);
		rect.setPosition( sf::Vector2f(pos.x * pxlByMtr, target.getSize().y - (pos.y + size.y) * pxlByMtr ) );
		target.draw(rect);
	}
	
	static void drawAll(sf::RenderTarget& target)
	{
		for (auto& i : allList)
		{
			target.draw(*i);
		}
	}

	static void update(float deltaT)
	{
		for (GObject* i : colidable)
		
		{
			i->updatePP(deltaT);
		}
		for (auto i = begin(colidable); i != end(colidable); i++)
		{
			(*i)->updateC(deltaT, i+1);
		}
		for (GObject* i : colidable)
		{
			i->updateP(deltaT);
		}
	}
	virtual void updatePP(float deltaT) {}; // predicted position
	virtual void updateC(float deltaT, std::deque<GObject*>::iterator); // colisions
	virtual void updateP(float deltaT) {}; // final posiotion

//protected:
	Vec2 pos;
	Vec2 size;
};



#endif // !OBJECT_H