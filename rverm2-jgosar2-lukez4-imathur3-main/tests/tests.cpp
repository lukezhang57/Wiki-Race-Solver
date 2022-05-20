#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "wikipedia.hpp"

TEST_CASE("Parsing", "[parsing]") {
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt");
    AdjacencyList& adjacencyList = w.getAdjacencyList();
    REQUIRE(w.getIdToName().size() == 1791489);
    REQUIRE(adjacencyList.size() == 1790518);

    int numEdges = 0;
    for (auto i = adjacencyList.begin(); i != adjacencyList.end(); ++i) {
        numEdges += (*i).second.size();
    }
    REQUIRE(numEdges == 28511807);
}

TEST_CASE("Parsing::readLine", "[parsing]") {
    pair<string, string> p = Wikipedia::readLine("a b");
    REQUIRE(p.first == "a");
    REQUIRE(p.second == "b");

    p = Wikipedia::readLine("320981 Basketball");
    REQUIRE(p.first == "320981");
    REQUIRE(p.second == "Basketball");  

    p = Wikipedia::readLine("5329 The Economist");
    REQUIRE(p.first == "5329");
    REQUIRE(p.second == "The Economist");  
}

TEST_CASE("BFS::SmallAdjacencyList1", "[BFS]")
{
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0), make_pair("Z", 1.0)};
    adjacencyList["Z"] = {make_pair("J", 1.0)};

    vector<string> bfs = Wikipedia::BFS(adjacencyList);

    vector<string> ans = {"A", "D", "B", "F", "C", "G", "E", "J", "Z"};
    REQUIRE(bfs == ans);
}

TEST_CASE("BFS::SmallAdjacencyList2", "[BFS]")
{
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("H", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["H"] = {make_pair("E", 1.0), make_pair("I", 1.0)};
    adjacencyList["I"] = {make_pair("H", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0)};

    vector<string> bfs = Wikipedia::BFS(adjacencyList);

    vector<string> ans = {"A","D","B","F","C","G","E","J","H","I" };
    REQUIRE(bfs == ans);
}

TEST_CASE("Diameter::SmallAdjacencyList1", "[diameter]") {
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0), make_pair("Z", 1.0)};
    adjacencyList["Z"] = {make_pair("J", 1.0)};

    pair<int, vector<string>> p = Wikipedia::getDiameter(adjacencyList);
    int diameter = p.first;
    vector<string> path = p.second;
    REQUIRE(diameter == 5);
    vector<string> ans = {"A", "D", "F", "G", "J", "Z"};
    REQUIRE(path == ans);
}

TEST_CASE("Diameter::SmallAdjacencyList2", "[diameter]") {
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("H", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["H"] = {make_pair("E", 1.0), make_pair("I", 1.0)};
    adjacencyList["I"] = {make_pair("H", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0)};
    
    pair<int, vector<string>> p = Wikipedia::getDiameter(adjacencyList);
    int diameter = p.first;
    vector<string> path = p.second;
    REQUIRE(diameter == 6);
    vector<string> ans = {"A", "D", "B", "C", "E", "H", "I"};
    REQUIRE(path == ans);
}

TEST_CASE("Diameter::WikipediaSubset1", "[diameter]") {
    int adjacencySizeLimit = 1000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt", adjacencySizeLimit);
    pair<int, vector<string>> p = w.getDiameter(w.getAdjacencyList());
    int diameter = p.first;
    vector<string> path = p.second;
    REQUIRE(diameter == 4);
    vector<string> ans = {"Third Eye (Redd Kross album)", "Robert Hecker", "Teen Babes from Monsanto", "Born Innocent (Redd Kross album)", "All Tomorrow's Parties (music festival)"};
    REQUIRE(path == ans);
}

TEST_CASE("Diameter::WikipediaSubset2", "[diameter]") {
    int adjacencySizeLimit = 10000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt", adjacencySizeLimit);
    pair<int, vector<string>> p = w.getDiameter(w.getAdjacencyList());
    int diameter = p.first;
    vector<string> path = p.second;
    REQUIRE(diameter == 10);
    vector<string> ans = {"Acid (band)", "Siam Shade", "Visual kei", "Kisaki", "Vidoll", "Gan-Shin", "Aural Vampire", "Blood (band)", "Blam Honey", "Suppurate System", "Mana"};
    REQUIRE(path == ans);
}

TEST_CASE("FloydWarshall::SmallAdjacencyList1", "[floyd-warshall]") { 
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0), make_pair("Z", 1.0)};
    adjacencyList["Z"] = {make_pair("J", 1.0)};

    vector<vector<int>> shortest_path = Wikipedia::FloydWarshall(adjacencyList);
    vector<vector<int>> ans = {{0,  2,  3,  1,  4,  2,  3,  4,  5},  
                                {2,  0, 1,  1,  2,  2,  3,  4,  5},  
                                {3,  1,  0,  2,  1,  3,  2,  3,  4},  
                                {1,  1,  2,  0,  3,  1,  2,  3,  4},  
                                {4,  2,  1,  3,  0,  2,  1,  2,  3},  
                                {2,  2,  3,  1,  2,  0,  1,  2,  3},  
                                {3,  3,  2,  2,  1,  1,  0,  1,  2},  
                                {4,  4,  3,  3,  2,  2,  1,  0,  1},  
                                {5,  5,  4,  4,  3,  3,  2,  1,  0}};  
    REQUIRE(shortest_path == ans);
}

