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

// CTFzoom_navigate  hold members and methods that are used in zooming in and out of game board and scrolling view on compass points.
// 
//  CTFzoom_navigate file is a subsidiary file for  CatchTheFly class 
// THEY are both called form CatchTheFly::update() that is called from CatchTheFly::Game


//******************************************************************************************************
//struct GamePiece
//{
//   gameNS::Types type;
//   std::string  name;
//   float x;  // window x,y
//   float y;
//   int row;  // row and col of hexagon
//   int col;
//   float scale;
//   Entity *pEntity;   // changed to Entity obj so can use all vectory, ai, stuff. 
//};
//******************************************************************************************************

#include "catchTheFly.h"
using namespace catchTheFlyNS;

//******************************************************************************************************************* bucci 
// called form CatchTheFly::update() that is called from CatchTheFly::Game
void CatchTheFly::scaleMap()
{  //   the background X and Y is where the background (that is the map)'s 0,0  will be drawn on the users area at users area x,y 
   float scale = 0;  scale = tile.getScale();

   if (input->getCharIn() == '0' && (scale > MIN_SCALE))  // zoom all the way out
   {
     tile.setScale(MIN_SCALE);
     mapX = 0.15f * GAME_WIDTH;
     mapY = 0.5f * GAME_HEIGHT;
     scale = MIN_SCALE;  // 'scale' is used to set tile.setScaleLast(scale) below...
   }
   else
   if (input->getCharIn() == '1' )  // reset scale to 1 : 1 so (x,y) == off set (deltaX, deltaY) in scale
   {
      mapX = 0.0 * GAME_WIDTH;
      mapY = 0.0 * GAME_HEIGHT;
      tile.setScale(ONE_TO_ONE_SCALE);
   }
   else
     if (input->getCharIn() == '2' && (scale < MAX_SCALE))  // zoom all the way in 
     {
       mapX = 0.0 * GAME_WIDTH;
       mapY = 0.0 * GAME_HEIGHT;
       tile.setScale(MAX_SCALE);
     }
     else
         if (input->isKeyDown(PLUS_KEY) || input->isKeyDown(PLUS_KEY_NUMPAD) && (scale < MAX_SCALE)) // zoom in 
         {
			 if (scale + scale * MAP_ZOOM_RATE < MAX_SCALE)
				 tile.setScale(scale += scale *  MAP_ZOOM_RATE);
			 else
				 tile.setScale(MAX_SCALE);
            mapX -= 0.5f * scale * MAP_ZOOM_RATE * GAME_WIDTH;
            mapY -= 0.5f * scale * MAP_ZOOM_RATE * GAME_HEIGHT;
         }
         else
            if (input->isKeyDown(MINUS_KEY) || input->isKeyDown(MINUS_KEY_NUMPAD)  && (scale > MIN_SCALE))  // zoom out
            {
				if (scale - scale * MAP_ZOOM_RATE > MIN_SCALE)
					tile.setScale(scale -= scale * MAP_ZOOM_RATE);
				else
					tile.setScale(MIN_SCALE);
               mapX += 0.5f * scale * MAP_ZOOM_RATE * GAME_WIDTH;
               mapY += 0.5f * scale * MAP_ZOOM_RATE * GAME_HEIGHT;
            }			
   
   tile.setScaleLast(scale);
   mapChange = true;    // if the mapX, mapY is changed this will be set to true so any counter on the move can correct for new map position / scale
   //   input->clear(inputNS::KEYS_PRESSED);   DO NOT USE input->clear(inputNS . . .  here it is only called at end of Game::run as Game has the controller's input in it.
   // CatchTheFly::update is called from inside Game::run so it will clear all input at its end
   return;
}// ****************** END CatchTheFly::zoomMap() 
//******************************************************************************************************************* bucci 


//******************************************************************************************************************* bucci 
// called form CatchTheFly::update() that is called from CatchTheFly::Game
/*******
mouse wheel value is +/- 120 on a wheel click, use old mouse wheel value to save LAST wheel click value
as once current value is read in "void CatchTheFly::update()" to test if mouse wheel moved
then in input.h
int  getMouseWheel()
{  int wheel = mouseWheel;   lastMouseWheel = mouseWheel; mouseWheel = 0;  return wheel;  }
mouseWheel value set to 0 so new value
I do not know why mouseWheel is set to 0, if I comment that line out it still works, maybe needed for multiple reads ? ? ?
********/
void CatchTheFly::scrollMap()
{
   float sOffSet = 1.0f / tile.getScale();
   if (sOffSet == 1) sOffSet = 0;
   float mapXLast, mapYLast;
   mapXLast = mapX;    mapYLast = mapY;
   if (input->isKeyDown(LEFT_ARROW) && GAME_WIDTH / 2 > getTileData_X(0, 0))
   {
      if (mapX < GAME_WIDTH)
         mapX += MAP_SCROLL_RATE;  // really this is off set for tile x,y draw but works like scroll     
   }
   else
      if ( (input->isKeyDown(UP_ARROW)  && GAME_HEIGHT / 2 > getTileData_Y(0, 0)) || (input->getLastMouseWheel() > 0  && GAME_HEIGHT / 2 > getTileData_Y(0, 0)) )
         mapY += MAP_SCROLL_RATE;
      else
         if (input->isKeyDown(RIGHT_ARROW) && GAME_WIDTH / 2 < getTileData_X(0, TILE_MAP_WIDTH - 1))
         {
            mapX -= MAP_SCROLL_RATE;
         }
         else
            if (input->isKeyDown(DOWN_ARROW)  && GAME_HEIGHT / 2 < getTileData_Y(TILE_MAP_HEIGHT - 1, 0) || (input->getLastMouseWheel() < 0 && GAME_HEIGHT / 2 < getTileData_Y(TILE_MAP_HEIGHT - 1, 0)))
            {
               mapY -= MAP_SCROLL_RATE;
            }

   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   // Now try to got mouse to move map up/down and left/right  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            else
              if (input->getMouseMButton() == TRUE )
              {
                int stop;
                stop = 0;
              }


   // Now try to got mouse to move map up/down and left/right  ----------------------------------------------------------------------------------------------------------------------
   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

   if ((GAME_WIDTH - TEXTURE_WIDTH) < getTileData_X(0, 0))
      mapX = 2 * mapXLast;;
   if (0 >= getTileData_X(TILE_MAP_HEIGHT - 1, TILE_MAP_WIDTH - 1))
      mapX = mapXLast;
   mapChange = true;    // if the mapX, mapY is changed this will be set to true so any counter on the move can correct for new map position / scale
   //   input->clear(inputNS::KEYS_PRESSED);   DO NOT USE input->clear(inputNS . . .  here it is only called at end of Game::run as Game has the controller's input in it.
   // CatchTheFly::update is called from inside  Game::run so it will clear all input at its end	
   return; 
}; // ********************** END CatchTheFly::navigateMap() ********************************************************************   
//******************************************************************************************************************* bucci 
