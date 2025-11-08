#include "Song.h"
#include "Playlist.h"
#include "User.h"
#include "CollaborationManager.h"
#include "MusicLibrary.h"
#include "PlaybackController.h"
#include "ThreadPool.h"
#include "NetworkStub.h"
#include "Utils.h"
#include <iostream>
#include <windows.h>
#include <limits>
using namespace std;


void setTextColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 0	Black	setTextColor(0)
// 1	Blue	setTextColor(1)
// 2	Green	setTextColor(2)
// 3	Aqua / Cyan	
// 4	Red	
// 5	Purple / Magenta	
// 6	Yellow / Brown	
// 7	Light Gray
// 8	Dark Gray	
// 9	Light Blue	
// 10	Light Green	
// 11	Light Cyan	
// 12	Light Red	
// 13	Light Magenta	
// 14	Light Yellow
// 15	White

void clearInputBuffer(){
    int c;
    while ((c=getchar())!='\n' && c!=EOF);
}
void displayMainMenu() {
    setTextColor(10);  
    cout << "\n==============================================\n";
    cout << "#    Collaborative Music Playlist Manager    #\n";
    cout << "==============================================\n";
    setTextColor(7);
    setTextColor(5);    
    cout << "1.  Add Song\n";
    cout << "2.  Remove Song\n";
    cout << "3.  Edit Song\n";
    cout << "4.  Display Playlist\n";
    cout << "5.  Shuffle Playlist\n";
    cout << "6.  Sort Playlist\n";
    cout << "7.  Undo\n";
    cout << "8.  Redo\n";
    cout << "9.  Save Playlist\n";
    cout << "10. Load Playlist\n";
    cout << "11. Playback Controls\n";
    cout << "12. Start Collaborative Session (Demo)\n";
    cout << "13. Exit\n";
    setTextColor(6);    
    cout << "Choice: ";
    setTextColor(7);
}

void displayPlaybackMenu() {
    setTextColor(10); 
    cout << "\n===================================\n";
    cout << "#         Playback Controls       #\n";
    cout << "===================================\n";
    setTextColor(5);
    cout << "1. Play\n";
    cout << "2. Pause\n";
    cout << "3. Resume\n";
    cout << "4. Next\n";
    cout << "5. Previous\n";
    cout << "6. Stop\n";
    cout << "7. Show Status\n";
    cout << "8. Back to Main Menu\n";
    setTextColor(6);
    cout << "Choice: ";
    setTextColor(7);
}

void displaySortMenu() {
    setTextColor(10);
    cout << "\nSort by:\n";
    cout << "1. Title\n";
    cout << "2. Artist\n";
    cout << "3. Rating\n";
    cout << "4. Duration\n";
    setTextColor(6);
    cout << "Choice: ";
    setTextColor(7);
}

void addSongInteractive(CollaborationManager& collabMgr, User& user) {
    setTextColor(9);
    cout << "Enter song title: ";
    setTextColor(8); 
    string title;
    getline(cin, title);

    setTextColor(9); 
    cout << "Enter artist name: ";
    string artist;
    setTextColor(8); 
    getline(cin, artist);

    setTextColor(9); 
    cout << "Enter genre: ";
    string genre;
    setTextColor(8); 
    getline(cin, genre);

    setTextColor(9);
    cout << "Enter duration (in seconds): ";
    int duration;
    setTextColor(8); 
    cin >> duration;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    setTextColor(9); 
    cout << "Enter rating (1-5): ";
    int rating;
    setTextColor(8); // Gray
    cin >> rating;

    if(rating < 1 || rating > 5){
        setTextColor(12); 
        cout << "Rating must be between 1 and 5.\n";
    }
    else if(duration <= 0 ||  duration > 3600){
        setTextColor(12);
        cout << "Enter a valid duration in seconds.\n";
    }
    else{
    setTextColor(6);
    Song song(title, artist, genre, duration, rating);
    collabMgr.collabAddSong(user, song);
    setTextColor(10);
    cout << "Song added successfully.\n";
    setTextColor(7);
    }
}

void removeSongInteractive(CollaborationManager& collabMgr, User& user) {
    setTextColor(9);
    cout << "Enter song title to remove: ";
    string title;
    setTextColor(8);
    getline(cin, title);

    setTextColor(7);

    if (collabMgr.collabRemoveSong(user, title)) {
        setTextColor(10); 
        cout << "Song removed successfully.\n";
        setTextColor(7);
    } else {
        setTextColor(12);
        cout << "Song not found.\n";
        setTextColor(7);
    }
}

