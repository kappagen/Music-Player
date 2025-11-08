#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include "MusicPlayer.h"
#include "Playlist.h"
#include <vector>

/**
 * PlaybackController manages playlist playback with controls.
 * Thread-safe operations for concurrent playback requests.
 * Supports play, pause, resume, next, previous, and stop commands.
 */
class PlaybackController {
public:
    enum class PlaybackState {
        STOPPED,
        PLAYING,
        PAUSED
    };

private:
    MusicPlayer player;
    Playlist* playlist;
    std::vector<Song> playbackQueue;
    int currentSongIndex;
    PlaybackState state;

public:
    PlaybackController(Playlist* pl);
    
    // Playback controls (all thread-safe)
    void play(); // Play current song or first song
    void pause();
    void resume();
    void next();
    void previous();
    void stop();
    
    // Queue management
    void refreshQueue(); // Update queue from current playlist
    void playFromIndex(int index);
    
    // Status
    PlaybackState getState() const;
    std::string getStateString() const;
    Song* getCurrentSong() const;
    int getCurrentIndex() const;
    
    // Display status
    void displayStatus() const;
};

#endif // PLAYBACKCONTROLLER_H