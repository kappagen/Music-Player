# Makefile for Collaborative Music Playlist Manager
# Windows compatible version (no threading)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS =

# Directories
SRC_DIR = src
INC_DIR = include
DATA_DIR = data

# Target executable
TARGET = playlist_manager.exe

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@if not exist $(DATA_DIR) mkdir $(DATA_DIR)

# Link object files to create executable (simplified for Windows)
$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_DIR)/*.cpp
	@echo Build complete: $(TARGET)

# Clean build artifacts
clean:
	-@if exist $(TARGET) del /Q $(TARGET) 2>nul
	@echo Cleaned build artifacts

# Clean everything including data
cleanall: clean
	@if exist $(DATA_DIR)\*.txt del /Q $(DATA_DIR)\*.txt
	@echo Cleaned all files including data

# Run the program
run: all
	$(TARGET)

# Debug build
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean all

# Release build with optimizations
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all

# Help target
help:
	@echo Available targets:
	@echo   all      - Build the project (default)
	@echo   clean    - Remove build artifacts
	@echo   cleanall - Remove build artifacts and data files
	@echo   run      - Build and run the program
	@echo   debug    - Build with debug symbols
	@echo   release  - Build with optimizations
	@echo   demo     - Run collaborative demo
	@echo   display  - Display current playlist
	@echo   help     - Show this help message

# Quick test commands
demo: all
	@(echo 12 && echo 13) | $(TARGET)

display: all
	@(echo 4 && echo 13) | $(TARGET)

.PHONY: all clean cleanall run debug release help directories demo display
