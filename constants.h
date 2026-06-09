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

#pragma once
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>


//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "catchTheFly";
const char GAME_TITLE[] = "To Catch the Fly 0.1 Tile Back Ground";
const bool FULLSCREEN =  false;              // windowed or fullscreen
//const UINT GAME_WIDTH =  640;               // width of game in pixels
//const UINT GAME_HEIGHT = 480;               // height of game in pixels
const UINT GAME_WIDTH =  1280;               // width of game in pixels
const UINT GAME_HEIGHT =  720;               // height of game in pixels


// NVIDIAN RESOLUTIONS @ 60 Hz
// 1680x1050  1600x1024  1600x900  1440x900  1366x900  1360x768  1280x1024  1280x960  1280x800  1280x768  1280x720  1152x864  1024x768
// Windows 800x600 but we can run down to 640x480. 
const int WINDOW_H_P = 50;				//horizontal position of window
const int WINDOW_V_P = 5;             // default vertical position of window
const float START_SCALE = 1.0f;          // starting game scale used in CatchTheFly constructor, and CatchTheFly::zoomMap as scale reset value.
const float MIN_SCALE = 0.4f;             // minimum scale for game
const float MAX_SCALE = 2.0f;            // maximum scale for game
const float ONE_TO_ONE_SCALE = 1.0f; // 1 : 1 scale for game

// game
const float COUNTER_SPEED = 0.1f; // speed that counters move at
const int   COUNTER_WIDTH = 37;
const int   COUNTER_HEIGHT = 32;
const bool VSYNC = false;                   // true locks display to vertical sync rate
const float FRAME_RATE = 240.0f;            // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float MAP_SCROLL_RATE = 60.0f; // rate of map scroll in catchTheFly::navation();
const float MAP_ZOOM_RATE = 0.1f;  // rate of zoom in/out of background (map)
const double PI = 3.14159265;
const float FLY_OFF_SET = 0.0f;  // off set for fly sprite in hexagon
const int  FLY_START_FRAME = 3;            // starting frame of fly animation
const int  FLY_END_FRAME = 3;              // last frame of fly animation
const float FLY_ANIMATION_DELAY = 0.0f;    // time between frames of fly animation
const int  FLY_COLS = 4;                   // fly texture has 1 columns
const int  FLY_WIDTH = 37;                 // width of fly image
const int  FLY_HEIGHT = 32;                // height of fly image
const float NATIVE_OFF_SET = 0.0f;  // off set for native sprite in hexagon
const int  NATIVE_START_FRAME = 15;            // starting frame of native animation
const int  NATIVE_END_FRAME = 15;              // last frame of native animation
const float NATIVE_ANIMATION_DELAY = 0.0f;    // time between frames of native animation
const int  NATIVE_COLS = 10 ;                   // native  N1 texture is in 10 column wide composit  pick file 
const int  NATIVE_WIDTH = 37;                 // width of fly image
const int  NATIVE_HEIGHT = 32;                // height of fly image
const UINT  TILE_MAP_WIDTH = 40;           // width of tile map in tiles
const UINT  TILE_MAP_HEIGHT = 30;           // height of tile map in tiles
const    int NUMBER_OF_TYPES = 8;          // types of game counters
const    int NUMBER_OF_NAMES = 14;       //  names of game counters 
const std::string counterNames[14] = { "Fly", "S1", "S2", "S3", "C1", "C2", "C3", "A1", "Boat Large", "Boat Small", "Skill Boanian", "Highlighter", "Red Ball", "Green Ball" };
enum _eGAME_COUNTER {_eFLY, _eS1, _eS2, _eS3, _eC1, _eC2, _eC3, _eA1, _eBL, _eBS, _eSBOAN, _eHL, _eRB, _eGB };    // used to id a particular game counter and get ride of the hard values in many 'if' statements
// graphic images
const char MENU_IMAGE[] =     "pictures\\Splash2.png";      // menu texture
const char SPLASH1_IMAGE[] = "pictures\\Splash2.png";      // splash1 texture
const char FLY_IMAGE[] = "pictures\\hexText1EXP.png";                   // fly texture
const char NATIVE_IMAGE[] = "pictures\\hexText1EXP.png";                   // native texture
const char COUNTER_IMAGE[] = "pictures\\hexText1EXP.png";  // textures of all game counters 
const char TILE_TEXTURES[] = "pictures\\hexText1EXP.png";         // tiles

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";
// XGS_FILE must be location of .xgs file.
const char XGS_FILE[]   = "audio\\Win\\CatchTheFly.xgs";
// Fly Buzz
const char FLY_BUZZ[] = "Buzz";
// Slap the Fly
const char SLAP[] = "Slap";


// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR F1_KEY = VK_F1;   // F1 key will now togle full screen to window. 
const UCHAR SPACE_KEY = VK_SPACE; // SPACE_KEY.
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR CTRL_KEY = VK_CONTROL; // CTRL key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR LEFT_ARROW = VK_LEFT; // left arrow key  0x25
const UCHAR UP_ARROW = VK_UP; // up arrow key   0x26
const UCHAR RIGHT_ARROW = VK_RIGHT; // right arrow  0x27
const UCHAR DOWN_ARROW = VK_DOWN; // down arrow  0x28
const UCHAR PLUS_KEY = VK_OEM_PLUS; //  the '+'   key 0xBB   // '+' any country
const UCHAR MINUS_KEY = VK_OEM_MINUS; // the '-' key  0xBD   // '-' any country
const UCHAR PLUS_KEY_NUMPAD = VK_ADD; // the '+' key on the number pad 0x6B
const UCHAR MINUS_KEY_NUMPAD = VK_SUBTRACT; // the '-' key on the number pad 0x6D
const UCHAR SHIFT_KEY = VK_SHIFT; // the 'SHIFT' keys    there is VK_LSHIFT  and VK_RSHIFT 
const UCHAR TAB_KEY = VK_TAB;   // the TAB key will be used in CTFSwapGCounters along with the 'Highlighter' to rotate game counters that are on the same hexagon  so 1,2,3 will 'swap' to 2,3,1 then 3,1,2 so player can see all game counters that are on a particular hexagon think FCII


//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
