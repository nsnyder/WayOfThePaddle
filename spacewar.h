// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "paddle.h"
#include "ball.h"
#include <sstream>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	// My defines

	#define SONY_IMAGE_SCALE 1

// My vars

	float sonyXVel;
	float sonyYVel;
	TextureManager sonyTexture;
	TextureManager bgTexture;
	TextureManager ballTexture;
	Paddle sony;
	Paddle sony2;
	Ball ball;
	Image bg;
	TextDX  *dxFont96;
	bool sonyLastFrame, sony2LastFrame;

	struct position{
		float xPos;
		float yPos;
		position() {xPos = 0; yPos = 0;}
	} sonyPos;

	struct velocity{
		float xVel;
		float yVel;
		velocity() { xVel = 0; yVel = 0;}
	} sonyVel, sony2Vel;
	
public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

//Stuff for physics


#endif
