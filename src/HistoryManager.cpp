#include "HistoryManager.h"

HistoryManager::HistoryManager() {}

HistoryManager::~HistoryManager() {
    clearHistory();
}

void HistoryManager::saveState(const Playlist& playlist) {
    
    // Clone the playlist for history
    Playlist* snapshot = playlist.clone();
    undoStack.push(snapshot);
    
    // Clear redo stack when new action is performed
    while (!redoStack.isEmpty()) {
        Playlist* p = redoStack.pop();
        delete p;
    }
    
    // Limit history size
    if (undoStack.getSize() > MAX_HISTORY) {
        // Remove oldest entry (at bottom of stack)
        Stack<Playlist*> tempStack;
        while (undoStack.getSize() > 1) {
            tempStack.push(undoStack.pop());
        }
        Playlist* oldest = undoStack.pop();
        delete oldest;
        
        while (!tempStack.isEmpty()) {
            undoStack.push(tempStack.pop());
        }
    }
}

Playlist* HistoryManager::undo() {
    
    if (undoStack.isEmpty()) {
        return nullptr;
    }
    
    Playlist* previousState = undoStack.pop();
    redoStack.push(previousState->clone());
    
    return previousState;
}

Playlist* HistoryManager::redo() {
    
    if (redoStack.isEmpty()) {
        return nullptr;
    }
    
    Playlist* nextState = redoStack.pop();
    undoStack.push(nextState->clone());
    
    return nextState;
}

void HistoryManager::clearHistory() {
    
    while (!undoStack.isEmpty()) {
        Playlist* p = undoStack.pop();
        delete p;
    }
    
    while (!redoStack.isEmpty()) {
        Playlist* p = redoStack.pop();
        delete p;
    }
}

bool HistoryManager::canUndo() const {
    return !undoStack.isEmpty();
}

bool HistoryManager::canRedo() const {
    return !redoStack.isEmpty();
}

int HistoryManager::getUndoCount() const {
    return undoStack.getSize();
}

int HistoryManager::getRedoCount() const {
    return redoStack.getSize();
}