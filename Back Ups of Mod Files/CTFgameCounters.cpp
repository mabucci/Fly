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

// CTFgameCounters  hold members and methods that will update the counters used in the game
// their position on the board and their individual characteristics and conditions
//  CTFgameCounters file is a subsidiary file for  CatchTheFly class methods 


//******************************************************************************************************
// For reference 
//struct GameCounter
//{
//	std::string  name;
//	gameNS::Types C_type;   // game counter type see enum Types in namespace gameNS above...      //   Only one 'BOAT' Type  for all boats large and small
//	int idNumber;   //   fly = 0  SEARCH 100 series  CATCH 200 series  AIR 300 series  BOAT (large) 400 series BOAT (small) 500  NATIVES 600 series
//	float x;  // window x,y current location
//	float y;
//	float xd; // window x,y destination 
//	float yd;
// float deltaX;  // change in counter's x as the counter moves
// float deltaY; // change in counter's y as the counter moves
//	int row;  // row and col of current hexagon
//	int col;
//	int rowd; // row and col destination hexagon
//	int cold;
//	float scale;
//	int gCCurentFrame;  // the frame for this particular counter S1 or BL or what ever this gameCounter array member represents
//	bool counterClickedOn; // if a counter is in a hexagon and that hexagon is mouse clicked with left mouse button then this is set to true for that game counter
//	bool gCVisible;   // make the game piece visible or not 
//	Entity *pEntity;  // just in case
//};
//******************************************************************************************************

#include "catchTheFly.h"
using namespace catchTheFlyNS;
                                                   // Entity* pE == Image*pE   pointer Counter Entity 
void CatchTheFly::nameGameCounters(Entity* pE)
{
   // enum Types { FLY, SEARCH, CATCH, AIR, BOATLARGE, BOATSMALL, NATIVE, MARKER};  Boat Large == 8						   Highlighter == 11 
   // const std::string counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Ball", "Green Ball"};
  // enum _eGAME_COUNTER {_eFLY, _eS1, _eS2, _eS3, _eC1, _eC2, _eC3, _eA1, _eBL, _eBS, _eSB, _eHL, _eBR, _eBG };
   int j = 0; // for Types 
   for (int i = 0; i < NUMBER_OF_NAMES; ++i)
   { //    enum Types { FLY, SEARCH, CATCH, AIR, BOATLARGE, BOATSMALL, NATIVE} ;        
     if (i == 0)
     {  // i == 0 == FLY
       gameCounter[i].name = counterNames[i];
       gameCounter[i].C_type = (gameNS::Types) j; // j starts at 0 == Types FLY
       gameCounter[i].idNumber = 0; // FLY id is zero		
       gameCounter[i].row = 1 +(rand() % TILE_MAP_HEIGHT - 1); // set fly off randomly over titles
       gameCounter[i].col  = 1 +(rand() % TILE_MAP_WIDTH - 1);
       gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
       gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
       gameCounter[i].gCCurentFrame = 3;  // the frame for this particular counter S1 or BL or what ever this gameCounter array member represents
       gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
       gameCounter[i].gCVisible = true;   // make the game piece visible or not 
       gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
       gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
       gameCounter[i].pEntity = &counter; //  just in case we needed a pointer to an Entity obj
       gameCounter[i].deltaX = 0.0;   // change in counter's x as the counter moves
       gameCounter[i].deltaY = 0.0;  // change in counter's y as the counter moves 
       gameCounter[i].timeTillMove = gameCounter[0].timeTillMove = (5.0f + (float) (rand() % 5));  // used in flyAI method to randomly move the 'Fly' around
       timer = time(NULL);   // get time now
       gameCounter[i].gCArrivalTime = timer; // set to game start time 
       gameCounter[i].gCDrawPriority = timer; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                            // set to 'i' to start then can be changed later by player 
       gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
     }
      else
        if (i >= 1 && i <= 3)
        {  // i == 1 to 3 some SEARCH
          if (i == 1) ++j;
          gameCounter[i].name = counterNames[i];
          gameCounter[i].C_type = (gameNS::Types) j;  // J == 1 == Types S1 so on
          gameCounter[i].idNumber = 100 + i; // all SEARCH counters are 100 seares           
          gameCounter[i].row = 0;
          gameCounter[i].col = i;
          gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
                                                                 // if game counter is not moving then row,col == rowd, cold						gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;
          gameCounter[i].gCCurentFrame = i - 1;  // the frame for this particular counter S1 or BL or what ever this gameCounter array member represents
          gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
          gameCounter[i].gCVisible = true;   // make the game piece visible or not 
      		gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
          gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
          gameCounter[i].pEntity = &counter; //  just in case we needed a pointer to an Entity obj
          gameCounter[i].deltaX = 0;   // change in counter's x as the counter moves
          gameCounter[i].deltaY = 0;  // change in counter's y as the counter moves 
          gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
          timer = time(NULL);   // get time now
          gameCounter[i].gCArrivalTime = timer; // set to game start time 
          gameCounter[i].gCDrawPriority = timer; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                               // set to 'i' to start then can be changed later by player 
          gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
        }
            else
            if (i >= 4 && i <= 6)
            {  // i == 4 to 6 == some CATCH
            if (i == 4) ++j;
            gameCounter[i].name = counterNames[i];               
            gameCounter[i].C_type = (gameNS::Types) j;
            gameCounter[i].idNumber = 200 + i-3; // all CATCH counters are 200 seares  when i == 4,  i-3 == 1 idNumber set to 201, 202, 203 
            gameCounter[i].row = 0;
            gameCounter[i].col = i;
            gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
            gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
            // if game counter is not moving then row,col == rowd, cold
            gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
            gameCounter[i].cold = gameCounter[i].col;
            gameCounter[i].gCCurentFrame = i ;
            gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
            gameCounter[i].gCVisible = true;   // make the game piece visible or not 
            gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
            gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
            gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
            gameCounter[i].pEntity = &counter;
            gameCounter[i].deltaX = 0;   // change in counter's x as the counter moves
            gameCounter[i].deltaY = 0;  // change in counter's y as the counter moves 
            gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
            timer = time(NULL);   // get time now
            gameCounter[i].gCArrivalTime = timer; // set to game start time 
            gameCounter[i].gCDrawPriority = timer; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                                 // set to 'i' to start then can be changed later by player 
            gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
            }
     // set to 'i' to start then can be changed later by player 
          else
          if (i == 7)
          { // i == 7 some AIR
          if (i == 7) ++j;
          gameCounter[i].name = counterNames[i];                 
          gameCounter[i].C_type = (gameNS::Types) j;
          gameCounter[i].idNumber = 300 + i-6; // all AIR counters are 300 seares
          gameCounter[i].row = 0;
          gameCounter[i].col = 0;
          gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
						          // if game counter is not moving then row,col == rowd, cold
          gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;
          gameCounter[i].gCCurentFrame =  i+2 ; // 9 is AIR texture column 
          gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
          gameCounter[i].gCVisible = true;   // make the game piece visible or not 
				  gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
				  gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
          gameCounter[i].pEntity = &counter;
				  gameCounter[i].deltaX = 0;   // change in counter's x as the counter moves
				  gameCounter[i].deltaY = 0;  // change in counter's y as the counter moves 
				  gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
          timer = time(NULL);   // get time now
          gameCounter[i].gCArrivalTime = timer; // set to game start time 
          gameCounter[i].gCDrawPriority = timer; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                               // set to 'i' to start then can be changed later by player 
          gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
          }

         else
          if (i == 8)
          {  // i == 8 some BOAT  only one 'BOAT' Type  for all boats large and small
          if (i == 8) ++j;
          gameCounter[i].name = counterNames[i];                    
          gameCounter[i].C_type = (gameNS::Types) j;
          gameCounter[i].idNumber = 400 + i-7; // all BOAT LARGE counters are 400 seares
          gameCounter[i].row = -1;
          gameCounter[i].col = -1;
          gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
							          // if game counter is not moving then row,col == rowd, cold
          gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
          gameCounter[i].cold = gameCounter[i].col;
          gameCounter[i].x = tileData[0][0].x;
          gameCounter[i].y = tileData[0][0].y;
          gameCounter[i].gCCurentFrame =  i-1 ;
          gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
          gameCounter[i].gCVisible = true;   // make the game piece visible or not 
          gameCounter[i].gBoatSpeed = 20.0f;   // used for the boat navigation speed as boat move over sea
          gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
          gameCounter[i].pEntity = &counter;
          gameCounter[i].deltaX =  164.5f;   //  boat's scaled off set from H(0,0)   also starting position  when boat get move command (xDta, yDta) are set to (xDd, yDd) 
          gameCounter[i].deltaY = -33.0f;  //  boat's scaled off set from H(0,0)   also starting position     when boat get move command (xDta, yDta) are set to (xDd, yDd) 
          gameCounter[i].frameTimeElapsed = 0.0f;  // time between boat movement.   boats move by x,y float value change
          gameCounter[i].gCcalcD = false;   // bool to show new deltaX delta Y has been calculated
          gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
          gameCounter[i].gCArrivalTime = -1.0; // set to -1 at game start to show this 
          gameCounter[i].gCDrawPriority = 0.0; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                               // set to 'i' to start then can be changed later by player 
          gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
          gameCounter[i].closingRateNew = 0.0f;  // if 'closingRate is   '-'   then moving toward destination, if 'closeingRate'   '+'    then moving away and counter is in run-a-way
          gameCounter[i].closingRateOld = 0.0f;
          }

          else
            if (i == 9)
            {  // i == 9 some BOAT  j == j         only one 'BOAT' Type  for all boats large and small       
              gameCounter[i].name = counterNames[i];                      
              gameCounter[i].C_type = (gameNS::Types) j;
              gameCounter[i].idNumber = 500 + i-8; // all BOAT SMALL counters are 500 seares                      
              gameCounter[i].row = -1;
              gameCounter[i].col = -1;
							gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
							gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
																	  // if game counter is not moving then row,col == rowd, cold
							gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
							gameCounter[i].cold = gameCounter[i].col;
              gameCounter[i].x = tileData[0][3].x;
              gameCounter[i].y = tileData[0][3].y;
              gameCounter[i].gCCurentFrame = i-1 ;
              gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
							gameCounter[i].gCVisible = true;   // make the game piece visible or not 
							gameCounter[i].gBoatSpeed = 20.0f;   // used for the boat navigation speed as boat move over sea
							gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
							gameCounter[i].pEntity = &counter;
							gameCounter[i].deltaX = 120.0f;   // boat's scaled off set from H(0,0)   also starting position
							gameCounter[i].deltaY = -33.0f;   // boat's scaled off set from H(0,0)   also starting position
							gameCounter[i].frameTimeElapsed = 0.0f;  // time between boat movement.   boats move by x,y float value change
							gameCounter[i].gCcalcD = false;   // bool to show new deltaX deltaY has been calculated
							gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
							gameCounter[i].gCArrivalTime = -1.0; // set to -1 at game start to show this 
              gameCounter[i].gCDrawPriority = 0.0; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                                   // set to 'i' to start then can be changed later by player 
              gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
              gameCounter[i].closingRateNew = 0.0f;  // if 'closingRate is   '-'   then moving toward destination, if 'closeingRate'   '+'    then moving away and counter is in run-a-way
              gameCounter[i].closingRateOld = 0.0f;
            }
							else
								if (i == 10)
                 {  // i == 10 some NATIVE
                  if (i == 10) ++j;
                  gameCounter[i].name = counterNames[i];                          
                  gameCounter[i].C_type = (gameNS::Types) j;
                  gameCounter[i].idNumber = 600 + i-9; // all NATIVE counters are 600 seares            
                  gameCounter[i].row = 1 + ( rand() % TILE_MAP_HEIGHT - 1); // set NATIVE off randomly over titles
                  gameCounter[i].col =  1 + (rand() % TILE_MAP_WIDTH - 1); // set NATIVE off randomly over titles
						      gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
						      gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
																		    // if game counter is not moving then row,col == rowd, cold
                  gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
						      gameCounter[i].gCVisible = true;   // make the game piece visible or not 
						      gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
						      gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
                  gameCounter[i].gCCurentFrame = i+7;
						      gameCounter[i].deltaX = 0;   // change in counter's x as the counter moves
						      gameCounter[i].deltaY = 0;  // change in counter's y as the counter moves 
						      gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
                  timer = time(NULL);   // get time now
                  gameCounter[i].gCArrivalTime = timer; // set to game start time 
                  gameCounter[i].gCDrawPriority = timer; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                                       // set to 'i' to start then can be changed later by player 
                  gameCounter[i].gCTopCounter = false;  // shows that this counter is top (or only) counter on this hexagon
                }

						else
              if (i >= 11)
              {  // i >= some MARKER 
                if (i == 11) ++j;
                gameCounter[i].name = counterNames[i];
                gameCounter[i].C_type = (gameNS::Types) j;
                gameCounter[i].idNumber = 700 + i - 10; // all  MARKERS are 700 seares            
                gameCounter[i].row = rand() % TILE_MAP_HEIGHT - 1; // set MARKER off randomly over titles  'Ball' and  only visible when called 'Highlighter' will follow mouse pointer
                gameCounter[i].col = rand() % TILE_MAP_WIDTH - 1; // set MARKER off randomly over titles
                gameCounter[i].rowd = gameCounter[i].row;  // row and col destination hexagon
                gameCounter[i].cold = gameCounter[i].col;     // current window x,y and destination xd, yd are set in update see bottom of this file.
                                        // if game counter is not moving then row,col == rowd, cold								
                gameCounter[i].counterClickedOn = false; // use to tell which counter was clicked on    all set to false at start
                gameCounter[i].gCVisible = true;   // make the game piece visible or not 
                gameCounter[i].gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
                gameCounter[i].gCmove = false;  // bool that will have this game counter move towards its it xd, yd destination that is also its rowd, and cold destination
                gameCounter[i].gCCurentFrame = i + 33;
                gameCounter[i].deltaX = 0;   // change in counter's x as the counter moves
                gameCounter[i].deltaY = 0;  // change in counter's y as the counter moves 
                gameCounter[i].timeTillMove = -1.0f;  // set to -1 so when the counter moves it can be given a new count down time
                gameCounter[i].gCArrivalTime = time(NULL); // set to game start time so gCTopCounter is set to 'true' in catchTheFly.cpp update method   this way if this counter is the only counter on a hexagon it will be draw   only counters with gCTopCounter == 'true' are draw so counter with latest arrival time is the one that is drawn that way it looks like last counter to get to a hexagon (without shuffle) is seen on top THINK FCII
                gameCounter[i].gCDrawPriority = 0.0; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw(); 		                     
                                                     // set to 'i' to start then can be changed later by player 
                gameCounter[i].gCTopCounter = true;  // shows that this counter is top (or only) counter on this hexagon
              }//end if above...                       			

   }  //end 'for loop' on NUMBER_OF_NAMES...
}// ************* END Constructor ******************************

