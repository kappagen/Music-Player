#include "PlaybackController.h"
#include <iostream>
#include <windows.h>

using namespace std;

void setTextColor1(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
PlaybackController::PlaybackController(Playlist* pl) 
    : playlist(pl), currentSongIndex(-1), state(PlaybackState::STOPPED) {
    refreshQueue();
}

void PlaybackController::refreshQueue() {
    playbackQueue = playlist->getAllSongs();
    if (currentSongIndex >= (int)playbackQueue.size()) {
        currentSongIndex = -1;
    }
}

void PlaybackController::play() {
    
    refreshQueue();
    
    if (playbackQueue.empty()) {
        setTextColor1(12);
        cout << "Playlist is empty. Cannot play.\n";
        setTextColor1(7);
        return;
    }
    
    // If stopped, start from beginning or current index
    if (state == PlaybackState::STOPPED) {
        if (currentSongIndex < 0 || currentSongIndex >= (int)playbackQueue.size()) {
            currentSongIndex = 0;
        }
        player.play(&playbackQueue[currentSongIndex]);
        state = PlaybackState::PLAYING;
    } else if (state == PlaybackState::PAUSED) {
        player.resume();
        state = PlaybackState::PLAYING;
    }
}

void PlaybackController::pause() {
    
    if (state == PlaybackState::PLAYING) {
        player.pause();
        state = PlaybackState::PAUSED;
    }
}

void PlaybackController::resume() {
    
    if (state == PlaybackState::PAUSED) {
        player.resume();
        state = PlaybackState::PLAYING;
    }
}

void PlaybackController::next() {
    
    refreshQueue();
    
    if (playbackQueue.empty()) {
        setTextColor1(12);
        cout << "Playlist is empty.\n";
        setTextColor1(7);
        return;
    }
    
    currentSongIndex++;
    if (currentSongIndex >= (int)playbackQueue.size()) {
        currentSongIndex = 0; // Loop to beginning
    }
    
    player.stop();
    player.play(&playbackQueue[currentSongIndex]);
    state = PlaybackState::PLAYING;

    setTextColor1(9);
    cout << " Skipped to next song\n";
    setTextColor1(7);
}

void PlaybackController::previous() {
    
    refreshQueue();
    
    if (playbackQueue.empty()) {
        setTextColor1(12);
        cout << "Playlist is empty.\n";
        setTextColor1(7);
        return;
    }
    
    currentSongIndex--;
    if (currentSongIndex < 0) {
        currentSongIndex = playbackQueue.size() - 1; // Loop to end
    }
    
    player.stop();
    player.play(&playbackQueue[currentSongIndex]);
    state = PlaybackState::PLAYING;

    setTextColor1(9);
    cout << "Skipped to previous song\n";
    setTextColor1(7);
}

void PlaybackController::stop() {
    
    player.stop();
    state = PlaybackState::STOPPED;
    currentSongIndex = -1;
}

void PlaybackController::playFromIndex(int index) {
    
    refreshQueue();
    
    if (index < 0 || index >= (int)playbackQueue.size()) {
        setTextColor1(12);
        cout << "Invalid song index.\n";
        setTextColor1(7);
        return;
    }
    
    currentSongIndex = index;
    player.stop();
    player.play(&playbackQueue[currentSongIndex]);
    state = PlaybackState::PLAYING;
}

PlaybackController::PlaybackState PlaybackController::getState() const {
    return state;
}

std::string PlaybackController::getStateString() const {
    switch (state) {
        case PlaybackState::PLAYING: return "PLAYING";
        case PlaybackState::PAUSED: return "PAUSED";
        case PlaybackState::STOPPED: return "STOPPED";
        default: return "UNKNOWN";
    }
}

Song* PlaybackController::getCurrentSong() const {
    if (currentSongIndex >= 0 && currentSongIndex < (int)playbackQueue.size()) {
        return player.getCurrentSong();
    }
    return nullptr;
}

int PlaybackController::getCurrentIndex() const {
    return currentSongIndex;
}

void PlaybackController::displayStatus() const {
    cout << "\n=== Playback Status ===\n";
    cout << "State: " << getStateString() << "\n";
    
    if (getCurrentSong()) {
        cout << "Current Song [" << (currentSongIndex + 1) << "/" 
             << playbackQueue.size() << "]: " 
                  << getCurrentSong()->toString() << "\n";
        cout << "Position: " << player.getCurrentPosition() 
             << "s / " << getCurrentSong()->getDuration() << "s\n";
    } else {
        cout << "No song currently playing\n";
    }

    cout << "Queue Size: " << playbackQueue.size() << " songs\n";
    cout << "======================\n";
}