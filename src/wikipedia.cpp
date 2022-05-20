#include "wikipedia.hpp"

Wikipedia::Wikipedia(string articleNamesFile, string articleHyperlinksFile, int adjacencySizeLimit) {
    this->idToName = makeArticleMap(articleNamesFile);    
    this->adjacencyList = makeAdjacencyList(articleHyperlinksFile, adjacencySizeLimit);
}

map<string, string> Wikipedia::makeArticleMap(string filePath) {
    // Make Mapping from Article ID to Article Name
    map<string, string> idToName;
    fstream file(filePath);
    string str; 
    while (getline(file, str)) {
        pair<string, string> articlePair = readLine(str);
        idToName.insert(articlePair);
    }
    file.close();

    std::cout << "Number of articles in database: " << idToName.size() << std::endl;
    return idToName;
}

pair<string, string> Wikipedia::readLine(string line) {
    int space = line.find_first_of(" ");
    string articleId = line.substr(0, space);
    string articleName = line.substr(space + 1);
    return make_pair(articleId, articleName);
}

AdjacencyList Wikipedia::makeAdjacencyList(string filePath, int adjacencySizeLimit) {
    cout << "Making Adjacency List\n";
    
    // Make Adjacency List
    fstream file(filePath);
    string str;
    AdjacencyList adjacencyList;
    int numEdges = 0;
    while (getline(file, str)) {
        pair<string, string> edge = readLine(str);
        string article = idToName[edge.first];
        string hyperlink = idToName[edge.second];
        // Weight of edge is 1 by default
        pair<string, float> pair = make_pair(hyperlink, 1);
        adjacencyList[article].push_back(pair);
        numEdges += 1;
        if (numEdges == adjacencySizeLimit) {
            break;
        }
    }
    file.close();

    cout << "Weighing Adjacency List\n";
    /* Weight the edges of the adjacency list. The weight is 1 / # of adjacent edges
    For example, if an article links to 20 other articles (ie has 20 adjacent edges)
    then each edge will be weighted as 1/20.
    The hyperlink and edge are stored as a pair */
    for (auto i = adjacencyList.begin(); i != adjacencyList.end(); ++i) {
        string article = (*i).first;
        int numAdjacentEdges = (*i).second.size();
        for (int j = 0; j  < numAdjacentEdges; ++j) {
            adjacencyList[article][j].second = 1.0 / numAdjacentEdges;
        }
    }

    cout << "Number of edges in adjacency list: " << numEdges << endl;
    cout << "Number of vertices in adjacency list: " << adjacencyList.size() << endl;
    return adjacencyList;
}

vector<string> Wikipedia::BFS(AdjacencyList &adjacencyList) {
    auto itr = adjacencyList.begin();
    unordered_set<string> visited;
    queue<string> bfsQueue;
    vector<string> bfs;
    visited.insert((*itr).first);
    bfsQueue.push((*itr).first);
    while (!bfsQueue.empty()) {
        auto article = bfsQueue.front();
        bfsQueue.pop();
        // cout << "Article: " << article << endl;
        bfs.push_back(article);
        for (auto i = adjacencyList[article].begin(); i != adjacencyList[article].end(); ++i) {
            string hyperlink = (*i).first;
            if (visited.find(hyperlink) == visited.end()) {
                visited.insert(hyperlink);
                bfsQueue.push(hyperlink);
            }
        }
    }
    return bfs;
}

pair<int, vector<string>> Wikipedia::getDiameter(AdjacencyList& adjacencyList) {
    // Diameter is # of vertices in longest shortest path between any 2 vertices
    // Calculate diameter of graph finding the distance between every pair
    // of vertices and taking the maximum of those distances

    vector<vector<string>> allPaths;
    for (auto i = adjacencyList.begin(); i != adjacencyList.end(); ++i) {
        BFSDiam(adjacencyList, (*i).first, allPaths);
    }

    // Find the longest path size
    unsigned long max_path_size = 0;
    vector<string> best_path;
    for (auto path : allPaths) {
        if (path.size() > max_path_size) {
            max_path_size = path.size();
            best_path = path;
        }
    }
    return {max_path_size - 1, best_path};
}

void Wikipedia::BFSDiam(AdjacencyList& adjacencyList, string start, vector<vector<string>>& allPaths) {
    auto itr = adjacencyList.find(start);
    if(itr == adjacencyList.end()) return;
    unordered_set<string> visited;
    queue<string> bfsQueue;
    map<string, pair<int, string>> distance_prev_node;

    visited.insert((*itr).first);
    bfsQueue.push((*itr).first);
    distance_prev_node[(*itr).first] = make_pair(0, "");
    while (!bfsQueue.empty()) {
        auto article = bfsQueue.front();
        bfsQueue.pop();
        for (auto i = adjacencyList[article].begin(); i != adjacencyList[article].end(); ++i) {
            string hyperlink = (*i).first;
            if (visited.find(hyperlink) == visited.end()) {
                visited.insert(hyperlink);
                bfsQueue.push(hyperlink);
                distance_prev_node[hyperlink].first = distance_prev_node[article].first + 1;
                distance_prev_node[hyperlink].second = article;
            }
        }
    }

    // Starting from start node, find the longest distance
    int maxDistance = 0;
    string end = "";
    for (auto i = distance_prev_node.begin(); i != distance_prev_node.end(); ++i) {
        if ((*i).second.first > maxDistance) {
            maxDistance = (*i).second.first;
            end = (*i).first;
        }
    }

    // Back track from max node to the starting, storing the path as article names
    vector<string> path;
    while(maxDistance>=0) {
        path.push_back(end);
        end = distance_prev_node[end].second;
        maxDistance--;
    }
    std::reverse(path.begin(), path.end());
    allPaths.push_back(path);
}

