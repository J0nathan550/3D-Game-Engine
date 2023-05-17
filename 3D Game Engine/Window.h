#pragma once
#include<Windows.h>

class Window
{
public:
	Window(); 
	bool init(); // Init window
	bool broadcast(); 
	bool release(); // Release memory of the window
	bool isRun(); 

	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy() = 0;

	~Window(); 
protected:
	HWND m_hwnd; 
	bool m_is_run;
};