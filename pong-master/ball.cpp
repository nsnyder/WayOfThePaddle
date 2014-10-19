// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 ship.cpp v1.0

#include "ball.h"
extern int score1;
extern int score2;

//=============================================================================
// default constructor
//=============================================================================
Ball::Ball() : Entity()
{
    spriteData.width = ballNS::WIDTH;           // size of Ship1
    spriteData.height = ballNS::HEIGHT;
    spriteData.x = ballNS::X;                   // location on screen
    spriteData.y = ballNS::Y;
    spriteData.rect.bottom = ballNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = ballNS::WIDTH;
	edge.top = -ballNS::HEIGHT/2;
    edge.left = -ballNS::WIDTH/2;
	edge.bottom = ballNS::HEIGHT/2;
    edge.right = ballNS::WIDTH/2;
    velocity.x = 100;                             // velocity X
    velocity.y = 100;                             // velocity Y
    frameDelay = ballNS::SHIP_ANIMATION_DELAY;
    startFrame = ballNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = ballNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = ballNS::WIDTH/2.0;
    collisionType = entityNS::BOX;
	direction.x = 1;
	direction.y = 1;
	spin = 1.0f;
}
void Ball::setSpin(float s){
	spin = s;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
float Ball::getSpin(){return spin;}
void Ball::update(float frameTime)
{
    Entity::update(frameTime);

	//movement control
	/*if(input->isKeyDown(VK_UP))
	{
		direction.y = 1;
	}
	if(input->isKeyDown(VK_UP))
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
	D3DXVec2Normalize(&direction,&direction);
	
	spriteData.x += frameTime * velocity.x * direction.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y * direction.y;     // move ship along Y

    //wall-bounding
	
    if (spriteData.x > GAME_WIDTH-ballNS::WIDTH*getScale())
    {
        spriteData.x = GAME_WIDTH/2; 
		spriteData.y = GAME_HEIGHT/2;
		audio->playCue(MISS);
		score1++;
    } 
    else if (spriteData.x < 0)
    {
        spriteData.x = GAME_WIDTH/2;
		spriteData.y = GAME_HEIGHT/2;
		audio->playCue(MISS);
		score2++;
		velocity.x = 100;
		velocity.y = 100;
    }
    if (spriteData.y > GAME_HEIGHT-ballNS::HEIGHT*getScale())
    {
        direction.y *= -1;
		velocity *= .9;
		spriteData.y = GAME_HEIGHT-ballNS::HEIGHT*getScale() - 1;
	}
	else if (spriteData.y < 0)
	{
		velocity *= .9;
		direction.y *= -1;
		
	}
	velocity.y += frameTime * GRAVITY * direction.y  * spin;
	spriteData.angle += frameTime * spin * ballNS::ROTATION_RATE;
	
}
