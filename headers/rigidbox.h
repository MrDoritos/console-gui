#pragma once
#include "box.h"
#include "boxsize.h"
#include "rigidbody.h"
#include "png.h"
class rigidbox :
	public rigidbody
{
public:
	rigidbox(float velocity, float degrees, char * framebuffer, boxsize * rigidBoxSize, boxsize * constraints, bool isAlpha = false);
	rigidbox();
	~rigidbox();
	void sampleImage(png &image);
	/*
	box* getBox(box& b) { 
		boxsize size;
		getBody(size);
		b = box(size, cachedSampledImage, bBox.characters()); 
		return &b; 
	}
	*/
	char* getSampledImage() { return cachedSampledImage; }
	void flipH();
	void flipV();	
private:
	void swap(char* fb0, char* fb1, int length);
	box bBox;
	char* cachedSampledImage; //Shhh, don't tell anyone
};

