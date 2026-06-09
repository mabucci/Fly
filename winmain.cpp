// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by:
// Charles Kelly
// Game Engine winmain.cpp v1.1

#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "resource.h"
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include "catchTheFly.h"


// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 
bool AnotherInstance();

// Game pointer
CatchTheFly *game = NULL;
HWND hwnd = NULL;

//=============================================================================
// Starting point for a Windows application
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    // Check for memory leak if debug build
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    MSG msg;

    // Mutex to stop multiple copies of game running.  ******************************************************************bucci
    if (AnotherInstance())
    {
      MessageBox(NULL, "A copy of \"To Catch the Fly\" is already running, \nand one Fly is enough!\n\n\t\t\t You FLY out of luck man!", "Error", MB_OK);
      return 1;
    }
   
    // Create the game, sets up message handler
    game = new CatchTheFly;

    // Create the window
    if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
        return 1;

    //  **********************************************************************************bucci 
    //  this grays out the MAXIMIZE window title bar button and removes the resizing ability 
    // this is stop gap till find solution to counter movement
    SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    try{
        game->initialize(hwnd);     // throws GameError

        // main message loop
        int done = 0;
        while (!done)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
            {
                // look for quit message
                if (msg.message == WM_QUIT)
                    done = 1;

                // decode and pass messages on to WinProc
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else
                game->run(hwnd);    // run the game loop
        }
        safeDelete(game);           // free memory before exit
        return msg.wParam;
    }
    catch(const GameError &err)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    }
    catch(...)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, "Unknown error occured in game.\n  You FLY out of luck man!", "Error", MB_OK);
    }

    safeDelete(game);       // free memory before exit
    return 0;
}

//=============================================================================
// window event callback function
//=============================================================================
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return (game->messageHandler(hwnd, msg, wParam, lParam));
}

//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
    wcx.cbSize = sizeof(wcx);           // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
    wcx.lpfnWndProc = WinProc;          // points to window procedure 
    wcx.cbClsExtra = 0;                 // no extra class memory 
    wcx.cbWndExtra = 0;                 // no extra window memory 
    wcx.hInstance = hInstance;          // handle to instance 
  	wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1) );  // to load flyIcon image
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW );   // predefined arrow 
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background 
    wcx.lpszMenuName =  NULL;           // name of menu resource 
    wcx.lpszClassName = CLASS_NAME;     // name of window class 
    wcx.hIconSm = NULL;                 // small class icon 
 
    // Register the window class. 
    // RegisterClassEx returns 0 on error.
    if (RegisterClassEx(&wcx) == 0)    // if error
        return false;

    //set up the screen in windowed or fullscreen mode?
    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW;

    // Create window
    hwnd = CreateWindow(
        CLASS_NAME,             // name of the window class
        GAME_TITLE,             // title bar text
        style,                  // window style					
        WINDOW_H_P,          // const set horizontal position of window
        WINDOW_V_P,          // const set  vertical position of window
        GAME_WIDTH,             // width of window
        GAME_HEIGHT,            // height of the window
        (HWND) NULL,            // no parent window
        (HMENU) NULL,           // no menu
        hInstance,              // handle to application instance
        (LPVOID) NULL);         // no window parameters
	
    // if there was an error creating the window
    if (!hwnd)
        return false;

    if(!FULLSCREEN)             // if window
    {
        // Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);   // get size of client area of window
        MoveWindow(hwnd,
                   WINDOW_H_P,                                           // Left
                   WINDOW_V_P,                                           // Top
                   GAME_WIDTH+(GAME_WIDTH-clientRect.right),    // Right
                   GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), // Bottom
                   TRUE);                                       // Repaint the window
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    return true;
}

//*************************************************************************************
// Mutex to stop multiple copies of game running. 
bool AnotherInstance()
{
  HANDLE ourMutex;
  // Attemp to create a mutex using our unique string
  ourMutex = CreateMutex(NULL, true, "To_Catch_the_Fly_01292017");
  if (GetLastError() == ERROR_ALREADY_EXISTS)
    return true;
  else
  return false;
}


