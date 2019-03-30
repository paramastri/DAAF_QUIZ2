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

-LIBRARY-

The library we use is:

```cpp
#include<Windows.h>
#include<bits/stdc++.h>
using namespace std;
```
#include<bits/stdc++.h> is an implementation file for a precompiled header whereas,
#include<bits/stdc++.h> is Windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API, all the common macros used by Windows programmers, and all the data types used by the various functions and subsystems.

-STRUCT-

Then, We declare the struct nd with contains vertex, dist, and prev, which is a composite data type (or record) declaration that defines a physically grouped list of variables to be placed under one name in a block of memory, allowing the different variables to be accessed via a single pointer, or the struct declared name which returns the same address.

The vertex attribute functions to store the current vertex information, dist to store the shortest route information to this vertex and prev to store the travel vertex information before reaching this vertex.

This attribute information prev will later be used to trace the route (plot).

```cpp
typedef struct nd {
	int vertex, dist, prev;
} node ;
```

-BUILD ALPHABET FUNCTION-

In this program, even though the vertex is denoted using the letters of the alphabet, the representation of the letters of the alphabet still uses numbers. For example letter A is represented by number 1, B by number 2 and so on until Z by number 26.
This is to simplify the computing process later.

This process is shown in the buildAlphabet() function

```cpp
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

-STRUCT COMPARE-

We declare a struct comp which contains boolean operator for node A and so node B that will return to distance of A is greater that the distance of B.

```cpp
struct comp {
	bool operator () (node A, node B) {
		return A.dist > B.dist;
	}
};
```

-CLASS,PRIVATE,AND PUBLIC-

We build the graph with declaring a class which inside of the class, there are some functions.
```cpp
class graph ()
```

Public and private are protection mechanisms for our classes in C++.
If a member variable/function is public, it can be used anywhere within the class. If a member variable/function is private, it can only be accessed by member functions of that class.

For private, we have the code below, that represents:

* This code snippet explains how adjacency lists are implemented.
* The Adjacency list is created using STL vector which contains pair <int, int>. The first element for storing vertex information and the second element for storing weight information (distance traveled).

```cpp
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

```cpp
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

-ADD EDGE FUNCTION-

To add edge, use the addEdge() function that takes parameters from, to, and dist.
From = the origin vertex from the edge, to = the destination vertex of the edge , whereas dist = the distance from the origin vertex to the destination vertex.

```cpp
void addEdge (int from, int to, int dist) {
	list[from].push_back(make_pair(to,dist));
	list[to].push_back(make_pair(from,dist));
}
```

-PRINT LIST FUNCTION-

We display the adjacency list with make function printList() as this code below, with using a vector containing <int, int> pair. The first element (first) is the vertex itself and the second (second) is the weight (distance).

The output display of the adjacency list is a list with the format:
From city 𝑨 , will arrive to the city 𝑩_𝟏 with cost (𝒙_𝟏) .  𝑩_𝟐 with cost (𝒙_𝟐) . 𝑩_𝟑 with cost (𝒙_𝟑) ... 𝑩_𝒊 with cost (𝒙_𝒊)
Where A is the origin vertex and each B is a vertex connected with distance x

```cpp
		void printList () {
			for (int i=1; i<=N_vertex; i++)
			{
				if (list[i].empty()) continue;
				printf("from city %c , you will arrive to the city = ",alphabet[i]);
				for (int j=0; j<list[i].size(); j++) {
					int x = list[i][j].first;
					int y = list[i][j].second;
					printf("%c with cost %d . ",alphabet[x],y);
				}
				puts("");
			}

		}
}
```
#### DFS Implementation Part

-CHECK ROUTE FUNCTION-

After the Dijkstra process is done, the next process is to check the route using the checkRoute () function. This function aims to find which points can be addressed (available routes) and which cannot be reached from the origin.

In its implementation, the checkRoute () function uses the Depth-First Search (DFS) method that utilizes recursive capabilities. If the status of a vertex is false, it means that the vertex has never been visited / there is no route to get to the vertex.
```cpp
void checkRoute (int n) {
	if (visit[n]) return;
	visit[n] = true;
	for (int i=0; i<list[n].size(); i++) {
	checkRoute(list[n][i].first);
	}
}
```

#### Dijkstra Implementation Part

-PSEUDOCODE DIJKSTRA-

To determine the shortest path of the origin vertex to other points, the algorithm used is the Dijkstra algorithm. The implementation of this algorithm refers to the following pseudocode:

![alt text](https://github.com/paramastri/DAAF_QUIZ2/blob/master/dijkstra_pseudocode.png)

-FIND SHORTEST PATH FORM FUNCTION-

Based on the pseudocode above, the application of the Dijkstra algorithm uses the priority queue structure and requires the origin vertex as its main component. Implementation in this program is shown in:

We use priority queue here and it contains elements called nodes. The node is a user-defined data type that contains attributes in struct nd

```cpp
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

```cpp
while (!pQ.empty()) {
temp = pQ.top();
pQ.pop();

int v_now = temp.vertex, dist_now = temp.dist;
int sze = list[v_now].size();
for (int i=0; i<sze; i++)
```
This section is to relax each neighbor from the vertex being extracted.

```cpp
{
	int cost = list[v_now][i].second;
	int v_next = list[v_now][i].first;
```
This part is a relax process. Here, if the total distance traveled + the weight to a vertex v is smaller than the current distance to the vertex v then relax.

Here also when doing relax, a process is performed to save the previous travel vertex to the vertex v.

