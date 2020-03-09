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
global float arenaHalfSizeX = 48.f;
global float arenaHalfSizeY = 48.f;
global float playerHalfSizeX = 1.f;
global float playerHalfSizeY = 10.f;
global float ballPosX = 50.f;
global float ballPosY = 50.f;
global float ballHalfSizeX = 0.5f;
global float ballHalfSizeY = 1.f;
float borderTop = 87.5f;
float borderBot = 12.5f;
float playerSpeed = 50.f;
float ballSpeed = 50.f;

void InitStartConditions()
{
	playerOnePosY = 50.f;
	playerTwoPosY = 50.f;
	playerOnePosX = 5.f;
	playerTwoPosX = 95.f;
	arenaHalfSizeX = 48.f;
	arenaHalfSizeY = 48.f;
	playerHalfSizeX = 1.f;
	playerHalfSizeY = 10.f;
	ballPosX = 50.f;
	ballPosY = 50.f;
	ballHalfSizeX = 0.5f;
	ballHalfSizeY = 1.f;
}

bool BallIsCollide()
{
	bool leftCollide = ballPosX + ballHalfSizeX <= playerOnePosX + playerHalfSizeX && (ballPosY + ballHalfSizeY > playerTwoPosY - playerHalfSizeY) && (ballPosY + ballHalfSizeY < playerTwoPosY + playerHalfSizeY);
	bool rightCollide = ballPosX + ballHalfSizeX >= playerTwoPosX - playerHalfSizeX && (ballPosY + ballHalfSizeY > playerTwoPosY - playerHalfSizeY) && (ballPosY + ballHalfSizeY < playerTwoPosY + playerHalfSizeY);
	return rightCollide + leftCollide;
}

bool BallOutOfBorder()
{

}

internal void
Simulate(Input *input, RenderState renderState, float deltaTime)
{
	ClearScreen(renderState, 0x000000);
	RenderBackground(renderState, 0xAAFFAA);
	DrawFilledRect(renderState, 50, 50, arenaHalfSizeX, arenaHalfSizeY, 0x000000);										//Arena
	
																														//Ball
	ballPosX += ballSpeed * deltaTime;
	DrawFilledRect(renderState, ballPosX, ballPosY, ballHalfSizeX, ballHalfSizeY, 0xAAFFAA);							
	if (BallIsCollide()) ballSpeed *= -1;

	if (isDown(BUTTON_W) && playerOnePosY < borderTop) playerOnePosY += playerSpeed * deltaTime;
	if (isDown(BUTTON_S) && playerOnePosY > borderBot) playerOnePosY -= playerSpeed * deltaTime;
	if (isDown(BUTTON_UP) && playerTwoPosY < borderTop) playerTwoPosY += playerSpeed * deltaTime;
	if (isDown(BUTTON_DOWN) && playerTwoPosY > borderBot) playerTwoPosY -= playerSpeed * deltaTime;

	DrawFilledRect(renderState, playerOnePosX, playerOnePosY, playerHalfSizeX, playerHalfSizeY, 0xFFAA00);				//Player One
	DrawFilledRect(renderState, playerTwoPosX, playerTwoPosY, playerHalfSizeX, playerHalfSizeY, 0x00AAFF);				//Player Two
}