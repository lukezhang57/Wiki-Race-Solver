#ifndef WIKIPEDIA_H
#define WIKIPEDIA_H

#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef map<string, vector<pair<string, float>>> AdjacencyList;

class Wikipedia {
    public:
        Wikipedia(string articleNamesFile, string articleHyperlinksFile, int adjacencySizeLimit=-1);
        map<string, string> makeArticleMap(string filePath);
        AdjacencyList makeAdjacencyList(string filePath, int adjacencySizeLimit);
        
        AdjacencyList& getAdjacencyList();
        map<string, string>& getIdToName();
        
        static pair<string, string> readLine(string line);
        static vector<string> BFS(AdjacencyList &adjacencyList);
        static pair<int, vector<string>> getDiameter(AdjacencyList& adjacencyList);
        static void BFSDiam(AdjacencyList& adjacencyList, string start, vector<vector<string>>& allPaths);
        static vector<string> AStar(AdjacencyList& adjacencyList, string src, string dest);
        static vector<vector<int>> FloydWarshall(AdjacencyList& adjacencyList);

    private:
        map<string, string> idToName;
        AdjacencyList adjacencyList;
};

#endif