# DAAF_QUIZ2

Dedicated for Quiz 2 DAA-F

Made by:
* 05111740000019  Paramastri Ardiningrum (github.com/paramastri)
* 05111740000113  Octaviannus Giovanni Yaunatan (github.com/Axerion1210)
* 05111740000115  Chaniyah Zulfa Mukhlishah (github.com/chanzm)

## A Simple Tour Guide Application

We create a simple application that implements the Dijkstra algorithm.

The large number of tourists who are traveling and struggling to find the most effective distance that they can travel to their destination makes us inspired to make this program. So here we provide a solution for them, through a simple application that implements the Dijkstra algorithm, and is expected that later it will be able to help solve their problem.

1.	User can input the number of cities (origin and destination).
2.	The user inputs how many paths are passed.
3.	Users input how many kilometers (km) distance from one city to another, which in this application is represented by alphabet. Example: [City 1] [City 2] [Distance].
4.	The program will display lists of alternative information between cities and their distances.
5.	From this information, user can enter their current location.
6.	Finally, the program displays the shortest route from the current location to all the destination cities that have been entered earlier.

### Source Code and The Analysis

#### Vertex and Edge Specifications

The type of graph implemented in this program is the Undirected-Weighted Graph.

* Vertex Specifications

The vertices in this graph are denoted by the letters of the capital capital A.d. Z. Thus, the maximum number of vertices that can be used is 26 vertices.

* Edge Specifications

Edge in this graph connects two vertices in the same direction (directed) and each edge has a weight in the form of the largest distance. Because the weight is in the form of distance, the weights cannot be negative.

#### Code Analysis

The library we use is:

```
#include<bits/stdc++.h>
using namespace std;
```

We declare the struct, which is a composite data type (or record) declaration that defines a physically grouped list of variables to be placed under one name in a block of memory, allowing the different variables to be accessed via a single pointer, or the struct declared name which returns the same address.

The variable that defined within the struct nd are vertex, dist, and prev.

The vertex attribute functions to store the current vertex information, dist to store the shortest route information to this vertex and prev to store the travel vertex information before reaching this vertex.

This attribute information prev will later be used to trace the route (plot).

```
typedef struct nd {
	int vertex, dist, prev;
} node ;
```

In this program, even though the vertex is denoted using the letters of the alphabet, the representation of the letters of the alphabet still uses numbers. For example letter A is represented by number 1, B by number 2 and so on until Z by number 26.
This is to simplify the computing process later.

This process is shown in the buildAlphabet() function

```
char alphabet[28];
map <char,int> alpha;
void buildAlphabet ()
{
	for (int i=65; i<=90; i++) {
		alphabet[(i-65)+1] = char(i);
		alpha[char(i)] = (i-65)+1;
	}
}
```
We declare a struct comp. The variable that defined within the struct comp are boolean operator for node A and node B that will return to distance of A is greater that the distance of B.

```
struct comp {
	bool operator () (node A, node B) {
		return A.dist > B.dist;
	}
};
```
We declare a class to build the graph.

```
class graph ()
```

Inside the class, there are functions.

Public and private are protection mechanisms for our classes in C++. If a member variable/function is public, it can be used anywhere within the class. If a member variable/function is private, it can only be accessed by member functions of that class.

In private, we have the code below, that represents:

* This code snippet explains how adjacency lists are implemented.
* The Adjacency list is created using STL vector which contains pair <int, int>. The first element for storing vertex information and the second element for storing weight information (distance traveled).

```
private :
    // first pair declares vertex
		vector < pair<int,int> > *list; 
		int N_vertex;
    // first pair declares shorterst path
    // second pair declares previous vertex
		pair<int,int> vertex[30]; 
		bool visit[30];
```

In public, we have the code below, that in this code, we build an adjacency list in a new vector and set the vertex into integer max (INT_MAX). Hence we have memset which contains of variables (visit, false, and the size of visit).

```
public:
graph(int N) {
	N_vertex = N;
	// make the adjacency list
	list = new vector<pair<int,int> > [N+2]; 
	
	// set the vertex into INT_MAX
	for (int i=0; i<N+2; i++) { 	
	vertex[i+1].first = INT_MAX;
	}
	
	memset(visit, false, sizeof(visit));
}
```
* To add edge, use the addEdge() function that takes parameters from, to, and dist.
* From is the origin vertex from the edge, to is the destination vertex of the edge and dist is the distance from the origin vertex to the destination vertex.

