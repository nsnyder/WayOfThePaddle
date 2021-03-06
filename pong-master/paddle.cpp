// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 ship.cpp v1.0

#include "paddle.h"

//=============================================================================
// default constructor
//=============================================================================
Paddle::Paddle() : Entity()
{
    spriteData.width = paddleNS::WIDTH;           // size of Ship1
    spriteData.height = paddleNS::HEIGHT;
    spriteData.x = paddleNS::X;                   // location on screen
    spriteData.y = paddleNS::Y;
	spriteData.rect.top = 0;
	spriteData.rect.left = 0;
    spriteData.rect.bottom = paddleNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = paddleNS::WIDTH;
	edge.top = -paddleNS::HEIGHT/2;
    edge.left = -paddleNS::WIDTH/2;
	edge.bottom = paddleNS::HEIGHT/2;
    edge.right = paddleNS::WIDTH/2;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = paddleNS::SHIP_ANIMATION_DELAY;
    startFrame = paddleNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = paddleNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    collisionType = entityNS::BOX;
	direction.x = 0;
	direction.y = 0;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Paddle::update(float frameTime)
{
    Entity::update(frameTime);

	//movement control
	/*direction.x = 0;
	direction.y = 0;
	if(input->isKeyDown(VK_UP))
	{
		direction.y = 1;
	}*/
	/*if(input->isKeyDown(VK_UP))
	{
		direction.y = -1;
	}
	if(input->isKeyDown(VK_UP))
	{
		direction.x = -1;
	}
	if(input->isKeyDown(VK_UP))
	{
		direction.x = 1;
	}*/
	/*
	D3DXVec2Normalize(&direction,&direction);
	
	float prevX = spriteData.x;

	spriteData.x += frameTime * velocity.x * direction.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y * direction.y;     // move ship along Y

	velocity.x = (prevX-spriteData.x)/frameTime;

    //wall-bounding
    if (spriteData.x > GAME_WIDTH-paddleNS::WIDTH*getScale())
    {
        spriteData.x = GAME_WIDTH-paddleNS::WIDTH*getScale();   
    } 
    else if (spriteData.x < 0)
    {
        spriteData.x = 0;
    }
    if (spriteData.y > GAME_HEIGHT-paddleNS::HEIGHT*getScale())
    {
        spriteData.y = GAME_HEIGHT-paddleNS::HEIGHT*getScale();
	}
	else if (spriteData.y < 0)
	{
		spriteData.y = 0;
	}
	*/
}