TEST_CASE("FloydWarshall::SmallAdjacencyList2", "[floyd-warshall]") { 
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("D", 1.0)};
    adjacencyList["B"] = {make_pair("D", 1.0), make_pair("C", 1.0)};
    adjacencyList["C"] = {make_pair("E", 1.0), make_pair("B", 1.0)};
    adjacencyList["D"] = {make_pair("A", 1.0), make_pair("B", 1.0), make_pair("F", 1.0)};
    adjacencyList["E"] = {make_pair("C", 1.0), make_pair("H", 1.0), make_pair("G", 1.0)};
    adjacencyList["F"] = {make_pair("D", 1.0), make_pair("G", 1.0)};
    adjacencyList["G"] = {make_pair("E", 1.0), make_pair("J", 1.0), make_pair("F", 1.0)};
    adjacencyList["H"] = {make_pair("E", 1.0), make_pair("I", 1.0)};
    adjacencyList["I"] = {make_pair("H", 1.0)};
    adjacencyList["J"] = {make_pair("G", 1.0)};

    vector<vector<int>> shortest_path = Wikipedia::FloydWarshall(adjacencyList); 
    vector<vector<int>> ans = {{0,  2,  3,  1,  4,  2,  3,  5,  6,  4},  
                                {2,  0, 1,  1,  2,  2,  3,  3,  4,  4},  
                                {3,  1,  0,  2,  1,  3,  2,  2,  3,  3},  
                                {1,  1,  2,  0,  3,  1,  2,  4,  5,  3},  
                                {4,  2,  1,  3,  0,  2,  1,  1,  2,  2},  
                                {2,  2,  3,  1,  2,  0,  1,  3,  4,  2},  
                                {3,  3,  2,  2,  1,  1,  0,  2,  3,  1},  
                                {5,  3,  2,  4,  1,  3,  2,  0,  1,  3},  
                                {6,  4,  3,  5,  2,  4,  3,  1,  0,  4},  
                                {4,  4,  3,  3,  2,  2,  1,  3,  4,  0}};
    REQUIRE(shortest_path == ans);
}

TEST_CASE("AStar::SmallAdjacencyList1", "[a-star]") { 
    AdjacencyList adjacencyList;
    adjacencyList["A"] = {make_pair("B", 0.5), make_pair("C", 0.5)};
    adjacencyList["B"] = {make_pair("D", 0.5), make_pair("E", 0.5)};
    adjacencyList["C"] = {make_pair("F", 0.333), make_pair("G", 0.333),  make_pair("H", 0.333)};
    adjacencyList["E"] = {make_pair("Z", 1)};
    adjacencyList["H"] = {make_pair("Z", 1)};
    adjacencyList["Z"] = {};

    vector<string> shortest_path = Wikipedia::AStar(adjacencyList, "A", "Z");
    vector<string> ans = {"A", "C", "H", "Z"};
    REQUIRE(shortest_path == ans);
}

TEST_CASE("AStar::WikipediaSubset1", "[a-star]") { 
    int adjacencySizeLimit = 300000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt", adjacencySizeLimit);
    AdjacencyList& adjacencyList = w.getAdjacencyList();
    vector<string> shortest_path = w.AStar(adjacencyList, "Population history of indigenous peoples of the Americas", "Restriction modification system");
    vector<string> ans = {"Population history of indigenous peoples of the Americas", "Bacteria", "Restriction modification system"};
    REQUIRE(shortest_path == ans);
}

TEST_CASE("AStar::WikipediaSubset2", "[a-star]") { 
    int adjacencySizeLimit = 300000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt", adjacencySizeLimit);
    AdjacencyList& adjacencyList = w.getAdjacencyList();
    vector<string> shortest_path = w.AStar(adjacencyList, "Adult", "Enzyme");
    vector<string> ans = {"Adult", "Biology", "Bacteria", "Enzyme"};
    REQUIRE(shortest_path == ans);
}

TEST_CASE("AStar::WikipediaSubset3", "[a-star]") { 
    int adjacencySizeLimit = 1000000;
    Wikipedia w = Wikipedia("./data/article_names.txt", "./data/article_hyperlinks.txt", adjacencySizeLimit);
    AdjacencyList& adjacencyList = w.getAdjacencyList();
    vector<string> shortest_path = w.AStar(adjacencyList, "Champion (sportswear)", "Aspirin");
    vector<string> ans = {"Champion (sportswear)", "Wonderbra", "Israel", "Jordan", "Cancer", "Aspirin"};
    REQUIRE(shortest_path == ans);
}