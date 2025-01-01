#include "Window.h" 

LRESULT Wndproc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	Window* wnd = (Window*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	switch (uMsg)
	{
	case WM_RBUTTONUP:
	{
		if(wnd->rbClickHandle)wnd->rbClickHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_LBUTTONUP:
	{
		if (wnd->rbClickHandle)wnd->lbClickHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (wnd->rbClickHandle)wnd->mouseMoveHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_KEYDOWN:
	{
		if (wnd->keyboardHandle)wnd->keyboardHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_COMMAND:
	{
		if (wnd->contextMenuHandle)wnd->contextMenuHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_KILLFOCUS:
	{
		if(wnd->unfocusHandle)wnd->unfocusHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	case WM_SETFOCUS:
	{
		if (!wnd->programInstance)break;
		if (wnd->focusHandle)wnd->focusHandle(hWnd, uMsg, wParam, lParam);
		break;
	}

	default:
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
}

void Window::_initWndClass()
{
	if (this->WINDOW_CLASS != NULL)return;
	WNDCLASS wndClass;
	wndClass.style = 0;
	wndClass.lpfnWndProc = &Wndproc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = NULL;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"Okno";

	this->WINDOW_CLASS = (ATOM)RegisterClass(&wndClass);
}

void Window::_initWindow()
{



	if (Window::WINDOW_CLASS == NULL)return;
	HWND hwnd = CreateWindowEx(
		0,
		(LPCWSTR)Window::WINDOW_CLASS,
		L"",
		WS_TILEDWINDOW,
		100, 100, //POS
		this->width, this->height,
		NULL, NULL, NULL, NULL
	);

	if (hwnd == NULL)return;
	this->windowPtr = hwnd;
	SetWindowLongPtrW(this->windowPtr, GWLP_USERDATA, (LONG_PTR)this);
	ShowWindow(hwnd, SW_NORMAL);
}

void Window::_initGL()
{
	HDC context = GetDC(this->windowPtr);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // Size of this structure,
		1, // Structure version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
		32, // Color bits
		8, // R
		0, // R-S
		8, // G
		0, // G-S
		8, // B
		0, // B-S
		8, // A
		0, // A-S
		32, // Accum
		8, 8, 8, 8, // Depth
		24,
		8, // Stencil
		0, // AUX
		PFD_MAIN_PLANE,
		0, // Visible mask
		0 // Damage mask
	};

	int result = ChoosePixelFormat(context, &pfd);
	BOOL ret = SetPixelFormat(context, result, &pfd);
	HGLRC glInstance = wglCreateContext(context);
	HGLRC glInstance2 = wglCreateContext(context);

	ret = wglMakeCurrent(context, glInstance);

	RECT    rcCli;
	GetClientRect(WindowFromDC(context), &rcCli);
	
	this->width = (float)rcCli.right;
	this->height = (float)rcCli.bottom;

	gluOrtho2D(0, this->width, 0, this->height);

}

void Window::_eventHandler()
{
	MSG msg;
	if (PeekMessageA(&msg, 0, 0, 0, 1))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

Window::Window(int width, int height, std::string title) : width(width), height(height), title(title)
{
	this->WINDOW_CLASS = (ATOM)NULL;
	this->_initWndClass();
	this->_initWindow();
	this->_initGL();
}

void Window::Update()
{
	this->_eventHandler();
	SwapBuffers(GetDC(this->windowPtr));
}

HWND Window::GetWindow()
{
	return this->windowPtr;
}
