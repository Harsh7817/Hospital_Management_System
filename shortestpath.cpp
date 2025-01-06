#include "shortestpath.h"
#include <fstream>
#include<sstream>
// Constructor
ShortestPath::ShortestPath() 
{
    // Load data from the file if it exists
    ifstream file("location.txt");
    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        {
            size_t pos = line.find(':');
            if (pos != string::npos) 
            {
                string location = line.substr(0, pos);
                string connections = line.substr(pos + 1);
                addLocation(location);

                stringstream ss(connections);
                string connection;

                while (getline(ss, connection, ',')) 
                {
                    if (!connection.empty()) 
                    {
                        adjList[location].push_back(connection);
                    }

                }

            }

        }
        file.close();
        
    }
}

// Add a location to the graph and save it to the file
void ShortestPath::addLocation(const string& location) 
{
    if (adjList.find(location) == adjList.end()) 
    {
        adjList[location] = vector<string>();

        // Save to file
        ofstream file("location.txt", ios::app);
        if (file.is_open()) 
        {
            file << location << ":" << endl; // Add the new location with no connections yet
            file.close();
        }
    }
}

// Add a connection between two locations and update the file
void ShortestPath::addConnection(const string& location1, const string& location2) 
{
    adjList[location1].push_back(location2);
    adjList[location2].push_back(location1);

    // Save updated connections to the file
    ofstream file("location.txt");
    if (file.is_open()) 
    {
        for (const auto& entry : adjList) 
        {
            file << entry.first << ":";

            for (const string& connection : entry.second) 
            {
                file << connection << ",";
            }
            file << endl;
        }
        file.close();

    }
}

// Find and print the shortest path using BFS
void ShortestPath::findShortestPath(const string& start, const string& target) 
{
    if (adjList.find(start) == adjList.end() || adjList.find(target) == adjList.end()) 
    {
        cout << "Invalid locations!" << endl;
        return;
    }

    unordered_map<string, string> predecessor;
    unordered_map<string, bool> visited;

    queue<string> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) 
    {

        string current = q.front();
        q.pop();

        for (const string& neighbor : adjList[current]) 
        {
            if (!visited[neighbor]) 
            {
                visited[neighbor] = true;
                predecessor[neighbor] = current;
                
                q.push(neighbor);

                if (neighbor == target) 
                {
                    goto path_found;
                }
            }
        }
    }

path_found:
    if (!visited[target]) 
    {
        cout << "No path found from " << start << " to " << target << "!" << endl;
        return;
    }

    // Reconstruct the path
    stack<string> path;

    for (string at = target; at != ""; at = predecessor[at]) 
    {
        path.push(at);
    }

    cout << "Shortest path from " << start << " to " << target << ": ";
    while (!path.empty()) 
    {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

// Display all locations in the graph
void ShortestPath::displayLocations() 
{
    cout << "Hospital Locations: " << endl;
    for (const auto& location : adjList) 
    {
        cout << "- " << location.first << endl;
    }
}
