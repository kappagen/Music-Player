#include "Playlist.h"
#include "SortingAlgorithms.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

Playlist::Playlist(const std::string& name) : head(nullptr), size(0), name(name) {}

Playlist::~Playlist() {
    clear();
}

void Playlist::addSong(const Song& song) {
    Node* newNode = new Node(song);
    
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

bool Playlist::removeSong(const std::string& title) {
    if (!head) return false;
    
    // Special case: removing head
    if (head->data.getTitle() == title) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    // Search for node to remove
    Node* current = head;
    while (current->next) {
        if (current->next->data.getTitle() == title) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }
    
    return false;
}

bool Playlist::editSong(const std::string& title, const Song& newSongData) {
    Node* current = head;
    while (current) {
        if (current->data.getTitle() == title) {
            current->data = newSongData;
            current->data.updateTimestamp();
            return true;
        }
        current = current->next;
    }
    return false;
}

Song* Playlist::findSong(const std::string& title) {
    Node* current = head;
    while (current) {
        if (current->data.getTitle() == title) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

void Playlist::display() const {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }
    
    cout << "\n=== " << name << " (" << size << " songs) ===\n";
    
    // Print table header
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" 
         << string(22, '-') << "+" << string(17, '-') << "+" 
         << string(10, '-') << "+" << string(10, '-') << "+" << endl;
    
    cout << "| " << left << setw(3) << "No" << " | " 
         << setw(30) << "Title" << " | " 
         << setw(20) << "Artist" << " | " 
         << setw(15) << "Genre" << " | " 
         << setw(8) << "Duration" << " | " 
         << setw(8) << "Rating" << " |" << endl;
    
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" 
         << string(22, '-') << "+" << string(17, '-') << "+" 
         << string(10, '-') << "+" << string(10, '-') << "+" << endl;
    
    Node* current = head;
    int index = 1;
    while (current) {
        string title = current->data.getTitle();
        string artist = current->data.getArtist();
        string genre = current->data.getGenre();
        
        // Truncate if too long
        if (title.length() > 30) title = title.substr(0, 27) + "...";
        if (artist.length() > 20) artist = artist.substr(0, 17) + "...";
        if (genre.length() > 15) genre = genre.substr(0, 12) + "...";
        
        cout << "| " << right << setw(3) << index++ << " | " 
             << left << setw(30) << title << " | " 
             << setw(20) << artist << " | " 
             << setw(15) << genre << " | " 
             << setw(6) << current->data.getDuration() << "s" << " | " 
             << setw(4) << current->data.getRating() << "/5" << "  |" << endl;
        
        current = current->next;
    }
    
    cout << "+" << string(5, '-') << "+" << string(32, '-') << "+" 
         << string(22, '-') << "+" << string(17, '-') << "+" 
         << string(10, '-') << "+" << string(10, '-') << "+" << endl;
    cout << "Total songs: " << size << endl << endl;
}

std::vector<Song> Playlist::getAllSongs() const {
    std::vector<Song> songs;
    Node* current = head;
    while (current) {
        songs.push_back(current->data);
        current = current->next;
    }
    return songs;
}

void Playlist::shuffle() {
    if (size <= 1) return;
    
    // Convert to vector for easier shuffling
    std::vector<Song> songs = getAllSongs();
    
    // Shuffle using random device
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(songs.begin(), songs.end(), gen);
    
    // Rebuild linked list
    clear();
    for (const auto& song : songs) {
        addSong(song);
    }
}

void Playlist::sortByTitle() {
    if (!head) return;
    
    // Convert to SortingAlgorithms Node format
    SortingAlgorithms::Node* sortHead = nullptr;
    SortingAlgorithms::Node* sortTail = nullptr;
    
    Node* current = head;
    while (current) {
        SortingAlgorithms::Node* newNode = new SortingAlgorithms::Node(current->data);
        if (!sortHead) {
            sortHead = sortTail = newNode;
        } else {
            sortTail->next = newNode;
            sortTail = newNode;
        }
        current = current->next;
    }
    
    // Sort
    sortHead = SortingAlgorithms::bubbleSortByTitle(sortHead);
    
    // Convert back
    clear();
    while (sortHead) {
        addSong(sortHead->data);
        SortingAlgorithms::Node* temp = sortHead;
        sortHead = sortHead->next;
        delete temp;
    }
}

void Playlist::sortByArtist() {
    if (!head) return;
    
    SortingAlgorithms::Node* sortHead = nullptr;
    SortingAlgorithms::Node* sortTail = nullptr;
    
    Node* current = head;
    while (current) {
        SortingAlgorithms::Node* newNode = new SortingAlgorithms::Node(current->data);
        if (!sortHead) {
            sortHead = sortTail = newNode;
        } else {
            sortTail->next = newNode;
            sortTail = newNode;
        }
        current = current->next;
    }
    
    sortHead = SortingAlgorithms::bubbleSortByArtist(sortHead);
    
    clear();
    while (sortHead) {
        addSong(sortHead->data);
        SortingAlgorithms::Node* temp = sortHead;
        sortHead = sortHead->next;
        delete temp;
    }
}

void Playlist::sortByRating() {
    if (!head) return;
    
    SortingAlgorithms::Node* sortHead = nullptr;
    SortingAlgorithms::Node* sortTail = nullptr;
    
    Node* current = head;
    while (current) {
        SortingAlgorithms::Node* newNode = new SortingAlgorithms::Node(current->data);
        if (!sortHead) {
            sortHead = sortTail = newNode;
        } else {
            sortTail->next = newNode;
            sortTail = newNode;
        }
        current = current->next;
    }
    
    sortHead = SortingAlgorithms::bubbleSortByRating(sortHead);
    
    clear();
    while (sortHead) {
        addSong(sortHead->data);
        SortingAlgorithms::Node* temp = sortHead;
        sortHead = sortHead->next;
        delete temp;
    }
}

void Playlist::sortByDuration() {
    if (!head) return;
    
    SortingAlgorithms::Node* sortHead = nullptr;
    SortingAlgorithms::Node* sortTail = nullptr;
    
    Node* current = head;
    while (current) {
        SortingAlgorithms::Node* newNode = new SortingAlgorithms::Node(current->data);
        if (!sortHead) {
            sortHead = sortTail = newNode;
        } else {
            sortTail->next = newNode;
            sortTail = newNode;
        }
        current = current->next;
    }
    
    sortHead = SortingAlgorithms::bubbleSortByDuration(sortHead);
    
    clear();
    while (sortHead) {
        addSong(sortHead->data);
        SortingAlgorithms::Node* temp = sortHead;
        sortHead = sortHead->next;
        delete temp;
    }
}

int Playlist::getSize() const {
    return size;
}

std::string Playlist::getName() const {
    return name;
}

void Playlist::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

Playlist* Playlist::clone() const {
    Playlist* newPlaylist = new Playlist(this->name);
    Node* current = head;
    while (current) {
        newPlaylist->addSong(current->data);
        current = current->next;
    }
    return newPlaylist;
}

void Playlist::copyFrom(const Playlist& other) {
    clear();
    this->name = other.name;
    Node* current = other.head;
    while (current) {
        addSong(current->data);
        current = current->next;
    }
}