// CTFgcAddWayPoint
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

// CTFgCAddWayPoint  holds members and methods that will way points to  the counter's path around the board
// New method to set user counters movement, direction, seed, destination.... 
//  CTFgCAddWayPoint file is a subsidiary file for  CatchTheFly class methods 


//******************************************************************************************************
//  FOR REFERENCE -------------------------------------
//namespace gameNS
//{
//   const char FONT[] = "Courier New";  // font
//   const int POINT_SIZE = 14;          // point size
//   const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);    // white
//   enum Types { FLY, SEARCH, CATCH, AIR, BOAT, NATIVE };
//}
//
//struct TileData {   // tile data struct it holds curent and last x,y, tile t ype, and the curent tile scale
//   float x;
//   float y;
//   float xLast;
//   float yLast;
//   int tileType;
//   float tileScale;
//};
//
//struct GameCounter
//{
//std::string  name;
//gameNS::Types C_type;   // game counter type see enum Types in namespace gameNS above...
//int idNumber;   //   fly = 0  SEARCH 100 series  CATCH 200 series  AIR 300 series  BOAT (large) 400 series BOAT (small) 500  NATIVES 600 series
//int row;  // row and col of current hexagon
//int col;
//int rowd; // row and col destination hexagon
//int cold;
//int rowd1; // second possible destination
//int cold1;
//int rowd2; // third possible destination
//int cold2;
//int rowd3; // forth possible destination
//int cold3;
//
//int oldRow; // last row and col that counter was on use this to keep moving counter from lossing it place on game board is board is scaled or scrolled
//int oldCol;
//int gCCurentFrame;  // the frame for this particular counter S1 or BL or what ever this gameCounter array member represents
//double  gCDrawPriority; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 
//                        // this way if two or more game counters are on the same hexagon hitting tab key will shift the draw order and bottom counter will
//                        // be drawn on top THING OF FCII counters
//double gCArrivalTime;  // time at which a game counter arrives at the current hexagon it is on						 
//float x;  // window x,y current location
//float y;
//float xd; // window x,y destination 
//float yd;
//float deltaX;  // change in counter's x as the counter moves
//float deltaY; // change in counter's y as the counter moves
//float tempX; // used as temporary x,y position as the counter is moving from hex to hex.
//float tempY; // also used by boats in their movements. 
//float deltaXd;  // NOW  need to come up with a deltaXd deltaYd  that is a delta off set from td[0][0] to the boats destination 
//float deltaYd;  // that deltaXd and deltaYd can be updated as map is scrolled and scaled     that might work to keep boats movement working the way you want 
//float xDt;  // temporary floats for movement delta x,y  try keep boats in consort with map scale/scroll 
//float yDt;
//float closingRateNew;  // if 'closingrate is   '-'   then moving toward destination, if 'closeingrate'   '+'    then moving away and counter is in run-a-way
//float closingRateOld;
//float gBoatSpeed;   // used for the boat navigation speed as boat move over sea  
//float scale;
//float frameTimeElapsed; // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
//float timeTillMove;          // this will hold the time that the game counter must wait until it can move to next hexagon used with frame time elapse to give screen count down
//bool counterClickedOn; // if a counter is in a hexagon and that hexagon is mouse clicked with left mouse button then this is set to true for that game counter
//bool gCVisible;   // make the game piece visible or not 
//bool gCmove;   // bool that will have this game counter move towards its  xd, yd destination that is also its rowd, and cold destination
//bool gCcalcD;   // bool to show new deltaX delta Y has been calculated
//bool mChange; // this way each boat can see if map was changed,  if you just switch on map change the first boat to reach its destination will stop the other boat from getting its xd yd up dated
//bool gCTopCounter; // this is bool that if true shows that this counter is the top (or only) counter on this hexagon
//struct tm gCTstruct;  // to format time to H:M:S game counter arrived at current hexagon  used in game.cpp text display
//Entity *pEntity;  // just in case
//};
// const std::string counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Red Ball", "Green Ball" };
// enum _eGAME_COUNTER { _eFLY, _eS1, _eS2, _eS3, _eC1, _eC2, _eC3, _eA1, _eBL, _eBS, _eSBOAN, _eHL, _eRB, _eGB };    // used to id a particular game counter and get ride of the hard values in many 'if' statements
//******************************************************************************************************
// if all values same x == xd  row == rows … then this counter is at rest and will not move, but if in gCmove the destination values are  
// different than the location values then the counter will have its position changed, it will move 'step by step' towards its destination values.

