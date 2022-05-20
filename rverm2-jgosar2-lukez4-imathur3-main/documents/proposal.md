<h1>Leading Question</h1>
Using this Wikipedia dataset, we will build a graph that denotes the connections between all Wikipedia articles. Namely, these directed edges will pertain to the hyperlinks between these articles (ie. if one article provides a link to another article). The edges will be weighted by 1 / the # of hyperlinks an article has. For example, if an article links to many other articles (say 20), then each individual hyperlink is "less important". Each individual hyperlink would be weighted as 1/20. Alternatively, if an article only links to a few other articles (say 5), then each individual hyperlink is "more important", and would be weighted as 1/5.  By building this graph, we will be able to determine the most popular Wikipedia articles, as those will be the ones with the most edges leading to them. We can further subdivide these articles into categories to draw insights about the most popular people, places, foods, etc.

We intend on using the Floyd-Warshall algorithm to find the shortest path between all articles (or a subset of the dataset if it’s too computationally expensive). Furthermore, we will build an algorithm specifically to play the Wikipedia Game. For those not familiar, this game places a user in a randomly selected article, and tasks them with navigating to a pre-selected article solely by clicking on hyperlinks within the articles. The goal is to reach the destination article in as few clicks as possible. We plan on using the A* algorithm to find this shortest distance. 

<h1>Dataset Acquisition and Processing</h1>

1. **Data Format**
The data is formatted in the dataset files provided by Stanford. The data is contained in a CSV file that has all the connections between two articles. Each article has a number and has the associated numbers for articles that are linked to it. There is another file that lists out the names of the article number that corresponds to it.

2. **Data Correction**
The data should be relatively clean but if there are nodes with bad data, we will just throw out those nodes. If the connection is not found within a set amount of time, we will terminate the find and report the nodes as too far apart. If we find that this is still too large, we will use a subset of the data.  
	
3. **Data Storage**
Data will be stored in an adjacency list. In order to minimize the data we will be storing, we will only load the integer values of the article number and once the final path is found, we will only read the names for the articles in the path. This way we are not storing a large number of strings. The storage cost for this implementation will be O(V + E) where V represents the number of articles and E represents the number of edges between these articles. We are not using the adjacency matrix because it’s space complexity is O(V^2).

<h1>Graph Algorithms</h1>

A star algorithm:

1. **Function Inputs**
The inputs will be the two wikipedia articles that we want to find the shortest path between as well as the graph with the connections between all the Wikipedia articles. Initially, the heuristic we will use for the A* algorithm will be finding a "hub article" from both the start and end. A hub article will be the article which is linked in the current that has the most outgoing links. After a few iterations of finding bigger hubs, there will be a high probability of the two hubs being the same or having a very short path between them. So we will try different thresholds for how big we want the hub article to find a good balance. 
 
2. **Function Outputs**
The sequence of wikipedia articles that need traversed in order to reach the desired wikipedia article. It will be a list of numbers that correspond to the articles that it clicked through and the size of the chain. 
 
 
3. **Function Efficiency**
A* is an informed algorithm whose runtime is dependent on the heuristic that we use. However, as an estimate, in the worst case, A* would perform similarly to Dijkstra’s algorithm, which has a runtime of O(V^2) (it can be optimized to O(V + ElogV). With our additional heuristics, we can expect to achieve better efficiency, although at the moment it is unclear what that precise runtime would be.
 
Floyd-Warshall Algorithm:
1. **Function Inputs**
A subset of a weighted, directed graph containing the wikipedia articles. The size of this subset will depend on how data we can store in memory and how fast the algorithm can run on that data. 
 
2. **Function Outputs**
A shortest distance matrix that has the length of the shortest path between any two wikipedia articles from our subset of graphs. We can make a visualization for a subset of this matrix so it’s easily interpretable.
 
3. **Function Efficiency**
The algorithm has a time complexity of O(V^3) and an O(V^2) space complexity where V is the number of articles in the Wikipedia dataset.

We also will calculate the diameter of the graph which is the longest shortest distance between any two articles which implies that any 2 articles are within a certain number of hyperlink or connections between each other. 

<h1>Traversal</h1>

The traversal that we will be using is breadth first search (BFS). 

<h1>Timeline</h1>
We have already downloaded the dataset, so the first step would be to load it using C++ and exploring the data. The next step would be building the adjacency list and coding up basic traversals from the Wikipedia article connections by 4/07/22. 

Then we would work on implementing the Floyd-Warshall Algorithm and this will be completed by 4/16/22 and the A* algorithm by 4/29/22. 

By 5/6/22, we will have the visualizations, write test cases, clean up the code base, document our code, and make our final presentation. 
