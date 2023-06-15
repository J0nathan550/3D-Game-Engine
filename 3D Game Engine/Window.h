#pragma once
#include<Windows.h>
class Window
{
public: 
	Window();
	// Init params to launch window
	bool init(); 
	bool broadcast();
	// Release memory of window after closing window
	bool release();
	bool isRun(); 
	// Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy(); 
	~Window(); 
protected:
	HWND m_hwnd; 
	bool m_isRun;
};