#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "Playlist.h"
#include <string>

/**
 * MusicLibrary handles file I/O for playlist persistence.
 * Saves and loads playlists in CSV format with error handling for malformed data.
 */
class MusicLibrary {
private:
    std::string dataDirectory;

public:
    MusicLibrary(const std::string& dataDir = "data/");
    
    /**
     * Save playlist to CSV file
     * Returns true on success, false on failure
     */
    bool savePlaylist(const Playlist& playlist, const std::string& filename);
    
    /**
     * Load playlist from CSV file
     * Returns true on success, false on failure
     * Gracefully handles malformed lines
     */
    bool loadPlaylist(Playlist& playlist, const std::string& filename);
    
    /**
     * Check if file exists
     */
    bool fileExists(const std::string& filename) const;
};

#endif // MUSICLIBRARY_H