#pragma once
#include "Window.h"
class AppWindow: public Window
{
public:
	AppWindow();
	// implemented events from Window.cpp
	virtual void onCreate() override; 
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	~AppWindow();
};