#include <iostream>
#include "screen.h"

using namespace std;

class test : public screen<test> {
	public:
	test() : screen<test>(0,0,20,20)
	{
		events.setReferer(this);
		events.assign(FLG_KEYPRESS, func(test, test::onClick));
	}
	
	void onClick() {
		std::cout << "Hello World" << std::endl;
	}
};

int main() {
	test scr = test();
	scr.events.handle(FLG_KEYPRESS);
	
	//Test possible situation
	scr.events.handle(FLG_KEYRELEASE);
	
	return 0;
}