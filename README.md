# Collaborative Music Playlist Manager

A C++ application for managing music playlists with collaborative features, sorting, playback controls, and undo/redo functionality.

## Features

- ✅ Add, remove, and edit songs
- ✅ Sort playlists by title, artist, rating, or duration
- ✅ Shuffle playlists
- ✅ Undo/Redo operations
- ✅ Save and load playlists
- ✅ Collaborative session simulation
- ✅ Playback controls (play, pause, resume, next, previous, stop)
- ✅ Persistent storage

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -I./include src/*.cpp -o playlist_manager.exe
```

## Running the Program

```bash
.\playlist_manager.exe
```

## Menu Options

1. **Add Song** - Add a new song to the playlist
2. **Remove Song** - Remove a song by title
3. **Edit Song** - Modify song details
4. **Display Playlist** - Show all songs in the playlist
5. **Shuffle Playlist** - Randomize song order
6. **Sort Playlist** - Sort by title, artist, rating, or duration
7. **Undo** - Revert last operation
8. **Redo** - Restore undone operation
9. **Save Playlist** - Save to file (data/playlist.txt)
10. **Load Playlist** - Load from file
11. **Playback Controls** - Control music playback
12. **Start Collaborative Session (Demo)** - Simulate multi-user editing
13. **Exit** - Save and quit

## Example Usage

### Display Playlist
```bash
echo "4`n13" | .\playlist_manager.exe
```

### Run Collaborative Demo
```bash
echo "12`n13" | .\playlist_manager.exe
```

## Data Storage

- Playlists are saved to: `data/playlist.txt`
- Collaboration logs: `data/collab_log.txt`

## Project Structure

```
E:\C\
├── include/
│   ├── BinarySearchTree.h     # BST implementation
│   ├── HashTable.h            # Hash table for O(1) lookups
|   ├── BinarySearchTree.h      # BST search
│   ├── CollaborationManager.h   # Collab edit
│   ├── Graph.h                 # Genre graph
│   ├── HashTable.h            # Song lookup
│   ├── HistoryManager.h       # Undo redo
│   ├── MaxHeap.h              # Top songs
│   ├── MusicLibrary.h         # Music lib
│   ├── MusicPlayer.h          # Player core
│   ├── NetworkStub.h          # Network mock
│   ├── PlaybackController.h   # Playback ctrl
│   ├── Playlist.h             # Linked list
│   ├── QueueAndStack.h        # Queue stack
│   ├── Song.h                 # Song info
│   ├── SortingAlgorithms.h    # Sort logic
│   ├── ThreadPool.h           # Thread pool
│   ├── User.h                 # User data
│   └── Utils.h                # Utilities
│
├── src/
│   ├── BinarySearchTree.cpp
│   ├── CollaborationManager.cpp
│   ├── Graph.cpp
│   ├── HashTable.cpp
│   ├── HistoryManager.cpp
│   ├── main.cpp
│   ├── MaxHeap.cpp
│   ├── MusicLibrary.cpp
│   ├── MusicPlayer.cpp
│   ├── NetworkStub.cpp
│   ├── PlaybackController.cpp
│   ├── Playlist.cpp
│   ├── Song.cpp
│   ├── SortingAlgorithms.cpp
│   ├── ThreadPool.cpp
│   ├── User.cpp
│   └── Utils.cpp
│   
├── data/
│   ├── playlist.txt            # Saved playlists
│   └── collab_log.txt          # Collaboration logs
|
├── COMMANDS.md             # CLI commands documentation
├── DSA_TOPICS.md           # Detailed DSA topic coverage
├── README.md               # Main documentation
└── Makefile                # Build configuration file

```

## Notes

- This version has been simplified to remove threading dependencies
- Compatible with MinGW GCC 6.3.0 and newer
- No external dependencies required