//*******************************************************************************************************
// Destructor
//*******************************************************************************************************
// td == to tile data array that has the x, y scale, and xH, yH, and terrain type of tile.
// input == pointer to the input class, has all mouse, keyboard, game pad inputs.
// cEA[] == array of game counter Entities
// cn == index number for cIA[]
// textureWidth == to the constants file TEXTURE_WIDTH needed to calculate r, R of Hexagon, this will help find the sweet spot inside each hexagon
// that is the area that can be clicked on to select a hexagon
//
// **************** OVER LOADED method updateCounters   gameCounter array 
//void CatchTheFly::updateCounters(TileData td[][40], Input* input, Entity* cEA, int cn, const int textureWidth)
////void CatchTheFly::updateCounters(TileData td[][40], Input* input,  int cn, const int textureWidth)
//{
//   float A = (float)textureWidth;
//   float r = (sqrtf(3) * A / 4.0f);
//   float R = (2 * r / sqrtf(3));
//   float xH, yH;
//   float mX = (float)input->getMouseX();
//   float mY = (float)input->getMouseY();
//   int cN;   // counter Number
//   cN = cn;
//   // may not need this here see if on mouse left below..........................
//   //r -= 5.0f ;   // the -5 is our buffer inside the hexagon
//   //R -= 5.0f;
//   if (td[0][0].tileScale != 0.0f)  r *= td[0][0].tileScale;  // this give r,R the same scale as the hexagons
//   if (td[0][0].tileScale != 0.0f) R *= td[0][0].tileScale;
//
//   for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
//   {
//      for (int col = 0; col < TILE_MAP_WIDTH; ++col)
//      {
//         xH = td[row][col].x;
//         yH = td[row][col].y;
//
//         cN = cn;
//            if (input->getMouseLButton())  // If left mouse button is clicked **************************
//            {
//               if (abs(xH + R - mX) < r / 2.0f) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
//                  if (abs(yH + r - mY) < r / 2.0f)
//                  {
//                     cEA[cN]->setX( td[row][col].x );   // cN == counter Number
//                     cEA[cN]->setY( td[row][col].y );
//                     cEA[cN]->setScale( td[row][col].tileScale );
//                     cEA[cN]->setRow(  row );
//                     cEA[cN]->setCol( col );
//                  }
//            }// end if mouse left button down ******************************
//            else
//            {
//              int row = cEA[cN]->getRow( );  int col = cEA[cN]->getCol( );
//               cEA[cN]->setX( td[row][col].x );
//               cEA[cN]->setY( td[row][col].y );
//               cEA[cN]->setScale( td[row][col].tileScale );
//               // *****************************************************************************
//            }
//         }
//      }
//      return;
//}// ************** END OF overloaded method updateCounters ***************************************



