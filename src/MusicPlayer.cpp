#include "MusicPlayer.h"
#include <iostream>

using namespace std;

MusicPlayer::MusicPlayer() 
    : currentSong(nullptr), isPlaying(false), isPaused(false), currentPosition(0) {}

MusicPlayer::~MusicPlayer() {
    stop();
}

// Simplified non-threaded playback simulation

void MusicPlayer::play(Song* song) {
    if (song == nullptr) return;
    
    // Stop current playback if any
    stop();
    
    currentSong = song;
    currentPosition = 0;
    isPlaying = true;
    isPaused = false;

    cout << "\n♪ Now playing: " << song->toString() << "\n";
}

void MusicPlayer::pause() {
    if (isPlaying && !isPaused) {
        isPaused = true;
        cout << "\n⏸ Paused: " << currentSong->getTitle() 
                  << " at " << currentPosition << "s\n";
    }
}

void MusicPlayer::resume() {
    if (isPlaying && isPaused) {
        isPaused = false;
        cout << "\n▶ Resumed: " << currentSong->getTitle() 
                  << " from " << currentPosition << "s\n";
    }
}

void MusicPlayer::stop() {
    if (isPlaying) {
        isPlaying = false;
        isPaused = false;
        
        if (currentSong) {
            cout << "\n⏹ Stopped: " << currentSong->getTitle() << "\n";
        }
        
        currentSong = nullptr;
        currentPosition = 0;
    }
}

Song* MusicPlayer::getCurrentSong() const {
    return currentSong;
}

bool MusicPlayer::getIsPlaying() const {
    return isPlaying;
}

bool MusicPlayer::getIsPaused() const {
    return isPaused;
}

int MusicPlayer::getCurrentPosition() const {
    return currentPosition;
}