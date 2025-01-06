#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

class ShortestPath {
private:
    unordered_map<string, vector<string>> adjList; // Graph representation

public:
    ShortestPath();
    void addLocation(const string& location);
    void addConnection(const string& location1, const string& location2);
    void findShortestPath(const string& start, const string& target);
    void displayLocations();
};

#endif
