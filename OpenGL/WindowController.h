#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTRLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public: 
	WindowController();
	virtual ~WindowController();

	GLFWwindow* getWindow() { if (window == nullptr) { NewWindow(); } return window; }

	void NewWindow();
	Resolution GetResolution();

private:
	//Members
	GLFWwindow* window;
};

#endif