void editSongInteractive(CollaborationManager& collabMgr, User& user) {
    setTextColor(9);
    cout << "Enter song title to edit: ";
    string title;
    setTextColor(8);
    getline(cin, title);
    setTextColor(7);
    
    Song* song = collabMgr.getPlaylist()->findSong(title);
    if (!song) {
        setTextColor(12);
        cout << "Song not found.\n";
        setTextColor(7);
        return;
    }

    setTextColor(6);
    cout << "Current details: ";
    setTextColor(2);
    cout << song->toString() << "\n";

    setTextColor(14);
    cout << "Enter new details:\n";

    setTextColor(9); 
    cout << "New title (or press Enter to keep): ";
    setTextColor(8); 
    string newTitle;
    getline(cin, newTitle);

    setTextColor(9);
    cout << "New artist (or press Enter to keep): ";
    setTextColor(8);
    string newArtist;
    getline(cin, newArtist);

    setTextColor(9);
    cout << "New genre (or press Enter to keep): ";
    setTextColor(8);
    string newGenre;
    getline(cin, newGenre);
    setTextColor(7);

    
    Song newSong = *song;
    if (!newTitle.empty()) newSong.setTitle(newTitle);
    if (!newArtist.empty()) newSong.setArtist(newArtist);
    if (!newGenre.empty()) newSong.setGenre(newGenre);
    
    setTextColor(9); 
    cout << "New duration in seconds (or press Enter to keep): ";
    string durationStr;
    setTextColor(8);
    getline(cin, durationStr);
    setTextColor(7);
    if (!durationStr.empty()) {
        newSong.setDuration(stoi(durationStr));
    }

    string ratingStr;
    setTextColor(9);
    cout << "New rating 1-5 (or press Enter to keep): ";
    setTextColor(8);
    getline(cin, ratingStr);
    setTextColor(7);
    if (!ratingStr.empty()) {
        newSong.setRating(stoi(ratingStr));
    }

    setTextColor(7);
    collabMgr.collabEditSong(user, title, newSong);
    setTextColor(10);
    cout << "Song edited successfully.\n";
    setTextColor(7);
}

void sortPlaylistInteractive(CollaborationManager& collabMgr, User& user) {
    displaySortMenu();
    int choice = Utils::getIntInput("", 1, 4);
    
    switch (choice) {
        case 1:
            collabMgr.collabSortByTitle(user);
            setTextColor(10);
            cout << "Sorted by title.\n";
            break;
        case 2:
            collabMgr.collabSortByArtist(user);
            setTextColor(10);
            cout << "Sorted by artist.\n";
            break;
        case 3:
            collabMgr.getPlaylist()->sortByRating();
            setTextColor(10);
            cout << "Sorted by rating.\n";
            break;
        case 4:
            collabMgr.getPlaylist()->sortByDuration();
            setTextColor(10);
            cout << "Sorted by duration.\n";
            break;
    }
}

void playbackControlsMenu(PlaybackController& playback) {
    while (true) {
        displayPlaybackMenu();
        int choice = Utils::getIntInput("", 1, 8);
        
        switch (choice) {
            case 1:
                playback.play();
                break;
            case 2:
                playback.pause();
                break;
            case 3:
                playback.resume();
                break;
            case 4:
                playback.next();
                break;
            case 5:
                playback.previous();
                break;
            case 6:
                playback.stop();
                break;
            case 7:
                setTextColor(9);
                playback.displayStatus();
                setTextColor(7);
                break;
            case 8:
                return;
        }
    }
}

