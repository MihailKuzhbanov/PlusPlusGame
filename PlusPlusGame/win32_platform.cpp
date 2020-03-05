#include "Renderer.hpp"
#include "PlatformCommon.hpp"
#include "Game.hpp"

#define processButton(b, vk)\
case vk:\
{\
	input.buttons[b].changed = isDown != input.buttons[b].isDown;\
	input.buttons[b].isDown = isDown;\
} break;

global bool running(true);
global RenderState renderState;
global float deltaTime = 0.016666f;


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

		int bufferSize = renderState.width * renderState.height * sizeof(u32);

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
	Input input = {};
	LARGE_INTEGER frameBeginTime;
	QueryPerformanceCounter(&frameBeginTime);

	float perfomanceFrequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		perfomanceFrequency = (float)perf.QuadPart;
	}

	while (running)
	{
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				u32 vkCode = (u32)message.wParam;
				bool isDown = ((message.lParam & (1 << 31)) == 0);
				switch (vkCode)
				{
					processButton(BUTTON_UP, VK_UP);
					processButton(BUTTON_DOWN, VK_DOWN);
					processButton(BUTTON_W, 'W');
					processButton(BUTTON_S, 'S');
				}
			} break;

			default:
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}

		Simulate(&input, renderState, deltaTime);
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frameEndTime;
		QueryPerformanceCounter(&frameEndTime);
		deltaTime = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / perfomanceFrequency;
		frameBeginTime = frameEndTime;

	}
}