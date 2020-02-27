#pragma once
#include <Windows.h>
#include "Utils.hpp"

struct RenderState
{
	int height, width;
	void * memory;

	BITMAPINFO bitmapInfo;
};

global float renderScale = 0.01f;

internal void
RenderBackground(RenderState renderState, u32 color)
{
	u32 * pixel = (u32*)renderState.memory;
	for (int y = 0; y < renderState.height; y++)
	{
		for (int x = 0; x < renderState.width; x++)
		{
			*pixel++ = color;
		}
	}
}

internal void
ClearScreen(RenderState renderState, u32 color)
{
	RenderBackground(renderState, color);
}

internal void
DrawFilledRectInPixels(RenderState renderState, int x0, int y0, int x1, int y1, u32 color)
{
	x0 = clamp(0, x0, renderState.width);
	x1 = clamp(0, x1, renderState.width);
	y0 = clamp(0, y0, renderState.height);
	y1 = clamp(0, y1, renderState.height);

	for (int y = y0; y < y1; y++)
	{
		u32 * pixel = (u32*)renderState.memory + x0 + y * renderState.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}

internal void
DrawFilledRect(RenderState renderState, float x, float y, float halfSizeX, float halfSizeY, u32 color)
{
	x *= renderState.width * renderScale;
	y *= renderState.height * renderScale;
	halfSizeX *= renderState.width * renderScale;
	halfSizeY *= renderState.height * renderScale;

	int x0 = x - halfSizeX;
	int x1 = x + halfSizeX;
	int y0 = y - halfSizeY;
	int y1 = y + halfSizeY;

	DrawFilledRectInPixels(renderState, x0, y0, x1, y1, color);
}