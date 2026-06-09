// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// game.cpp v1.2
// Last modified Feb-11-2013

#include "game.h"
// The primary class should inherit from Game class

//=============================================================================
// Constructor
//=============================================================================
Game::Game()
{
    input = new Input();        // initialize keyboard input immediately
    // additional initialization is handled in later call to input->initialize()
    paused = false;             // game is not paused
    graphics = NULL;
    audio = NULL;
    console = NULL;
    messageDialog = NULL;
    inputDialog = NULL;
    fps = 100;
    fpsOn = true;              // default to fps display off
    gameDataOn = true;            // xy of first hexagon
    counterDataOn = true;           // xy of mouse pointer display off
    initialized = false;
}

//=============================================================================
// Destructor
//=============================================================================
Game::~Game()
{
    deleteAll();                // free all reserved memory
    ShowCursor(true);           // show cursor
}

//=============================================================================
// Window message handler
//=============================================================================
LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    if(initialized)     // do not process messages if not initialized
    {
		HINSTANCE hInstance;
        switch( msg )
        {   
            case WM_DESTROY:
                PostQuitMessage(0);        //tell Windows to kill this program
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // key up
                input->keyUp(wParam);
                return 0;
            case WM_CHAR:                           // character entered
                input->keyIn(wParam);                
                return 0;
            case WM_MOUSEMOVE:                      // mouse moved
                input->mouseIn(lParam);
                return 0;
            case WM_INPUT:                          // raw mouse data in
                input->mouseRawIn(lParam);
                return 0;
            case WM_LBUTTONDOWN:                    // left mouse button down
                input->setMouseLButton(true);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_LBUTTONUP:                      // left mouse button up
                input->setMouseLButton(false);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_MBUTTONDOWN:                    // middle mouse button down
                input->setMouseMButton(true);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_MBUTTONUP:                      // middle mouse button up
                input->setMouseMButton(false);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_RBUTTONDOWN:                    // right mouse button down
                input->setMouseRButton(true);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_RBUTTONUP:                      // right mouse button up
                input->setMouseRButton(false);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_XBUTTONDOWN: case WM_XBUTTONUP: // mouse X button down/up
                input->setMouseXButton(wParam);
                input->mouseIn(lParam);             // mouse position
                return 0;
            case WM_MOUSEWHEEL:                     // mouse wheel move
                input->mouseWheelIn(wParam);
                return 0;
            case WM_DEVICECHANGE:                   // check for controller insert
                input->checkControllers();
                return 0;                       			
        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // let Windows handle it
}

//=============================================================================
// Initializes the game
// throws GameError on error
//=============================================================================
void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // save window handle

    // initialize graphics
    graphics = new Graphics();
    // throws GameError
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);

    // initialize input, do not capture mouse
    input->initialize(hwnd, false);             // throws GameError

    // initialize console
    console = new Console();
    console->initialize(graphics, input);       // prepare console
    console->print("---Console---");

    // initialize messageDialog
    messageDialog = new MessageDialog();
    messageDialog->initialize(graphics, input, hwnd);

    // initialize inputDialog
    inputDialog = new InputDialog();
    inputDialog->initialize(graphics, input, hwnd);

    // initialize DirectX font
    if(dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font.\n  You FLY out of luck man!"));

    dxFont.setFontColor(gameNS::FONT_COLOR);

    // init sound system
    audio = new Audio();
    if (*WAVE_BANK != '\0' && *SOUND_BANK != '\0')  // if sound files defined
    {
        if( FAILED( hr = audio->initialize() ) )
        {
            if( hr == HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ) )
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system because media file not found.\n  You FLY out of luck man!"));
            else
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system.\n  You FLY out of luck man!"));
        }
    }

    // attempt to set up high resolution timer
    if(QueryPerformanceFrequency(&timerFreq) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer\n  You FLY out of luck man!"));

    QueryPerformanceCounter(&timeStart);        // get starting time

    initialized = true;
}