// Simulate collaborative session with multiple users
void simulateCollaboration(CollaborationManager& collabMgr) {
    setTextColor(6);
    cout << "\n=== Starting Collaborative Session Demo ===\n";
    setTextColor(7);
    cout << "Simulating 3 users making concurrent edits...\n\n";

    // Create users
    User alice("Alice", 1);
    User bob("Bob", 2);
    User charlie("Charlie", 3);
    
    collabMgr.addUser(alice);
    collabMgr.addUser(bob);
    collabMgr.addUser(charlie);
    
    // Create thread pool for concurrent operations
    ThreadPool pool(3);
    
    // User Alice adds songs
    pool.enqueue([&]() {
        Song song1("Bohemian Rhapsody", "Queen", "Rock", 354, 5);
        collabMgr.collabAddSong(alice, song1);
    });
    
    pool.enqueue([&]() {
        Song song2("Imagine", "John Lennon", "Pop", 183, 5);
        collabMgr.collabAddSong(alice, song2);
    });
    
    // User Bob adds and edits
    pool.enqueue([&]() {
        Song song3("Stairway to Heaven", "Led Zeppelin", "Rock", 482, 5);
        collabMgr.collabAddSong(bob, song3);
    });
    
    pool.enqueue([&]() {
        Song editedSong("Bohemian Rhapsody", "Queen", "Classic Rock", 354, 5);
        collabMgr.collabEditSong(bob, "Bohemian Rhapsody", editedSong);
    });
    
    // User Charlie adds songs
    pool.enqueue([&]() {
        Song song4("Hotel California", "Eagles", "Rock", 391, 4);
        collabMgr.collabAddSong(charlie, song4);
    });
    
    pool.enqueue([&]() {
        collabMgr.collabSortByTitle(charlie);
    });
    
    // Bob performs undo
    pool.enqueue([&]() {
        collabMgr.collabUndo(bob);
    });
    
    // Alice performs redo
    pool.enqueue([&]() {
        collabMgr.collabRedo(alice);
    });

    pool.enqueue([&]() {
        collabMgr.collabRemoveSong(charlie, "Imagine");
    });
    
    setTextColor(10);
    cout << "\n=== Collaboration Session Complete Successfully ===\n";
    setTextColor(6);
    cout << "Check data/collab_log.txt for detailed log\n";
    setTextColor(7);
    
    collabMgr.displayPlaylist();
}

int main() {
    // Initialize system
    CollaborationManager collabMgr("Shared Playlist");
    MusicLibrary library;
    
    // Create main user
    User mainUser("MainUser", 0);
    collabMgr.addUser(mainUser);
    
    // Initialize playback controller
    PlaybackController playback(collabMgr.getPlaylist());
    
    // Load existing playlist if available
    if (library.fileExists("playlist.txt")) {
        cout << "Found existing playlist. Loading...\n";
        library.loadPlaylist(*collabMgr.getPlaylist(), "playlist.txt");
    }
    
    bool running = true;
    
    while (running) {
        displayMainMenu();
        int choice = Utils::getIntInput("", 1, 13);
        
        switch (choice) {
            case 1:
                addSongInteractive(collabMgr, mainUser);
                break;
                
            case 2:
                removeSongInteractive(collabMgr, mainUser);
                break;
                
            case 3:
                editSongInteractive(collabMgr, mainUser);
                break;
                
            case 4:
                setTextColor(11); // Light Cyan
                collabMgr.displayPlaylist();
                setTextColor(7); // Reset to default color
                break;
                
            case 5:
                collabMgr.collabShuffle(mainUser);
                break;
                
            case 6:
                sortPlaylistInteractive(collabMgr, mainUser);
                break;
                
            case 7:
                if (collabMgr.collabUndo(mainUser)) {
                    cout << "Undo successful.\n";
                } else {
                    cout << "Nothing to undo.\n";
                }
                break;
                
            case 8:
                if (collabMgr.collabRedo(mainUser)) {
                    cout << "Redo successful.\n";
                } else {
                    cout << "Nothing to redo.\n";
                }
                break;
                
            case 9:
                library.savePlaylist(*collabMgr.getPlaylist(), "playlist.txt");
                break;
                
            case 10:
                setTextColor(1);
                library.loadPlaylist(*collabMgr.getPlaylist(), "playlist.txt");
                setTextColor(7);
                break;
                
            case 11:
                playback.refreshQueue();
                playbackControlsMenu(playback);
                break;
                
            case 12:
                simulateCollaboration(collabMgr);
                playback.refreshQueue(); // Refresh after collaboration
                break;
                
            case 13:
                setTextColor(1);
                cout << "Saving and exiting...\n";
                library.savePlaylist(*collabMgr.getPlaylist(), "playlist.txt");
                setTextColor(7);
                playback.stop();
                running = false;
                break;
        }
    }
    setTextColor(10);
    cout << "Goodbye!\n";
    setTextColor(7);
    return 0;
}