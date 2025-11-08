# Collaborative Music Playlist Manager

A C++ application for managing music playlists with collaborative features, sorting, playback controls, and undo/redo functionality.

## 🎯 Features

- **CRUD Operations**: Add, remove, edit songs with metadata (title, artist, genre, duration, rating)
- **Multi-User Collaboration**: Thread-safe concurrent editing with 3+ simultaneous users
- **Undo/Redo System**: Stack-based history (50 operations) with global undo across users
- **Playlist Operations**: Shuffle and sort by title/artist/rating/duration
- **Playback Controls**: Play, pause, resume, next, previous, stop with state tracking
- **File Persistence**: CSV-based save/load with error handling
- **Collaboration Logging**: Timestamped operation logs for all user actions
- **Conflict Resolution**: First-writer-wins policy with timestamp tracking

## 🛠️ Technologies Used

- **Language**: C++
- **Threading**: POSIX threads (pthread)
- **Synchronization**: std::mutex, std::lock_guard, std::condition_variable
- **Time**: std::chrono for timestamps
- **Containers**: Custom implementations (no STL containers for core DS)
- **Compiler**: g++ 7.0+
- **Build System**: GNU Make

## 📁 Project Structure

```
CollaborativeMusicPlaylistManager/
├── include/                    # Header files (.h)
│   ├── Song.h                 # Song data model
│   ├── Playlist.h             # Linked list playlist
│   ├── User.h                 # User representation
│   ├── CollaborationManager.h # Multi-user coordinator
│   ├── HistoryManager.h       # Undo/redo manager
│   ├── MusicLibrary.h         # File I/O handler
│   ├── QueueAndStack.h        # Custom templates
│   ├── SortingAlgorithms.h    # Bubble sort implementations
│   ├── MusicPlayer.h          # Playback simulator
│   ├── PlaybackController.h   # Playback state manager
│   ├── ThreadPool.h           # Thread pool for tasks
│   ├── NetworkStub.h          # Network placeholder
│   └── Utils.h                # Helper utilities
├── src/                       # Implementation files (.cpp)
│   ├── Song.cpp
│   ├── Playlist.cpp
│   ├── User.cpp
│   ├── CollaborationManager.cpp
│   ├── HistoryManager.cpp
│   ├── MusicLibrary.cpp
│   ├── SortingAlgorithms.cpp
│   ├── MusicPlayer.cpp
│   ├── PlaybackController.cpp
│   ├── ThreadPool.cpp
│   ├── NetworkStub.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── data/                      # Data files
│   ├── playlist.txt          # Saved songs (CSV)
│   └── collab_log.txt        # Operation logs
├── Makefile                   # Build configuration
└── README.md                  # Documentation
```

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -I./include src/*.cpp -o playlist_manager.exe
```

## Running the Program

```bash
.\playlist_manager.exe
```


### Display Playlist
```bash
echo "4`n13" | .\playlist_manager.exe
```

### Run Collaborative Demo
```bash
echo "12`n13" | .\playlist_manager.exe
```

## Notes

- This version has been simplified to remove threading dependencies
- Compatible with MinGW GCC 6.3.0 and newer
- No external dependencies required

## 📄 License

Educational project - Free to use and modify.

## 👨‍💻 Authors

Demonstration of advanced C++17 features and concurrent programming techniques.
