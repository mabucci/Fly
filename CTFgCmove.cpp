// CTFgCmove
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

// CTFgCmove  holds members and methods that will move the counters around the board
// New method to set user counters movement, direction, seed, destination.... 
//  CTFgCmove file is a subsidiary file for  CatchTheFly class methods 


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
// enum _eGAME_COUNTER { _eFLY, _eS1, _eS2, _eS3, _eC1, _eC2, _eC3, _eA1, _eBL, _eBS, _eSBOAN, _eHL, _eBR, _eBG };    // used to id a particular game counter and get ride of the hard values in many 'if' statements
//******************************************************************************************************
 // if all values same x == xd  row == rows … then this counter is at rest and will not move, but if in gCmove the destination values are  
 // different than the location values then the counter will have its position changed, it will move 'step by step' towards its destination values.

#include "catchTheFly.h"
using namespace catchTheFlyNS;
// New method to set user counters movement, direction, seed, destination.... 
void CatchTheFly::gCmove(TileData td[][TILE_MAP_WIDTH], Input* input, const int cn, const int textureWidth, const int textureHight)
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

	for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
	{   
    if (bBoatBreak == true)
      break;
		for (int col = 0; col < TILE_MAP_WIDTH; ++col)
		{
			xH = td[row][col].x;
			yH = td[row][col].y;

			if (abs(xH + R - mX) < r / 1.50f) // this is our curent buffer to make sure mouse pointer is pointing to center of hexagon 
				if (abs(yH + r - mY) < r / 1.50f)
				{
					// Only need this one break it will break user out of inner for loop and that way the outer for loop will just run 
					// to row < TILE_MAP_HEIGHT and then exit.  Simple.
					if (input->getMouseLButton() && gameCounter[cn].name == "Highlighter")
					{
            bBoatBreak = true;
						break;  
					}
					
					if (gameCounter[cn].name == "Highlighter")
					{
					  linePoints.x1 = td[row][col].x; // x1 and y1 are the Highlighter's location once Highlighter is locked down to a Hexagon we do not want these updated.
					  linePoints.y1 = td[row][col].y;
					  gameCounter[cn].oldRow = row; // use the old row and old col in the Highlighter counters to keep track of their LINE origins  
					  gameCounter[cn].oldCol = col;
					}
					  setMHrow(row);
					  setMHcol(col);
					  gameCounter[cn].x = td[row][col].x;
					  gameCounter[cn].y = td[row][col].y;
					  gameCounter[cn].row = row;
					  gameCounter[cn].col = col;
					  gameCounter[cn].scale = td[row][col].tileScale;					
					  gameCounter[cn].gCVisible = true;

					if (gameCounter[cn].name == "Red Ball" ) 
					{
						gameCounter[cn].gCVisible = false; // do not draw RED ball now					
						linePoints.bDrawLine = false; // do not draw line now
					}
	
					// const std::string counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Red Ball", "Green Ball" };
					if (input->getMouseLButton() && (gameCounter[cn].name == "Red Ball")   && linePoints.x1 >= td[0][0].x  && linePoints.y1 >= td[0][0].y) // If left mouse button is clicked **************************
					{	// build in more logic to keep ball off map if line starts on a boat...........
						for (int i = 1; i < 10; ++i)
						{   // Highlighter# is Ball's - 1   cn == _eRB and cn-1 == _eHL 
							if (gameCounter[cn - 1].row == gameCounter[i].row && gameCounter[cn - 1].col == gameCounter[i].col)
							{
								linePoints.x1 = td[gameCounter[cn - 1].oldRow][gameCounter[cn - 1].oldCol].x;  // use the old row and old col in the Highlighter's counter to keep track of their LINE origins  
								linePoints.y1 = td[gameCounter[cn - 1].oldRow][gameCounter[cn - 1].oldCol].y;
								linePoints.x2 = td[row][col].x; // x2 and y2 are Ball's location 
								linePoints.y2 = td[row][col].y;
								gameCounter[cn].gCVisible = true;	// draw ball now										
								linePoints.bDrawLine = true;   // draw line now				
                 //?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
                //  trying to stop all counters on a hexagon from moving,   just want top counter to move
                //?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

							/**************
							As most people now use laptops with touch pads and touch screens adding the “ || (input->isKeydown(SPACE_KEY)” to
							if (input->getMouseRButton() || (input->isKeyDown(SPACE_KEY)))
							will make using the touch pad / screen possible.

              Look at second 'if' below
              if player calls RED BALL on a non moving game counter then clicks RMBD or SPACE_BAR on that game counter's Hexagon the game counter would be
              told to find the best way to get to where it is     so in CTFgameCounters a game counter at xH==0 yH==0 would be moved to the closest Hexagon
              to xH==0 yH==0 mostly that would be xH==1 yH==0, then game counter would move back to xH==0 yH==0   that is why the counters were moving 
              down one column and then back when RED BALL was on them and  RMBD or SPACE_BAR clicked
              the last  '&&'(||)' in the 'if' will stop the game counter from being told to move to where it currently is
              ***************/
								if (  input->getMouseRButton() || input->isKeyDown(SPACE_KEY) ) 
								{
                  for (int i = 1; i < 10; ++i)   // to have gotten here cn == _eRB and cn-1 == _eHL 
                  {
                    if (gameCounter[cn - 1].row == gameCounter[i].row && gameCounter[cn - 1].col == gameCounter[i].col &&
                      gameCounter[i].gCTopCounter == true && (gameCounter[i].row != gameCounter[_eRB].row  ||  gameCounter[i].col != gameCounter[_eRB].col ) )                  
										{
											gameCounter[i].xd = gameCounter[cn].x;  // a hard coded test to get a player controlled game counter on the move ********************************
											gameCounter[i].yd = gameCounter[cn].y;
											gameCounter[i].rowd = gameCounter[cn].row;
											gameCounter[i].cold = gameCounter[cn].col;  

											gameCounter[i].gCmove = true;
                      if(input->getMouseRButton())   //  if you use the Mouse Right Button to sent to counter highlighted to the hexagon the 'Ball' is on you must clear the Mouse or some or all of any other game counters under the one you want to move may pick up the move command.
                        input->clearAll();                  //  if you use the 'SPACE_KEY' you can send one after the other of game counters from one hexagon to the destination hexagon with no follow on by game counters you want to stay on origin hexagon
										}// END on 'if' gameCounter...
									}// END on 'for' i < 10...
								}// END 'if' on input->isKeyDown...
                else
                  if ( (input->getMouseLButton() && (gameCounter[cn].name == "Red Ball")  )  &&
                                 (  input->isKeyDown('W')   || input->isKeyDown('X') || input->isKeyDown('Y') || input->isKeyDown('Z') )  ) // call to way points to be added
                  {
                    gCAddWayPoint(td, input, cn); // go to AddWayPoint to add a way point to this 'i' game counter
                  }// END 'if' on  if (input->isKeyDown('w'))" call to way points
							}// END 'if' on '	if (gameCounter[cn - 1].row == gameCounter[i].row && gameCounter[cn - 1].col == gameCounter[i].col)'
						}// END 'for' on i...						
					}// end if mouse left button down ******************************
				}// END 'if' on   (abs(yH + r - mY) < r / 2.0f) ...

			// this stops ball and line from being drawn from a map game counter out over the sea 
			if ((mX <  getXh() || mY < getYh()) || (mX >  getTileData_X(TILE_MAP_HEIGHT - 1, TILE_MAP_WIDTH - 1) + 
						textureWidth * tile.getScale() || mY >(getTileData_Y(TILE_MAP_HEIGHT - 1, TILE_MAP_WIDTH - 1) + textureHight * tile.getScale())))
			{
				setMHrow(-1);
				setMHcol(-1);
				gameCounter[cn].gCVisible = false;
				linePoints.bDrawLine = false;
			}
		}// END inner for loop on column... 
	}// END outter for loop on row...
  bBoatBreak = false; // set bBoatBreak to false just encase it get used to breakout of the outer 'for' loop

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // FOR boats ONLY ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// remember it is only;  Highlighter, Ball, and Green Ball that are the trips in this method ... 
	// so only cn == 11 == Highlighter, cn == 12 == Ball, and cn == 13 == Green Ball are in the parameters of this 'if' statement 
	// all markers;  Highlighter, Ball, and Green Ball....  are 700 series 
	// gBoatSpeed = 0.0f;   // used for the boat navigation speed as boat move over sea
   // Highlighter, Ball, and Green Ball are 700 series game counters
  // Only one 'BOAT' Type  for all boats large and small

	if (gameCounter[cn].idNumber >= 700 && gameCounter[cn].idNumber <= 799 && getMHrow() == -1 && getMHcol() == -1)
	{																											// when on the sea mouse Hexagon row and col is -1 
		// for testing boat large is 8 boat small is 9
		for (int i = 8; i <= 9; ++i)
		{
			boatNumber = i;
			if (gameCounter[i].idNumber <= 400 || gameCounter[i].idNumber >= 600) // boat are [401 599] so break on others
				break; // so only boats get this far   this is safty that may be needed later

			boatX  = gameCounter[i].x;  // now have current boat x,y values at upper left of rectangle  not center of hexagon
			boatY  = gameCounter[i].y;
			
			if (abs(boatX + R - mX) < r / 2.0f) // this is our current buffer to make sure mouse pointer is pointing to center of hexagon 
				if (abs(boatY + r - mY) < r / 2.0f)
				{	//  without the left mouse button NOT DOWN  (!up) and you put the mouse pointer over a boat the MARKER highlighter comes on 
					if ( !(input->getMouseLButton() ) &&  gameCounter[cn].name == "Highlighter")  
					{
						gameCounter[cn].gCVisible = true;
						gameCounter[cn].x = boatX;
						gameCounter[cn].y = boatY;
						gameCounter[cn].scale = td[0][0].tileScale;
						linePoints.x1 = boatX;
						linePoints.y1 = boatY;
					}					
				}// END 'if' on abs(boatX...

			// for watch window so can see  deff. between mX and mY  and island shore
		    fx = td[TILE_MAP_HEIGHT - 1][TILE_MAP_WIDTH - 1].x + TEXTURE_HEIGHT * td[0][0].tileScale * 2;
			fy = td[TILE_MAP_HEIGHT - 1][TILE_MAP_WIDTH - 1].y + TEXTURE_HEIGHT * td[0][0].tileScale * 2;
		   
        // below is code that shuts the ball and navigation line off if the line is pulled over land 
        // when the pointer is moved from over sea to over land set visibility on markers; Highlighter, Ball and Line to false 
			if (input->getMouseLButton() && (gameCounter[cn].name == "Red Ball"))  // If left mouse button is clicked  and the marker is "Ball" **************************
			{
				if (gameCounter[i].x == gameCounter[cn - 1].x && gameCounter[i].y == gameCounter[cn - 1].y)    // if [cn] == "Red Ball" then [cn-1] == "Highlighter" 
				{  // now 'Highlighter' and some boat have same coordinates
					bBoatBreak = false;  // if set to 'true' below this will break out of outer 'for loop'
					// (mHrow >= 0 || mHcol >= 0)  // when the pointer is moved from over sea to over land set visibility on Highlighter, Ball and Navigation Line to false 
					for (int row = 0; row < TILE_MAP_HEIGHT; ++row)
					{
						if (bBoatBreak)
							break;
						for (int col = 0; col < TILE_MAP_WIDTH; ++col)
						{   // stops the navigation Ball get over any land hexagon
							if ( (abs(mX - (td[row][col].x +  R)) <= 2.0f * R ) && (abs(mY - (td[row][col].y + r)) <= 2.0f * r) )
							{
								gameCounter[cn - 1].gCVisible = false;  // do not draw Highlighter now    If pointer is here then you are over land but have a Highlighter on a boat. 
								gameCounter[cn].gCVisible = false;	// do not draw Ball now	
								linePoints.bDrawLine = false;   // do not draw Navigation Line now	
								bBoatBreak = true;
								break;
							}
						}// end of 'for loop' on 'j'...
					}// end of 'for loop' on 'i'...
			
             /************************************************************************************************************************************
					   The break statement is used with the conditional switch statement and with the do, for, and while loop statements.
						In a switch statement, the break statement causes the program to execute the next statement outside the switch statement.Without a break statement, every statement from the matched case label to the end of the switch statement, including the default clause, is executed.
						In loops, the break statement ends execution of the nearest enclosing do, for, or while statement.Control passes to the statement that follows the ended statement, if any.
						Within nested statements, the break statement ends only the do, for, switch, or while statement that immediately encloses it.You can use a return or goto statement to transfer control from more deeply nested structures.
            ***************************************************************************************************************************************/
					//  need to know if line between boat and ball is pulled around island, if it is pulled around island so boat is on one side and ball is on the other
					//	then want line, ball and bDrawLine all set to false     just line when ball is pulled over island.
					//	well try this
					//	boat point to ball point get R / R then divide by line length by 100
					//	'for' loop R / R + (line length) / 100 to test 100 points along line from boat to ball
					//	if any point if td[n][m].x, y + r then set all visible to FALSE and 'break'
				
					//deltaLineX = mX ;  //   the deltaLineX/Y is the end of navigation line   by subtracting the incrementLineX from it you can walk back along that line to its' origin at the boat
					//deltaLineY = mY ;  //   "

//************************************************************************************************************************************************
					incrementLineX =  ( ( boatX + R) - mX) / navigationLineDivisor;  //  length of navigation line is divided up in to 'n' number of x,y positions and each is tested agains all hexagons centers
					incrementLineY =  ( ( boatY + r ) - mY) / navigationLineDivisor;  //  if navigation line is dragged with in 2*'R' for 'x' value or 2*'r' for 'y' value of a hexagon center the navigation line is set to 'false'
				                               // the +R +r will start the navigation line at the center of the boat not the upper left corner of the boats sprite this took some time to find ??? 
 //************************************************************************************************************************************************

					//  now need to come up with a test for the navigation line, that will not let it come so close to land that the boat runs aground.   look at the ball navigation code above 
					// some type of nested 'for loop's may work out, make sure it is td[row][col].x/y  that is test row n col m, row n col m+1, that way you go across the row column by column
			       //	bBoatBreak = false;  // may want this left at state set in Ball navigation above   that way will not have to test navigation line against hexagon if Ball is too close to land and has shut down Ball+Line+Highlighter
					
				   // IT LOOKS LIKE IT IS THE NAVIGATION LINE THAT IS BEACHING THE BOATS ON THE SOUTH AND EAST SHORES *****************************************************
					for (int row = 0; row < TILE_MAP_HEIGHT; ++row) // down one row at a time
					{
						for (int col = 0; col < TILE_MAP_WIDTH; ++col)  // acrose one column at a time
						{
							deltaLineX = mX;  //   the deltaLineX/Y is the end of navigation line   by subtracting the incrementLineX from it you can walk back along that line to its' origin at the boat
							deltaLineY = mY;  //   "
												
							for (int a = 1; a <= navigationLineDivisor; ++a)
							{
// IT LOOKS LIKE IT IS THE NAVIGATION LINE THAT IS BEACHING THE BOATS ON THE SOUTH AND EAST SHORES *****************************************************
								if( (abs(  td[row][col].x + R - deltaLineX )< 2*R)  &&  (abs(td[row][col].y + r - deltaLineY) < 2*r)  )
								{  // get here and the line from a BOAT to BALL is over land ????????????????????????????????????????????????????????????????????????????????????????
									gameCounter[cn - 1].gCVisible = false;  // do not draw Highlighter now  
									gameCounter[cn].gCVisible = false;	// do not draw Ball now	
									linePoints.bDrawLine = false;   // do not draw Navigation Line now		

									gameCounter[cn].x = boatX;  // this will put ball back to some BOAT possition this way you do not keep comming in here    as with out this 
									gameCounter[cn].y = boatY;  //  the BALL is not visible but is still on the other side of the island and this test will keep bringing you in. 

									bBoatBreak = true;
									break;  // this way you can break out of 'for' ON (int a = 1; a <= 10; ++a) ...
								}            //  The break statement is used with the conditional switch statement and with the do, for, and while loop statements.
								deltaLineX += incrementLineX;  // now walk back towards boat along the navigation line
								deltaLineY += incrementLineY; // "
								if (bBoatBreak)
									break;  // out of 'for loop' on 'a'
							}// end of 'for loop' on 'a'
							if (bBoatBreak)
							  break; // out of 'for loop' on 'j'
						}// end of 'for loop' on 'j' == column...
						if (bBoatBreak)
							break; // out of 'for loop' on 'row'
					 }// end of outer 'for loop' on 'row'...

					if (bBoatBreak) break;   // this way you can break out of the outer 'if' ON (gameCounter[cn].idNumber >= 700 && gameCounter[cn].idNumber <= 799 && getMHrow() == -1 && getMHcol() == -1)	

					//  if you get to here then everything is good and you can set up all the info and turn on all the switches for the boat to move
					gameCounter[cn].x = mX - (TEXTURE_WIDTH * td[0][0].tileScale) / 2.0f;
					gameCounter[cn].y = mY - (TEXTURE_HEIGHT * td[0][0].tileScale) / 2.0f;
					gameCounter[cn].scale = td[0][0].tileScale;
					linePoints.x2 = mX - (TEXTURE_WIDTH * td[0][0].tileScale) / 2.0f;
					linePoints.y2 = mY - (TEXTURE_HEIGHT * td[0][0].tileScale) / 2.0f;

					gameCounter[cn - 1].gCVisible = true;  // Highlighter stays visible until right mouse button down, or left mouse button released  
					gameCounter[cn].gCVisible = true;	// draw ball now	
					linePoints.bDrawLine = true;   // draw line now			

					// if you get here then you are over the sea and have a Highlighter on a boat 
					// if right mouse button down boat will move to this new position 

					/*****************
					As most people now use laptops with touch pads and touch screens adding the “ || (input->isKeydown(SPACE_KEY)” to
					if (input->getMouseRButton() || (input->isKeyDown(SPACE_KEY)))
					will make using the touch pad / screen possible.
					************************/

					if (input->getMouseRButton() || (input->isKeyDown(SPACE_KEY)))
					{
						gameCounter[i].xd = linePoints.x2;
						gameCounter[i].yd = linePoints.y2;
						// NOW  need to come up with a deltaXd deltaYd  that is a delta off set from td[0][0] to the boats destination 
						// that deltaXd and deltaYd can be updated as map is scrolled and scaled     that might work to keep boats movement working the way you want
						// divide by the current tile scale so deltaXd deltaYd are at 1:1 scale value that way they can be scaled correctly in CTFgameCounters 
						gameCounter[i].deltaXd = (gameCounter[i].xd - td[0][0].x) / tile.getScale();
						gameCounter[i].deltaYd = (gameCounter[i].yd - td[0][0].y) / tile.getScale();																	
						gameCounter[i].gCmove = true;					
					}
				}// end of 'if' on gameCounter[i] ...
			}  // END OF 'if (input->getMouseLButton() && (gameCounter[cn].name == "Red Ball") )' ...		
		}// END 'for' ON for (int i = 8; i <= 9; ++i)  ...
	}// END 'if' ON (gameCounter[cn].idNumber >= 700 && gameCounter[cn].idNumber <= 799 && getMHrow() == -1 && getMHcol() == -1) ...	
