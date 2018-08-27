#pragma once

class Object
{
protected:
	int x;
	int y;

	unsigned width;
	unsigned height;

	unsigned w, h;

	unsigned char r;
	unsigned char g;
	unsigned char b;

	float speed;

public:
	virtual bool draw(unsigned row, unsigned field)
	{
		if (row >= y && row <= y + height)
			if (field >= x && field <= x + width)
				return true;

		return false;

		/*for (int i = 0; i < w * h; ++i)
		{
			unsigned row = i / w;
			unsigned field = i % w;

			if (row >= y && row <= y + height)
				if (field >= x && field <= x + width)
					*(buf + i) = (r << 16) | (g << 8) | b;
		}*/
	}

	virtual bool collision(unsigned int _x, unsigned int _y, unsigned int _w, unsigned int _h)
	{
		//столкнулись сверху
		if (y + height >= _y && y < _y && x < _x + _w && x + width > _x)
		{
			return true;
		}
		//столкнулись снизу
		if (y <= _y + _w && y + height > _y + _w && x < _x + _w && x + width > _x)
		{
			return true;
		}
		//столкнулись слева
		if (x + width >= _x && x < _x && y < _y + _h && y + height > _y)
		{
			return true;
		}
		//столкнулись справа
		if (x <= _x + _w && x + width > _x + _w && y < _y + _h && y + height > _y)
		{
			return true;
		}
		
		return false;
	}

	virtual unsigned int getRGB() { return (r << 16) | (g << 8) | b; }

	virtual unsigned int getx() { return x; }
	virtual unsigned int gety() { return y; }
	virtual unsigned int getw() { return width; }
	virtual unsigned int geth() { return height; }

	virtual void setx(unsigned _x) { x = _x; }
	virtual void sety(unsigned _y) { y = _y; }
	virtual void setw(unsigned _w) { w = _w; }
	virtual void seth(unsigned _h) { h = _h; }

	virtual void setscreen(unsigned _w, unsigned _h)
	{
		w = _w;
		h = _h;
	}
};