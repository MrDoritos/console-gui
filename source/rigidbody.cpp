#include "rigidbody.h"
#include <cmath>
#include <stdlib.h>

rigidbody::rigidbody()
{
}

/*
rigidbody::~rigidbody()
{
}
*/
rigidbody::rigidbody(float velocity, float degrees, boxsize * size, boxsize * rigidBounds)
{
	this->velocity = velocity;
	degsetangle(degrees);
	this->positionX = size->offsetX;	
	this->positionY = size->offsetY;
	this->sizeX = size->sizeX;
	this->sizeY = size->sizeY;
	this->rigidBounds = rigidBounds;
}

void rigidbody::update(float elapsedtime)
{
	float distance = elapsedtime * velocity;

	move(distance);
}

void rigidbody::move(float distance)
{
	float dist;
	int wall;
	bool positionUpdated = _lastUpdateHitWall = false;
	while (distance >= (dist = distanceToWall(degrees, &wall))) {
		//if (dist > 0.0f) {
		//	positionUpdated = true;
		//	positionX += cos(radians) * dist;
		//	positionY -= sin(radians) * dist;
		//}
		distance -= dist;
		int iBounce = bounce((int)degrees, lastWall = wall);
		degsetangle(getNewAngle(degrees, iBounce, wall));
		setdefaultpos(wall);
		_lastUpdateHitWall = positionUpdated = true;
	}

	if (distance > 0.0f && !positionUpdated) {
	//if (distance > 0.0f) {
		positionX += cos(radians) * distance;
		positionY -= sin(radians) * distance;
	}
}

float rigidbody::distanceToSide0()
{
	return distanceToWall(getMaxX(), getMinY(), rigidBounds->getMaxX(), getMinY(), degrees);
}

float rigidbody::distanceToSide1()
{
	return distanceToWall(getMinX(), getMinY(), getMinX(), rigidBounds->offsetY, degrees);
}

float rigidbody::distanceToSide2()
{
	return distanceToWall(getMinX(), getMinY(), rigidBounds->offsetX, getMinY(), degrees);
}

float rigidbody::distanceToSide3()
{
	return distanceToWall(getMaxX(), getMaxY(), getMaxX(), rigidBounds->getMaxY(), degrees);
}

float rigidbody::getNewAngle(float current, float bounce, int wall)
{
	return (bounce + (((wall + 1) % 4) * 90));
	//float newAngle = current + 180.0f - bounce;
	//float wrappedAngle = wrap(newAngle);
	//return wrappedAngle;
	//int peek = 90 * (wall + 1);
	//int 
}

void rigidbody::setdefaultpos(int wall)
{
	switch (wall)
	{
	case 0:
		positionX = rigidBounds->getMaxX() - sizeX;
		break;
	case 1:
		positionY = rigidBounds->getMinY();
		break;
	case 2:
		positionX = rigidBounds->getMinX();
		break;
	case 3:
		positionY = rigidBounds->getMaxY() - sizeY;
		break;
	default:
		exit(99892);
		break;
	}
}


int rigidbody::bounce(int degrees, int wall) {
	int peek = (wall + 1) * 90;
	return (peek - degrees)/* + ((std::rand() / ((RAND_MAX + 1u) / 90)))*/;
	//return ((std::rand() / ((RAND_MAX + 1u) / 50))) + 10;
	//Eliminate any divide by zero errors
	//degrees += 90;
	//int interiorAngle = (int)degrees % 90;
	//interiorAngle = 90 - interiorAngle;

	
	//return (interiorAngle + 10.0f);
}


float rigidbody::distanceToWall(float posX, float posY, float boundsX, float boundsY, float degrees)
{
	float somethin = rigidbody::distance(posX, boundsX, posY, boundsY);
	float distance = sin(degtorad(degrees)) * somethin;
	return abs(distance);
}

float rigidbody::distanceToWall(float degrees, int* wall)
{
	*wall = getWall(degrees);
	switch (*wall)
	{
	case 0:
		return distanceToWall(getMaxX(), getMinY(), rigidBounds->getMaxX(), getMinY(), degrees);
	case 1:
		return distanceToWall(getMinX(), getMinY(), getMinX(), rigidBounds->offsetY, degrees);
	case 2:
		return distanceToWall(getMinX(), getMinY(), rigidBounds->offsetX, getMinY(), degrees);
	case 3:
		return distanceToWall(getMaxX(), getMaxY(), getMaxX(), rigidBounds->getMaxY(), degrees);
	default:
		exit(99893);
	}
	return 0.0f;
}

int rigidbody::getWall(float degrees)
{
	//Target
	int quadrant = getQuadrant(wrap(degrees));
	//int target = getQuadrant(wrap(degrees + 45.0f)) - 1;

	float o0, o1;

	switch (quadrant)
	{
	case 1:
		o0 = distanceToSide0();
		o1 = distanceToSide1();
		return o0 < o1 ? 0 : 1;
	case 2:
		o0 = distanceToSide1();
		o1 = distanceToSide2();
		return o0 < o1 ? 1 : 2;
	case 3:
		o0 = distanceToSide2();
		o1 = distanceToSide3();
		return o0 < o1 ? 2 : 3;
	case 4:
		o0 = distanceToSide3();
		o1 = distanceToSide0();
		return o0 < o1 ? 3 : 0;
	}
}

int rigidbody::getQuadrant(float degrees)
{
	if (degrees < 1.0f) {
		return 1;
	}
	return ((int)(degrees / 90)) + 1;
}

float rigidbody::wrap(float f)
{
	/*
	f = abs(f);
	while (f > 360.0f) {
		f -= 360.0f;
	}
	*/
	while (f >= 360.0f) {
		f -= 360.0f;
	}
	while (f < 0.0f)
	{
		f += 360.0f;
	}
	return f;
}

float rigidbody::distance(float X0, float X1, float Y0, float Y1)
{
	float distance = ((X1 - X0) * (X1 - X0)) + ((Y1 - Y0) * (Y1 - Y0));
	return sqrt(distance);
}