AdjacencyList& Wikipedia::getAdjacencyList() {
    return this->adjacencyList;
}

map<string, string>& Wikipedia::getIdToName() {
    return this->idToName;
}

vector<vector<int>> Wikipedia::FloydWarshall(AdjacencyList& adjacencyList){
    // Returns the shortest path from every pair of vertices
    
    unordered_map<string, int> indices;
    int count = 0; 
    for (auto i = adjacencyList.begin(); i != adjacencyList.end(); ++i) {
        indices[(*i).first] = count; 
        count++;
    }

    vector<vector<int>> shortest_path;
    //intialize matrix diag to 0 and rest to int max
    for (unsigned i = 0; i < adjacencyList.size(); i++) {
        std::vector<int> vect;
        for (unsigned j = 0; j < adjacencyList.size(); j++){
            if (i == j){
                vect.push_back(0);
            }
            else {
                vect.push_back(INT16_MAX);
            }
        }
        shortest_path.push_back(vect);
    }
    //intiailize matrixes with weights
    map<string, vector<pair<string, float>>>::iterator it;
    for (it = adjacencyList.begin(); it != adjacencyList.end(); it++)
    {
        vector<pair<string, float>> edges = it->second;
        int u = indices[it->first];
        for (unsigned i = 0; i < edges.size(); i++){
            int v = indices[edges[i].first];
            int weight = edges[i].second;
            shortest_path[u][v] = weight;
        }
    }
    map<string, vector<pair<string, float>>>::iterator it1;
    map<string, vector<pair<string, float>>>::iterator it2;
    map<string, vector<pair<string, float>>>::iterator it3;
    for (it1 = adjacencyList.begin(); it1 != adjacencyList.end(); it1++)
    {
        for (it2 = adjacencyList.begin(); it2 != adjacencyList.end(); it2++)
        {
            for (it3 = adjacencyList.begin(); it3 != adjacencyList.end(); it3++)
            {
                int w = indices[it1->first];
                int u = indices[it2->first];
                int v = indices[it3->first];
                if (shortest_path[u][v] > shortest_path[u][w] + shortest_path[w][v]){
                    shortest_path[u][v] = shortest_path[u][w] + shortest_path[w][v];
                }
            }
        }
    }
    return shortest_path;
}

vector<string> Wikipedia::AStar(AdjacencyList& adjacencyList, string src, string dest) {
    // Returns the shortest path from src to dest using A* algorithm
    
    // Key: node    val: dist away from src
    unordered_map<string, float> dist; 
    // Key: node    val: node's parent
    unordered_map<string, string> parent;
    for(auto& key_val : adjacencyList) {
        dist[key_val.first] = INT16_MAX;
    }
    dist[src] = 0;

    unordered_set<string> visitedHubs;

    priority_queue<pair<string, float>> q;
    q.push(make_pair(src, 0));

    // globalMin ensures that we only push neighbor nodes to the queue
    // if the distance between the source and that neighbor is less than the
    // current smallest distance to the destination because there are no
    // negative edge weights so we can prune our search there
    float globalMin = 99999999;
    int hubSize = 200;
    while (!q.empty()) {
        pair<string, float> u = q.top();
        q.pop();

        for (pair<string, float> neighbor : adjacencyList[u.first]) {
            // Dijkstra's
            float alt = dist.at(u.first) + neighbor.second;

            // A* heuristic: Prioritize neighbors which are hubs
            // Check if it's a hub we haven't seen before
            // If it's not a hub, push it to the priority queue if its distance is less than
            // the current distance to the neighbor
            bool shouldTraverseHub = false;;
            if (adjacencyList[neighbor.first].size() > 0 && adjacencyList[neighbor.first][0].second <= 1.0/hubSize) {
                if (visitedHubs.find(neighbor.first) == visitedHubs.end()) {
                    shouldTraverseHub = true;
                    visitedHubs.insert(neighbor.first);
                }
            }

            if (shouldTraverseHub || (alt < dist[neighbor.first] && alt < globalMin)) {
                dist.at(neighbor.first) = alt;
                parent[neighbor.first] = u.first;
                // Smaller values have more priority so we multiply by -1
                // before inserting and again by -1 to recover the original value
                q.push(make_pair(neighbor.first, -1 * neighbor.second));
                if (neighbor.first == dest) {
                    globalMin = alt;
                }
            }
        }
    }

    // Recover path
    vector<string> path;
    string start = dest;
    while (start != src) {
        path.push_back(start);
        start = parent[start];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}