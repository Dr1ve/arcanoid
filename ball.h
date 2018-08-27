#pragma once

#include "object.h"

//квадратный мячик
class Ball : public Object
{
private:
	bool top, left, right, bottom;
	float steep;
public:
	Ball()
	{
		x = 100;
		y = 100;
		width = 10;
		height = 10;
		r = 255;
		g = 0;
		b = 0;

		speed = 5;
		steep = 0;

		top = true;
		left = true;
		right = false;
		bottom = false;
	}

	void setscreen(unsigned _w, unsigned _h)
	{
		w = _w;
		h = _h;
		y = h - height - 40;
		x = (w / 2) - (width / 2);
	}

	bool collision(unsigned int _x,unsigned int _y, unsigned int _w, unsigned int _h)
	{
		//столкнулись сверху
		if (y + height >= _y && y < _y && x < _x + _w && x + width > _x)
		{
			bottom = false;
			top = true;
			return true;
		}
		//столкнулись снизу
		if (y <= _y + _w && y + height > _y + _w && x < _x + _w && x + width > _x)
		{
			bottom = true;
			top = false;
			return true;
		}
		//столкнулись слева
		if (x + width >= _x && x < _x && y < _y + _h && y + height > _y)
		{
			right = false;
			left = true;
			return true;
		}
		//столкнулись справа
		if (x <= _x + _w && x + width > _x + _w && y < _y + _h && y + height > _y)
		{
			right = true;
			left = false;
			return true;
		}

		return false;
	}

	bool move(float d)
	{
		bool res = true;
		steep += d * 100.0f;
		if ((int)steep > 0)
		{
			if (top)
			{
				if (y - steep > 0)
					y -= steep;
				else
				{
					top = false;
					bottom = true;
					res = true;
				}
			}
			else
			{
				if (bottom)
				{
					if (y + height + steep < h)
						y += steep;
					else
					{
						bottom = false;
						top = true;
						res = false;
					}
				}
			}
			if (left)
			{
				if (x - steep > 0)
					x -= steep;
				else
				{
					left = false;
					right = true;
					res = true;
				}
			}
			else
			{
				if (right)
				{
					if (x + width + steep < w)
						x += steep;
					else
					{
						right = false;
						left = true;
						res = true;
					}
				}
			}
			steep = 0;
		}
		
		return res;
	}
};