// **************************** FLY AND NATIVE  FLY AND NATIVE  ******************************************************
// ****************** OVER LOADED method updateSeaCounters  
//  FLY counter is 0 id   and  all  NATIVE counters are 600 seares
void CatchTheFly::updateFNCounters(TileData td[][40], Input* input, int cn, const int textureWidth)
{
	if (gameCounter[cn].idNumber / 100 == 6 || gameCounter[cn].idNumber == 0)
	{
		float A = (float)textureWidth;
		float r = (sqrtf(3) * A / 4.0f);
		float R = (2 * r / sqrtf(3));
		float mX = (float)input->getMouseX();
		float mY = (float)input->getMouseY();

		// may not need this here see if on mouse left below..........................
		//r -= 5.0f ;   // the -5 is our buffer inside the hexagon
		//R -= 5.0f;
		if (td[0][0].tileScale != 0.0f)  r *= td[0][0].tileScale;  // this give r,R the same scale as the hexagons
		if (td[0][0].tileScale != 0.0f) R *= td[0][0].tileScale;

		// this just sets the game counters x, y to the tile's x,y it is on   need that to draw it 
		// if gCmove == false then this counter has not been told to move to a new location
		if (gameCounter[cn].gCmove == false)
		{
			gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
			gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
			gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
		}
		else  // if gCmove == true then this game counter is on the move from x,y to xd,yd   row,col to rowd, cold
			if (gameCounter[cn].gCmove == true)
			{
				gameCounter[cn].x = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				gameCounter[cn].y = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
				gameCounter[cn].gCDrawPriority = timer;  // this is when this 'gameCounter[cn]' move to this hexagon    last is drawn on top...
				gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the hexagon it is currently one
				gameCounter[cn].gCTstruct = *localtime(&timer);
			}

		//for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
		//{
		//   for (int col = 0; col < TILE_MAP_WIDTH; ++col)
		//   {
		//      xH = td[row][col].x;
		//      yH = td[row][col].y;
		//      //if (input->getMouseLButton())  // If left mouse button is clicked **************************
		//      //{
		//      //   if (abs(xH + R - mX) < r / 2.0f) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
		//      //      if (abs(yH + r - mY) < r / 2.0f)
		//      //      {
		//      //         gameCounter[cn].x = td[row][col].x;
		//      //         gameCounter[cn].y = td[row][col].y;
		//      //         gameCounter[cn].row = row;
		//      //         gameCounter[cn].col = col;
		//      //         gameCounter[cn].scale = td[row][col].tileScale;
		//      //      }
		//      //}// end if mouse left button down ******************************
		//      //else
		//      {
		//         gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
		//         gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
		//         gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
		//         // empty *****************************************************************************
		//      }
		//   }// END for on col...
		//}// END for on row
	}
	return;
}// END  ***************************** FLY AND NATIVE  FLY AND NATIVE ******************************************************
 // ********************************** FLY AND NATIVE  FLY AND NATIVE ******************************************************



