#include <iostream>
#include "boxsize.h"
#include "box.h"
#include <stdlib.h>
#include "gameEngine.h"
#include <Windows.h>
#include "imath.h"
#include <cmath>

void invalidArgs();
void error(char* mes, int er = 1);

class test3d : gameEngine {
	public:
	test3d(box* camera, CHAR_INFO* buffer) :
	gameEngine(camera, GetStdHandle(STD_OUTPUT_HANDLE), buffer, false) 
	{
		consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		consoleIn = GetStdHandle(STD_INPUT_HANDLE);
		ConstructConsole(camera->sizeX, camera->sizeY, 8,8, (wchar_t*)L"Raster");
		//ConstructConsole(camera->sizeX, camera->sizeY, 4, 6, (wchar_t*)L"Lucida Console");
		SetTargetTicksPerSecond(60);
		doClear = false;
	}
	static void Game(int width, int height) {
		//box cam(0, 0, width, height);
		boxsize camSize(0,0,width, height);
		char* frameBuf = (char*)alloca(sizeof(char) * camSize.characters());
		box cam(camSize, frameBuf, camSize.characters());
		CHAR_INFO* buf = (CHAR_INFO*)alloca(sizeof(CHAR_INFO) * camSize.characters());
		test3d d(&cam, buf);
		d.Start();
	}
	struct m_t {
		public:
		m_t() {
			memset(this, 0, sizeof(m_t));
			//curx = 0;
			//cury = 0;
			//lastx = 0;
			//lasty = 0;
		}
		bool moved() {
			return (curx != lastx || cury != lasty);
		}
		int getLastX() {return lastx;}
		int getLastY() {return lasty;}
		int getCurX() {return curx;}
		int getCurY() {return cury;}
		void update(int newx, int newy) {
			lastx = curx;
			lasty = cury;
			curx = newx;
			cury = newy;
		}
		private:
		int curx, cury;
		int lastx, lasty;
	} m_;
	//struct p {
 	//	public:
	//	p() {x = -1; y = -1;}
	//  int x, y;
	//} last;
	bool OnUpdate(float elapsedtime) override {		
		static struct etch_t {
			public:
			#define S_SIZE 10
			void update(int x, int y) {
				if (++c > S_SIZE - 1) {
					for (int i = 1; i < S_SIZE; i++) {
						points[i - 1] = points[i];
					}
					c = 9;
				}
				points[c - 1] = p(x, y);
			}				
			etch_t() {
				c = 0;
			}
			struct p {
				public:
				p() {
					x = 0;
					y = 0;
				}
				p(int x, int y) {
					this->x = x;
					this->y = y;
				}
				int x, y;
			} points[S_SIZE];
			int c;		
		} etch;		
		
		if (getKey(VK_ESCAPE)->bReleased) {
			Close();
		}
		m_.update(getMouseX(),getMouseY());
		if (mouse[0].bHeld && m_.moved()) {
			const char scC[71] = { "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. " };
			etch.update(m_.getCurX(),m_.getCurY());
			for (int i = 0; i < etch.c - 1; i++) {
				drawline(etch.points[i].x,etch.points[i].y, m_.getCurX(), m_.getCurY(), scC[int((double(i) / double(etch.c)) * 70)]);
			}
			
			#undef S_SIZE
			
			/* CIRCLE & SPEED */
			//double speed = abs(dist(m_.getLastX(), m_.getLastY(), m_.getCurX(), m_.getCurY()));
			//drawCircle(m_.getCurX(), m_.getCurY(), 1 + 5 / speed);
		} else if (mouse[0].bReleased) {
			etch.c = 0;
		}
		if (mouse[1].bReleased) {
			forceclear();
			
			etch.c = 0;
			
		}
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
	test3d::Game(width, height);
	return 0;
}

void invalidArgs() {
	error("Invalid Arguments");
}

void error(char* mes, int er) {
	printf("%i: %s", er, mes);
	exit(er);
}