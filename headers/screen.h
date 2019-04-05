#pragma once

#include "eventHandler.h"
#include "box.h"

template<class _b>
class screen : public box {
	public:
	screen(int offsetx, int offsety, int sizex, int sizey)
	:box(offsetx, offsety, sizex, sizey)
	{
		
	}
	eventHandler<_b> events;
};