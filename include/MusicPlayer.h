#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "Song.h"

/**
 * MusicPlayer simulates song playback with timing controls.
 * Tracks playback progress and supports pause/resume functionality.
 */
class MusicPlayer {
private:
    Song* currentSong;
    bool isPlaying;
    bool isPaused;
    int currentPosition; // Current playback position in seconds

public:
    MusicPlayer();
    ~MusicPlayer();
    
    // Start playing a song
    void play(Song* song);
    
    // Pause current playback
    void pause();
    
    // Resume paused playback
    void resume();
    
    // Stop playback completely
    void stop();
    
    // Get current song
    Song* getCurrentSong() const;
    
    // Get playback status
    bool getIsPlaying() const;
    bool getIsPaused() const;
    int getCurrentPosition() const;
};

#endif // MUSICPLAYER_H