#include "catchTheFly.h"
using namespace catchTheFlyNS;
// New method to set user counters movement, direction, seed, destination.... 
// to have gotten here cn == _eRB and cn-1 == _eHL 
void CatchTheFly::gCAddWayPoint(TileData td[][TILE_MAP_WIDTH], Input* input, const int cn)
{
 /*****************
 Look at second 'if' below
    if player calls RED BALL on a non moving game counter then clicks RMBD or SPACE_BAR on that game counter's Hexagon the game counter would be
      told to find the best way to get to where it is     so in CTFgameCounters a game counter at xH == 0 yH == 0 would be moved to the closest Hexagon
      to xH == 0 yH == 0 mostly that would be xH == 1 yH == 0, then game counter would move back to xH == 0 yH == 0   that is why the counters were moving
      down one column and then back when RED BALL was on them and  RMBD or SPACE_BAR clicked
      the last two '&& (||)' in the 'if' will stop the game counter from being told to move to where it currently is
****************************/

  char _cWayPointEntered;

    for (int i = 1; i < 10; ++i)
    {
      if(gameCounter[cn - 1].row == gameCounter[i].row && gameCounter[cn - 1].col == gameCounter[i].col &&
        gameCounter[i].gCTopCounter == true && (gameCounter[i].row != gameCounter[_eRB].row || gameCounter[i].col != gameCounter[_eRB].col))
      {
        _cWayPointEntered = input->getCharIn();
        switch (_cWayPointEntered)  // this will make the input char == to the key code 
        {
        case 'W': 
          _cWayPointEntered = 'w';
          break;
        case 'X':
          _cWayPointEntered = 'x';
          break;
        case 'Y':
          _cWayPointEntered = 'y';
          break;
        case 'Z':
          _cWayPointEntered = 'z';
          break;
        default:
          break;
        } // 

        switch (_cWayPointEntered)
        {
        case  'w': {
          gameCounter[i].rowd1 = gameCounter[cn].row;
          gameCounter[i].cold1 = gameCounter[cn].col;
          gameCounter[i]._caWayPointsActive[0] = 'w';
          gameCounter[i].WayPointsToReached++;
          input->clearAll();
          break;
        }
        case 'x': {
          gameCounter[i].rowd2 = gameCounter[cn].row;
          gameCounter[i].cold2 = gameCounter[cn].col;
          gameCounter[i]._caWayPointsActive[1] = 'x';
          gameCounter[i].WayPointsToReached++;
          input->clearAll();
          break;
        }
        case 'y': {
          gameCounter[i].rowd3 = gameCounter[cn].row;
          gameCounter[i].cold3 = gameCounter[cn].col;
          gameCounter[i]._caWayPointsActive[2] = 'y';
          gameCounter[i].WayPointsToReached++;
          input->clearAll();
          break;
        }
        case 'z': {
          gameCounter[i].rowd4 = gameCounter[cn].row;
          gameCounter[i].cold4 = gameCounter[cn].col;
          gameCounter[i]._caWayPointsActive[3] = 'z';
          gameCounter[i].WayPointsToReached++;
          input->clearAll();
          break;
        }
        default:
        {
          _cWayPointEntered = '\0';   // Should not need this as only 'w,x,y,z' will get player into “CTFgcAddWayPoint”
          input->clearAll();
          break;
        }
        } // END of 'switch' ------------------------
        input->clearAll(); // Should not need this as only 'w,x,y,z' will get player into “CTFgcAddWayPoint”
      }// END of 'if' on ' gameCounter[cn-1].row  ' -------------------------------------------------
      else
      {
        // may need for something ....
      }
    }// END of 'for' on i ->10 --------------------------------------------------------------------------
  return;
}// END of gCAddWayPoint method --------------------------------------------------------------------------------------------