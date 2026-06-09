// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// createThisClass.cpp v1.1
// This class is the core of the game

#include "catchTheFly.h"
using namespace catchTheFlyNS;

//=============================================================================
// Constructor
//=============================================================================
CatchTheFly::CatchTheFly() : Game()
{
  dxFont = new TextDX();  // DirectX font
  messageY = 0;
  _bSplashScreen = true;
  mapX =  0.10f * GAME_WIDTH;
  mapY =  0.5f * GAME_HEIGHT;
  tile.setScale(START_SCALE - 0.0f);
	mapChange = false;	
	bBoatBreak = false;  //  for breaking out of 'for loop' in CTFgCmove.cpp   set to 'false' in catchTheFly.cpp
  srand((UINT)time(NULL)); //   seeding the random number generator with clock time
}

//=============================================================================
// Destructor
//=============================================================================
CatchTheFly::~CatchTheFly()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void CatchTheFly::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
    // background texture Going to try tile matrix, like Flow Power demo,
 /*   if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));*/

    // map textures
    if (!tileTextures.initialize(graphics, TILE_TEXTURES))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile textures\n  You FLY out of luck man!"));

    // game counters textures ******************************************************************************        
    if (!counterTexture.initialize(graphics, COUNTER_IMAGE))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile counter textures\n  You FLY out of luck man!"));

    // menu texture
    if (!menuTexture.initialize(graphics, MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture\n  You FLY out of luck man!"));

    // splash1 texture // ******************************************************************** bucci
    if (!splash1Texture.initialize(graphics, SPLASH1_IMAGE))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash1 texture\n  You FLY out of luck man!"));

    // flyTexture  // ******************************************************************** bucci
    if (!flyTexture.initialize(graphics, FLY_IMAGE))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fly texture\n  You FLY out of luck man!"));
    // flyInitialize  // ******************************************************************** bucci
    if (!fly.initialize(this, FLY_WIDTH, FLY_HEIGHT, FLY_COLS, &flyTexture))   // 'this' == 'graphics pointer' DD == Every object has access to its own address throught the 'this' pointer
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fly\n  You FLY out of luck man!"));    // 'this' is passed into the object (by the compiler) as an implicit first argument on every non-STATIC member
    fly.setX(tile.getX());                                                                         // function call to the object.        
    fly.setY(tile.getY());
    fly.setFrames(FLY_START_FRAME, FLY_END_FRAME);   // animation frames
    fly.setCurrentFrame(FLY_START_FRAME);     // starting frame
    fly.setFrameDelay(FLY_ANIMATION_DELAY);    
   // fly.setDegrees(45.0f);                     // angle of fly      

    // nativeTexture  // ******************************************************************** bucci
    if (!nativeTexture.initialize(graphics, NATIVE_IMAGE))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing native texture\n  You FLY out of luck man!"));
    // nativeInitialize  // ******************************************************************** bucci
    if (!native.initialize(this, NATIVE_WIDTH, NATIVE_HEIGHT, NATIVE_COLS, &nativeTexture))   // 'this' == 'graphics pointer' DD == Every object has access to its own address throught the 'this' pointer
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing native\n  You FLY out of luck man!"));    // 'this' is passed into the object (by the compiler) as an implicit first argument on every non-STATIC member
    native.setX(tile.getX());                                                                         // function call to the object.        
    native.setY(tile.getY());
    native.setFrames(NATIVE_START_FRAME, NATIVE_END_FRAME);   // animation frames
    native.setCurrentFrame(NATIVE_START_FRAME);     // starting frame
    native.setFrameDelay(NATIVE_ANIMATION_DELAY);
    // native.setDegrees(45.0f);                     // angle of native


    // in initialize game counter all game pieces will use one tile just like the hexagon map does.  ******************************************************
    // see fly.initialize above on why 'this' pointer 
    if (!counter.initialize(this, TEXTURE_WIDTH, TEXTURE_HEIGHT, COUNTER_COLS, &counterTexture)) 
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing counters\n  You FLY out of luck man!"));  
    counter.setFrames(0, 0);
    counter.setCurrentFrame(0);
 
    // background image Going to try tile matrix, like Flow Power demo, **************************************************************************
    /*if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));*/
    if (!tile.initialize(graphics, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_COLS, &tileTextures))  // ON FIRST TILE ERROR YOU HAD 0,0,0 NOT TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile\n  You FLY out of luck man!"));                          // WITH 0,0,0  TEXTURE_SIZE == 0 TEXTURE_COLS == 0 DirectX reads hole *png as one tile.
    tile.setFrames(0, 0); 
    tile.setCurrentFrame(0);

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu\n  You FLY out of luck man!"));

    // splash1 image ************************************************************************ bucci
    if (!splash1.initialize(graphics, 0, 0, 0, &splash1Texture))
       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash1\n  You FLY out of luck man!"));

    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font\n  You FLY out of luck man!"));

   /* menu.setDegrees(300);
    menu.setScale(0.002861f);*/
    splash1.setDegrees(300); // ********************************************************************* bucci
    splash1.setScale(0.002861f); // ******************************************************************* bucci

    nameGameCounters(pCounterEntity); // CatchTheFly::nameGameCounters   will load into gameCounters array each individual counter's name, C_type, idNumber, texture#, starting row/col. and so no.
    
    message += "\n\n\n\n\nGod Bless You Dr. Kelly\n";
    message += "Utilizes Object Oriented C++ and DirectX\n\n";
    message += "Sprites with Transparency\n\n";
    message += "Collision Detection Supported:\n";
    message += "     - Circular (Distance)\n";
    message += "     - Axis-aligned bounding box\n";
    message += "     - Rotated bounding box\n";
    message += "     - Rotated bounding box and circle\n";
    message += "     - Pixel Perfect\n\n";
    message += "XACT Audio\n\n";
    message += "Sprite and DirectX Text\n\n";
    message += "Tile Based Graphics\n\n";
    message += "Xbox 360 Controller Input\n\n";
    message += "TCP/IP and UDP/IP Network Support\n\n";
    message += "God Bless You Dr. Kelly\n";
    message += "Press any key to start!";

    messageY = GAME_HEIGHT;

    return;
}


//=============================================================================
// Update all game items
//=============================================================================
void CatchTheFly::update()
{
  if (_bSplashScreen)
  {
    static float delay = 0;
    delay += frameTime;

    if (splash1.getDegrees() > 0)  // menu to splash1 ************************************************************* bucci
    {
      splash1.setDegrees(splash1.getDegrees() - frameTime * 120);
      splash1.setScale(splash1.getScale() + frameTime * 0.4f);
      if (audio->getBuzz() == true)
      {                                      // play buzz once ****************************************************************bucci
        audio->setBuzz(false);
        audio->playCue(FLY_BUZZ);   // play sound of buzzing fly ******************************************************bucci
      }
    }
    else
    {
      if (delay >= 4 && audio->getSlap() == true )
      {
       
        audio->setSlap(false);
        audio->playCue(SLAP);
        }
    splash1.setDegrees(0);
    }

      if (delay > 40)           // start over
      {
         splash1.setDegrees(300);
         splash1.setScale(0.002861f);
         splash1.setY(0);
         delay = 0;
         messageY = GAME_HEIGHT;    // message text is just below screen at messageY = GAME_HIGHT, after 5 sec delay 
         audio->setBuzz(true);             // messageY -= frameTime * 300 will roll the message text up the screen
         audio->setSlap(true);             // frameTime = Elapsed time of the prevous frame in seconds, after 15 sec delay redo openning splash
      }                                          
      else if (delay > 5)                    
      {
         splash1.setY(splash1.getY() - frameTime * 300);
         if (messageY > 10)
            messageY -= frameTime * 300;
      }
      if (input->anyKeyPressed() || input->getMouseLButton() )  // ends _bSplashScreen and startup credits 
      {
         _bSplashScreen = false;
         audio->stopCue(FLY_BUZZ);
         audio->stopCue(SLAP);
         input->clearAll();
      }
   }  // END if (_bSplashScreen) ******************************************************************************************************** 
   
   // Call to CatchTheFly::navigateMap() ***********************************************************************************************
   // Want to navagate around map   Will use Ch 9 Space Wars scrolling bit map   
   if (input->isKeyDown(LEFT_ARROW) || input->isKeyDown(UP_ARROW) || input->isKeyDown(RIGHT_ARROW) \
			|| input->isKeyDown(DOWN_ARROW) || input->getMouseWheel() != 0 )
   {
	  scrollMap();
      //navigateMap(); // call to CatchThefly::navageteMap() ***************
      input->clearAll();  // clear the key inputs or get stuck here.
   }//End navagate call  ************************************************
   // **************************************************************

   //**************************************************************************************************************************
   // Call to CatchTheFly::zoomMap() ***********************************************************************************************
   if (input->isKeyDown(PLUS_KEY) || input->isKeyDown(MINUS_KEY) || input->isKeyDown(PLUS_KEY_NUMPAD) || input->isKeyDown(MINUS_KEY_NUMPAD) \
	   || input->getCharIn() == '0' || input->getCharIn() == '1' || input->getCharIn()=='2')
   {
	  scaleMap();
      //zoomMap();
	  scrollMap();
      //navigateMap(); // call to CatchThefly::navageteMap() ***************
      input->clearAll(); // clear the key inputs or get stuck here.
   }// End zoom in *************************************************
   // end call to CatchTheFly::zoomMap() **************************************************

   // if TAB_KEY is down than go to gCShuffleCounters() ....
   if (input->isKeyDown(TAB_KEY))
   {
	   gCShuffleCounters(); // with 'Hightlighter' on an island hexagon that has two or more game counters on it the player can swap the counts to see what counters are on that hexagon
	   input->clearAll(); // clear the key inputs or get stuck here.
   }//end  call to CatchTheFly::gCShuffleCounters() *************************************************



  // updateCounters(tileData, input, fly, 0, TEXTURE_WIDTH);  // 
   //fly.draw();  at bottom of updata  
   //
   //updateCounters(tileData, input, counter, 1, TEXTURE_WIDTH);  // 
   //counter.draw(); at bottom of updata

   // This code is at the bottom of initialize the counters only need there names Types and pointers set once.
   //pCounterEntityArray[0] = &fly;
   //for (int i = 1; i < NUMBER_OF_NAMES; ++i)
   //{
   //   pCounterEntityArray[i] = &counter;
   //}
   //nameGameCounters(pCounterEntityArray);

   // fly is now an entity obj   so can use ai  it will be controlled by the ai.
   // The FLY will be controlled by 'ai' so it will no be cycled through CatchTheFly::gameCounters method.
   //   The NATIVES also will be controlled by 'ai'.so they too will not be passed to gameCounters
   //   This will skip over fly and natives.
   //   if (!gameCounter[i].C_type == FLY || !gameCounter[i].C_type == NATIVE)

   if (mapChange)
   {
	   gameCounter[_eBL].mChange = true;
	   gameCounter[_eBS].mChange = true;
	   mapChange = false;
   }
   for (int i = 0; i < NUMBER_OF_NAMES; ++i)
   {     
     if (gameCounter[i].C_type == BOAT)    
       updateSeaCounters(tileData, input, i, TEXTURE_WIDTH);  // Remember there are only one each  title-Image,  and fly, native and counter, -Entity.			
      else
        if (gameCounter[i].C_type == AIR)       
          updateAirCounters(tileData, input, i, TEXTURE_WIDTH);  // Remember there are only one each  title-Image,  and fly, native and counter, -Entity.
         else
           if (gameCounter[i].C_type == FLY || gameCounter[i].C_type == NATIVE)
           {
             if(!_bSplashScreen) // if _bSplashScreen IS NOT being displayed then let the Fly's AI work
              updateFNCounters(tileData, input, i, TEXTURE_WIDTH);  // Remember there are only one each  title-Image,  and fly, native and counter, -Entity.
           }
            else
              if (gameCounter[i].C_type == MARKER && (gameCounter[i].name == "Highlighter" || gameCounter[i].name == "Ball"))     // CTH method for 'Highlighter' and 'Ball' used to set counters movement, direction, seed, destination.... 						
                gCmove(tileData, input, i, TEXTURE_WIDTH, TEXTURE_HEIGHT);  // the MARKERS will use gCmove to update their position 
              else              
                updateCounters(tileData, input, i, TEXTURE_WIDTH);  // Remember there are only one each  title-Image,  and fly, native and counter, -Entity.	  
   };
   // now set the game counters drawing priorities according to arrival time, last one to hex is drawn last
   // it should not matter where they are it is their arrival time that matters

   // want to reset 'gCswapStack' with all -1 values so new game counter position can be entered
   for (int row = 0; row < TILE_MAP_HEIGHT; ++row) // down one row at a time
   {
     for (int col = 0; col < TILE_MAP_WIDTH; ++col)  // acrose one column at a time
     {
       for (int i = 0; i < NUMBER_OF_NAMES; ++i)
       {
         _dGCSwapStack[row][col][i] = -1;  // no game counter has a name in 'const std::string counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Ball", "Green Ball"};' that has an index number < 0  so a value of -1 means no marker of this type on this hexagon			
         gameCounter[i].gCTopCounter = false;  // reset all game counter Top Counter values to false   this way they can be reevaluated in the code below ...
       }//end 'for loop' on i...
     }//end 'for loop' on col...
   }//end 'for loop' on row...

   for (int i = 0; i < NUMBER_OF_NAMES; ++i)
   {
 //    gameCounter[i].gCDrawPriority = gameCounter[i].gCArrivalTime;   NOW SET GcdRAWpRIORITY ALONG WITH gCArrivalTime in movement code  THIS LINE MAY NOT BE NEEDED NOW.
     // can't pickup boats as their row and col values are set to -1 in 'void CatchTheFly::nameGameCounters(Entity* pE)' 	   		
     // if they get to gCSwapStack their 'row' == -1 and 'col' == -1 will put the gCSwapStack array out of its' memery assingment and they just happends to stop the marker 'HIGHLIGHTER' from being displayed
     if (gameCounter[i].row <= -1  &&  gameCounter[i].col <= -1)
       continue;
     _dGCSwapStack[gameCounter[i].row][gameCounter[i].col][i] = gameCounter[i].gCDrawPriority;  // a game counter's drawing priority, that is which game counter is drawn first, ... , last
   }//end of 'for (int i; i < NUMBER_OF_NAMES; ++i)'

    // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    // want to know top game counter of each hexagon only top counter can be moved   that way all the counters on one hexagon will not pick up the same move instruction
   double _dTopTime[2];   // will hold  0==i, 1==draw priority 

   for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
   {
     for (int col = 0; col < TILE_MAP_WIDTH; ++col)
     {
       _dTopTime[0] = -1.0;      // game counter index number
       _dTopTime[1] = -1.0;      // draw priority that goes with that 'i' game counteer
       for (int i = 0; i < NUMBER_OF_NAMES; ++i)
       {

        if (_dGCSwapStack[row][col][i] > -1)   // if one or more game counters are on a map hexagon they were entered in this array[ROW][COL][i==game counter's array index number]   
         {                                                      // if no game counters on this row,col hexagon then 'for loop' 'for loop' to next hexagon to assess
          if (_dTopTime[1] < _dGCSwapStack[row][col][i])  // to get here there is a game counter at row,col, and its index == 'i' and its draw priority is greater than what _dTopTime[1] holds, if this is first time throught then _dTopTime[1] == -1.0
          {
            if (_dTopTime[0] > -1.0)   // if this IS NOT first time here for this hexagon then the is an other game counter or counters, and the last one that was set to top counter 'true' must me set to 'false'
            {
              gameCounter[(int)_dTopTime[0]].gCTopCounter = false;
             }
            _dTopTime[0] = i;
            _dTopTime[1] = _dGCSwapStack[row][col][i];
            gameCounter[(int)_dTopTime[0]].gCTopCounter = true;   // now game counter index 'i' is current top counter for this hexagon
           }     
          }// end 'if' on  (_dGCSwapStack[row][col][i] > -1) ...

       }// end 'for' on NUMBER_OF_NAMES...
     }// end 'for' on TILE_MAP_WIDTH...
   }// end of 'for' on TILE_MAP_HEIGHT...
  
     // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   return;  // 'return' void at end of 'update()'
}// END void CatchTheFly::update() ********************************************************************************************
//*************************************************************************************************************************


//=============================================================================
// Artificial Intelligence
// Now we can add some Fly smarts     At first just move the Fly from hexagon to hexagon randomly
//=============================================================================
void CatchTheFly::ai()
{
  flyAI();
}//end   Artificial Intelligence ------------------------------------------------------------------------------------------------------------

//=============================================================================
// Handle collisions
//=============================================================================
void CatchTheFly::collisions()
{}

//=============================================================================
// Render game items
// catchTheFly files
// render()  sets up the tiles with any addjustments made in zoomMap() or navageteMap().
// the rows of tile are offset;  tiles in even and odd rows are spaced out so when drawn they will over lap and the hexagon board will appear as one solid background.
// all the fiddling in the  tile.setX and tile.setY is needed to make my Hexagons fix together.
// the last fiddle is to center the tile this helps somewhat with scaling appearance
// the setTileData_X­_Y_T_S set each tile's data members to that tiles x,y its' type of tile beach to mountain
//=============================================================================
void CatchTheFly::render()
{
	graphics->spriteBegin();                // begin drawing sprites  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// try tile tile map ***************************************************************************************bucci
	float scale = tile.getScale();

	if (_bSplashScreen)
	{
		// tile.draw(graphicsNS::ALPHA50);
		splash1.draw();
		fly.draw();
		dxFont->setFontColor(graphicsNS::RED);
		dxFont->print(message, 20, (int)messageY);
	}
	else
	{
		for (int row = 0; row < MAP_HEIGHT; row++)       // for each row of map
		{
			tile.setY((float)(row*TEXTURE_HEIGHT)); // set tile Y
			for (int col = 0; col < MAP_WIDTH; col++)    // for each column of map
			{
				if (tileMap[row][col] >= 0)          // if tile present
				{
					tile.setCurrentFrame(tileMap[row][col]);    // set tile texture
					if (row % 2 == 1)
					{// odd rows that are spaces out 1 texture width and shifted in 1/2 TW  to help form the hexagon pattern      
					   // mapX and mapY or offsets from zoomMap() and navageteMap()  they help a good bit in keeping the map from shifting too much 
						tile.setX((float)((TEXTURE_WIDTH - 10 + col * TEXTURE_WIDTH * 1.5f + mapX) * tile.getScale()));  // set tile X
						tile.setY((float)((0.5f * row * TEXTURE_HEIGHT + mapY) * tile.getScale()));  // set tile Y    

						// this last fiddle is to center the tile this helps somewhat with scaling appearance   
						tile.setX(tile.getX() + TEXTURE_WIDTH / 2);  tile.setY(tile.getY() + TEXTURE_HEIGHT / 2);

						setTileData_X(row, col, tile.getX());
						setTileData_Y(row, col, tile.getY());
						setTileData_T(row, col, tileMap[row][col]); // tile type   ***  struct TileData { float x;  float y;  int tileType; };  this struct will hold data for each individual map tile.
						setTileData_S(row, col, tile.getScale()); // tile scale   ***  struct TileData { float x;  float y;  float tileScale; };  this struct will hold data for each individual map tile.	
						tileData[row][col].row = row;   // set each member of the tileData struct array with its row and col values
						tileData[row][col].col = col;
					}
					else
					{// even rows that are spaced and shifted 
						tile.setX((float)(col * TEXTURE_WIDTH * 1.5f + mapX) * tile.getScale());  // set tile X
						tile.setY((float)(0.5f * row * TEXTURE_HEIGHT + mapY) * tile.getScale());  // set tile Y

						// this last fiddle is to center the tile this helps somewhat with scaling appearance   
						tile.setX(tile.getX() + TEXTURE_WIDTH / 2);  tile.setY(tile.getY() + TEXTURE_HEIGHT / 2);

						setTileData_X(row, col, tile.getX());
						setTileData_Y(row, col, tile.getY());
						setTileData_T(row, col, tileMap[row][col]); // tile type   ***  struct TileData { float x;  float y;  int tileType; };  this struct will hold data for each individual map tile.
						setTileData_S(row, col, tile.getScale()); // tile scale   ***  struct TileData { float x;  float y;  float tileScale; };  this struct will hold data for each individual map tile.
						tileData[row][col].row = row;   // set each member of the tileData struct array with its row and col values
						tileData[row][col].col = col;
					}
					// if tile on screen
					if ((tile.getX() > -2.0f * TEXTURE_WIDTH && tile.getX() < GAME_WIDTH) &&
						(tile.getY() > -2.0f * TEXTURE_HEIGHT && tile.getY() < GAME_HEIGHT))  // need the 2.0f * so bottom of top row of tiles will be draw in   
						tile.draw();                // draw tile
				}
			}
		}// try tile  map ***************************************************************************************bucci
		setXh(getTileData_X(0, 0)); // need for console display of xy of first hexagon
		setYh(getTileData_Y(0, 0));
		//map of Skull Bone Island is built   now put in characteristics  the characteristics will change as the game goes on *********************************
		gCTileUpKeep(tileData);
	}// End else ***********************************************


	 // sets up draw on fly...
	fly.setX(gameCounter[0].x);
	fly.setY(gameCounter[0].y);
	fly.setRow(gameCounter[0].row);
	fly.setCol(gameCounter[0].col);
	fly.setScale(gameCounter[0].scale);
	fly.setCurrentFrame(gameCounter[0].gCCurentFrame);
	fly.draw();

	// sets up draw on native...
	native.setX(gameCounter[10].x);
	native.setY(gameCounter[10].y);
	native.setRow(gameCounter[10].row);
	native.setCol(gameCounter[10].col);
	native.setScale(gameCounter[10].scale);
	native.setCurrentFrame(gameCounter[10].gCCurentFrame);
	native.draw();

	// fly is i==0, native is i==10, ball and marker are not visible unless called 
	// **************** PROBLEM IS;   when two or more counters are on the same hexagon the last of the counters in this 'for loop' get drawn on top	 
	// this is old WORKING code for drawing game counters by there 'i' number in NUMBER_OF_NAMES set in the method 'void CatchTheFly::nameGameCounters(Entity* pE)'
	//  for (int i = 1; i < NUMBER_OF_NAMES; ++i)
	//  {
		  //if (i == 10) continue;  // skip native #10

			 // counter.setX(gameCounter[i].x);
			 // counter.setY(gameCounter[i].y);
			 // counter.setRow(gameCounter[i].row);
			 // counter.setCol(gameCounter[i].col);
			 // counter.setScale(gameCounter[i].scale);
			 // counter.setCurrentFrame(gameCounter[i].gCCurentFrame);			   			 
			 // counter.setVisible(gameCounter[i].gCVisible);
			 // counter.draw();  // Remember there are only one each;  title-Image,  and fly, native and counter, -Entity.     		   
	//  }//end 'for loop' on NUMBER_OF_NAMES

//************** NEW FROM CODE ABOVE *******************************************************************************************************************************
// fly is i==0, native is i==10, ball and marker are not visible unless called 
// **************** PROBLEM IS;   when two or more counters are on the same hexagon the last of the counters in this 'for loop' get drawn on top	 
// want to come up with new drawing scheme that will let player shuffle game counters if there are two or more on the same hexagon    like FCII.


   // by the time you get here all the game counters have been updated and their arrival times are set the arrival times will determine the counters drawing order
   // swapping the draw order is called up in 'update' above by ' gCShuffleCounters();'
  double _dArrivaltimes[NUMBER_OF_NAMES];
  for (int i = 0; i < NUMBER_OF_NAMES; ++i) // want to have the game counters rendered in their order of draw priority 
  {
    _dArrivaltimes[i] = gameCounter[i].gCArrivalTime;
  }

 // want to have the game counters rendered in their order of draw priority 

		for (int i = 1; i < NUMBER_OF_NAMES; ++i)
		{
			if (i == 10) continue;  // skip native #10

			counter.setX(gameCounter[i].x);
			counter.setY(gameCounter[i].y);
			counter.setRow(gameCounter[i].row);
			counter.setCol(gameCounter[i].col);
			counter.setScale(gameCounter[i].scale);
			counter.setCurrentFrame(gameCounter[i].gCCurentFrame);
			counter.setVisible(gameCounter[i].gCVisible);
			counter.draw();  // Remember there are only one each;  title-Image,  and fly, native and counter, -Entity.     		 		
		}//end 'for loop' on 'i' to  NUMBER_OF_NAMES...
			 
// want to come up with new drawing scheme that will let player shuffle game counters if there are two or more on the same hexagon    like FCII.

// this is slow way to draw last counter to arrive on hexagon but may work and be safe
    for (int i = 0; i < NUMBER_OF_NAMES; ++i)
    {
      if (gameCounter[i].name == "Ball" || gameCounter[i].name == "Highlighter")
          gameCounter[i].gCTopCounter = true;
      if (gameCounter[i].gCTopCounter == true)
      {
        counter.setX(gameCounter[i].x);
        counter.setY(gameCounter[i].y);
        counter.setRow(gameCounter[i].row);
        counter.setCol(gameCounter[i].col);
        counter.setScale(gameCounter[i].scale);
        counter.setCurrentFrame(gameCounter[i].gCCurentFrame);
        counter.setVisible(gameCounter[i].gCVisible);
        counter.draw();  // Remember there are only one each;  title-Image,  and fly, native and counter, -Entity.     		 		
      }

    }
//************** NEW FORM CODE ABOVE *******************************************************************************************************************************

	   graphics->spriteEnd(); // end drawing sprites -------------------------------------------------------------------------------------------------------------------------------------

/* 
	   have this linedrawing call but to get it to draw on top of game board not under it the call the game->drawLine() had to be in game class or in catchTheFly class
		but in CTF class it had to have its own
		 Begin …
		   and End sprite calls surrounding it.The tiles and counters are draw then spriteEnd is called
		   next …. this restarts the sprite drawing draws the line then ends the sprite drawing    so the line is drawn after the board and counters   
		   you can test this by leading the line over some of the game counters.*/
	   graphics->spriteBegin();   // begin drawing sprites ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	   if (linePoints.bDrawLine)
	   {		            
		  // void Graphics::drawLine(float x1, float y1, float x2, float y2, float width, COLOR_ARGB color)   Has to be here so line is drawn on top of game board not under it.
		   graphics->drawLine(linePoints.x1 + 0.5f * TEXTURE_WIDTH * tile.getScale(), linePoints.y1 + 0.5f *TEXTURE_HEIGHT* tile.getScale(), \
			   linePoints.x2 + 0.5f * TEXTURE_WIDTH * tile.getScale(), linePoints.y2 + 0.5f *TEXTURE_HEIGHT* tile.getScale(), 1.5f, graphicsNS::RED);	
	   }
	   graphics->spriteEnd();                  // end drawing sprites --------------------------------------------------------------------------------------------------------------------------------------------
}// ******************* END render 

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void CatchTheFly::releaseAll()
{
    dxFont->onLostDevice();
    nativeTexture.onLostDevice();
    flyTexture.onLostDevice();
    splash1Texture.onLostDevice();
    menuTexture.onLostDevice();
    counterTexture.onLostDevice();
    tileTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void CatchTheFly::resetAll()
{
   tileTextures.onResetDevice();
   counterTexture.onResetDevice();
   menuTexture.onResetDevice();
   splash1Texture.onResetDevice();
   flyTexture.onResetDevice();
   nativeTexture.onResetDevice();
   dxFont->onResetDevice();
    Game::resetAll();
    return;
}