// ********************************************** SEARCH AND CATCH  SEARCH AND CATCH **************************************
// ********************************************** SEARCH AND CATCH  SEARCH AND CATCH **************************************
// ****************** OVER LOADED method updateCounters  Image& **************************************************************
// ****************** OVER LOADED method updateCounters  Image& **************************************************************
void CatchTheFly::updateCounters(TileData td[][40], Input* input, int cn, const int textureWidth)
{   // all SEARCH counters are 100 seares idNumber set are 101, 102, 103...   all CATCH counters are 200 seares  idNumber set to 201, 202, 203... 
	if (gameCounter[cn].idNumber / 100 == 1 || gameCounter[cn].idNumber / 100 == 2 )
	{	
		float A = (float)textureWidth;
		float r = (sqrtf(3) * A / 4.0f);
		float R = (2 * r / sqrtf(3));
		float mX = (float)input->getMouseX();
		float mY = (float)input->getMouseY();
		int  rowT; // row and col of destination  hexagon  and temp row and col
		int  colT;
		float tempd; // temporary distance from adjacent hexagon to destination hexagon smallest one winds.  
		int moveTime; //  gets the random number that is used in a 'switch' to pick and set counter member 'timeTillMove'
		XYhexagonNext xyNextH[6]; // will hold neighboring hexagon x,y pairs for testing to see which hexagon to move to
		int row, col;  // row, col will be used with int values the get (R-2,C) . . . to get neighboring hexagon's x,y values for testing.
					   // also used to hold new row and col counter will move to		
					 // may not need this here see if on mouse left below..........................
					 //r -= 5.0f ;   // the -5 is our buffer inside the hexagon
					 //R -= 5.0f;
	  if (td[0][0].tileScale != 0.0f)  r *= td[0][0].tileScale;  // this give r,R the same scale as the hexagons
	  if (td[0][0].tileScale != 0.0f) R *= td[0][0].tileScale;

    // if a players game counter is on the move and the player has highlighted it and pushed the 's' or 'S' key this is a signal to stop this game counter on the
    // current hexagon   by simply settings its' rowd = row, and cold = col, and gCmove = false   this seems to work 
    // HIGHLIGHTER cn == 11
    // clear all input so a string of “sssss” do not build up in the input stream 
    // GROUND ****
    if ( (input->isKeyDown('s') || input->isKeyDown('S')  )&& (gameCounter[cn].row == gameCounter[11].row && gameCounter[cn].col == gameCounter[11].col) )
    {
      gameCounter[cn].rowd = gameCounter[cn].row;
      gameCounter[cn].cold = gameCounter[cn].col;
      gameCounter[cn].gCmove = false;
      gameCounter[cn].timeTillMove = 0.0;
      input->clearAll();
      return;
    }

	  // this just sets the game counters x, y to the tile's x,y it is on   need that to draw it 
	  // if gCmove == false then this counter has not been told to move to a new location

	  if (gameCounter[cn].gCmove == false)
	  {
		  gameCounter[cn].frameTimeElapsed = 0.0f;  // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
		  gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
		  gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
		  gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale		
	  }
    else
      // this way only the top game counter will get the new Hexagon x,y coordinates and by that only the top game counter on a hexagon will move I HOPE!!!
     // Search and Catch counters
    if (gameCounter[cn].gCmove == true && gameCounter[cn].gCTopCounter == false  )
    {
      gameCounter[cn].frameTimeElapsed = 0.0f;  // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
      gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
      gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
      gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale		
      if (gameCounter[cn].row == gameCounter[cn].rowd &&  gameCounter[cn].col == gameCounter[cn].cold)
      {
        gameCounter[cn].gCmove = false;   // will set all the game counters below the top counter on a hexagon to  'gCmove = false' 
      }
    }
    
	  else  // if gCmove == true then this game counter is on the move from x,y to xd,yd   row,col to rowd, cold
		  if (gameCounter[cn].gCmove == true)
		  {
			  // this map change reset of position my have been solved by the code below I will keep it commented out just in case
			  //if (mapChange)
			  // {				
				 // gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
				 // gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
				 // gameCounter[cn].xd = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				 // gameCounter[cn].yd = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				 // gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
				 // mapChange = false;
				 // return;
			  //}// END if(mapChange) ...

			   // now will use this information to move the game counter
			   // need to slow down movement so will use frameTime when frameTime elapsed to >= 1 second then move to next hexagon 
			   // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other frameTimeElapsed is set to 0.0 in CTFgCmove
			   // To move from anyone of these hexagons to an adjacent hexagon IF THE ORIGINAL HEXAGON row col is ODD,EVEN number

			   // there are four possibly combination of odd, even row, col values for each hexagon
			   // It seems to work on the row, not the column,  ODD,EVEN AND ODD,ODD have same results

			   // from hexagon R,C  where row value is odd, and col value is even.   ROW,COL → ODD, EVEN
			   // to hexagon north R - 2, C
			   // to hexagon north east R - 1, C + 1
			   // to hexagon south east R + 1, C + 1
			   // to hexagon south R + 2, C
			   // to hexagon south west R + 1, C
			   // to hexagon north west R - 1, C

			   //      		  from hexagon R, C  where row value is odd, and col value is odd.ROW, COL → ODD, ODD
			   //				  to hexagon north R - 2, C
			   //				  to hexagon north east R - 1, C + 1
			   //				  to hexagon south east R + 1, C + 1
			   //				  to hexagon south R + 2, C
			   //				  to hexagon south west R + 1, C
			   //				  to hexagon north west R - 1, C
			   //          
			   //                It seems to work on the row, not the column,  EVEN, ODD AND EVEN, EVEN have same results
			   //				  from hexagon R, C  where row value is even, and col value is odd.ROW, COL → EVEN, ODD
			   //				  to hexagon north R - 2, C
			   //				  to hexagon north east R - 1, C
			   //				  to hexagon south east R + 1, C
			   //				  to hexagon south R + 2, C
			   //				  to hexagon south west R + 1, C - 1
			   //				  to hexagon north west R - 1, C - 1
			   //
			   //				  from hexagon R, C  where row value is even, and col value is even.ROW, COL → EVEN, EVEN
			   //				  to hexagon north R - 2, C
			   //				  to hexagon north east R - 1, C
			   //				  to hexagon south east R + 1, C
			   //				  to hexagon south R + 2, C
			   //				  to hexagon south west R + 1, C - 1
			   //				  to hexagon north west R - 1, C - 1
			   //
			   //

			   // Will try to come up with an algorithm that will let the counter pick the best direction to move in one hexagon at a time to get to it destination.
			   // the counter will be limited to the movements outlined above.the counter can only move to an adjacent hexagon.
			   // When a counter is on the move it knows  x, y xd, yd, so look at all the adjacent hexagons and test their x, y for distances to target hexagon's x,y.
			   // The adjacent hexagon with x, y closest to target hexagon's x,y is the hexagon counter should move to  
			   //  struct XYhexagonNext { int x, y; };  // will hold neighboring hexagon x,y pairs for testing to see which hexagon to move to in CTFgmaeCounters.cpp
			   //  const enum COMPASSPOINTS { N, NE, SE, S, SW, NW }; // compass points to neighboring hexagons north north-east … 

			   // 'frameTime' time required for last frame to be rendered     'frameTimeElapsed' is total of all those frame times.   that data can be used as a timer to control game counter movement
			   // this code sets the movement time of the AIR counters "A1..." as they move from one terrain type to and other
			  gameCounter[cn].frameTimeElapsed = frameTime + gameCounter[cn].frameTimeElapsed;
			  if (gameCounter[cn].timeTillMove <= -1.0f)
			  {
				  moveTime = rand() % 3;
				  switch (moveTime)
				  {
				  case 0: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyLow;
					  break;
				  case 1: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyMedium;
					  break;
				  case 2: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyHight;
					  break;
				  default:   gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyLow;
					  break;
				  }// end 'switch'...
			  }// end 'if'...

			if (gameCounter[cn].frameTimeElapsed >= gameCounter[cn].timeTillMove) // set speed of counter movement from hex to hex
			  {
				timer = time(NULL);   // get time now  time(NULL) == time(&timer)
				gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the destination hexagon it is currently one
				gameCounter[cn].gCTstruct = *localtime(&timer);  // should let game display H:M:S of arrival time

				gameCounter[cn].timeTillMove = -1.0f;  // so will get new 'timeTillMove' value above
			    row = gameCounter[cn].row;
			    col = gameCounter[cn].col;

				  if (row % 2)
				  {
					  if (row <= 1)
					  {
						  xyNextH[N].x = -1;
						  xyNextH[N].y = -1;  // get x,y location of hexagon to north				  
					  }
					  else
					  {
						  xyNextH[N].x = td[row - 2][col].x;
						  xyNextH[N].y = td[row - 2][col].y;  // get x,y location of hexagon to north			
					  }
					  //---------------------------						
					  if (row <= 0 || col >= TILE_MAP_WIDTH - 1)
					  {
						  xyNextH[NE].x = -1;
						  xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[NE].x = td[row - 1][col + 1].x;
						  xyNextH[NE].y = td[row - 1][col + 1].y;  // get x,y location of hexagon to north east 										
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 2 || col >= TILE_MAP_WIDTH - 2)
					  {
						  xyNextH[SE].x = -1;
						  xyNextH[SE].y = -1;  // get x,y location of hexagon to north		
					  }
					  else
					  {
						  xyNextH[SE].x = td[row + 1][col + 1].x;
						  xyNextH[SE].y = td[row + 1][col + 1].y; // ...							 
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 2)
					  {
						  xyNextH[S].x = -1;
						  xyNextH[S].y = -1;  // get x,y location of hexagon to north		
					  }
					  else
					  {
						  xyNextH[S].x = td[row + 2][col].x;
						  xyNextH[S].y = td[row + 2][col].y;
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 2)
					  {
						  xyNextH[SW].x = -1;
						  xyNextH[SW].y = -1;  // get x,y location of hexagon to north		
					  }
					  else
					  {
						  xyNextH[SW].x = td[row + 1][col].x;
						  xyNextH[SW].y = td[row + 1][col].y;
					  }
					  //---------------------------										
					  if (row <= 0)
					  {
						  xyNextH[NE].x = -1;
						  xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[NW].x = td[row - 1][col].x;
						  xyNextH[NW].y = td[row - 1][col].y;
					  }
				  }// END 'if' on  (row%2) ...

				  else // START  'else' on 	if (row%2)  eles row is even number ************************************************************************************
				  {
					  if (row <= 1)
					  {
						  xyNextH[N].x = -1;
						  xyNextH[N].y = -1;  // get x,y location of hexagon to north				  
					  }
					  else
					  {
						  xyNextH[N].x = td[row - 2][col].x;
						  xyNextH[N].y = td[row - 2][col].y;  // get x,y location of hexagon to north				  
					  }
					  //---------------------------
					  if (row <= 0)
					  {
						  xyNextH[NE].x = -1;
						  xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[NE].x = td[row - 1][col].x;
						  xyNextH[NE].y = td[row - 1][col].y;  // get x,y location of hexagon to north east 
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 1)
					  {
						  xyNextH[SE].x = -1;
						  xyNextH[SE].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[SE].x = td[row + 1][col].x;
						  xyNextH[SE].y = td[row + 1][col].y; // ...
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 3)
					  {
						  xyNextH[S].x = -1;
						  xyNextH[S].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[S].x = td[row + 2][col].x;
						  xyNextH[S].y = td[row + 2][col].y;
					  }
					  //---------------------------
					  if (row >= TILE_MAP_HEIGHT - 2 || col <= 0)
					  {
						  xyNextH[SW].x = -1;
						  xyNextH[SW].y = -1;  // get x,y location of hexagon to north east 
					  }
					  else
					  {
						  xyNextH[SW].x = td[row + 1][col - 1].x;
						  xyNextH[SW].y = td[row + 1][col - 1].y;
					  }
					  //---------------------------
					  if (row <= 0 || col <= 0)
					  {
						  xyNextH[NW].x = -1;
						  xyNextH[NW].y = -1;
					  }
					  else
					  {
						  xyNextH[NW].x = td[row - 1][col - 1].x;
						  xyNextH[NW].y = td[row - 1][col - 1].y;
					  }
				  }// END 'if' 'else' on even or odd row...


				  if (row == 0) { xyNextH[NW].x = -1; xyNextH[NW].y = -1; xyNextH[N].x = -1; xyNextH[N].y = -1; xyNextH[NE].x = -1; xyNextH[NE].y = -1; }
				  if (row == TILE_MAP_HEIGHT - 1) { xyNextH[SW].x = -1; xyNextH[SW].y = -1; xyNextH[S].x = -1; xyNextH[S].y = -1; xyNextH[SE].x = -1; xyNextH[SE].y = -1; }
				  // the even rows are the ones that start on the outer left side that is why row%2 if even then = 0 and x,y gets -1				      
				  if (col == 0 && row % 2 == 0) { xyNextH[NW].x = -1; xyNextH[NW].y = -1; xyNextH[SW].x = -1; xyNextH[SW].y = -1; }
				  if (col == 0 && row == TILE_MAP_HEIGHT - 2) { xyNextH[S].x = -1; xyNextH[S].y = -1; } // next to last col 0 hexagon its bottom is out in blue...

				  if (col == TILE_MAP_WIDTH - 1 && row % 2 == 1) { xyNextH[NE].x = -1; xyNextH[NE].y = -1; xyNextH[SE].x = -1; xyNextH[SE].y = -1; }// only blue on the right side...

				  if (col == TILE_MAP_WIDTH - 1 && row == 1) { xyNextH[N].x = -1; xyNextH[N].y = -1; } // last hexagon second row its head is out in blue...

				  if (col == TILE_MAP_WIDTH - 1 && row == TILE_MAP_HEIGHT - 1) { xyNextH[S].x = -1; xyNextH[S].y = -1; } // last hexagon its NE side is out in blue...

																														 //now have all the x,y location values of the surrounding hexagon next find which adjacent hexagon is closest to destination hexagon
																														 // squ(delta x^2+ delta y^2) will give distance to destination hexagon.

																														 // just to give tempd a big value to start will be set to 
				  tempd = GAME_WIDTH * GAME_HEIGHT;

				  for (int i = 0; i < NW + 1; ++i)
				  {
					  if (xyNextH[i].x != -1 || xyNextH[i].y != -1)
						  if (sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2)) <= tempd)
						  {
							  rowT = 0;
							  colT = 0;
							  // temporary distance should not be more than distance between furthest two hexagons for curent counter path
							  tempd = sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2));
							  //td[row][col] id only so need row,col to test x,y of tile  
							  if (row % 2) // if rows are odd
							  {
								  if (i == N) { rowT = row - 2; colT = col; }   // get row, col of  hexagon to north	
								  if (i == NE) { rowT = row - 1; colT = col + 1; }   // get row, col of hexagon to north east	
								  if (i == SE) { rowT = row + 1; colT = col + 1; }   // get row, col of hexagon to south east
								  if (i == S) { rowT = row + 2; colT = col; }   // get row, col of hexagon to south 
								  if (i == SW) { rowT = row + 1; colT = col; }   // get row, col of hexagon to south west
								  if (i == NW) { rowT = row - 1; colT = col; }   // get row, col of hexagon to north west						
							  }
							  else // if rows are even
							  {
								  if (i == N) { rowT = row - 2; colT = col; }   // get row, col of  hexagon to north	
								  if (i == NE) { rowT = row - 1; colT = col; }   // get row, col of hexagon to north east	
								  if (i == SE) { rowT = row + 1; colT = col; }   // get row, col of hexagon to south east
								  if (i == S) { rowT = row + 2; colT = col; }   // get row, col of hexagon to south 
								  if (i == SW) { rowT = row + 1; colT = col - 1; }   // get row, col of hexagon to south west
								  if (i == NW) { rowT = row - 1; colT = col - 1; }   // get row, col of hexagon to north west		
							  }
						  }//END 'if' on  "if (sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2)) <= tempd)"					
				  }// END 'for' on i<=NW...

				   // if this is active counter can't get to 0,0 **************************************************************************************
				   // for testing only ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
				   /*if ( rowT == 0 && colT == 0)
				   {
				   int stop;
				   stop = 1;
				   rowT = gameCounter[cn].oldRow;
				   colT = gameCounter[cn].oldCol;
				   }*/
				  gameCounter[cn].oldRow = rowT;
				  gameCounter[cn].oldCol = colT;
				  // for testing only ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

				  gameCounter[cn].x = td[rowT][colT].x;
				  gameCounter[cn].y = td[rowT][colT].y;
				  gameCounter[cn].col = td[rowT][colT].col;
				  gameCounter[cn].row = td[rowT][colT].row;
				  gameCounter[cn].scale = td[rowT][colT].tileScale;  // can do this with just row col as all tiles have same scale
				  gameCounter[cn].frameTimeElapsed = 0.0f;

				  gameCounter[cn].oldRow = gameCounter[cn].row;
				  gameCounter[cn].oldCol = gameCounter[cn].col;

				  // *********** GET arrival time at new hexagon  *************************
				  timer = time(NULL);   // get time now  time(NULL) == time(&timer)
				  gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the hexagon it is currently one


				  if (gameCounter[cn].rowd == gameCounter[cn].row)  // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
					  if (gameCounter[cn].cold == gameCounter[cn].col)
					  {
						  gameCounter[cn].x = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
						  gameCounter[cn].y = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
						  gameCounter[cn].row = td[gameCounter[cn].rowd][gameCounter[cn].cold].row;
						  gameCounter[cn].col = td[gameCounter[cn].rowd][gameCounter[cn].cold].col;
						  gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
						  gameCounter[cn].gCmove = false;
						  gameCounter[cn].deltaX = 0.0f;
						  gameCounter[cn].deltaY = 0.0f;
					  }// END inner 'if' 

			  }//END 'if' on frameTimeCount >= 1 sec ?
			  else
			  {
				  //  this is the same code as from  “if (gameCounter[cn].gCmove == false )”  except that it does not reset the frameTimeCount to zero
				  //   this way if the map is scaled or scrolled between counter moves the counter will stay fixed to the current hexagon it is on
				  gameCounter[cn].xd = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				  gameCounter[cn].yd = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				  gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
				  gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
				  gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale		
			  }
	    	  timer = time(NULL);   // get time now
			  gameCounter[cn].gCDrawPriority = timer;  // this is when this 'gameCounter[cn]' move to this hexagon    last is drawn on top...		
		//	  gameCounter[cn].gCTstruct = *localtime(&timer);  // should let game display H:M:S of arrival time
		  }//END 'if' gCmove == true...	

   }// END first 'if' on if (gameCounter[cn].idNumber / 100 == 1 ...
    return;
}// ************** END OF overloaded method updateCounters ***************************************
 // ********************************************** SEARCH AND CATCH  SEARCH AND CATCH **************************************
 // ********************************************** SEARCH AND CATCH  SEARCH AND CATCH **************************************


