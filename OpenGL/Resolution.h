#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	int width = 1920;
	int height = 1080;

	Resolution(int _width, int _height)
	{
		width = _width;
		height = _height;
	}
};

#endif