#include <Windows.h>

bool running(true);

struct RenderState
{
	int height, width;
	void * memory;

	BITMAPINFO bitmapInfo;
};

RenderState renderState;


LRESULT CALLBACK windowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result(0);
	switch (uMsg)
	{
	case WM_CLOSE:

	case WM_DESTROY:
	{
		running = false;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		renderState.width = rect.right - rect.left;
		renderState.height = rect.bottom - rect.top;

		int bufferSize = renderState.width * renderState.height * sizeof(unsigned int);

		if (renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);

		renderState.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		renderState.bitmapInfo.bmiHeader.biSize = sizeof(renderState.bitmapInfo.bmiHeader);
		renderState.bitmapInfo.bmiHeader.biWidth = renderState.width;
		renderState.bitmapInfo.bmiHeader.biHeight = renderState.height;
		renderState.bitmapInfo.bmiHeader.biPlanes = 1;
		renderState.bitmapInfo.bmiHeader.biBitCount = 32;
		renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;

	}
	break;
	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = "Game Window Class";
	windowClass.lpfnWndProc = windowCallback;

	RegisterClass(&windowClass);

	HWND window = CreateWindow(windowClass.lpszClassName, "PlusPlusGame", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running)
	{
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		unsigned int * pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++)
		{
			for (int x = 0; x < renderState.width; x++)
			{
				*pixel++ = 0xff2277*rand();
			}
		}

		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	}
}