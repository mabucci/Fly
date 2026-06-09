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

// this file will hold catchTheFly class methods that will let the player "swap" counters that are on the same hexagon
// if two or more game counters are on the same hexagon then by placing the highlighter on that hexagon and pressing the TAB key the counters will be rotated top to bottom
// think FCII  (TAB + SHIFT counter rotate) 

//******************************************************************************************************
// for referenced only**************************************************************************************
//struct TileData {   // tile data struct  holds curent and last x,y, tile t ype, and the curent tile scale
//	float x;  // curent x,y
//	float y;
//	float xLast;  // last x,y
//	float yLast;
//	int tileType;  // type of tile beach, hill, forest...
//	int tileMDifficultyLow; // low difficulty value of moving through this map tile's terain
//	int tileMDifficultyHight;    // hight difficulty value of moving through this map tile's terain
//	float tileScale;
//	int row; // curent row, col
//	int col;
//};
//******************************************************************************************************

#include "catchTheFly.h"
using namespace catchTheFlyNS;
//  counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Ball", "Green Ball" };
void CatchTheFly::gCShuffleCounters()
{
  int rowH, colH;  // to hold row and col of highlighter 
  double tempDrawPriority; // to hold the DP of the top game counter of a particular hexagon
  double _dTDPH[1][2], _dTDPL[1][2];  // High and Low Draw Priority
  double _dTemp1, _dTemp2, _dTemp3;  // three double temps needed for swapping top counter value
  int _iNCH = 0;   //  Number of Counters on this Hexagon
  double _dTID[NUMBER_OF_NAMES][2];  // temporary holder of 'i' and draw priority

  tempDrawPriority = -1;
  _dTDPH[0][0] = -1;   _dTDPH[0][1] = -1;
  _dTDPL[0][0] = -1;   _dTDPL[0][1] = -1;

  for (int x = 0; x < NUMBER_OF_NAMES; ++x)
  {
    _dTID[x][0] = -1.0;
    _dTID[x][1] = -1.0;
  }

  for (int i = 0; i < NUMBER_OF_NAMES; ++i)
    if (gameCounter[i].name == "Highlighter")
    {
      rowH = gameCounter[i].row;   // now have row and col 'Highlighter' is on
      colH = gameCounter[i].col;
    }//end 'if for'. . .

  for (int i = 0; i < NUMBER_OF_NAMES; ++i)
  {
    if (_dGCSwapStack[rowH][colH][i] != -1)    // BOAT types have (row, col)  set to (-1, -1) at instantiation 
    {
      if (gameCounter[i].C_type == MARKER)
        continue;  // this will stop accidental LMB (Left Mouse Button) click while swapping counter drawing priorities

// now load  ' _dTID[NUMBER_OF_NAMES][2]'   double temporary holder of game counter's 'i' and that game counter's draw priority value.  NOTE not game counters arrival time as that will affect the display
      _dTID[_iNCH][0] = i;
      _dTID[_iNCH][1] = gameCounter[i].gCDrawPriority;
      ++_iNCH;// number of game counters on this (rowH, colH) hexagon

      if (tempDrawPriority < gameCounter[i].gCDrawPriority)
      {
        tempDrawPriority = gameCounter[i].gCDrawPriority;
        _dTDPH[0][0] = tempDrawPriority;
        _dTDPH[0][1] = i;
      }//end 'if' on (tempDrawPriority < gameCounter[i].gCDrawPriority)...

      if (tempDrawPriority > gameCounter[i].gCDrawPriority)
      {
        tempDrawPriority = gameCounter[i].gCDrawPriority;
        _dTDPL[0][0] = tempDrawPriority;
        _dTDPL[0][1] = i;
      }//end 'if' on (tempDrawPriority < gameCounter[i].gCDrawPriority)...
    }//end 'if' on (gCSwapStack[rowH][colH][i] != -1)...
  }//end 'for loop' above...

   // now have the high and low draw priority counters and a list of all of the counters on this hexagon [ i, arrival time ]   now try to shuffle
  if ( ! input->isKeyDown(SHIFT_KEY))
  {
    _dTemp3 = _dTID[_iNCH - 1][1];   //  saves the bottom draw priority  as it gets over writed at start
    for (int x = _iNCH - 1; x > 0; --x)
    {
      _dTID[x][1] = _dTID[x - 1][1];  // swaps the draw priority from   G <- E <- D <- C <- B <-A   and then -dTemp3 == G -> A on first line after 'for' loop
    }
    _dTID[0][1] = _dTemp3;  // the bottom of the draw priority _dTID array was saved before the 'for' loop and is now set to the old top of the _dTID array  see G -> A comment above
  }
  else     // if SHIFT_KEY down them revers order of shuffle 
    if (input->isKeyDown(SHIFT_KEY))
    {
      _dTemp3 = _dTID[0][1];   //  saves the top draw priority  as it gets over writed at start
      for (int x = 0; x < _iNCH - 1;  ++x)
      {
        _dTID[x][1] = _dTID[x + 1][1];   // swaps the draw priority from    A <- B <- C <- E <- g   and then -dTemp3 == A -> G on first line after 'for' loop
      }
      _dTID[_iNCH-1][1] = _dTemp3;  // the bottom of the draw priority _dTID array was saved before the 'for' loop and is now set to the old top of the _dTID array  see A -> G comment above
    }

  // load the new draw  priority values into the  gameCounter objects and the _dGCSwapStack array 
  for (int i = 0; i < _iNCH; ++i)
  {
    gameCounter[ (int) _dTID[i][0] ].gCDrawPriority = _dTID[i][1];
    _dGCSwapStack[rowH][colH][i] = gameCounter[i].gCDrawPriority;
  }
 
  return; //  end of "void CatchTheFly::gCShuffleCounters()"... 
  }// end of "void CatchTheFly::gCShuffleCounters()"...
 //  counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Marker", "Ball", "Green Ball" };

/***********************************************
for (int row = 0; row < TILE_MAP_HEIGHT; ++row) // down one row at a time
{
	for (int col = 0; col < TILE_MAP_WIDTH; ++col)  // acrose one column at a time
	{
		for (int i = 0; i < NUMBER_OF_NAMES; ++i)
		{
			gCSwapStack[row][col][i] = -1;  // no marker has a name in 'const std::string counterNames[13] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Ball" };' that has an index number < 0  so a value of -1 means no marker of this type on this hexagon			
		}//end 'for loop' on i...
	}//end 'for loop' on col...
}//end 'for loop' on row...
gCDrawPriority; // is the priority of order that a game counter will be draw in the draw queue for Entity.Draw();
****************************************************************/