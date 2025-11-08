#include "CollaborationManager.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

CollaborationManager::CollaborationManager(const string& playlistName, const string& logPath) : logFilePath(logPath) {
    sharedPlaylist = new Playlist(playlistName);
    
    // Create/clear log file
    ofstream logFile(logFilePath, ios::trunc);
    if (logFile.is_open()) {
        logFile << "=== Collaboration Log Started ===\n";
        logFile.close();
    }
}

CollaborationManager::~CollaborationManager() {
    delete sharedPlaylist;
}

void CollaborationManager::addUser(const User& user) {
    activeUsers.push_back(user);
    logOperation(user, "JOIN", "User joined collaboration session");
}

vector<User> CollaborationManager::getActiveUsers() const {
    return activeUsers;
}

string CollaborationManager::getTimestamp() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    ostringstream oss;
    oss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void CollaborationManager::logOperation(const User& user, const string& operation,
                                       const string& details) {

    ofstream logFile(logFilePath, ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] " 
                << user.getUsername() << " - " 
                << operation << ": " << details << "\n";
        logFile.close();
    }
}

void CollaborationManager::collabAddSong(const User& user, const Song& song) {
    
    // Save state before modification for undo
    globalHistory.saveState(*sharedPlaylist);
    
    sharedPlaylist->addSong(song);
    logOperation(user, "ADD", song.toString());
    
    cout << "[" << user.getUsername() << "] Added: " << song.toString() << "\n";
}

bool CollaborationManager::collabRemoveSong(const User& user, const string& title) {

    Song* song = sharedPlaylist->findSong(title);
    if (!song) {
        logOperation(user, "REMOVE_FAILED", "Song not found: " + title);
        return false;
    }
    
    // Save state before modification
    globalHistory.saveState(*sharedPlaylist);

    string songInfo = song->toString();
    bool success = sharedPlaylist->removeSong(title);
    
    if (success) {
        logOperation(user, "REMOVE", songInfo);
        cout << "[" << user.getUsername() << "] Removed: " << songInfo << "\n";
    }
    
    return success;
}

bool CollaborationManager::collabEditSong(const User& user, const string& title,
                                         const Song& newData) {
    
    Song* song = sharedPlaylist->findSong(title);
    if (!song) {
        logOperation(user, "EDIT_FAILED", "Song not found: " + title);
        return false;
    }
    
    // Check timestamp for conflict resolution (first-writer-wins)
    // If multiple edits happen, the one with earlier timestamp when acquired lock wins
    
    // Save state before modification
    globalHistory.saveState(*sharedPlaylist);

    string oldInfo = song->toString();
    bool success = sharedPlaylist->editSong(title, newData);
    
    if (success) {
        string editDetails = "Changed from: " + oldInfo + " to: " + newData.toString();
        logOperation(user, "EDIT", editDetails);
        cout << "[" << user.getUsername() << "] Edited: " << title << "\n";
    }
    
    return success;
}

void CollaborationManager::collabSortByTitle(const User& user) {
    
    globalHistory.saveState(*sharedPlaylist);
    sharedPlaylist->sortByTitle();
    
    logOperation(user, "SORT", "Sorted playlist by title");
    cout << "[" << user.getUsername() << "] Sorted playlist by title\n";
}

void CollaborationManager::collabSortByArtist(const User& user) {
    
    globalHistory.saveState(*sharedPlaylist);
    sharedPlaylist->sortByArtist();
    
    logOperation(user, "SORT", "Sorted playlist by artist");
    cout << "[" << user.getUsername() << "] Sorted playlist by artist\n";
}

void CollaborationManager::collabShuffle(const User& user) {
    
    globalHistory.saveState(*sharedPlaylist);
    sharedPlaylist->shuffle();
    
    logOperation(user, "SHUFFLE", "Shuffled playlist");
    cout << "[" << user.getUsername() << "] Shuffled playlist\n";
}

bool CollaborationManager::collabUndo(const User& user) {
    
    if (!globalHistory.canUndo()) {
        cout << "[" << user.getUsername() << "] Nothing to undo\n";
        return false;
    }
    
    Playlist* previousState = globalHistory.undo();
    if (previousState) {
        sharedPlaylist->copyFrom(*previousState);
        delete previousState;
        
        logOperation(user, "UNDO", "Reverted to previous state");
        cout << "[" << user.getUsername() << "] Undo successful\n";
        return true;
    }
    
    return false;
}

bool CollaborationManager::collabRedo(const User& user) {
    
    if (!globalHistory.canRedo()) {
        cout << "[" << user.getUsername() << "] Nothing to redo\n";
        return false;
    }
    
    Playlist* nextState = globalHistory.redo();
    if (nextState) {
        sharedPlaylist->copyFrom(*nextState);
        delete nextState;
        
        logOperation(user, "REDO", "Restored next state");
        cout << "[" << user.getUsername() << "] Redo successful\n";
        return true;
    }
    
    return false;
}

void CollaborationManager::displayPlaylist() const {
    sharedPlaylist->display();
}

Playlist* CollaborationManager::getPlaylist() {
    return sharedPlaylist;
}

void CollaborationManager::clearLog() {
    ofstream logFile(logFilePath, ios::trunc);
    if (logFile.is_open()) {
        logFile << "=== Collaboration Log Cleared ===\n";
        logFile.close();
    }
}