//=============================================================================
// Render game items
//=============================================================================
void Game::renderGame()
{
  const int BUF_SIZE = 200;
  static char buffer[BUF_SIZE];
	char* condition;  // used to hold true/false state of counters moving or not.
	const int tDs = 210;  // top of screen display x spacing 
	// needed for time display of game counters movement
	int minutes, seconds;  
	float tempSeconds;
	char Tbuf[80];

    //start rendering +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();           // call render() in derived object

        graphics->spriteBegin();    // begin drawing sprites ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if(fpsOn)           // if fps display requested
        {
            // convert fps to string
            _snprintf_s(buffer, BUF_SIZE, "fps %d ", (int)fps);
            dxFont.print(buffer,GAME_WIDTH-300,GAME_HEIGHT-18);
        }
        if (gameDataOn)
        {
           // convert first hexagon xy postion to string  lower right hand hexagon and mouse data...
          _snprintf_s(buffer, BUF_SIZE, "hexagon scale %f", getTileData_S(0, 0));
          dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 78);
          // show Hx and Hy of mouse pointer local
          _snprintf_s(buffer, BUF_SIZE, "Hi Light Marker @ H row = %d, H col = %d ", getMHrow(), getMHcol()); 
          dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 68);
          // show Hx and Hy of mouse pointer local
          _snprintf_s(buffer, BUF_SIZE, "Hi Light Marker Hex x =%3.2f, y =%3.2f ", gameCounter[_eHL].x,  gameCounter[_eHL].y );//   getTileData_X(getMHrow(), getMHcol()), getTileData_Y(getMHrow(), getMHcol()));
          dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 58);
          // convert first hexagon xy postion to string
          _snprintf_s(buffer, BUF_SIZE, "x,y of mouse pointer x = %d, y = %d ", input->getMouseX(), input->getMouseY());
          dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 48);
          _snprintf_s(buffer, BUF_SIZE, "x,y of first hexagon %d, %d ", (int)(getXh()), (int)(getYh()));
          dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 38);
           _snprintf_s(buffer, BUF_SIZE, "x,y of last hexagon  %d, %d ", (int)(getTileData_X(TILE_MAP_HEIGHT - 1, TILE_MAP_WIDTH - 1)), (int)(getTileData_Y(TILE_MAP_HEIGHT - 1, TILE_MAP_WIDTH - 1)));
           dxFont.print(buffer, GAME_WIDTH - 300, GAME_HEIGHT - 28);
        
         
		   _snprintf_s(buffer, BUF_SIZE, "A1's time to move: %3.1f ",  gameCounter[7].timeTillMove - gameCounter[7].frameTimeElapsed);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 18);
		   _snprintf_s(buffer, BUF_SIZE, "A1's xd, yd:%*d,%*d ", 5, (int)gameCounter[7].xd, 5, (int)gameCounter[7].yd);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 28);
		   _snprintf_s(buffer, BUF_SIZE, "A1's x, y:  %*d,%*d ", 5, (int)gameCounter[7].x, 5,  (int)gameCounter[7].y);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 38);				   
		   _snprintf_s(buffer, BUF_SIZE, "A1's Orow, Ocol: %*d, %*d ", 2, (int)gameCounter[7].oldRow, 2, (int)gameCounter[7].oldCol);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 48);
		   _snprintf_s(buffer, BUF_SIZE, "A1's rowd, cold: %*d, %*d ", 2, (int)gameCounter[7].rowd, 2, (int)gameCounter[7].cold);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 58);
		   _snprintf_s(buffer, BUF_SIZE, "A1's row, col:   %*d, %*d ", 2, (int)gameCounter[7].row, 2, (int)gameCounter[7].col);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 68);

	
		   condition = (gameCounter[7].gCmove ? "True" : "False");
		   _snprintf_s(buffer, BUF_SIZE, "A1 is moving %s.", condition);
		   dxFont.print(buffer, GAME_WIDTH - 476, GAME_HEIGHT - 78);

		   _snprintf_s(buffer, BUF_SIZE, "S1's x, y:  %*d,%*d ", 5, (int)gameCounter[1].x, 5, (int)gameCounter[1].y);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 38);
		   _snprintf_s(buffer, BUF_SIZE, "S1's xd, yd:%*d,%*d ", 5, (int)gameCounter[1].xd, 5, (int)gameCounter[1].yd);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 28);
		   _snprintf_s(buffer, BUF_SIZE, "S1's row, col:   %*d, %*d ", 2, (int)gameCounter[1].row, 2, (int)gameCounter[1].col);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 68);
		   _snprintf_s(buffer, BUF_SIZE, "S1's rowd, cold: %*d, %*d ", 2, (int)gameCounter[1].rowd, 2, (int)gameCounter[1].cold);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 58);
		   _snprintf_s(buffer, BUF_SIZE, "S1's Orow, Ocol: %*d, %*d ", 2, (int)gameCounter[1].oldRow, 2, (int)gameCounter[1].oldCol);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 48);
		   
		   condition = (gameCounter[1].gCmove ? "True" : "False");
		   _snprintf_s(buffer, BUF_SIZE, "S1 is moving %s.", condition);
		   dxFont.print(buffer, GAME_WIDTH - 680, GAME_HEIGHT - 78);
   

		   // ******************** boat data *****************************************************
		   // boat large
		   condition = (gameCounter[8].gCmove ? "True" : "False");
		   _snprintf_s(buffer, BUF_SIZE, "Boat Large is moving %s.", condition);
		   dxFont.print(buffer, 5, GAME_HEIGHT - 78);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Large's x, y: %3.2f, %3.2f", gameCounter[8].x, gameCounter[8].y);   // true windows (x,y) user area position
		   dxFont.print(buffer, 5, GAME_HEIGHT - 68);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Large's xd, yd: %3.2f, %3.2f", gameCounter[8].xd, gameCounter[8].yd);  // true windows (x,y) destination that is picked up from "Red Ball"
		   dxFont.print(buffer, 5, GAME_HEIGHT - 58);
       _snprintf_s(buffer, BUF_SIZE, "Boat Large's xDt, yDt: %3.2f, %3.2f", gameCounter[8].xDt, gameCounter[8].yDt); // boat's scaled off set from H(0,0) as it is moving  its temp position 
       dxFont.print(buffer, 5, GAME_HEIGHT - 48);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Large's dXd, dYd: %3.2f, %3.2f", gameCounter[8].deltaXd, gameCounter[8].deltaYd);  //  boat's scaled (x,y) destination 
		   dxFont.print(buffer, 5, GAME_HEIGHT - 38);		
		   _snprintf_s(buffer, BUF_SIZE, "Boat Large's xDta, yDta: %3.2f, %3.2f", gameCounter[8].deltaX, gameCounter[8].deltaY);  // boat's scaled off set from H(0,0)   also starting position  when boat get move command (xDta, yDta) are set to (xDd, yDd) 
		   dxFont.print(buffer, 5, GAME_HEIGHT - 28);

		   // boat small
		   condition = (gameCounter[9].gCmove ? "True" : "False");
		   _snprintf_s(buffer, BUF_SIZE, "Boat Small is moving %s.", condition);
		   dxFont.print(buffer, 295, GAME_HEIGHT - 78);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Small's x, y: %3.2f, %3.2f", gameCounter[9].x, gameCounter[9].y);
		   dxFont.print(buffer, 295, GAME_HEIGHT - 68);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Small's xd, yd: %3.2f, %3.2f", gameCounter[9].xd, gameCounter[9].yd);
		   dxFont.print(buffer, 295, GAME_HEIGHT - 58);
       _snprintf_s(buffer, BUF_SIZE, "Boat Small's xDt, yDt: %3.2f, %3.2f", gameCounter[9].xDt, gameCounter[9].yDt);
       dxFont.print(buffer, 295, GAME_HEIGHT - 48);
		   _snprintf_s(buffer, BUF_SIZE, "Boat Small's xDd, yDd: %3.2f, %3.2f", gameCounter[9].deltaXd, gameCounter[9].deltaYd);
		   dxFont.print(buffer, 295, GAME_HEIGHT - 38);		 
		   _snprintf_s(buffer, BUF_SIZE, "Boat Small's xDta, yDta: %3.2f, %3.2f", gameCounter[9].deltaX, gameCounter[9].deltaY);
		   dxFont.print(buffer, 295, GAME_HEIGHT - 28);
		   		   
			   // fly position . . .
			   condition = (gameCounter[0].gCVisible ? "True" : "False");
			   _snprintf_s(buffer, BUF_SIZE, "%s is Visible:        %s ", &gameCounter[0].name, condition);
			   dxFont.print(buffer, 0, 60);  // just screen position stuff  top display spacing tDs
			   _snprintf_s(buffer, BUF_SIZE, "%s Current Hex r,c:   %*d,%*d ", &gameCounter[0].name, 2, (int)gameCounter[0].row, 2, (int)gameCounter[0].col);
			   dxFont.print(buffer, 0, 70);  // just screen position stuff			 

			   // native position . . .
			   condition = (gameCounter[10].gCVisible ? "True" : "False");
			   _snprintf_s(buffer, BUF_SIZE, "%s is Visible:        %s ", &gameCounter[10].name, condition);
			   dxFont.print(buffer, tDs, 60);  // just screen position stuff  top display spacing tDs
			   _snprintf_s(buffer, BUF_SIZE, "%s Current Hex r,c:   %*d,%*d ", &gameCounter[10].name, 2, (int)gameCounter[10].row, 2, (int)gameCounter[10].col);
			   dxFont.print(buffer, tDs, 70);  // just screen position stuff			 

          // green ball position . . .
         condition = (gameCounter[_eGB].gCVisible ? "True" : "False");
         _snprintf_s(buffer, BUF_SIZE, "%s is Visible:        %s ", &gameCounter[_eGB].name, condition);
         dxFont.print(buffer,(2*tDs + 70), 60);  // just screen position stuff  top display spacing tDs
         _snprintf_s(buffer, BUF_SIZE, "%s Current Hex r,c:   %*d,%*d ", &gameCounter[_eGB].name, 2, (int)gameCounter[_eGB].row, 2, (int)gameCounter[_eGB].col);
         dxFont.print(buffer,(2*tDs + 70), 70);  // just screen position stuff			 


		  
        }		
		// this is the top of screen display of the player's counters tells if counter is moving, current position and destination.
		if (counterDataOn)
		{
			for (int i = 1; i < NUMBER_OF_NAMES; ++i)
			{
				if (i <= 6)
				{
					condition = (gameCounter[i].gCmove ? "True" : "False");
					_snprintf_s(buffer, BUF_SIZE, "%s is moving %s ", &gameCounter[i].name, condition);					
					dxFont.print(buffer, (tDs*(i-1)), 0 );  // just screen position stuff  top display spacing tDs
					_snprintf_s(buffer, BUF_SIZE, "%s Current Hex r,c:    %*d,%*d ", &gameCounter[i].name, 2, (int)gameCounter[i].row, 2, (int)gameCounter[i].col);
					dxFont.print(buffer, (tDs * (i-1)), 10);  // just screen position stuff
					_snprintf_s(buffer, BUF_SIZE, "%s Destination Hex r,c:%*d,%*d ", &gameCounter[i].name, 2, (int)gameCounter[i].rowd, 2, (int)gameCounter[i].cold);
					dxFont.print(buffer, (tDs * (i-1)), 20);  // just screen position stuff
					

					minutes =(int) (gameCounter[i].timeTillMove - gameCounter[i].frameTimeElapsed) / 60;
					seconds = (int) (gameCounter[i].timeTillMove - gameCounter[i].frameTimeElapsed) % 60;
					tempSeconds = (gameCounter[i].timeTillMove - gameCounter[i].frameTimeElapsed) - (int)(gameCounter[i].timeTillMove - gameCounter[i].frameTimeElapsed);
					tempSeconds += (float)seconds;
					if (seconds <= -1) tempSeconds = 0.0f;
					
					_snprintf_s(buffer, BUF_SIZE, "Time to move:%02d min,%004.1f sec", minutes, tempSeconds);
					dxFont.print(buffer, (tDs * (i - 1)), 30);  // just screen position stuff			
			
					strftime(Tbuf, sizeof(Tbuf), "Arrived current Hex %X", &gameCounter[i].gCTstruct);
					_snprintf_s(buffer, BUF_SIZE, "%s", Tbuf );
					dxFont.print(buffer, (tDs * (i - 1)), 40);  // just screen position stuff			
				}
			}
		}

        graphics->spriteEnd();      // end drawing sprites----------------------------------------------------------------------------------------------------------------------------------------

        console->draw();    // console is drawn here so it appears on top of game

        messageDialog->draw();  // dialog is drawn on top
        inputDialog->draw();    // dialog is drawn on top

        //stop rendering -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
        graphics->endScene();
    }
    handleLostGraphicsDevice();

    //display the back buffer on the screen
    graphics->showBackbuffer();
}

