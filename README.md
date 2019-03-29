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

```
#include<bits/stdc++.h>
using namespace std;

typedef struct nd {
	int vertex, dist, prev;
} node ;
```

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

```
struct comp {
	bool operator () (node A, node B) {
		return A.dist > B.dist;
	}
};
```


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
