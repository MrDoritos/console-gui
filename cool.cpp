#include <iostream>
#include "boxsize.h"
#include "box.h"
#include <stdlib.h>
#include "gameEngine.h"
#include <Windows.h>
#include "imath.h"
#include <cmath>
#include "png.h"

void invalidArgs();
void error(char* mes, int er = 1);

class textAsset {
	public:
	textAsset(const char* pngPath)
		:source(pngPath)
	{
		
	}
	const int charcount = 25;	
	const char* characters = "abcdefghijklmnopqrstuvwxyz ";
	void draw(box* cam, int x, int y, int size, char b) {
		char* bss = cam->getFramebuffer();
		for (int bx = 0, dx = x; bx < size; dx++, bx++) {
			for (int by = 0, dy = y; by < size; dy++, by++) {
				bss[cam->get(dx, dy)] = sample((b - 'a') * 30, 0, bx, by, size);
			}
		}
	}
	char sample(int offsetx, int offsety, int x, int y, int max) {
		float scalex = max / 30, scaley = max / 30;
		return getGSC(source.getPixel((int)((x / scalex) + offsetx), (int)((y / scaley) + offsety))->value());
	}	
	inline char getGSC(float val) {	
		const int size = 70;
		const char scC[71] = { "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. " };
		return scC[int(size * val)];
	}
	
	private:
	png source;
};

class game : gameEngine {
	public:
	textAsset ass;
	game(box* camera, CHAR_INFO* buffer) :
	gameEngine(camera, GetStdHandle(STD_OUTPUT_HANDLE), buffer, false),
	ass("font.png")
	{
		consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		consoleIn = GetStdHandle(STD_INPUT_HANDLE);
		ConstructConsole(camera->sizeX, camera->sizeY, 8,8, (wchar_t*)L"Raster");
		SetTargetTicksPerSecond(2);
		doClear = true;
	}
	static void Game(int width, int height) {
		boxsize camSize(0,0,width, height);
		char* frameBuf = (char*)alloca(sizeof(char) * camSize.characters());
		box cam(camSize, frameBuf, camSize.characters());
		CHAR_INFO* buf = (CHAR_INFO*)alloca(sizeof(CHAR_INFO) * camSize.characters());
		game d(&cam, buf);
		d.Start();
	}
	char s = 'a';
	bool OnUpdate(float elapsedtime) override {		
		if (getKey(VK_ESCAPE)->bReleased) {
			Close();
		}
		ass.draw(this,0,0,50,s++);
		return false;
	}
	bool OnCreate() override {		
		return false;
	}
	bool OnFrame() override {
		return true;
	}
	void OnClose() override {
		
	}
};


int main(int argc, char** argv) {
	int width = 80, height = 80;
	if (argc > 2) {
		if (sscanf(argv[1], "%i", &width) != 1)
			invalidArgs();
		if (sscanf(argv[2], "%i", &height) != 1)
			invalidArgs();
	}
	printf("%i, %i", width, height);
	game::Game(width, height);
	return 0;
}

void invalidArgs() {
	error("Invalid Arguments");
}

void error(char* mes, int er) {
	printf("%i: %s", er, mes);
	exit(er);
}