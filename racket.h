#pragma once

#include "object.h"

class Racket : public Object
{
private:

public:
	Racket()
	{
		x = 200;
		y = 200;
		width = 100;
		height = 10;
		r = 255;
		g = 255;
		b = 255;
	}

	void setscreen(unsigned _w, unsigned _h)
	{
		w = _w;
		h = _h;
		y = h - height - 10;
		x = (w / 2) - (width / 2);
	}

	void move_left()
	{
		if (x - 1 > 0)
		{
			--x;
		}
	}

	void move_right()
	{
		if (x + width + 1 < w)
		{
			++x;
		}		
	}
};