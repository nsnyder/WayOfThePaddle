// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
int score1=0,score2=0;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	
};

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	score1=0;
	score2=0;
	youWin = false;
	gameOver = false;
    Game::initialize(hwnd); // throws GameError

	// Ball
	if (!ballTexture.initialize(graphics, BALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Sony texture initialization failed"));
	if (!ball.initialize(this, ballNS::WIDTH,ballNS::HEIGHT,0, &ballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init ball"));
	ball.setScale(.4);

	//player 1
	if (!sonyTexture.initialize(graphics, SONY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Sony texture initialization failed"));
	if (!sony.initialize(this, 64,64,paddleNS::TEXTURE_COLS, &sonyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init sony"));
	if (!bgTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Background texture initialization failed"));
	if (!bg.initialize(graphics, 640,480,0, &bgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init background"));
	sony.setX(50);
	sony.setY(GAME_HEIGHT/2 - (sony.getHeight()*SONY_IMAGE_SCALE)/2);
	sony.setScale(SONY_IMAGE_SCALE);
	
	//player 2
	if (!sony2.initialize(this, 64,64,paddleNS::TEXTURE_COLS, &sonyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init sony"));
	sony2.setX(590);
	sony2.setY(GAME_HEIGHT/2 - (sony2.getHeight()*SONY_IMAGE_SCALE)/2);
	sony2.setScale(SONY_IMAGE_SCALE);
	
	// 96 point Arial
	dxFont96 = new TextDX();
    if(dxFont96->initialize(graphics, 96, false, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	
	sonyVel.xVel = 600;
	sonyVel.yVel = 600;

	sony2Vel.xVel = 0;
	sony2Vel.yVel = 150;

	sonyLastFrame = false;
	sony2LastFrame = false;

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//Unomment to get the image to move
	ball.update(frameTime,gameOver);
	if(!gameOver) {
		//pos.x = sony.getX() + sonyVel.xVel * frameTime;
		//sony.setX(pos.x);
		//WRAP

 

		//REFLECT
 

		////////////////
		// INPUT MODS
		////////////////

		D3DXVECTOR2 direction(input->getMouseX()-64/2-sony.getX(),input->getMouseY()-64/2-sony.getY());
		D3DXVECTOR2 direction2(0,0);
	
	
		D3DXVec2Normalize(&direction, &direction);

		pos.y = sony.getY() + sonyVel.yVel * frameTime * direction.y;
		sony.setY(pos.y);

		pos2.y = sony2.getY() + sony2Vel.yVel * frameTime * direction2.y;
		sony2.setY(pos2.y);

	

		//Getting old positions so velocities work
		D3DXVECTOR2 tmpVel = sony.getVelocity();
		D3DXVECTOR2 tmpVel2 = sony2.getVelocity();
		float oldX = sony.getX();
		float oldY = sony.getY();
		float oldX2 = sony2.getX();
		float oldY2 = sony2.getY();

		//player 1
			// Instant jump
		/*
		sony.setY(input->getMouseY());
		if(input->getMouseX()-64/2<GAME_WIDTH/2){
			sony.setX(input->getMouseX()-64/2);
		}*/
	
		// Gradual movement
		if(sonyVel.xVel*frameTime > abs((input->getMouseX()-64/2)-sony.getX()) ) {
			pos.x = input->getMouseX()-64/2;
		} else {
			pos.x = sony.getX() + sonyVel.xVel * frameTime * direction.x;
		}
		if(sonyVel.yVel*frameTime > abs((input->getMouseY()-64/2)-sony.getY()) ) {
			pos.y = input->getMouseY()-64/2;
		} else {
			pos.y = sony.getY() + sonyVel.yVel * frameTime * direction.y;
		}

		sony.setX(pos.x);
		sony.setY(pos.y);
		if(sony.getX()>GAME_WIDTH/2-64) {
			sony.setX(GAME_WIDTH/2-64);
		}
	

		//player 2

		if(ball.getY() > sony2.getY() +sony2.getHeight()){
			sony2.setY(sony2.getY() + 2);
		}
		else if(ball.getY() < sony2.getY()){
			sony2.setY(sony2.getY() - 2);
		}
	

		//setting velocities
		if(!sonyLastFrame){
			tmpVel.x = (sony.getX() - oldX) / frameTime;
			tmpVel.y = (sony.getY() - oldY) / frameTime;
			sony.setVelocity(tmpVel);
		}
		//update velocity of ai
			tmpVel2.x = (sony2.getX() - oldX2) / frameTime;
			tmpVel2.y = (sony2.getY() - oldY2) / frameTime;
			sony2.setVelocity(tmpVel2);
		
		
	
	
	
	

		/*if (sony2.getY() > 480-sony2.getHeight()*sony2.getScale())
		{
			sony2.setY(480-sony2.getHeight()*sony2.getScale());
		}
		if (sony2.getY() < 0)
		{
			sony2.setY(0);
		}*/
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	if(!gameOver) {
		D3DXVECTOR2 temp;
		if(ball.collidesWith(sony, temp) && !sonyLastFrame && ball.getVelocity().x < 0)
		{
			sonyLastFrame = true;
			sony.setFrames(1,8);
			sony.setCurrentFrame(1);
			sony.setLoop(false);
			D3DXVECTOR2 newDir = -ball.getVelocity();
			newDir.x += sony.getVelocity().x;
			if(newDir.x <100){
				newDir.x = 100;
			}
			else if(newDir.x > 1000){
				newDir.x = 1000;
			}
			ball.setSpin(ball.getSpin() + sony.getVelocity().y);
			newDir.y = ball.getVelocity().y;
			ball.setVelocity(newDir);
			audio->playCue(HIT);
	
		}
		if(ball.collidesWith(sony2, temp) && !sony2LastFrame && ball.getVelocity().x > 0)
		{
			sony2LastFrame = true;
			sony2.setFrames(1,8);
			sony2.setLoop(false);
			sony2.setCurrentFrame(1);
			D3DXVECTOR2 newDir = -ball.getVelocity();
			newDir.x += sony2.getVelocity().x;
			ball.setSpin(ball.getSpin() + sony2.getVelocity().y);
			newDir.y = ball.getVelocity().y;
			ball.setVelocity(newDir);
			audio->playCue(HIT);
		}
		if(ball.collidesWith(sony, temp)) {
			sonyLastFrame = true;
		} else { sonyLastFrame = false; }
		if(ball.collidesWith(sony2, temp)) {
			sony2LastFrame = true;
		}else {
			sony2LastFrame = false;
		}
		sony.update(frameTime);
		sony2.update(frameTime);
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	bg.draw();
	if(!gameOver) {
		sony.draw();
		sony2.draw();
		ball.draw();
		std::stringstream s1;
		s1 << score1;
		std::stringstream s2;
		s2 << score2;
		dxFont96->print(s1.str(),110,76);         // display message
		dxFont96->print(s2.str(),400,76);         // display message

		if(score1==1) { youWin = true; gameOver = true; }
		if(score2==1) { youWin = false; gameOver = true; }
	
		/*std::stringstream vel;
		vel << sony2.getVelocity().y;
		dxFont96->print(vel.str(),0,0);
		*/
	} else {
		if(youWin) {
			dxFont96->print("You win! :D",20,GAME_HEIGHT/2);         // display message
		} else {
			dxFont96->print("You lose! :(",20,GAME_HEIGHT/2);         // display message
		}
	}

	ball.draw();
	std::stringstream s1;
	s1 << score1;
	std::stringstream s2;
	s2 << score2;
	dxFont96->print(s1.str(),110,76);         // display message
	dxFont96->print(s2.str(),400,76);         // display message

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	sonyTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	sonyTexture.onResetDevice();
    Game::resetAll();
    return;
}