// ************************** BOATS BOATS BOATS **********************************************
// ****************** OVER LOADED method updateSeaCounters  
//   Only one 'BOAT' Type  for all boats large and small
// all BOAT (large) counters are 400 seares   // all BOAT (small) counters are 500 seares
// For boat navigation each boat is given an x,y point somewhere off the shore to move to and remain at until a new x,y position is entered for that boat
// Since boats do not go on land they have a unique navigation system
//   Only one 'BOAT' Type  for all boats large and small
void CatchTheFly::updateSeaCounters(TileData td[][40], Input* input, int cn, const int textureWidth)
{
	if (gameCounter[cn].idNumber / 100 == 4 || gameCounter[cn].idNumber / 100 == 5)
	{
		float A = (float)textureWidth;
		float r = (sqrtf(3) * A / 4.0f);
		float R = (2 * r / sqrtf(3));
		float mX = (float)input->getMouseX();
	  float mY = (float)input->getMouseY();
		float Xnav = (float) gameCounter[cn].idNumber / 100;  // BOATs have off set as they do not go on land.	  
		float Ynav = (float) gameCounter[cn].idNumber / 100;

		// may not need this here see if on mouse left below..........................
		//r -= 5.0f ;   // the -5 is our buffer inside the hexagon
		//R -= 5.0f;
		if (tile.getScale() != 0.0f)  r *= tile.getScale();  // this give r,R the same scale as the hexagons
		if (tile.getScale() != 0.0f)  R *= tile.getScale();


    // BOATS ***** STOP STOP STOP   
    // if a players boat game counter is on the move and the player has highlighted it and pushed the 's' or 'S' key this is a signal to stop this boat game counter at the
    // the current x,y valuse    by simply using an inverse of the algorithm that determines a boats offset from td[0][0] location  and setting  gCmove = false
    // HIGHLIGHTER cn == 11  
    // _eHL == HIGHLIGHTER enum == 11
    // r == center of hexagon to the midle of a side
    // R == center of hexagon to the apex of two side
    // clear all input so a string of “sssss” do not build up in the input stream 

    // BOATS ***** STOP STOP STOP   

    /*****
    i do not know what is happening here at all ???
    in game play sometimes the boats will not stop when the HIGHLIGHTER is on them and 's' || 'S' key is down
    by moving the mouse and by that the HIGHLIGHTER over the island's hexagons with high Hexagon Row and Column
    values, half way to TILE_MAP_WIDTH and TILE_MAP_HIGHT and then retrying the boat's stop command the boat('s) stop 
    run the HIGHLIGHTER over low Hexagon Row and Column  ( like row [0  3],  col [0  3]  ) does not seem to help
    i do not know why for an instant changing the HIGHLIGHTER's x,y to the far end of the island and then back to this boat helps but it seems to???

    i have tried code that duplicates that movement but that does not seem to help???
    *************/

   if ( (input->isKeyDown('s') || input->isKeyDown('S')  )  && gameCounter[_eHL].gCVisible &&
             gameCounter[cn].x == gameCounter[_eHL].x ) // 's' or 'S' is down, HIGHLIGHTER is visible and boat[cn].x == high lighter [_eHL].x  should keep more than one boat getting the STOP command
      if(  ( (abs(gameCounter[cn].x  -  gameCounter[_eHL].x  ) < ( 2.0f * R ) )  &&    // boat and HIGHLIGHTER are with in R,r of of their x,y
               ( abs(gameCounter[cn].y - gameCounter[_eHL].y ) < ( 2.0f * r ) ) )  && gameCounter[cn].gCmove == true ) // this boat is gCmove=='true'      
        {
          gameCounter[cn].deltaX = ( gameCounter[cn].x - td[0][0].x ) / tile.getScale();
          gameCounter[cn].deltaY = ( gameCounter[cn].y - td[0][0].y)  / tile.getScale();
          gameCounter[cn].xd = gameCounter[cn].x;
          gameCounter[cn].yd = gameCounter[cn].y;
          gameCounter[cn].deltaXd = gameCounter[cn].deltaX;
          gameCounter[cn].deltaYd = gameCounter[cn].deltaY;
          gameCounter[cn].gCmove = false;
          gameCounter[cn].timeTillMove = 0.0;
          input->clearAll();
          return;
        }

    // this just sets the game counters (boats)  x, y to tile( R0,C0) x,y plus the boats off set times the current scale 
		// if gCmove == false then this counter (boat)  has not been told to move to a new location
		if (gameCounter[cn].gCmove == false)
		{
			gameCounter[cn].x = td[0][0].x + gameCounter[cn].deltaX * tile.getScale();
			gameCounter[cn].y = td[0][0].y + gameCounter[cn].deltaY * tile.getScale();
			gameCounter[cn].scale = tile.getScale();  // can do this with just row col as all tiles have same scale
      gameCounter[cn].closingRateNew = 0.0f; // if not moving set closing rate to 0
      gameCounter[cn].closingRateOld = 0.0f;
		}
		else  // if gCmove == true then this game counter is on the move from x,y to xd,yd or   row,col to rowd, cold if not boat...
			if (gameCounter[cn].gCmove == true)
			{
				if (gameCounter[cn].gCcalcD == false) // if false then the boat needs to have it destination updated 
				{
					gameCounter[cn].xDt = gameCounter[cn].deltaX;  // get copy of deltaX deltaY before any movement calculation is done will try to modify this temp deltaX,Y to keep boats oriented to island during they movement 
					gameCounter[cn].yDt = gameCounter[cn].deltaY;

					gameCounter[cn].tempX = gameCounter[cn].xd - td[0][0].x;  // this give you the new delta from td 0,0 
					gameCounter[cn].tempY = gameCounter[cn].yd - td[0][0].y;
					gameCounter[cn].tempX /= tile.getScale();   // remember that deltaX and deltaY are used to keep the counters position stable with regards to td 0,0 position if the counter is not moving
					gameCounter[cn].tempY /= tile.getScale();   // by dividing the tempX,Y by the scale the new deltaX,Y will be at scale 1:1 that is needed when movement is finished and counters position is stable
					gameCounter[cn].deltaX = gameCounter[cn].tempX;  // as deltaX,Y is always scaled    see 'if' gameCounter[cn].gCmove == false   above
					gameCounter[cn].deltaY = gameCounter[cn].tempY;

					gameCounter[cn].tempX = td[0][0].x + gameCounter[cn].deltaX * tile.getScale();  // do this to get tempX,Y back to current scale
					gameCounter[cn].tempY = td[0][0].y + gameCounter[cn].deltaY * tile.getScale();

					gameCounter[cn].tempX -= gameCounter[cn].x;  // this gives tempX,Y the new distance to x,y and by dividing that distance will can control speed for testing movement     
					gameCounter[cn].tempY -= gameCounter[cn].y;
					gameCounter[cn].tempX /= 16000;  // when movement is good and testing not needed this can be removed and a time scale put in its place
					gameCounter[cn].tempY /= 16000;

					gameCounter[cn].gCcalcD = true;
					}

/******************************************************************************************************************
this simple 'if' is what stops BOATS when they reach their DeltaX and DeltaY from td[0][0].x / .y
this works just the way I want on North and West shores but BALL safety(that stops boats from running onto shore and getting stuck)
keeps them a full game piece width and height from East and South shoreline try working on BALL safety for East and South shorelines
see if that helps
*****************************************************************************************************************/

				if ( (abs(gameCounter[cn].x - (td[0][0].x + gameCounter[cn].deltaX * tile.getScale())) <  0.2f
						&& abs(gameCounter[cn].y - (td[0][0].y + gameCounter[cn].deltaY * tile.getScale()) < 0.2f))  ) // if on abs(game...
				{
					gameCounter[cn].gCmove = false;  // as we are in  "void CatchTheFly::updateSeaCounters" this just stops boats when they get to their DeltaX DeltaY positions. 
					gameCounter[cn].gCcalcD = false;
          // *********** GET arrival time at new boat location  *************************
          timer = time(NULL);   // get time now  time(NULL) == time(&timer)
          gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the hexagon it is currently one
				 }
				else
				{	
					gameCounter[cn].xDt += gameCounter[cn].tempX;
					gameCounter[cn].yDt += gameCounter[cn].tempY;
					gameCounter[cn].x = td[0][0].x + gameCounter[cn].xDt * tile.getScale();
					gameCounter[cn].y = td[0][0].y + gameCounter[cn].yDt * tile.getScale();		
					gameCounter[cn].scale = td[0][0].tileScale;  // can do this with just row col as all tiles have same scale
				}
				//	a safety to stop boat run-a-way may not be needed    												
			}// end 'if' 'else'...
	}// END first 'if' in this method

   // new safty that will stop boats from going into run-a-way...
   //   boat's scaled (x,y) destination   gameCounter[cn].deltaXd     gameCounter[cn].deltaYd     
   //   boat's scaled off set from H(0,0) as it is moving  its temp position   gameCounter[cn].xDt      gameCounter[cn].yDt

  double _dTempXdestination, _dTempYdestination;
  _dTempXdestination = abs(gameCounter[cn].deltaXd - gameCounter[cn].xDt);
  _dTempYdestination = abs(gameCounter[cn].deltaYd - gameCounter[cn].yDt);

  if (gameCounter[cn].mChange == true)
  {  
     // if map is SCALED or SCROLLED (deltaXd, deltaYd) may have been over run  and boat may be in run-a-way
    gameCounter[cn].mChange = false;
  }//end 'if' on mChange...

  // try to come up with fix that will recalculate a boats xDd and yDd (their off set destination)   
  // sometimes the boat stop at their (deltaXd, deltaYd) and some times they do not      it is when the right (wrong) combination of scaling and scrolling commands trips there current temporary moving 
  // values (tempX tempY) to beyond their (deltaXd, deltaYd) destination off sets from H(0,0) values, once beyond their destination values there is no mechanism  to stop their movement   
  //as their movement values (tempX, tempY) have gone +/- past  the values of (deltaXd, deltaYd)  that would have tripped the boats gCmove to false and stopped their movement
  // in CTFgCmove.cpp 
  // gameCounter[i].deltaXd = (gameCounter[i].xd - td[0][0].x) / tile.getScale();
  // gameCounter[i].deltaYd = (gameCounter[i].yd - td[0][0].y) / tile.getScale();
  // gameCounter[i].gCmove = true;
  // (xd, yd) == to new window destination coordinates   
  // AND  gameCounter[i].deltaXd = (gameCounter[i].xd - td[0][0].x) / tile.getScale(); == to new H(0,0) off set  UN-scaled as their values will be scaled in CTFgameCounters.cpp
  // when the map gets scrolled or scaled  a moving boat's new  (deltaXd, deltaYd) may now be invalid see +/- above...     
  // now (deltaX, deltaY) hold the wanted window destination off set values from H(0,0)    get new scaled/scrolled H(0,0) window (x,y) add to it scailed (deltaX, deltaY) and this should give the new values for
  // the boats off set from H(0,0)      after it has been scaled and or scrolled  I HOPE ***************************************************************************
  // this is only needed for moving boats as stationary boat only need their (deltaX, deltaY) off sets from H(0,0) updated to maintain their rendered position relative to H(0,0) and the map as a whole  

  //  (gameCounter[8].x, gameCounter[8].y) true windows (x,y) user area position    display titles   x, y
  //  true windows (x,y) destination that is picked up from "Ball"    display titles dx, dy
  //   (gameCounter[8].xDt, gameCounter[8].yDt)  boat's scaled off set from H(0,0) as it is moving this is its temp position   display titles  xDt, yDt 
  //   (gameCounter[8].deltaXd, gameCounter[8].deltaYd)  boat's scaled (x,y) destination    display titles  dXd, dYd  THIS IS WHAT MUST BE UPDATED IF SCROLL or SCALE used
  //   (gameCounter[8].deltaX, gameCounter[8].deltaY)  boat's scaled off set from H(0,0)   also starting position  display titles xDta, yDta 
  //   when boat get move command (xDta, yDta) are set to (dXd, dYd) 

   return;
}// END ********************** BOATS BOATS BOATS **********************************************
// *********************************************************************************************