```cpp	
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
-FIND PATH FUNCTION-

After Dijkstra process have been done, we create The findPath() function to find a path that tells which vertex to pass in order to reach the destination point from the starting point.

```cpp
		void findPath (int from, int goal) {
			stack <int> st;
			int now = from;
			while (now != goal) {
				st.push(now);
				now = vertex[now].second;
			}
			st.push(goal);
			printf("\n Route you will pass : ");
			while (!st.empty()) {
				now = st.top();
				printf("%c",alphabet[now]);
				if (now != from) printf(" ==> ");
				st.pop();
			}
		}
```

-FIND SHORTEST PATH FUNCTION-

Last, we create FindShortestPath function to find a path that tells which vertex to pass in order to reach the destination point from the starting point

```cpp
		void findShortestPath (int from, int to) {
			if (!visit[to]) printf("There is no route found from %c to %c\n",alphabet[from], alphabet[to]);
			else {
				printf("\n======================================================================\n");
				printf("The shortest distance from %c to %c is %d \n",alphabet[from], alphabet[to], vertex[to].first);
				findPath(to, from);
				puts("");
			}
		}
```

#### Main Program
-MAIN FUNCTION-

First, we give the appearance of the color of our program where specified by two hex digits.the first corresponds to the background, whereas the second for the foreground. represent with this code :

```cpp
	system("color 7C");		
```

We use Sleep function to delay program execution for a given number of seconds

```cpp
	printf("=============================\n");
	printf(" WELCOME TO APPLICATION \n");
	printf("=============================\n\n\n");
	Sleep(1000);
	printf("You will get easier to go everywhere you want most effective ! \n\n");
	printf("=========Lets try it now !========== \n\n");	
```

We call function buildAlphabet() first and declare some variables. N_vertex = the number of vertices, M_edge = the number of edges, u = vertex source,v = the destination vertex.

```cpp
	buildAlphabet();
	int N_vertex, M_edge, x, a, b;
	char u, v;	
```

to clear the screen, we use the cls provided on the system shown in this code below, on the other hand, The number of vertices ranges from 1-26 using the name A-Z, so the number of vertices can't be greater than 26. Also it can't be negative or zero.

```cpp
		do {
		Sleep(2000);
		system("cls");
			printf("\n======================================================================");
		printf("\n\nInsert amount of cities : ");
		cin >> N_vertex;
		if (N_vertex < 1) puts("[Cities amount can't be negative or zero!]\n");
		else if (N_vertex > 26) puts("[Cities amount can't be greater than 26!]\n");
	} while(N_vertex < 1 || N_vertex > 26);		
```

We also make sure the edge always has the value. So, we enter the number of edges on the graph that may not be negative

```cpp
		do {
		printf("\n======================================================================");
		printf("\n\nInsert amount of roads : ");
		cin >> M_edge;
		if (M_edge < 0)puts("[Roads number can't be negative or zero!]\n");
	
	} while(M_edge < 0);
```

We denote vertices with capital alphabetical ordered as per the number of vertices shown with this code below :

```cpp
		printf("\n");
	printf("\n======================================================================\n");
	puts("Each cities is represented by a capital letter :");

	int i;
	for (i=1; i<=N_vertex; i++) {
	
		cout << alphabet[i] << " ";
	}
	printf("\n======================================================================");
	Sleep(200);
	
```

Input the road with the format u v x as many as the number that has been entered before, where u = vertex source, v = the destination vertex, and x = the distance from u to v. Here, the edge can't be negative or zero also must be less than 1000. after we have inputed all road, then we call addEdge function.

```cpp
	printf("\n\nInsert two cities and the distance between.\nThe format is A B X (separated by space), which distance between Cities A and B is X kilometers.\n\n");

	graph G(N_vertex);

	for (int i=1; i<=M_edge; i++) {
		do {
			printf("\n---\n");
			printf("Road %d : ",i);
			cin >> u >> v >> x;
			if (x < 0) printf("[Distance X can't be negative or zero]\n\n");
			else if (x > 999) printf("[Distance X must be less than 1000!]\n\n");
		} while (x < 0 || x > 999);

		a = alpha[u];
		b = alpha[v];
		G.addEdge(a,b,x);
	}
	
	Sleep(1000);
	system("cls");
	printf("\n======================================================================");	
```

last of all, we display representations of Adj.List and djikstra, The last djikstra results show the cost and the shortest route with calling findShortestPath function

```cpp
	printf("\nLIST OF EACH CITY WITH DISTANCES WITH ADJACENT CITIES\n\n");
	G.printList();
	printf("\n======================================================================\n");
	printf("\n Now, you can think at what Starting City you will start going\n");

	Sleep(5000);
	system("cls");
	printf("\n WE WILL FIND THE ROUTES FOR YOU WITH THE SHORTEST DISTANCE \n\n");
	printf("\n======================================================================");
	printf("\nInput Starting City : ");
	cin >> u;
	a = alpha[u];
	G.findShortestPathFrom(a);

	for (int i=1; i<=N_vertex; i++) {
		if (i == a) continue;
		G.findShortestPath(a,i);
	}
	
	Sleep(5000);
	system("cls");
	printf("====================================\n");
	printf("||                                  ||\n");
	printf("   THANKS FOR USING OUR APPLICATION    \n");
	printf("||                                  ||\n");
	printf("====================================\n\n");
	return 0;		
```

#### OUTPUT PROGRAM

![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output1.png)
![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output2.png)
![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output3.png)
![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output4.png)
![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output5.png)
![alt text](https://github.com/chanzm/DAAF_QUIZ2/blob/master/Output6.png)
![alt text](https://github.com//DAAF_QUIZ2/blob/master/Output7.png)

For has passed doing this report , if there are any mistake, we apologize fully and last we say Thankyou.
