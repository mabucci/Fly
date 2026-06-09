// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// copyright (c) 02 / 17 / 2016 by Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// createThisClass.h

#ifndef _CATCHTHEFLY_H           // Prevent multiple definitions if this 
#define _CATCHTHEFLY_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
// needed to stop error on compile with 'gameCounter[cn].gCTstruct = *localtime(&timer);'  'localtime and localtime_s' ???   has to do with Preprocessor Definitions
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// GameCounters class has been put after Game class and infront of CatchTheFly class
#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include <time.h>

namespace catchTheFlyNS
{
   using namespace gameNS;    // THIS seems to work but I do not know if it is kosher???
   const int TEXTURE_HEIGHT = 32;
   const int TEXTURE_WIDTH = 37;
   const int TEXTURE_COLS = 9;
   const int COUNTER_COLS = 10;
   const int MAP_HEIGHT = 30 ;  // ******* this is how the map on the screen is shown ***************************************
   const int MAP_WIDTH = 40;
   struct XYhexagonNext { float x,  y; };  // will hold neighboring hexagon x,y pairs for testing to see which hexagon to move to in CTFgmaeCounters.cpp
   const enum COMPASSPOINTS {N,NE,SE,S,SW,NW}; // compass points to neighboring hexagons north north-east … 

   const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 13, 13, 13,
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
      13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
   };

}

//=============================================================================
// This class is the core of the game
//=============================================================================
class CatchTheFly : public Game 
{
  private:
    // game items
  TextureManager menuTexture, backgroundTexture, tileTextures, flyTexture, nativeTexture, counterTexture; // textures
  TextureManager splash1Texture;  // texture  ************************************************************** bucci 
  Image splash1;  // ************************************************************************************ bucci
  Image   menu;               // menu image
  Image   background;         // background image
//   Image fly;                        // fly image
  Entity fly;   // try fly as entity so can use entity's ai
  Entity native; // native is also to be controlled by ai
  Image tile;    //    Image counter;  Images do not react they are not game pieces that have to move independent of the island...
  Entity counter;  //  counter is entity so can use entity's movement methods an entity moves independent of the island...
  Entity  *pCounterEntity; // Remember there are only one each  title-Image,  and fly, native and counter, -Entity.
  TextDX  *dxFont;            // DirectX font
  std::string  message;
  float messageY;
  bool _bSplashScreen;
  float   mapX, mapY;
	bool mapChange;  // if the mapX, mapY is changed this will be set to true so any counter on the move can correct for new map position / scale
	bool bBoatBreak;  // for breaking out of 'for loop' in CTFgCmove.cpp   set to 'false' in catchTheFly.cpp
	double   _dGCSwapStack[catchTheFlyNS::MAP_HEIGHT][catchTheFlyNS::MAP_WIDTH][NUMBER_OF_NAMES]; // if two or more game counters are on the same map hexagon they will be entered in this array and then can have their 'gCDrawPriority' (that determines which counter is draw first to last) swapped by the player to see what counters are on that hexagon 
	time_t timer;  //  needed to get curent time of game counter arrival at current hexagon
  time_t timerOld; // needed so every game counter has unique arrival time a current hexagon
public:
  // Constructor
  CatchTheFly();
  // Destructor
  virtual ~CatchTheFly();
  // Initialize the game
  void initialize(HWND hwnd);
  void update();      // must override pure virtual from Game
  void ai();          // "
  void collisions();  // "
  void render();      // "
  void releaseAll();
  void resetAll();
	void scrollMap();   // move around map ************************************************
    // void navigateMap();  // move around map ************************************************
	void scaleMap();    // zoom in and out form map background ********************************
	// void zoomMap();      // zoom in and out form map background ********************************
	//void setMapChange(bool b) { mapChange = b; } // inline mapChange valuel
	//bool getMapChange() { return mapChange; }
  void nameGameCounters(Entity*);  
  //void updateCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, Entity*, int, const int);
  //void updateCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, int, const int);
  void updateCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, int, const int);   // used for SEARCH AND CATCH placement on board
  void updateSeaCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, int, const int); // used for BOAT placement on board
  void updateAirCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, int, const int);   // used for AIR placement on board       
  void updateFNCounters(TileData td[][catchTheFlyNS::MAP_WIDTH], Input* i, int, const int ); // ** FLY AND NATIVE  placement on board
  void CatchTheFly::gCmove(TileData td[][catchTheFlyNS::MAP_WIDTH], Input* input, const int cn,  const int textureWidth, const int textureHight); // used to set destination of counters and their type of movement
  void CatchTheFly::gCAddWayPoint(TileData td[][catchTheFlyNS::MAP_WIDTH], Input* input, const int cn); // used to set destination of counters and their type of movement
  void CatchTheFly::gCTileUpKeep(TileData td[][catchTheFlyNS::MAP_WIDTH]);
	void CatchTheFly::gCShuffleCounters(); // // this method will hold catchTheFly class methods that will let the player "swap" counters that are on the same hexagon
  void CatchTheFly::flyAI();   // this  method will hold the Fly's AI 
  void CatchTheFly::nativeAI();
  void CatchTheFly::displayCounterPath(TileData td[][catchTheFlyNS::MAP_WIDTH], Input*, const int textureWidth, const int textureHight);  // will display the path of a players game counter
  // this method will hold the Native's  AI
};
#endif