// *********************************************************************************************
// **************************** AIR AIR AIR ******************************************************
// ****************** OVER LOADED method update AIR Counters  
// all AIR counters are 300 seares

// *****************************************
// For now the A1 (air counter) will have a speed of 1 second to move from hex to hex as altitude and weather have not yet been introduced.
//******************************************
void CatchTheFly::updateAirCounters(TileData td[][40], Input* input, int cn, const int textureWidth)
{
   if (gameCounter[cn].idNumber / 100 == 3 )
   {
      float A = (float)textureWidth;
      float r = (sqrtf(3) * A / 4.0f);
      float R = (2 * r / sqrtf(3));
      float mX = (float)input->getMouseX();
      float mY = (float)input->getMouseY();
	  int rowT; // row and col of destination  hexagon  and temp row and col
	  int colT;
	  float tempd; // temporary distance from adjacent hexagon to destination hexagon smallest one winds.  
	  int moveTime; //  gets the random number that is used in a 'switch' to pick and set counter member 'timeTillMove'
	  XYhexagonNext xyNextH[6]; // will hold neighboring hexagon x,y pairs for testing to see which hexagon to move to
	  int row, col;  // row, col will be used with int values the get (R-2,C) . . . to get neighboring hexagon's x,y values for testing.
					  // also used to hold new row and col counter will move to
      // may not need this here see if on mouse left below..........................
      //r -= 5.0f ;   // the -5 is our buffer inside the hexagon
      //R -= 5.0f;

      if (td[0][0].tileScale != 0.0f)  r *= td[0][0].tileScale;  // this give r,R the same scale as the hexagons
      if (td[0][0].tileScale != 0.0f) R *= td[0][0].tileScale;

      // if a players game counter is on the move and the player has highlighted it and pushed the 's' or 'S' key this is a signal to stop this game counter on the
      // current hexagon   by simply settings its' rowd = row, and cold = col, and gCmove = false   this seems to work 
      // HIGHLIGHTER cn == 11
      // clear all input so a string of “sssss” do not build up in the input stream 
      // AIR *****
      if ( (input->isKeyDown('s') || input->isKeyDown('S'))   && (gameCounter[cn].row == gameCounter[11].row && gameCounter[cn].col == gameCounter[11].col )  )
      {
        gameCounter[cn].rowd = gameCounter[cn].row;
        gameCounter[cn].cold = gameCounter[cn].col;
        gameCounter[cn].gCmove = false;
        gameCounter[cn].timeTillMove = 0.0;
        input->clearAll();
        return;
      }

	  // this just sets the game counters x, y to the tile's x,y it is on   need that to draw it 
	  // if gCmove == false then this counter has not been told to move to a new location
	  if (gameCounter[cn].gCmove == false )
	  {
		  gameCounter[cn].frameTimeElapsed = 0.0f;  // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
		  gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
		  gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;		  
		  gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale		
	  }

    else
      // this way only the top game counter will get the new Hexagon x,y coordinates and by that only the top game counter on a hexagon will move I HOPE!!!
      if (gameCounter[cn].gCmove == true && gameCounter[cn].gCTopCounter == false)
      {
        gameCounter[cn].frameTimeElapsed = 0.0f;  // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other
        gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
        gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
        gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale	
        if (gameCounter[cn].row == gameCounter[cn].rowd &&  gameCounter[cn].col == gameCounter[cn].cold)
        {
          gameCounter[cn].gCmove = false;    // will set all the game counters below the top counter on a hexagon to  'gCmove = false' 
        }// Air counters
      }

	  else  // if gCmove == true then this game counter is on the move from x,y to xd,yd   row,col to rowd, cold
		  if (gameCounter[cn].gCmove == true)
		  {
			  //if (mapChange)
			  //{
				 // gameCounter[cn].row = gameCounter[cn].oldRow;
				 // gameCounter[cn].col = gameCounter[cn].oldCol;
				 // gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
				 // gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
				 // gameCounter[cn].xd = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				 // gameCounter[cn].yd = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				 // gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
				 // mapChange = false;
				 // return;
			  //}// END if(mapChange) ...

			  // now will use this information to move the game counter
			  // need to slow down movement so will use frameTime when frameTime elapsed to >= 1 second then move to next hexagon 
			  // each counter will keep track of the elapsed frameTime that has past since its last move from one hexagon to an other frameTimeElapsed is set to 0.0 in CTFgCmove
			  // To move from anyone of these hexagons to an adjacent hexagon IF THE ORIGINAL HEXAGON row col is ODD,EVEN number

			     // there are four possibly combination of odd, even row, col values for each hexagon
			    // It seems to work on the row, not the column,  ODD,EVEN AND ODD,ODD have same results
			     
				 // from hexagon R,C  where row value is odd, and col value is even.   ROW,COL → ODD, EVEN
				 // to hexagon north R - 2, C
				 // to hexagon north east R - 1, C + 1
				 // to hexagon south east R + 1, C + 1
				 // to hexagon south R + 2, C
				 // to hexagon south west R + 1, C
				 // to hexagon north west R - 1, C

//      		  from hexagon R, C  where row value is odd, and col value is odd.ROW, COL → ODD, ODD
//				  to hexagon north R - 2, C
//				  to hexagon north east R - 1, C + 1
//				  to hexagon south east R + 1, C + 1
//				  to hexagon south R + 2, C
//				  to hexagon south west R + 1, C
//				  to hexagon north west R - 1, C
//          
//                It seems to work on the row, not the column,  EVEN, ODD AND EVEN, EVEN have same results
//				  from hexagon R, C  where row value is even, and col value is odd.ROW, COL → EVEN, ODD
//				  to hexagon north R - 2, C
//				  to hexagon north east R - 1, C
//				  to hexagon south east R + 1, C
//				  to hexagon south R + 2, C
//				  to hexagon south west R + 1, C - 1
//				  to hexagon north west R - 1, C - 1
//
//				  from hexagon R, C  where row value is even, and col value is even.ROW, COL → EVEN, EVEN
//				  to hexagon north R - 2, C
//				  to hexagon north east R - 1, C
//				  to hexagon south east R + 1, C
//				  to hexagon south R + 2, C
//				  to hexagon south west R + 1, C - 1
//				  to hexagon north west R - 1, C - 1
//
//

			     // Will try to come up with an algorithm that will let the counter pick the best direction to move in one hexagon at a time to get to it destination.
				 // the counter will be limited to the movements outlined above.the counter can only move to an adjacent hexagon.
			     // When a counter is on the move it knows  x, y xd, yd, so look at all the adjacent hexagons and test their x, y for distances to target hexagon's x,y.
				 // The adjacent hexagon with x, y closest to target hexagon's x,y is the hexagon counter should move to  
			//  struct XYhexagonNext { int x, y; };  // will hold neighboring hexagon x,y pairs for testing to see which hexagon to move to in CTFgmaeCounters.cpp
			//  const enum COMPASSPOINTS { N, NE, SE, S, SW, NW }; // compass points to neighboring hexagons north north-east … 

			// 'frameTime' time required for last frame to be rendered     'frameTimeElapsed' is total of all those frame times.   that data can be used as a timer to control game counter movement
			// this code sets the movement time of the AIR counters "A1..." as they move from one terrain type to and other
			  gameCounter[cn].frameTimeElapsed = frameTime + gameCounter[cn].frameTimeElapsed;
			  if (gameCounter[cn].timeTillMove <= -1.0f)
			  {
				  moveTime = rand() % 3;
				  switch (moveTime)
				  {
				  case 0: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyLow;
					  break;
				  case 1: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyMedium;
					  break;
				  case 2: gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyHight;
					  break;
				  default:   gameCounter[cn].timeTillMove = tileData[gameCounter[cn].row][gameCounter[cn].col].tileMDifficultyLow;
					  break;
				  }// end 'switch'...
			  }// end 'if'...


			   // for now A1's timeTillMove is == 1;  +++++++++++++++++++++++++++++TEMP TEMP TEMP +++++++++++++++++++++++++++++
         // For now the A1 (air counter) will have a speed of 1 second to move from hex to hex as altitude and weather have not yet been introduced.
			  gameCounter[cn].timeTillMove = 1.0f;

			  if (gameCounter[cn].frameTimeElapsed >= gameCounter[cn].timeTillMove) // set speed of counter movement from hex to hex
			  {
          timer = time(NULL);
          gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the destination hexagon it is currently one		
          gameCounter[cn].gCDrawPriority = timer;  // this is when this 'gameCounter[cn]' move to this hexagon    last is drawn on top...
          struct tm *localtime(const time_t *time);

          gameCounter[cn].timeTillMove = -1.0f;  // needed so new 'timeTillMove' will be picked above
          row = gameCounter[cn].row;
          col = gameCounter[cn].col;
									
				if (row%2)
				{
					if (row <= 1)
					{
						xyNextH[N].x = -1;
						xyNextH[N].y = -1;  // get x,y location of hexagon to north				  
					}
					else
					{
						xyNextH[N].x = td[row - 2][col].x;  
						xyNextH[N].y = td[row - 2][col].y;  // get x,y location of hexagon to north			
					}
					//---------------------------						
					if (row <= 0 || col >= TILE_MAP_WIDTH - 1) 
					{
						xyNextH[NE].x = -1;  
						xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[NE].x = td[row - 1][col + 1].x;  
						xyNextH[NE].y = td[row - 1][col + 1].y;  // get x,y location of hexagon to north east 										
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 2 || col >= TILE_MAP_WIDTH - 2)
					{
						xyNextH[SE].x = -1;
						xyNextH[SE].y = -1;  // get x,y location of hexagon to north		
					}
					else
					{
						xyNextH[SE].x = td[row + 1][col + 1].x;
						xyNextH[SE].y = td[row + 1][col + 1].y; // ...							 
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 2)
					{
						xyNextH[S].x = -1;
						xyNextH[S].y = -1;  // get x,y location of hexagon to north		
					}
					else
					{
						xyNextH[S].x = td[row + 2][col].x;  
						xyNextH[S].y = td[row + 2][col].y;
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 2)
					{
						xyNextH[SW].x = -1;
						xyNextH[SW].y = -1;  // get x,y location of hexagon to north		
					}
					else
					{
						xyNextH[SW].x = td[row + 1][col].x;  
						xyNextH[SW].y = td[row + 1][col].y;
					}
					//---------------------------										
					if (row <= 0)
					{
						xyNextH[NE].x = -1;
						xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[NW].x = td[row - 1][col].x;  
						xyNextH[NW].y = td[row - 1][col].y;
					}
				}// END 'if' on  (row%2) ...

				else // START  'else' on 	if (row%2)  eles row is even number ************************************************************************************
				{
					if (row <= 1)
					{
						xyNextH[N].x = -1;
						xyNextH[N].y = -1;  // get x,y location of hexagon to north				  
					}
					else
					{
						xyNextH[N].x = td[row - 2][col].x;  
						xyNextH[N].y = td[row - 2][col].y;  // get x,y location of hexagon to north				  
					}
					//---------------------------
					if (row <= 0)
					{
						xyNextH[NE].x = -1;
						xyNextH[NE].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[NE].x = td[row - 1][col].x;  
						xyNextH[NE].y = td[row - 1][col].y;  // get x,y location of hexagon to north east 
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 1)
					{
						xyNextH[SE].x = -1;
						xyNextH[SE].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[SE].x = td[row + 1][col].x;  
						xyNextH[SE].y = td[row + 1][col].y; // ...
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 3)
					{
						xyNextH[S].x = -1;
						xyNextH[S].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[S].x = td[row + 2][col].x;  
						xyNextH[S].y = td[row + 2][col].y;
					}
					//---------------------------
					if (row >= TILE_MAP_HEIGHT - 2 || col <= 0)
					{
						xyNextH[SW].x = -1;
						xyNextH[SW].y = -1;  // get x,y location of hexagon to north east 
					}
					else
					{
						xyNextH[SW].x = td[row + 1][col - 1].x;
						xyNextH[SW].y = td[row + 1][col - 1].y;
					}
					//---------------------------
					if (row <= 0 || col <= 0)
					{
						xyNextH[NW].x = -1;
						xyNextH[NW].y = -1;
					}
					else
					{
						xyNextH[NW].x = td[row - 1][col - 1].x;
						xyNextH[NW].y = td[row - 1][col - 1].y;
					}
				}// END 'if' 'else' on even or odd row...


				if (row == 0) { xyNextH[NW].x = -1; xyNextH[NW].y = -1; xyNextH[N].x = -1; xyNextH[N].y = -1; xyNextH[NE].x = -1; xyNextH[NE].y = -1; }
				if (row == TILE_MAP_HEIGHT - 1) { xyNextH[SW].x = -1; xyNextH[SW].y = -1; xyNextH[S].x = -1; xyNextH[S].y = -1; xyNextH[SE].x = -1; xyNextH[SE].y = -1; }
				// the even rows are the ones that start on the outer left side that is why row%2 if even then = 0 and x,y gets -1				      
				if (col == 0 && row % 2 == 0) { xyNextH[NW].x = -1; xyNextH[NW].y = -1; xyNextH[SW].x = -1; xyNextH[SW].y = -1; }
				if (col == 0 && row == TILE_MAP_HEIGHT - 2) { xyNextH[S].x = -1; xyNextH[S].y = -1; } // next to last col 0 hexagon its bottom is out in blue...

				if (col == TILE_MAP_WIDTH - 1 && row % 2 == 1) { xyNextH[NE].x = -1; xyNextH[NE].y = -1; xyNextH[SE].x = -1; xyNextH[SE].y = -1; }// only blue on the right side...

				if (col == TILE_MAP_WIDTH - 1 && row == 1) { xyNextH[N].x = -1; xyNextH[N].y = -1; } // last hexagon second row its head is out in blue...

				if (col == TILE_MAP_WIDTH - 1 && row == TILE_MAP_HEIGHT - 1) { xyNextH[S].x = -1; xyNextH[S].y = -1; } // last hexagon its NE side is out in blue...
					  
				//now have all the x,y location values of the surrounding hexagon next find which adjacent hexagon is closest to destination hexagon
				// squ(delta x^2+ delta y^2) will give distance to destination hexagon.

				// just to give tempd a big value to start will be set to 
				tempd = GAME_WIDTH * GAME_HEIGHT; 

				for (int i = 0; i < NW+1; ++i)
				{
					if(xyNextH[i].x != -1 || xyNextH[i].y != -1)
						if (sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2)) <= tempd)
						{
							rowT = 0; 
							colT = 0;
							// temporary distance should not be more than distance between furthest two hexagons for curent counter path
							tempd = sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2));												
							//td[row][col] id only so need row,col to test x,y of tile  
							if (row % 2) // if rows are odd
							{
								if (i == N) { rowT = row - 2; colT = col; }   // get row, col of  hexagon to north	
								if (i == NE) { rowT = row - 1; colT = col + 1; }   // get row, col of hexagon to north east	
								if (i == SE) { rowT = row + 1; colT = col + 1; }   // get row, col of hexagon to south east
								if (i == S) { rowT = row + 2; colT = col; }   // get row, col of hexagon to south 
								if (i == SW) { rowT = row + 1; colT = col; }   // get row, col of hexagon to south west
								if (i == NW) { rowT = row - 1; colT = col; }   // get row, col of hexagon to north west						
							}
							else // if rows are even
							{
								if (i == N) { rowT = row - 2; colT = col; }   // get row, col of  hexagon to north	
								if (i == NE) { rowT = row - 1; colT = col; }   // get row, col of hexagon to north east	
								if (i == SE) { rowT = row + 1; colT = col; }   // get row, col of hexagon to south east
								if (i == S) { rowT = row + 2; colT = col; }   // get row, col of hexagon to south 
								if (i == SW) { rowT = row + 1; colT = col - 1; }   // get row, col of hexagon to south west
								if (i == NW) { rowT = row - 1; colT = col - 1; }   // get row, col of hexagon to north west		
							}
						}//END 'if' on  "if (sqrt(pow((gameCounter[cn].xd - xyNextH[i].x), 2) + pow((gameCounter[cn].yd - xyNextH[i].y), 2)) <= tempd)"					
				}// END 'for' on i<=NW...

				// if this is active counter can't get to 0,0 **************************************************************************************
				 // for testing only ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
				/*if ( rowT == 0 && colT == 0)
				{
					int stop;
					stop = 1;
					rowT = gameCounter[cn].oldRow;
					colT = gameCounter[cn].oldCol;
				}*/
				gameCounter[cn].oldRow = rowT;
				gameCounter[cn].oldCol = colT;
				// for testing only ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

				gameCounter[cn].x = td[rowT][colT].x;
				gameCounter[cn].y = td[rowT][colT].y;
				gameCounter[cn].col = td[rowT][colT].col;
				gameCounter[cn].row = td[rowT][colT].row;
				gameCounter[cn].scale = td[rowT][colT].tileScale;  // can do this with just row col as all tiles have same scale
				gameCounter[cn].frameTimeElapsed = 0.0f;

				gameCounter[cn].oldRow = gameCounter[cn].row;
				gameCounter[cn].oldCol = gameCounter[cn].col;

				// *********** GET arrival time at new hexagon  *************************
				timer = time(NULL);   // get time now  time(NULL) == time(&timer)
				gameCounter[cn].gCArrivalTime = timer;   // use this to show when this 'cn' 'gameCounter' arrived at the hexagon it is currently one
        gameCounter[cn].gCDrawPriority = timer;  // this is when this 'gameCounter[cn]' move to this hexagon    last is drawn on top...

			   if (gameCounter[cn].rowd  ==  gameCounter[cn].row)  // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
			    if (gameCounter[cn].cold ==  gameCounter[cn].col)
			    {
			  		gameCounter[cn].x = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
			  		gameCounter[cn].y = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
			  		gameCounter[cn].row = td[gameCounter[cn].rowd][gameCounter[cn].cold].row;
			  		gameCounter[cn].col = td[gameCounter[cn].rowd][gameCounter[cn].cold].col;
			  		gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
			  		gameCounter[cn].gCmove = false;
			  		gameCounter[cn].deltaX = 0.0f;
			  		gameCounter[cn].deltaY = 0.0f;

					// *********** GET arrival time at destination hexagon  *************************
					timer = time(NULL);   // get time now  time(NULL) == time(&timer)
					gameCounter[cn].gCTstruct = *localtime(&timer);
			    }// END inner 'if' 

			  }//END 'if' on frameTimeCount >= 1 sec ?
			  else
			  {
			     //  this is the same code as from  “if (gameCounter[cn].gCmove == false )”  except that it does not reset the frameTimeCount to zero
				//   this way if the map is scaled or scrolled between counter moves the counter will stay fixed to the current hexagon it is on
				  gameCounter[cn].xd = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				  gameCounter[cn].yd = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				  gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
				  gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
				  gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale		
			  }
			  timer = time(NULL);   // get time now  time(NULL) == time(&timer)
			  gameCounter[cn].gCDrawPriority =  timer;  // this is when this 'gameCounter[cn]' move to this hexagon    last is drawn on top...			 			
		  }//END 'if' gCmove == true...

	

			 // gameCounter[cn].deltaX = frameTime * (td[gameCounter[cn].rowd][gameCounter[cn].cold].x - td[gameCounter[cn].row][gameCounter[cn].col].x);
			 // gameCounter[cn].deltaY = frameTime * (td[gameCounter[cn].rowd][gameCounter[cn].cold].y - td[gameCounter[cn].row][gameCounter[cn].col].y);

			 // // (x == y) ? a : b
			 // rOr = (gameCounter[cn].yd - gameCounter[cn].tempY) / (gameCounter[cn].xd - gameCounter[cn].tempX == 0) ?  1 : gameCounter[cn].xd - gameCounter[cn].tempX;
			 // z = rOr*frameTime;

			 // gameCounter[cn].tempX += gameCounter[cn].deltaX *   COUNTER_SPEED;
			 // gameCounter[cn].tempY += gameCounter[cn].deltaY *   COUNTER_SPEED;
			
			 // gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale

			 // for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
			 // {
				//  for (int col = 0; col < TILE_MAP_WIDTH; ++col)
				//  {
				//	  if (abs(td[row][col].x+R  - gameCounter[cn].tempX+R) < R   ) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
				//		  if (abs(td[row][col].y+r  - gameCounter[cn].tempY+r) < r )
				//		  {
				//			  gameCounter[cn].x = td[row][col].x;
				//			  gameCounter[cn].y = td[row][col].y;
				//			  gameCounter[cn].col = td[row][col].col;
				//			  gameCounter[cn].row = td[row][col].row;
				//			  gameCounter[cn].xd = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				//			  gameCounter[cn].yd = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				//		  }//END outter if...													        
				//  }// END of for on col...
			 // }// END of for on row...

			 // if (abs(gameCounter[cn].xd  -  gameCounter[cn].x) < R/2.0f ) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
				//  if (abs(gameCounter[cn].yd  -  gameCounter[cn].y) < r/2.0f )
				//  {
				//	gameCounter[cn].x = td[gameCounter[cn].rowd][gameCounter[cn].cold].x;
				//	gameCounter[cn].y = td[gameCounter[cn].rowd][gameCounter[cn].cold].y;
				//	gameCounter[cn].row = td[gameCounter[cn].rowd][gameCounter[cn].cold].row;
				//	gameCounter[cn].col = td[gameCounter[cn].rowd][gameCounter[cn].cold].col;
				//	gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
				//	gameCounter[cn].gCmove = false;
				//	gameCounter[cn].deltaX = 0.0f;
				//	gameCounter[cn].deltaY = 0.0f;
				//  }				   		
		  //}// END else ...

      //for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
      //{
      //   for (int col = 0; col < TILE_MAP_WIDTH; ++col)
      //   {
      //      xH = td[row][col].x;
      //      yH = td[row][col].y;
      //      //if (input->getMouseLButton())  // If left mouse button is clicked **************************
      //      //{
      //      //   if (abs(xH + R - mX) < r / 2.0f) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
      //      //      if (abs(yH + r - mY) < r / 2.0f)
      //      //      {
      //      //         gameCounter[cn].x = td[row][col].x;
      //      //         gameCounter[cn].y = td[row][col].y;
      //      //         gameCounter[cn].row = row;
      //      //         gameCounter[cn].col = col;
      //      //         gameCounter[cn].scale = td[row][col].tileScale;
      //      //      }
      //      //}// end if mouse left button down ******************************
      //      //else
      //      {
      //         gameCounter[cn].x = td[gameCounter[cn].row][gameCounter[cn].col].x;
      //         gameCounter[cn].y = td[gameCounter[cn].row][gameCounter[cn].col].y;
      //         gameCounter[cn].scale = td[gameCounter[cn].row][gameCounter[cn].col].tileScale;  // can do this with just row col as all tiles have same scale
      //         // empty *****************************************************************************
      //      }
      //   }// END 'for' on col...
      //}// END 'for' on row...
   }// END first 'if' on  if (gameCounter[cn].idNumber / 100 == 3)
   return;
}// END  **************************** AIR AIR AIR ******************************************************
// ********************************** AIR AIR AIR ******************************************************
