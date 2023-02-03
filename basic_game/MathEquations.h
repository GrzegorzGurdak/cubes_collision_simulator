#pragma once

#ifndef MATHEQUATIONS_H
#define MATHEQUATIONS_H

#include <cmath>

#include "Object.h"
//#include "Physical.h"

class Physical;

float ColisionV(float u1, float u2, float m1, float m2, float b);

void ColisionVx(Physical* that, Physical* other);
void ColisionVy(Physical* that, Physical* other);

float ColisionVsx(Physical* that, Physical* other);
float ColisionVsy(Physical* that, Physical* other);

float ColisionV(float u1, float b);

bool isHorizBound(GObject* that, GObject* other);

void dragAccX(Physical* that);
void dragAccY(Physical* that);

void dragAccX(Physical* that, Physical* other);
void dragAccY(Physical* that, Physical* other);

void colisionPosY(Physical* that, Physical* other);
void colisionPosX(Physical* that, Physical* other);

#endif // !MATHEQUATIONS_H