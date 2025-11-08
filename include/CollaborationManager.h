#ifndef COLLABORATIONMANAGER_H
#define COLLABORATIONMANAGER_H

#include "Playlist.h"
#include "User.h"
#include "HistoryManager.h"
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
/**
 * CollaborationManager handles multi-user concurrent editing of a shared playlist.
 * Thread-safe operations with first-writer-wins conflict resolution.
 * All operations are logged to collab_log.txt with timestamps.
 */

class CollaborationManager {
private:
    Playlist* sharedPlaylist;
    HistoryManager globalHistory;
    string logFilePath;
    vector<User> activeUsers;

    // Helper to log operations
    void logOperation(const User& user, const string& operation, 
                     const string& details);
    
    // Get timestamp string for logging
    string getTimestamp() const;

public:
    CollaborationManager(const string& playlistName, 
                        const string& logPath = "data/collab_log.txt");
    ~CollaborationManager();
    
    // User management
    void addUser(const User& user);
    vector<User> getActiveUsers() const;
    
    // Thread-safe collaborative operations
    // All operations use first-writer-wins based on timestamps
    void collabAddSong(const User& user, const Song& song);
    bool collabRemoveSong(const User& user, const string& title);
    bool collabEditSong(const User& user, const string& title, const Song& newData);

    // Thread-safe sorting and shuffling
    void collabSortByTitle(const User& user);
    void collabSortByArtist(const User& user);
    void collabShuffle(const User& user);
    
    // Global undo/redo across all users
    bool collabUndo(const User& user);
    bool collabRedo(const User& user);
    
    // Display (thread-safe read)
    void displayPlaylist() const;
    Playlist* getPlaylist();
    
    // Clear log file
    void clearLog();
};

#endif // COLLABORATIONMANAGER_H