// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// game.h v1.3

#ifndef _GAME_H                 // Prevent multiple definitions if this 
#define _GAME_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Game;

#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "console.h"
#include "gameError.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include <math.h>
#include <time.h>

namespace gameNS
{
    const char FONT[] = "Courier New";  // font
    const int POINT_SIZE = 14;          // point size
    const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255,255,255,255);    // white
    enum Types { FLY, SEARCH, CATCH, AIR, BOAT,  NATIVE, MARKER};
}

struct TileData {   // tile data struct  holds curent and last x,y, tile t ype, and the curent tile scale
   float x;  // curent x,y
   float y;
   float xLast;  // last x,y
   float yLast;
   int tileType;  // type of tile beach, hill, forest...
   float tileMDifficultyLow; // low difficulty value of moving through this map tile's terain
   float tileMDifficultyMedium; // medium difficulty value of moving through this map tiles's terain
   float tileMDifficultyHight;    // hight difficulty value of moving through this map tile's terain
   float tileScale;
   int row; // curent row, col
   int col;
};

struct GameCounter
{   
  std::string  name;   
  gameNS::Types C_type;   // game counter type see enum Types in namespace gameNS above...
  int idNumber;   //   fly = 0  SEARCH 100 series  CATCH 200 series  AIR 300 series  BOAT (large) 400 series BOAT (small) 500  NATIVES 600 series
  int row;  // row and col of current hexagon
  int col;
  int rowd; // row and col destination hexagon  IF NO WAY POINTS WANTED
  int cold;
  int rowd1; // first possible destination IF WAY POINTS ARE WANTED
  int cold1;
  int rowd2; // second possible destination IF WAY POINTS ARE WANTED
  int cold2;
  int rowd3; //  third possible destination IF WAY POINTS ARE WANTED
  int cold3;
  int rowd4;  // forth possible destination IF WAY POINTS ARE WANTED
  int cold4; 
  int WayPointsToReached;  // number of way points reached 
  char  _caWayPointsActive[4];  // number of way points entered   default 0
  int oldRow; // last row and col that counter was on use this to keep moving counter from lossing it place on game board is board is scaled or scrolled
  int oldCol;
  int gCCurentFrame;  // the frame for this particular counter S1 or BL or what ever this gameCounter array member represents
  double  gCDrawPriority; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 
                        // this way if two or more game counters are on the same hexagon hitting tab key will shift the draw order and bottom counter will
                        // be drawn on top THING OF FCII counters
  double gCArrivalTime;  // time at which a game counter arrives at the current hexagon it is on						 
  float x;  // window x,y current location
  float y;
  float xd; // window x,y destination 
  float yd;
  float xd1; // window x1,y1 destination 
  float yd1;
  float xd2; // window x2,y2 destination 
  float yd2;
  float xd3; // window x3,y3 destination 
  float yd3;
  float xd4; // window x4, y4 destination
  float yd4;

  float deltaX;  // change in counter's x as the counter moves
  float deltaY; // change in counter's y as the counter moves
  float tempX; // used as temporary x,y position as the counter is moving from hex to hex.
  float tempY; // also used by boats in their movements. 
  float deltaXd;  // NOW  need to come up with a deltaXd deltaYd  that is a delta off set from td[0][0] to the boats destination 
  float deltaYd;  // that deltaXd and deltaYd can be updated as map is scrolled and scaled     that might work to keep boats movement working the way you want 
  float xDt;  // temporary floats for movement delta x,y  try keep boats in consort with map scale/scroll 
  float yDt;
  float closingRateNew;  // if 'closingrate is   '-'   then moving toward destination, if 'closeingrate'   '+'    then moving away and counter is in run-a-way
  float closingRateOld; 
  float gBoatSpeed;   // used for the boat navigation speed as boat move over sea  
  float scale;
  float frameTimeElapsed; // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
  float timeTillMove;          // this will hold the time that the game counter must wait until it can move to next hexagon used with frame time elapse to give screen count down
  bool counterClickedOn; // if a counter is in a hexagon and that hexagon is mouse clicked with left mouse button then this is set to true for that game counter
  bool gCVisible;   // make the game piece visible or not 
  bool gCmove;   // bool that will have this game counter move towards its  xd, yd destination that is also its rowd, and cold destination
  bool gCcalcD;   // bool to show new deltaX delta Y has been calculated
  bool mChange; // this way each boat can see if map was changed,  if you just switch on map change the first boat to reach its destination will stop the other boat from getting its xd yd up dated
  bool gCTopCounter; // this is bool that if true shows that this counter is the top (or only) counter on this hexagon
  struct tm gCTstruct;  // to format time to H:M:S game counter arrived at current hexagon  used in game.cpp text display
Entity *pEntity;  // just in case
};

// In game.h game classs  use this to pass to line data back and forth between CTHgCmove and CTHgameCounters …. to catchTheFly class, has something to 
//do with scope can't put the drawLine call in any CTH... sub file for some reason  graphics->spriteBegin(); just does not pickup in catchTheFly sub file, 
//but it should it may be order of calling that I do not know of ?

struct LinePoints
{
	float x1;
	float y1;
	float x2;
	float y2;
	float width;
	COLOR_ARGB color;
	bool bDrawLine;
  bool bDrawLineGreen;
};

