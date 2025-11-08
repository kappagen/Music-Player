#ifndef SONG_H
#define SONG_H

#include <string>
#include <chrono>
#include <sstream>

/**
 * Song class represents an individual music track with metadata
 * including title, artist, genre, duration, rating, and modification timestamp.
 */
class Song {
private:
    std::string title;
    std::string artist;
    std::string genre;
    int durationSeconds;
    int rating; // 1-5
    std::chrono::system_clock::time_point lastModifiedTimestamp;

public:
    // Constructors
    Song();
    Song(const std::string& title, const std::string& artist, 
         const std::string& genre, int duration, int rating);
    
    // Getters
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getGenre() const;
    int getDuration() const;
    int getRating() const;
    std::chrono::system_clock::time_point getLastModified() const;
    
    // Setters
    void setTitle(const std::string& title);
    void setArtist(const std::string& artist);
    void setGenre(const std::string& genre);
    void setDuration(int duration);
    void setRating(int rating);
    void updateTimestamp();
    
    // CSV serialization
    std::string toCSV() const;
    static Song fromCSV(const std::string& csvLine);
    
    // Display
    std::string toString() const;
    
    // Comparison operators for sorting
    bool operator<(const Song& other) const; // Compare by title
    bool operator>(const Song& other) const;
    bool operator==(const Song& other) const;
};

#endif // SONG_H