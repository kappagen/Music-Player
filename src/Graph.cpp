#include "Graph.h"
#include "Utils.h"
#include <algorithm>

using namespace std;

Graph::Graph() {}

void Graph::addEdge(const string& genre1, const string& genre2) {
    adjacencyList[genre1].push_back(genre2);
    adjacencyList[genre2].push_back(genre1); // Undirected graph
}

void Graph::addSong(const Song& song) {
    string genre = Utils::toLower(song.getGenre());
    genreSongs[genre].push_back(song);
    
    // Ensure genre exists in adjacency list
    if (adjacencyList.find(genre) == adjacencyList.end()) {
        adjacencyList[genre] = vector<string>();
    }
}

vector<string> Graph::BFS(const string& startGenre) {
    vector<string> result;
    map<string, bool> visited;
    queue<string> q;
    
    string genre = Utils::toLower(startGenre);
    
    if (adjacencyList.find(genre) == adjacencyList.end()) {
        return result;
    }
    
    q.push(genre);
    visited[genre] = true;
    
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        result.push_back(current);
        
        for (const string& neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

void Graph::DFSHelper(const string& genre, map<string, bool>& visited, vector<string>& result) {
    visited[genre] = true;
    result.push_back(genre);
    
    for (const string& neighbor : adjacencyList[genre]) {
        if (!visited[neighbor]) {
            DFSHelper(neighbor, visited, result);
        }
    }
}

vector<string> Graph::DFS(const string& startGenre) {
    vector<string> result;
    map<string, bool> visited;
    
    string genre = Utils::toLower(startGenre);
    
    if (adjacencyList.find(genre) != adjacencyList.end()) {
        DFSHelper(genre, visited, result);
    }
    
    return result;
}

vector<Song> Graph::getRecommendations(const string& genre, int limit) {
    vector<Song> recommendations;
    string lowerGenre = Utils::toLower(genre);
    
    // Get related genres using BFS
    vector<string> relatedGenres = BFS(lowerGenre);
    
    for (const string& g : relatedGenres) {
        if (genreSongs.find(g) != genreSongs.end()) {
            for (const Song& song : genreSongs[g]) {
                recommendations.push_back(song);
                if (recommendations.size() >= (size_t)limit) {
                    return recommendations;
                }
            }
        }
    }
    
    return recommendations;
}

vector<Song> Graph::getSongsByGenre(const string& genre) {
    string lowerGenre = Utils::toLower(genre);
    
    if (genreSongs.find(lowerGenre) != genreSongs.end()) {
        return genreSongs[lowerGenre];
    }
    
    return vector<Song>();
}

bool Graph::hasGenre(const string& genre) const {
    string lowerGenre = Utils::toLower(genre);
    return genreSongs.find(lowerGenre) != genreSongs.end();
}

vector<string> Graph::getAllGenres() const {
    vector<string> genres;
    for (const auto& pair : genreSongs) {
        genres.push_back(pair.first);
    }
    return genres;
}

int Graph::getGenreCount() const {
    return genreSongs.size();
}

void Graph::clear() {
    adjacencyList.clear();
    genreSongs.clear();
}

void Graph::buildGenreRelationships() {
    // Build common genre relationships
    addEdge("rock", "metal");
    addEdge("rock", "alternative");
    addEdge("rock", "punk");
    addEdge("pop", "dance");
    addEdge("pop", "electronic");
    addEdge("hip hop", "rap");
    addEdge("hip hop", "r&b");
    addEdge("jazz", "blues");
    addEdge("jazz", "soul");
    addEdge("classical", "orchestral");
    addEdge("country", "folk");
    addEdge("electronic", "techno");
    addEdge("electronic", "house");
    addEdge("metal", "heavy metal");
    addEdge("alternative", "indie");
}