```
void addEdge (int from, int to, int dist) {
	list[from].push_back(make_pair(to,dist));
	list[to].push_back(make_pair(from,dist));
}
```
We display the adjacency list in this code below, created using a vector containing <int, int> pair. The first element (first) is the vertex itself and the second (second) is the weight (distance).

```
void printList () {
	for (int i=1; i<=N_vertex; i++)
	{
		if (list[i].empty()) continue;
		printf("%c -> ",alphabet[i]);
		for (int j=0; j<list[i].size(); j++) {
			int x = list[i][j].first;
			int y = list[i][j].second;
			printf("%c(%d) ",alphabet[x],y);
		}
			puts("");
	}
}
```
#### DFS Implementation Part

The checkRoute () function below uses the Depth-First Search (DFS) method that utilizes recursive capabilities. If the status of a vertex is false, it means that the vertex has never been visited / there is no route to get to the vertex. This function aims to find which points can be addressed (available routes) and which cannot be reached from the origin.

```
void checkRoute (int n) {
	if (visit[n]) return;
	visit[n] = true;
	for (int i=0; i<list[n].size(); i++) {
	checkRoute(list[n][i].first);
	}
}
```

#### Dijkstra Implementation Part

To determine the shortest path of the origin vertex to other points, the algorithm used is the Dijkstra algorithm. The implementation of this algorithm refers to the following pseudocode:

<GAMBAR PSEUDOCODE>

Based on the pseudocode above, the application of the Dijkstra algorithm uses the priority queue structure and requires the origin vertex as its main component. Implementation in this program is shown in:

By default, STL priority queue on C ++ will prioritize the largest element as top () (Biggest First Out). However, because the Dijkstra algorithm requires the smallest element (the smallest mileage) on the priority queue, it can be modified on the priority queuenya.

```
void findShortestPathFrom (int A) {
	priority_queue < node, vector<node>, comp > pQ;
	vertex[A].first = 0;
	vertex[A].second = A;
	node temp;
	temp.vertex = A; temp.dist = 0; temp.prev = A;
	pQ.push(temp);
```
Then, the next implementation of Pseudocode is as follows:

This section is to extract the smallest value (the distance to the smallest vertex i)

```
while (!pQ.empty()) {
temp = pQ.top();
pQ.pop();

int v_now = temp.vertex, dist_now = temp.dist;
int sze = list[v_now].size();
for (int i=0; i<sze; i++)
```
This section is to relax each neighbor from the vertex being extracted.

```
{
	int cost = list[v_now][i].second;
	int v_next = list[v_now][i].first;
```
This part is a relax process. Here, if the total distance traveled + the weight to a vertex v is smaller than the current distance to the vertex v then relax.

Here also when doing relax, a process is performed to save the previous travel vertex to the vertex v.

```	
if (cost + dist_now < vertex[v_next].first) {
		vertex[v_next].first = cost + dist_now;
		vertex[v_next].second = v_now;
	
		node x;
		x.dist = vertex[v_next].first;
		x.prev = v_now;
		x.vertex = v_next;
		pQ.push(x);
			}
		}
	}

	checkRoute(A);
}
```
The findPath() function is to find a path that tells which vertex to pass in order to reach the destination point from the starting point.

```
void findPath (int from, int goal) {
			stack <int> st;
			int now = from;
			while (now != goal) {
				st.push(now);
				now = vertex[now].second;
			}
			st.push(goal);
			printf("\nThe route : ");
			while (!st.empty()) {
				now = st.top();
				printf("%c",alphabet[now]);
				if (now != from) printf(" -> ");
				st.pop();
			}
		}
```

Then we display the shortest path by this function below:

```
void findShortestPath (int from, int to) {
			if (!visit[to]) printf("There is no route found from %c to %c\n",alphabet[from], alphabet[to]);
			else {
				printf("The shortest distance from %c to %c is %d",alphabet[from], alphabet[to], vertex[to].first);
				findPath(to, from);
				puts("");
			}
		}
```

#### Main Program
