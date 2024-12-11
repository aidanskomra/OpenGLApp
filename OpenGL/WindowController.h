#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTRLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public: 
	WindowController();
	virtual ~WindowController();

	void Create(int _width = -1, int _height = -1);

	GLFWwindow* getWindow() { if (window == nullptr) { NewWindow(); } return window; }

	void NewWindow();
	const Resolution& GetResolution() { return resolution; }

private:
	//Members
	GLFWwindow* window;
	Resolution resolution = { 1920, 1080 };
};

#endif