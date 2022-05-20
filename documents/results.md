<h1>Report</h1>
 
1. **Algorithms**
 
BFS: This is a commonly used traversal technique that starts with one node and explores all of its children before moving to grandchildren. We also used this traversal to find the diameter. We tested this by using a subset of the graph by enforcing a size limit of the adjacency. Running this gave us a diameter as well as the path which we checked to make sure was correctly identified. Since BFS checks through every edge and node the runtime is O(M + N).
 
Floyd Warshall: This is a simple algorithm used to find the shortest path from every pair of vertices. It is simple to write as it needs three for loops and we learned it in class. For testing it, we made our own small adjacency list. We then checked the output with one we had calculated which was a path matrix that indicated the correct step from each node to get to any node. As disscussed in class, since there are three for loops the runtime is O(N^3)
 
AStar: This was the algorithm that we chose to implement that we had not learned in class. It also calculates the shortest path but uses a heuristic instead. We chose to go towards neighbors which were hubs because it is likely that a Wikipedia page that has a lot of outgoing links is in the shortest path because two seemingly unrelated subjects might have some relation. An example of this would be the United States because it is such a broad topic and can lead to a lot of niche pages. This was implemented using a priority queue with the underlying Dijkstra's algorithm. This obviously runs faster than computing the whole path matrix but is not 100% guaranteed to find the shortest path. This was also tested on a subset of the dataset and the path found was checked with one we had calculated. Worst case  runtime is O(MlogN). 
 
 
2. **Leading question**
 
Our goal was to find connections between all Wikipedia articles through the hyperlinks they have to other articles. We wanted to see how well a computer would play the game if we used a heuristic that a human would generally use (visit popular pages that have a lot of connections). Ultimately we found that our project was indeed successful and that the computer was able to find very short paths between two seemingly random topics.  As expected it picked broad topics such as "Bacteria", "Space", "Greece". As a team we learned a lot and worked well with each other by sticking to our timelines.
 


