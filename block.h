#pragma once

#include "object.h"

class Block : public Object
{
public:
	Block()
	{
		x = 0;
		y = 0;
		width = 40;
		height = 40;
		r = 0;
		g = 0;
		b = 255;
	}
};