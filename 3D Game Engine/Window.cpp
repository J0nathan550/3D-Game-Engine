#include "Window.h"

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	switch (msg)
	{
	case WM_CREATE: { // Event that handles creation of Window
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->onCreate();
		break;
	}
	case WM_DESTROY: { // Event that handles destroying of Window
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL; 
}

bool Window::init()
{
	WNDCLASSEX wc; 
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL; 
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL; 
	wc.lpszClassName = "MyWindowClass"; 
	wc.lpszMenuName = NULL; 
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	// We are trying to create a window with paramaters we defined on top, if failed return false.
	if (!::RegisterClassEx(&wc)) {
		return false; 
	}
		
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "3D Game Engine - Unknown Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd)
	{
		return false;
	}


	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_isRun = true; // boolean that allows program understand if App is running or no. 
	return true;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	this->onUpdate();
	Sleep(0);
	return true;
}

bool Window::release()
{
	// Removing window, and releasing all used memory...
	if (!::DestroyWindow(m_hwnd))
	{
		return false; 
	}

	return true;
}

bool Window::isRun()
{
	return m_isRun;
}

void Window::onDestroy()
{
	m_isRun = false;
}

Window::~Window()
{
}