#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <string>
#include <vector>

/**
 * Playlist class manages a singly linked list of songs.
 * Provides operations for adding, removing, editing, shuffling, and sorting songs.
 * Memory management is handled through destructor to prevent leaks.
 */
class Playlist {
private:
    struct Node {
        Song data;
        Node* next;
        Node(const Song& s) : data(s), next(nullptr) {}
    };
    
    Node* head;
    int size;
    std::string name;

public:
    Playlist(const std::string& name = "My Playlist");
    ~Playlist();
    
    // Basic operations - O(n) or O(1) depending on operation
    void addSong(const Song& song); // O(n) - adds to end
    bool removeSong(const std::string& title); // O(n)
    bool editSong(const std::string& title, const Song& newSongData); // O(n)
    Song* findSong(const std::string& title); // O(n)
    
    // Display
    void display() const;
    std::vector<Song> getAllSongs() const;
    
    // Shuffle - O(n)
    void shuffle();
    
    // Sorting - O(n^2) bubble sort
    void sortByTitle();
    void sortByArtist();
    void sortByRating();
    void sortByDuration();
    
    // Utilities
    int getSize() const;
    std::string getName() const;
    void clear();
    
    // Deep copy for undo/redo
    Playlist* clone() const;
    void copyFrom(const Playlist& other);
};

#endif // PLAYLIST_H