// END boats ONLY -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// NEXT way point (if any) now to be made new rowd, cold, and or xd, yd ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
// Going to see if a routine in this method can be put here that will change the rowd, cold, xd, and yd of a game counter if that game counter had way points added
// to its course
  for (int i = 0; i < NUMBER_OF_NAMES; ++i)
  {
    if (gameCounter[i]._caWayPointsActive[0] != '\0' || gameCounter[i]._caWayPointsActive[1] != '\0' || gameCounter[i]._caWayPointsActive[2] != '\0' || 
                                                                               gameCounter[i]._caWayPointsActive[3] != '\0'  )
      if(gameCounter[i].row == gameCounter[i].rowd  && gameCounter[i].col == gameCounter[i].cold  && gameCounter[i].WayPointsToReached > 0
                                                                                                                                                     && !input->getMouseLButton())
    {
      for (int j = 0; j < 4; ++j)
      {
        switch (gameCounter[i]._caWayPointsActive[j])  // check if w,x,y, or z way points have been entered
        {
        case 'w':
          gameCounter[i].rowd = gameCounter[i].rowd1;  // sets destination to 'w' way point
          gameCounter[i].cold = gameCounter[i].cold1;
          gameCounter[i].xd = td[gameCounter[i].rowd1][gameCounter[i].cold1].x;   // sets destination x,y to 'w' way pont x,y
          gameCounter[i].yd = td[gameCounter[i].rowd1][gameCounter[i].cold1].y;
          gameCounter[i].gCmove = true;   
          input->clearAll(); // clear the isKeyDown('M')        
          if (gameCounter[i].row == gameCounter[i].rowd  && gameCounter[i].col == gameCounter[i].cold)
          {
            gameCounter[i]._caWayPointsActive[j] = '\0';  // this way 'w' way point can't be reset as destination on this 'move'
            gameCounter[i].WayPointsToReached--;   // need to use some type of safety to stop other way points from being set as destination before 'x' way point reached.
            gameCounter[i].gCmove = false; // helps reduce the move instruction confusion
          }
          break;

        case 'x':
          if (gameCounter[i]._caWayPointsActive[j - 1] != '\0')
            break;
             if (gameCounter[i].row != gameCounter[i].rowd  && gameCounter[i].col != gameCounter[i].cold)
            break;
          gameCounter[i].rowd = gameCounter[i].rowd2;
          gameCounter[i].cold = gameCounter[i].cold2;
          gameCounter[i].xd = td[gameCounter[i].rowd2][gameCounter[i].cold2].x;
          gameCounter[i].yd = td[gameCounter[i].rowd2][gameCounter[i].cold2].y;
          gameCounter[i].gCmove = true;
          input->clearAll(); // clear the isKeyDown('M')
          if (gameCounter[i].row == gameCounter[i].rowd  && gameCounter[i].col == gameCounter[i].cold)
          {
            gameCounter[i]._caWayPointsActive[j] = '\0';  // this way 'w' way point can't be reset as destination on this 'move'
            gameCounter[i].WayPointsToReached--;   // need to use some type of safety to stop other way points from being set as destination before 'x' way point reached.
            gameCounter[i].gCmove = false; // helps reduce the move instruction confusion
          }
          break;

        case 'y':
          if (gameCounter[i]._caWayPointsActive[j - 1] != '\0' || gameCounter[i]._caWayPointsActive[j - 2] != '\0')
            break;
             if (gameCounter[i].row != gameCounter[i].rowd  && gameCounter[i].col != gameCounter[i].cold )
            break;
          gameCounter[i].rowd = gameCounter[i].rowd3;
          gameCounter[i].cold = gameCounter[i].cold3;
          gameCounter[i].xd = td[gameCounter[i].rowd3][gameCounter[i].cold3].x;
          gameCounter[i].yd = td[gameCounter[i].rowd3][gameCounter[i].cold3].y;
          gameCounter[i].gCmove = true;
          input->clearAll(); // clear the isKeyDown('M')
          if (gameCounter[i].row == gameCounter[i].rowd  && gameCounter[i].col == gameCounter[i].cold)
          {
            gameCounter[i]._caWayPointsActive[j] = '\0';  // this way 'w' way point can't be reset as destination on this 'move'
            gameCounter[i].WayPointsToReached--;   // need to use some type of safety to stop other way points from being set as destination before 'x' way point reached.
            gameCounter[i].gCmove = false;  // helps reduce the move instruction confusion
          }
          break;

        case 'z':
          if (gameCounter[i]._caWayPointsActive[j - 1] != '\0' || gameCounter[i]._caWayPointsActive[j - 2] != '\0' || gameCounter[i]._caWayPointsActive[j - 3] != '\0')
            break;
            if (gameCounter[i].row != gameCounter[i].rowd  && gameCounter[i].col != gameCounter[i].cold )
            break;
          gameCounter[i].rowd = gameCounter[i].rowd4;
          gameCounter[i].cold = gameCounter[i].cold4;
          gameCounter[i].xd = td[gameCounter[i].rowd4][gameCounter[i].cold2].x;
          gameCounter[i].yd = td[gameCounter[i].rowd2][gameCounter[i].cold2].y;
          gameCounter[i].gCmove = true;
          input->clearAll(); // clear the isKeyDown('M')
          if (gameCounter[i].row == gameCounter[i].rowd  && gameCounter[i].col == gameCounter[i].cold)
          {
            gameCounter[i]._caWayPointsActive[j] = '\0';  // this way 'w' way point can't be reset as destination on this 'move'
            gameCounter[i].WayPointsToReached--;   // need to use some type of safety to stop other way points from being set as destination before 'x' way point reached.
            gameCounter[i].gCmove = false;  // helps reduce the move instruction confusion
          }
          break;

        default:
        {
          // same for later ...
        }
        
        }  // END switch 
      }// END  'for (int j = 0; j < 4; ++j)'
    }//  END ' if (gameCounter[i]._caWayPointsActive != '\0')'
  }// END ' for (int i = 0; i < NUMBER_OF_NAMES; ++i)'
	return ;
}// END method  void CatchTheFly::gCmove(TileData td[][40], Input* input, const int cn, const int textureWidth, const int textureHight)