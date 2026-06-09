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

// this file will hold catchTheFly class methods that will set the characteristics of the Hexagons that make up the map of Skull Bone island


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

void CatchTheFly::gCTileUpKeep(TileData td[][MAP_WIDTH])
{
	int tileType;
	// make a nested 'for loop' that will go through the whole Skull Bone Island map and put in the characteristic of each Hexagon
	for (int row = 0; row < MAP_HEIGHT; ++row)
	{
		for (int col = 0; col < MAP_WIDTH; ++col)
		{
			tileType =  td[row][col].tileType;
			switch (tileType)
			{                                                      
			case 13:		// beach										
				td[row][col].tileMDifficultyLow = 00.80f;
				td[row][col].tileMDifficultyMedium = 01.0f;
				td[row][col].tileMDifficultyHight = 01.20f;
				break;			
			case 22:  // green
				td[row][col].tileMDifficultyLow = 01.20f;
				td[row][col].tileMDifficultyMedium = 01.45f;
				td[row][col].tileMDifficultyHight =01.80f;
				break;
			case 21:  // hilly
				td[row][col].tileMDifficultyLow = 01.80f;
				td[row][col].tileMDifficultyMedium = 02.10f;
				td[row][col].tileMDifficultyHight = 2.85f;
				break;
			case 15:	  // mountainous			
				td[row][col].tileMDifficultyLow = 02.85f;
				td[row][col].tileMDifficultyMedium = 03.10f;
				td[row][col].tileMDifficultyHight = 03.50f;
				break;																														
			default:   // catch all orther tile types...
				td[row][col].tileMDifficultyLow = 01.09f;
				td[row][col].tileMDifficultyMedium = 01.09f;
				td[row][col].tileMDifficultyHight = 01.09f;
				break;
			}//end of 'switch'...
		}//end of 'for loop' on 'col' == column...
	}//end of 'for loop' on 'row' == row...
	return; // end of "void CatchTheFly::gCtileUpKeep(TileData td[][MAP_WIDTH])"
}// end of "void CatchTheFly::gCtileUpKeep(TileData td[][MAP_WIDTH])"

