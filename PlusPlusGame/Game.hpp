#pragma once
#include <Windows.h>
#include "Utils.hpp"
#include "PlatformCommon.hpp"
#include "Renderer.hpp"

#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

global float playerOnePosY = 50.f;
global float playerTwoPosY = 50.f;
global float playerOnePosX = 5.f;
global float playerTwoPosX = 95.f;
global float arenaHalfSizeX = 48, arenaHalfSizeY = 48;
float playerSpeed = 50.f;

internal void
Simulate(Input *input, RenderState renderState, float deltaTime)
{
	ClearScreen(renderState, 0x000000);
	RenderBackground(renderState, 0xAAFFAA);
	DrawFilledRect(renderState, 50, 50, arenaHalfSizeX, arenaHalfSizeY, 0x000000);							//Arena
	DrawFilledRect(renderState, 50, 50, 0.5, 1, 0xAAFFAA);							//Target

	if (isDown(BUTTON_W)) playerOnePosY += playerSpeed * deltaTime;
	if (isDown(BUTTON_S)) playerOnePosY -= playerSpeed * deltaTime;
	if (isDown(BUTTON_UP)) playerTwoPosY += playerSpeed * deltaTime;
	if (isDown(BUTTON_DOWN)) playerTwoPosY -= playerSpeed * deltaTime;


	DrawFilledRect(renderState, playerOnePosX, playerOnePosY, 1, 10, 0xFFAA00);		//Player One
	DrawFilledRect(renderState, playerTwoPosX, playerTwoPosY, 1, 10, 0x00AAFF);		//Player Two
}