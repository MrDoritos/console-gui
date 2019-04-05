#pragma once
//#define PI 3.1415926f
#include "boxsize.h"
#include "box.h"
class rigidbody
{
public:
	
	rigidbody();
	/*
	~rigidbody();
	*/
public:
	rigidbody(float velocity, float degrees, boxsize* size, boxsize* rigidBounds);
	//int getX() {return (int)positionX;}
	//int getY() {return (int)positionY;}
	//elapsedtime is the ticktime
	void update(float elapsedtime);
	void setvelocity(float velocity) { this->velocity = velocity; }
	void degsetangle(float degrees) { degrees = wrap(degrees); this->degrees = degrees; this->radians = degtorad(degrees); }
	void radsetangle(float radians) { this->degrees = radtodeg(degrees); this->radians = radians; }
	void move(float distance);
	int getMaxX() { return getMax(positionX, sizeX); }
	int getMaxY() { return getMax(positionY, sizeY); }
	int getMinX() { return getMin(positionX); }
	int getMinY() { return getMin(positionY); }
	float distanceToSide0();
	float distanceToSide1();
	float distanceToSide2();
	float distanceToSide3();
	float getNewAngle(float current, float bounce, int wall);
	void getBody(boxsize & size) {
		size.offsetX = positionX;
		size.offsetY = positionY;
		size.sizeX = sizeX;
		size.sizeY = sizeY;
	}
	int getLastWall() { return lastWall; }
	bool lastUpdateHitWall() { return _lastUpdateHitWall; }

protected:
	void setdefaultpos(int wall);
	int bounce(int degrees, int wall);
	float degrees;
	float radians;
	float velocity;

	float positionX;
	float positionY;
	boxsize* rigidBounds;
	int sizeX;
	int sizeY;

	bool outOfBounds(int posX, int posY);
	void newPosition(int posX, int posY, int *newPosX, int *newPosY, float elapsedtime);
	//returns new angle
	//degrees is angle of attack
	//int bounce(int degrees);
	void getNewX(int posX, int *newPosX, float elapsedtime);
	void getNewY(int posY, int *newPosY, float elapsedtime);
	float distanceToWall(float posX, float posY, float boundsX, float boundsY, float degrees);
	float distanceToWall(float degrees, int *wall);
	int getWall(float degrees);
	int getQuadrant(float degrees);
	float wrap(float f);
	int lastWall;
	bool _lastUpdateHitWall;

private:
	static int getMax(float position, int size) { return (int)(position + size); }
	static int getMin(float position) { return (int)position; }
public:
	static float distance(float X0, float X1, float Y0, float Y1);
	static float degtorad(float degrees) { return (degrees * PI / 180); }
	static float radtodeg(float radians) { return (radians * 180 / PI); }
};

