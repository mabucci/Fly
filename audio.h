// To Catch the Fly
// Is wholly bast on Charles Kelly work in Programming 2D Games
// It is his concept, design, and implementation, I am just monkey with it
// m a bucci 2016 to God knows. . .
// Copyright (c) 02 / 17 / 2016 by  Michael Bucci

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// audio.h v1.2

#ifndef _AUDIO_H                // Prevent multiple definitions if this 
#define _AUDIO_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Audio;

#include <xact3.h>
#include "constants.h"

class Audio
{
    // properties
  private:
    IXACT3Engine *xactEngine;   // pointer to XACT sound engine
    IXACT3WaveBank *waveBank;   // pointer to XACT wave bank
    IXACT3SoundBank *soundBank; // pointer to XACT sound bank
    IXACT3Wave *ppWave;         // pointer to XACT wave object
    XACTINDEX cueI;             // XACT sound index
    void *mapWaveBank;          // call UnmapViewOfFile() to release file
    void *soundBankData;
    bool coInitialized;         // set true if coInitialize is successful
    bool PLAY_BUZZ;     // audio for splash screen 
    bool PLAY_SLAP;     // audio for splash screen

  public:
    // Constructor
    Audio();

    // Destructor
    virtual ~Audio();

    // member functions

    // Initialize Audio
    HRESULT initialize();

    // Perform periodic sound engine tasks.
    void run();

    // Play sound specified by cue from sound bank.
    // If cue does not exist no error occurs, there is simply no sound played.
    void playCue(const char cue[]);

    // Stop a playing sound specified by cue from sound bank.
    // If cue does not exist no error occurs.
    void stopCue(const char cue[]);

    // Pause sound specified by category from sound bank.
    // If category does not exist no error occurs.
    void pauseCategory(const char category[]);

    // Resume playback of paused sound specified by category from sound bank.
    // If category does not exist no error occurs.
    void resumeCategory(const char category[]);

    // to stop buzz from being constantly started in catchTheFly update *********************************************
    bool getBuzz(){ return PLAY_BUZZ; }
    void setBuzz(bool b){ PLAY_BUZZ = b; }

    // to stop slap from being constantly started in catchTheFly update *********************************************
    bool getSlap() { return PLAY_SLAP; }
    void setSlap(bool b) { PLAY_SLAP = b; }
};

#endif