class Game
{
protected:
    // common game properties
    Graphics *graphics;             // pointer to the one and ONLY Graphics object
    Input   *input;                 // pointer to Input
    Audio   *audio;                 // pointer to Audio
    Console *console;               // pointer to Console
    MessageDialog *messageDialog;   // pointer to MessageDialog
    InputDialog *inputDialog;       // pointer to InputDialog
    HWND    hwnd;                   // window handle
    HRESULT hr;                     // standard return type
    LARGE_INTEGER timeStart;        // Performance Counter start value
    LARGE_INTEGER timeEnd;          // Performance Counter end value
    LARGE_INTEGER timerFreq;        // Performance Counter frequency
    float   frameTime;              // time required for last frame
    float   fps;                    // frames per second
    TextDX  dxFont;                 // DirectX font for fps
    bool    fpsOn;                  // true to display fps
    bool    gameDataOn;                  // true to display game data
	  bool    counterDataOn;               // true to display game counter position and distination only data
    DWORD   sleepTime;              // number of milli-seconds to sleep between frames
    bool    paused;                 // true if game is paused
    bool    initialized;
    std::string  command;           // command from console
    TileData tileData[TILE_MAP_HEIGHT][TILE_MAP_WIDTH];  //    this struct array will hold data on individual tiles x,y  last x,y, tile type and tile scale
    GameCounter gameCounter[NUMBER_OF_NAMES];   //  a gameCounter[] of GamePiece structs will hold individual game piece info AND game pointers like markers; Highlighter, Ball, and Line data ....
  	LinePoints linePoints; // used for graphics->drawLine call.
	                                                                       												                          
    float xH;              // x location of first hexagon
    float yH;              // y location of first hexagon

	int mHrow;          // mouse Hexagon row
	int mHcol;			// mouse Hexagon column

public:
	// SETs **********************************************************************************
   // set and get of xH ******************************************************************* bucci 
   void setXh(float x) { xH = x; }
   void setYh(float y) { yH = y; }
   void setMHrow(int r) { mHrow = r; }
   void setMHcol(int c) { mHcol = c; }
   // GETs ***********************************************************************************
   // set and get of yH   
   float getXh() { return xH; }
   float getYh(){ return yH; }
   int getMHrow() { return mHrow; }
   int getMHcol() { return mHcol;  }

   //set tileData struct *******************************************************************************
   void setTileData_X(int row, int col, float xNew) {
      if (xNew != tileData[row][col].x) 
         tileData[row][col].xLast = tileData[row][col].x;
      tileData[row][col].x = xNew; 
   }      
   void setTileData_Y(int row, int col, float yNew) { 
      if (yNew != tileData[row][col].y) 
         tileData[row][col].yLast = tileData[row][col].y;
      tileData[row][col].y = yNew; 
   }
   //void setTileData_Row(int r) { row = r; }
   //void setTileData_Col(int c) { col = c;  }
     
   void setTileData_xLast(int row, int col, float xL)
   {
      if (xL != tileData[row][col].x)  tileData[row][col].xLast = xL;
   }

   void setTileData_yLast(int row, int col, float yL)
   {
      if (yL != tileData[row][col].y)  tileData[row][col].yLast = yL;
   }

   void setTileData_T(int row, int col, int t) { tileData[row][col].tileType = t; }
   void setTileData_S(int row, int col, float s) { tileData[row][col].tileScale = s; }
   
   //get tileData struct
   float getTileData_X(int row, int col) { return tileData[row][col].x; }
   float getTileData_Y(int row, int col) { return tileData[row][col].y; }
   float getTileData_xLast(int row, int col) { return tileData[row][col].xLast; }
   float getTileData_yLast(int row, int col) { return tileData[row][col].yLast; }
   int   getTileData_T(int row, int col) { return tileData[row][col].tileType; }
   float   getTileData_S(int row, int col) { return tileData[row][col].tileScale; }
   //int getTileData_Row() { return row; }
   //int getTileData_Col() { return col; }

    // Constructor
    Game();
    // Destructor
    virtual ~Game();

    // Member functions

    // Window message handler
    LRESULT messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    // Initialize the game
    // Pre: hwnd is handle to window
    virtual void initialize(HWND hwnd);

    // Call run repeatedly by the main message loop in WinMain
    virtual void run(HWND);

    // Call when the graphics device was lost.
    // Release all reserved video memory so graphics device may be reset.
    virtual void releaseAll();

    // Recreate all surfaces and reset all entities.
    virtual void resetAll();

    // Delete all reserved memory.
    virtual void deleteAll();

    // Process console commands.
    virtual void consoleCommand();

    // Render game items.
    virtual void renderGame();

    // Handle lost graphics device
    virtual void handleLostGraphicsDevice();

    // Set display mode (fullscreen, window or toggle)
    void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

    // Return pointer to Graphics.
    Graphics* getGraphics() {return graphics;}

    // Return pointer to Input.
    Input* getInput()       {return input;}

    // Exit the game
    void exitGame()         {PostMessage(hwnd, WM_DESTROY, 0, 0);}

    // Return pointer to Audio.
    Audio* getAudio()       {return audio;}

    // Pure virtual function declarations
    // These functions MUST be written in any class that inherits from Game

    // Update game items.
    virtual void update() = 0;

    // Perform AI calculations.
    virtual void ai() = 0;

    // Check for collisions.
    virtual void collisions() = 0;

    // Render graphics.
    // Call graphics->spriteBegin();
    //   draw sprites
    // Call graphics->spriteEnd();
    //   draw non-sprites
    virtual void render() = 0;
};

#endif
