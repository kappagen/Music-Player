#ifndef GRAPH_H
#define GRAPH_H

#include "Song.h"
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

/**
 * Graph for representing relationships between songs (genre-based recommendations)
 * Uses adjacency list representation
 * Time Complexity: O(V + E) for BFS/DFS
 * Space Complexity: O(V + E)
 */
class Graph {
private:
    map<string, vector<string>> adjacencyList; // genre -> related genres
    map<string, vector<Song>> genreSongs; // genre -> songs
    
public:
    Graph();
    
    // Core operations
    void addEdge(const string& genre1, const string& genre2);
    void addSong(const Song& song);
    
    // Traversal
    vector<string> BFS(const string& startGenre);
    vector<string> DFS(const string& startGenre);
    
    // Recommendations
    vector<Song> getRecommendations(const string& genre, int limit = 5);
    vector<Song> getSongsByGenre(const string& genre);
    
    // Utilities
    bool hasGenre(const string& genre) const;
    vector<string> getAllGenres() const;
    int getGenreCount() const;
    void clear();
    
    // Build relationships automatically
    void buildGenreRelationships();
    
private:
    void DFSHelper(const string& genre, map<string, bool>& visited, vector<string>& result);
};

#endif // GRAPH_H
