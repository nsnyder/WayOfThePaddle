// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 ship.h v1.0

#ifndef _BALL_H                 // Prevent multiple definitions if this 
#define _BALL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ballNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 150;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 0;           // texture has 2 columns
    const int   SHIP1_START_FRAME = 0;      // ship starts at frame 0
    const int   SHIP1_END_FRAME = 0;         // ship animation frames 0,1,2,3
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
	const float BALL_SCALE = 0.2f;

}

// inherits from Entity class
class Ball : public Entity
{
private:
	float spin;
protected:
	VECTOR2 direction;
public:
    // constructor
    Ball();
	float getSpin();
	void setSpin(float);
	void invertSpin();
    // inherited member functions
    void update(float frameTime, bool gameOver);
};
#endif

