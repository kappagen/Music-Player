#include "MusicLibrary.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;

MusicLibrary::MusicLibrary(const string& dataDir) : dataDirectory(dataDir) {}

bool MusicLibrary::savePlaylist(const Playlist& playlist, const string& filename) {
    string filepath = dataDirectory + filename;
    ofstream file(filepath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filepath << "\n";
        return false;
    }
    
    // Write CSV header
    file << "Title,Artist,Genre,Duration,Rating,Timestamp\n";
    
    // Write each song
    vector<Song> songs = playlist.getAllSongs();
    for (const auto& song : songs) {
        file << song.toCSV() << "\n";
    }
    
    file.close();
    cout << "Playlist saved to " << filepath << "\n";
    return true;
}

bool MusicLibrary::loadPlaylist(Playlist& playlist, const string& filename) {
    string filepath = dataDirectory + filename;
    ifstream file(filepath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file for reading: " << filepath << "\n";
        return false;
    }
    
    playlist.clear();

    string line;
    bool firstLine = true;
    int lineNumber = 0;
    int loadedSongs = 0;

    while (getline(file, line)) {
        lineNumber++;
        
        // Skip header line
        if (firstLine) {
            firstLine = false;
            continue;
        }
        
        // Skip empty lines
        if (line.empty()) continue;
        
        try {
            Song song = Song::fromCSV(line);
            playlist.addSong(song);
            loadedSongs++;
        } catch (const exception& e) {
            cerr << "Warning: Skipping malformed line " << lineNumber 
                 << " in " << filepath << "\n";
            // Continue loading other songs
        }
    }
    
    file.close();
    cout << "Loaded " << loadedSongs << " songs from " << filepath << "\n";
    return true;
}

bool MusicLibrary::fileExists(const string& filename) const {
    string filepath = dataDirectory + filename;
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}