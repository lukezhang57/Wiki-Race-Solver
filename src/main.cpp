#include "wikipedia.hpp"

int main() {
    // int adjacencySizeLimit = 300000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt");
    AdjacencyList& adjacencyList = w.getAdjacencyList();

    vector<string> shortest_path = w.AStar(adjacencyList, "Mean Girls", "Couch");
    for (size_t i = 0; i < shortest_path.size(); i++) {
        std::cout << shortest_path[i] << " " << "\n";
    }
    return 0;
}