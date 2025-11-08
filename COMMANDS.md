# Quick Command Reference

## 🎵 Collaborative Music Playlist Manager Commands


### Using Makefile (Recommended)

```powershell
# Build the project
mingw32-make all

# Clean build files
mingw32-make clean

# Build and run interactively
mingw32-make run

# Display current playlist
mingw32-make display

# Run collaborative demo
mingw32-make demo

# Show help
mingw32-make help
```


### Using g++ directly

```powershell
# Compile
g++ -std=c++17 -Wall -Wextra -I./include src/*.cpp -o playlist_manager.exe

# Run
.\playlist_manager.exe
```



### PowerShell Scripted Commands

```powershell
# Display playlist then exit
(echo 4; echo 13) | .\playlist_manager.exe

# Run demo then exit
(echo 12; echo 13) | .\playlist_manager.exe

# Add a song (requires full input)
(echo 1; echo "My Song"; echo "Artist"; echo "Rock"; echo 180; echo 5; echo 13) | .\playlist_manager.exe
```




## Building & Running

```bash
# Clean previous builds
mingw32-make clean

# Build project
mingw32-make all

# Run application
.\playlist_manager.exe
```



## 📁 File Locations

- **Executable**: `playlist_manager.exe`
- **Source**: `src/*.cpp`
- **Headers**: `include/*.h`
- **Data**: `data/playlist.txt`, `data/collab_log.txt`

## 🔧 Troubleshooting

If program doesn't run:
1. Ensure g++ is in PATH: `g++ --version`
2. Rebuild: `mingw32-make clean && mingw32-make all`