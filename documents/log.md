 **Week of March 28 - April 3** 
1. Goals: We wanted to finish the building the adjacency list and coding up basic traversals. We have a adjacency list and a BFS traversal working.
2. We all updated the proposal based on the feedback. Ishaan built the adjacency list and Jimit wrote the BFS traversal.
3. No problems.
4. We are slightly ahead of schedule and will start working on implementing the Floyd-Warshall Algorithm. 


**Week of April 3 - April 10** 
1. Since we are already ahead of schedule, we worked on weighing the edges of the list which was the goal of this week.
2. Riya is working on calculating the diameter. Ishaan completed weighing the edges of the list.
3. Originally we were having trouble deciding how to weigh the graphs, but we added the weight to each edge based is 1 / number of hyperlinks an article has. 
4. We will finish calculating diameter and begin working on implementing the Floyd Warshall Algorithm.

**Week of April 10 - April 17** 
1. We finished the calculate_diameter function and wrote test cases for it and the traversals. 
2. Jimit wrote test cases for BFS, Ishaan wrote some test cases for calculate diameter and designed the class we will be using, Riya worked on calculate diamater and some test cases, and Luke is working on implementing the Floyd Warshall algorithm. 
3. No problems. The only thing is that the calculate diameter function is very slow on large, dense graphs so we will see if we can make optimizations.
4. We will finish working on implementing the Floyd Warshall Algorithm. 


**Week of April 18 - April 25** 
1. Riya and Ishaan jointly coded, and tested the Dijsktra's algorithm as a precursor to the A* algorithm with our custom heuristic.
2. One problem we encountered while implementing Dijsktra's algorithm was using a priority queue that gives smaller numbers (ie. smaller weight edges) greater priority. By default, the C++ priotity queue gives larger numbers higher priority. So we multiplied all edge weights by -1 when pushing them to the priority queue to give make the smaller edge weights actually larger. Then we multiply them by -1 when popping from the queue to get back the original edge weight.
3. Our plan for next week is to implement the custom heuristic and finish the A* algorithm.

**Week of April 26 - May 3** 
1. Our goal of completing the A* algorithm was accomplished this week.
2. Ishaan and Riya came up with a valid A* heuristic and implemented it on top off the Dijsktra's algorithm from the previous week. Luke wrote test cases for the algorithm.
3. We encountered problems coming up with a valid heuristic for A* that relied on more than just the edge weights.
4. Next week we will write the written report and make the final presentation.