//=============================================================================
// Handle lost graphics device
//=============================================================================
void Game::handleLostGraphicsDevice()
{
    // test for and handle lost device
    hr = graphics->getDeviceState();
    if(FAILED(hr))                  // if graphics device is not in a valid state
    {
        // if the device is lost and not available for reset
        if(hr == D3DERR_DEVICELOST)
        {
            Sleep(100);             // yield cpu time (100 mili-seconds)
            return;
        } 
        // the device was lost but is now available for reset
        else if(hr == D3DERR_DEVICENOTRESET)
        {
            releaseAll();
            hr = graphics->reset(); // attempt to reset graphics device
            if(FAILED(hr))          // if reset failed
                return;
            resetAll();
        }
        else
            return;                 // other device error
    }
}

//=============================================================================
// Toggle window or fullscreen mode
//=============================================================================
void Game::setDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
    releaseAll();                   // free all user created surfaces
    graphics->changeDisplayMode(mode);
    resetAll();                     // recreate surfaces
}

//=============================================================================
// Call repeatedly by the main message loop in WinMain
//=============================================================================
void Game::run(HWND hwnd)
{
    if(graphics == NULL)            // if graphics not initialized
        return;

    // calculate elapsed time of last frame, save in frameTime
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / (float)timerFreq.QuadPart;

    // Power saving code, requires winmm.lib
    // if not enough time has elapsed for desired frame rate
    if (frameTime < MIN_FRAME_TIME) 
    {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         // Request 1mS resolution for windows timer
        Sleep(sleepTime);           // release cpu for sleepTime
        timeEndPeriod(1);           // End 1mS timer resolution
        return;
    }

    if (frameTime > 0.0)
        fps = (fps*0.99f) + (0.01f/frameTime);  // average fps
    if (frameTime > MAX_FRAME_TIME) // if frame rate is very slow
        frameTime = MAX_FRAME_TIME; // limit maximum frameTime
    timeStart = timeEnd;

    // update(), ai(), and collisions() are pure virtual functions.
    // These functions must be provided in the class that inherits from Game.
    if (!paused)                    // if not paused
    {
        update();                   // update all game items
        ai();                       // artificial intelligence
        collisions();               // handle collisions
        input->vibrateControllers(frameTime); // handle controller vibration
    }
    renderGame();                   // draw all game items

    //check for console key
    if (input->getCharIn() == CONSOLE_KEY)
    {
        input->clearCharIn();       // clear last char
        console->showHide();
        paused = console->getVisible(); // pause game when console is visible
    }
    consoleCommand();               // process user entered console command

    input->readControllers();       // read state of controllers

    messageDialog->update();
    inputDialog->update();

    audio->run();                   // perform periodic sound engine tasks

    // if Alt+Enter toggle fullscreen/window
    if (input->isKeyDown(ALT_KEY) && input->wasKeyPressed(ENTER_KEY))
        setDisplayMode(graphicsNS::TOGGLE); // toggle fullscreen/window

    // if Esc key, set window mode
    if  (input->isKeyDown(F1_KEY))    
      setDisplayMode(graphicsNS::WINDOW); // set window mode

    // if Pause key
    if (input->wasKeyPressed(VK_PAUSE))
        paused = !paused;


    // EXIT PROGRAM NOW **************************************************************************************** bucci
    //if (wParam == SPACE_KEY) // the character is in wParam    
    if ( (input->isKeyDown(CTRL_KEY) && input->isKeyDown('q') )  ||  (input->isKeyDown(CTRL_KEY) && input->isKeyDown('Q') )    )
       PostQuitMessage(0);

    // Clear input keys pressed --------------------------------------------------------------------------------------------------------------------------------------
    // Call this after all key checks are done ----------------------------   Call NOTHING BELOW THE CALL TO clear -------------------------------
    input->clear(inputNS::KEYS_PRESSED);
}

