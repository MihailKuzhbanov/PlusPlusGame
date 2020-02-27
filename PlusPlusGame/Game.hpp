#pragma once
#include <Windows.h>
#include "Utils.hpp"
#include "PlatformCommon.hpp"
#include "Renderer.hpp"

#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

global float playerPosX = 0.f;
global float playerPosY = 0.f;
global float speed = 50.f;

internal void
Simulate(Input *input, RenderState renderState, float deltaTime)
{
	ClearScreen(renderState, 0xBBAA11);
	RenderBackground(renderState, 0xAA00AA);

	if (isDown(BUTTON_UP)) playerPosY += speed*deltaTime;
	if (isDown(BUTTON_DOWN)) playerPosY -= speed * deltaTime;
	if (isDown(BUTTON_RIGHT)) playerPosX += speed * deltaTime;
	if (isDown(BUTTON_LEFT)) playerPosX -= speed * deltaTime;

	DrawFilledRect(renderState, playerPosX, playerPosY, 5, 5, 0x00AAAA);

}