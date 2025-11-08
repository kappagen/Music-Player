#include "Song.h"
#include <iomanip>

using namespace std;

Song::Song() : title(""), artist(""), genre(""), durationSeconds(0), rating(3) {
    lastModifiedTimestamp = chrono::system_clock::now();
}

Song::Song(const string& title, const string& artist, 
           const string& genre, int duration, int rating)
    : title(title), artist(artist), genre(genre), 
      durationSeconds(duration), rating(rating) {
    lastModifiedTimestamp = chrono::system_clock::now();
}

string Song::getTitle() const { return title; }
string Song::getArtist() const { return artist; }
string Song::getGenre() const { return genre; }
int Song::getDuration() const { return durationSeconds; }
int Song::getRating() const { return rating; }
chrono::system_clock::time_point Song::getLastModified() const {
    return lastModifiedTimestamp;
}

void Song::setTitle(const string& t) { 
    title = t; 
    updateTimestamp();
}

void Song::setArtist(const string& a) { 
    artist = a; 
    updateTimestamp();
}

void Song::setGenre(const string& g) { 
    genre = g; 
    updateTimestamp();
}

void Song::setDuration(int d) { 
    durationSeconds = d; 
    updateTimestamp();
}

void Song::setRating(int r) { 
    if (r >= 1 && r <= 5) {
        rating = r;
        updateTimestamp();
    }
}

void Song::updateTimestamp() {
    lastModifiedTimestamp = std::chrono::system_clock::now();
}

string Song::toCSV() const {
    auto timestamp = std::chrono::system_clock::to_time_t(lastModifiedTimestamp);
    std::ostringstream oss;
    oss << title << "," << artist << "," << genre << "," 
        << durationSeconds << "," << rating << "," << timestamp;
    return oss.str();
}

Song Song::fromCSV(const string& csvLine) {
    istringstream iss(csvLine);
    string title, artist, genre;
    int duration, rating;
    long long timestamp;

    getline(iss, title, ',');
    getline(iss, artist, ',');
    getline(iss, genre, ',');
    iss >> duration;
    iss.ignore();
    iss >> rating;
    iss.ignore();
    iss >> timestamp;
    
    Song song(title, artist, genre, duration, rating);
    song.lastModifiedTimestamp = std::chrono::system_clock::from_time_t(timestamp);
    return song;
}

string Song::toString() const {
    ostringstream oss;
    oss << "\"" << title << "\" by " << artist 
        << " [" << genre << "] (" << durationSeconds << "s) Rating: " << rating << "/5";
    return oss.str();
}

bool Song::operator<(const Song& other) const {
    return title < other.title;
}

bool Song::operator>(const Song& other) const {
    return title > other.title;
}

bool Song::operator==(const Song& other) const {
    return title == other.title && artist == other.artist;
}