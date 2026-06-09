// CTFdisplayCounterPath
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

// CTFdisplayCounterPath  holds members and methods that will display the way points and path(s) to a game counter's path around the board 
//  CTFdisplayCounterPath file is a subsidiary file for  CatchTheFly class methods 


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
void CatchTheFly::displayCounterPath(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, const int textureWidth, const int textureHight)
{
  float A = (float)textureWidth;  //Hexagon dimensions ****************************************
  float r = (sqrtf(3) * A / 4.0f);
  float R = (2 * r / sqrtf(3));
  float xH, yH;
  float mX = (float)input->getMouseX();  //  give current x,y of mouse pointer on client array of window 
  float mY = (float)input->getMouseY();
  float  width; // for graphics class drawLine method.   that calls  LP_DXLINE   line->Draw(endpoints, 2, color);   see method in graphics.
  float boatX, boatY;
  std::string boatN;   // to hold boat name "Boat Large" or "Boat Small"
  COLOR_ARGB color = graphicsNS::YELLOW;  // line color 
  float deltaLineX, deltaLineY;   // the deltaLineX/Y is the off set from boat to end of navigation line
  float incrementLineX, incrementLineY; // that fraction of the navigation line that is to be tested against all hexagon centers
  int navigationLineDivisor = 10;  // value to divide the navigation line length with
  float fx, fy;  // for holding debug values
  width = 0.5f;   // line width  
  int boatNumber; // used instead of scope resolution operator :: to get 'i' of outer 'for' loop to inner 'for' loop 
                  // may not need this here see if on mouse left below..........................
                  // r -= 5.0f ;   // the -5 is our buffer inside the hexagon
                  // R -= 5.0f;
  if (td[0][0].tileScale != 0.0f)  r *= td[0][0].tileScale;  // this give r,R the same scale as the hexagons
  if (td[0][0].tileScale != 0.0f) R *= td[0][0].tileScale;


      if (gameCounter[_eHL].gCVisible)  // find game counter that highlighter is on    _eHL == highlighter enum
      {
        for (int i = 0; i < NUMBER_OF_NAMES; ++i)
        {
          if(i >= _eS1 && i <= _eA1)   // only players game counters should get past this point 
          if (gameCounter[i].gCmove == true && gameCounter[i].gCTopCounter == true 
                    && gameCounter[_eHL].row == gameCounter[i].row  && gameCounter[_eHL].col == gameCounter[i].col  )
          {
            gameCounter[_eGB].gCVisible = true;   // sets up green ball to be drawn at game counter's destination
            gameCounter[_eGB].gCTopCounter = true;
            gameCounter[_eGB].row = gameCounter[i].rowd;
            gameCounter[_eGB].col = gameCounter[i].cold;
            gameCounter[_eGB].x = gameCounter[i].xd;
            gameCounter[_eGB].y = gameCounter[i].yd;
            gameCounter[_eGB].scale = gameCounter[i].scale;
            linePoints.x1 = gameCounter[i].x;  // sets up green line to be drawn from game counter to its destination
            linePoints.y1 = gameCounter[i].y;
            linePoints.x2 = gameCounter[i].xd;
            linePoints.y2 = gameCounter[i].yd;
            linePoints.bDrawLineGreen = true;
            return;
          }// END gCmove 'true' 
          
          if (i >= _eBL && i <= _eBS && gameCounter[i].gCmove == true )
          {
            boatX = gameCounter[i].x;  // now have current boat x,y values at upper left of rectangle  not center of hexagon
            boatY = gameCounter[i].y;

            if (abs(boatX + R - mX) < r / 2.0f) // this is our current buffer to make sure mouse pointer is pointing to center of hexagon 
              if (abs(boatY + r - mY) < r / 2.0f)
               {
                  gameCounter[_eGB].gCVisible = true;   // sets up green ball to be drawn at game counter's destination
                  gameCounter[_eGB].gCTopCounter = true;
                  gameCounter[_eGB].row = -1;
                  gameCounter[_eGB].col = -1;
                  gameCounter[_eGB].x = td[0][0].x  + gameCounter[i].deltaXd * td[0][0].tileScale;   // boats need the off set from tile [0][0] and the scale 
                  gameCounter[_eGB].y = td[0][0].y + gameCounter[i].deltaYd * td[0][0].tileScale;
                  gameCounter[_eGB].scale = gameCounter[i].scale;
                  linePoints.x1 = gameCounter[i].x;  // sets up green line to be drawn from game counter to its destination
                  linePoints.y1 = gameCounter[i].y;
                  linePoints.x2 = td[0][0].x + gameCounter[i].deltaXd * td[0][0].tileScale;
                  linePoints.y2 = td[0][0].y + gameCounter[i].deltaYd * td[0][0].tileScale;
                  linePoints.bDrawLineGreen = true;
                  return;
                }
          }
            else
          {
            gameCounter[_eGB].gCVisible = false;      // make sure that green line and ball are not drawn
            gameCounter[_eGB].gCTopCounter = false;
            linePoints.bDrawLineGreen = false;
          }
        }// END  for loop on NUMBER_OF_NAMES
      }// END   if on gCVisible
      return;
} // END  method displayCounterPath ------------------------------------------------------------------------------------------------------