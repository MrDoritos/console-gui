#include "rigidbox.h"
#include "rigidbody.h"
#include "box.h"
#include <string>
#include <iostream>
#define GETCHAR1(xsssss) ((	 xsssss > 0.9f ? '@' :\
							 xsssss > 0.8f ? '%' :\
							 xsssss > 0.7f ? '#' :\
							 xsssss > 0.6f ? '*' :\
							 xsssss > 0.5f ? '+' :\
							 xsssss > 0.4f ? '=' :\
							 xsssss > 0.3f ? '-' :\
							 xsssss > 0.2f ? ':' :\
							 xsssss > 0.1f ? '.' :\
						     xsssss == 0.0f ? '\0' :\
							' '))

rigidbox::rigidbox(float velocity, float degrees, char * framebuffer, boxsize * rigidBoxSize, boxsize * constraints, bool isAlpha)	:
	rigidbody(velocity, degrees, rigidBoxSize, constraints), 
	bBox(*rigidBoxSize, framebuffer, rigidBoxSize->characters(), isAlpha)
{
	this->cachedSampledImage = framebuffer;
}

rigidbox::rigidbox()
	:rigidbody(), bBox()
{
}

rigidbox::~rigidbox()
{
}

void rigidbox::sampleImage(png & image)
{
	for (int y = 0; y < bBox.sizeY; y++) {
		for (int x = 0; x < bBox.sizeX; x++) {
			cachedSampledImage[bBox.get(x, y)] = GETCHAR1((image.getSample(x, y, &bBox)->negativeValue()));
		}
	}
}

void rigidbox::flipH()
{
	int characters = bBox.characters();
	char* fB = (char*)alloca(characters);
	for (int y = 0; y < bBox.sizeY + 1; y++) {
		for (int x = 0; x < bBox.sizeX + 1; x++) {
			fB[bBox.get(x, bBox.sizeY - y)] = cachedSampledImage[bBox.get(x, y)];
		}
	}
//	for (int i = 0; i < characters; i++) {
		//cachedSampledImage[i] = fB[i];
	//}
	swap(fB, cachedSampledImage, characters);
}



void rigidbox::flipV()
{
	int characters = bBox.characters();
	char* fB = (char*)alloca(characters);
	for (int x = 0; x < bBox.sizeX + 1; x++) {
		for (int y = 0; y < bBox.sizeY + 1; y++) {
			fB[bBox.get(bBox.sizeX - x, y)] = cachedSampledImage[bBox.get(x, y)];
		}
	}
	//std::memcpy(framebuffer, fB, characters);
	//for (int i = 0; i < characters; i++) {
	//	cachedSampledImage[i] = fB[i];
	//}
	swap(fB, cachedSampledImage, characters);
}

inline void rigidbox::swap(char * fb0, char * fb1, int length)
{
#ifdef GCC
	memcpy(fb1, fb0, length);
#else
	std::memcpy(fb1, fb0, length);
#endif
}
