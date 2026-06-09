// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine constants.h v4.0
// Last modification: Mar-1-2015
// move the Fly about randomly by timer.

#include "catchTheFly.h"

using namespace catchTheFlyNS;

//  counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Red Ball", "Green Ball" };
// enum _eGAME_COUNTER {_eFLY, _eS1, _eS2, _eS3, _eC1, _eC2, _eC3, _eA1, _eBL, _eBS, _eSBOAN, _eHL, _eRB, _eGB };    // used to id a particular game counter and get ride of the hard values in many 'if' statements
void CatchTheFly::flyAI()
{
  if (_bSplashScreen)   // if _bSplashScreen IS  being displayed then DO NOT let the Fly's AI work
  {
    return;
  }
   
  timer = time(NULL);

  // 'frameTime' time required for last frame to be rendered     'frameTimeElapsed' is total of all those frame times.   that data can be used as a timer to control game counter movement
  // this code sets the movement time of the AIR counters "A1..." as they move from one terrain type to and other
  gameCounter[0].frameTimeElapsed = frameTime + gameCounter[0].frameTimeElapsed;
  if (gameCounter[0].frameTimeElapsed >= gameCounter[0].timeTillMove)
  {
    gameCounter[0].row = 1 + (rand() % TILE_MAP_HEIGHT - 1); // set fly off randomly over titles
    gameCounter[0].col = 1 + (rand() % TILE_MAP_WIDTH - 1);
    gameCounter[0].timeTillMove = (2.0f + (float) (rand() % 9) );
    gameCounter[0].frameTimeElapsed = 0.0f;
  }


  return ;
} // end 