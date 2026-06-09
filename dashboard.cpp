// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// dashboard.cpp v1.0

#include "dashboard.h"

//=============================================================================
// Initialize the Bar 
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      color = color of bar
// Post: returns true on success, false on error
//=============================================================================
bool Bar::initialize(Graphics *graphics, TextureManager *textureM, int left,
                     int top, float scale, COLOR_ARGB color)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::BAR_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = color;
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// set the Bar size
//=============================================================================
void Bar::set(float p)
{
    if (p < 0)
        p = 0;
    else if(p > 100)
        p = 100;
    spriteData.rect.right = spriteData.rect.left + (LONG)(spriteData.width*p/100);
}

