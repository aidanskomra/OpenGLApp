#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	int width = 1280;
	int height = 768;

	Resolution(int _width, int _height)
	{
		width = _width;
		height = _height;
	}
};

#endif