#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "Playlist.h"
#include "QueueAndStack.h"

/**
 * HistoryManager implements undo/redo functionality using custom stacks.
 * Thread-safe operations for collaborative environments.
 * Time complexity: O(n) for undo/redo (due to playlist cloning)
 */
class HistoryManager {
private:
    Stack<Playlist*> undoStack;
    Stack<Playlist*> redoStack;
    
    const int MAX_HISTORY = 50; // Limit history to prevent memory issues

public:
    HistoryManager();
    ~HistoryManager();
    
    // Save current state before modification
    void saveState(const Playlist& playlist);
    
    // Undo last operation - returns nullptr if nothing to undo
    Playlist* undo();
    
    // Redo last undone operation - returns nullptr if nothing to redo
    Playlist* redo();
    
    // Clear all history
    void clearHistory();
    
    // Query history status
    bool canUndo() const;
    bool canRedo() const;
    int getUndoCount() const;
    int getRedoCount() const;
};

#endif // HISTORYMANAGER_H