//=============================================================================
// Process console commands
// Override this function in the derived class if new console commands are added.
//=============================================================================
void Game::consoleCommand()
{
    command = console->getCommand();    // get command from console
    if(command == "")                   // if no command
        return;

    if (command == "help")              // if "help" command
    {
        console->print("Console Commands:");
        console->print("fps - toggle display of frames per second");
        console->print("gameD -  toggle display of game data off/on");
        console->print("counterD -  toggle display of counters possition and destination");
        return;
    }

    if (command == "fps")
    {
        fpsOn = !fpsOn;                 // toggle display of fps
        if(fpsOn)
            console->print("fps On");
        else
            console->print("fps Off");
    }
    else if (command == "gameD")
    {
          gameDataOn = !gameDataOn;
       if (gameDataOn)
          console->print("game data display is On");
       else
          console->print("game data display is Off");
    }
    else if (command == "counterD")
    {
       counterDataOn = !counterDataOn;
       if (counterDataOn)
          console->print("counter data On");
       else
          console->print("counter data Off");
    }
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Game::releaseAll()
{
    safeOnLostDevice(inputDialog);
    safeOnLostDevice(messageDialog);
    safeOnLostDevice(console);
    dxFont.onLostDevice();
    return;
}

//=============================================================================
// Recreate all surfaces and reset all entities.
//=============================================================================
void Game::resetAll()
{
    dxFont.onResetDevice();
    safeOnResetDevice(console);
    safeOnResetDevice(messageDialog);
    safeOnResetDevice(inputDialog);
    return;
}

//=============================================================================
// Delete all reserved memory
//=============================================================================
void Game::deleteAll()
{
    releaseAll();               // call onLostDevice() for every graphics item
    safeDelete(audio);
    safeDelete(graphics);
    safeDelete(input);
    safeDelete(console);
    safeDelete(messageDialog);
    safeDelete(inputDialog);
    initialized = false;
}