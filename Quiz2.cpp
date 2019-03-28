#include<bits/stdc++.h>
using namespace std;

typedef struct nd {
	int vertex, dist, prev;
} node ;

char alphabet[28];
map <char,int> alpha;
void buildAlphabet ()
{
	for (int i=65; i<=90; i++) {
		alphabet[(i-65)+1] = char(i);
		alpha[char(i)] = (i-65)+1;
	}
}

struct comp {
	bool operator () (node A, node B) {
		return A.dist > B.dist;
	}
};

class graph
{
	private :
		int **matrix;
		vector < pair<int,int> > *list; // first untuk vertex
		int N_vertex;
		pair<int,int> vertex[30]; // first untuk jarak terpendek,
                                //second untuk vertex sebelumnya
		bool visit[30];

	public :
		graph(int N) {
			N_vertex = N;
			list = new vector<pair<int,int> > [N+2]; // adjacency list

			matrix = new int *[N+2];
			for (int i=0; i<N+2; i++) {
				matrix[i] = new int[N+2];
			}
			for (int i=0; i<N+2; i++) { 	// atur matrix ke 0
				vertex[i+1].first = INT_MAX;
				for (int j=0; j<N+2; j++) {
					matrix[i][j] = 0;
				}
			}
			memset(visit, false, sizeof(visit));
		}
		void addEdge (int from, int to, int dist) {
			list[from].push_back(make_pair(to,dist));
			matrix[from][to] = dist;
			list[to].push_back(make_pair(from,dist));
			matrix[to][from] = dist;
		}

		void printMatrix () {

			int i;
			printf("    ");
			for (i=1; i<=N_vertex; i++) printf("%c   ",alphabet[i]);
			puts("");
			printf("    ");
			for (i=1; i<=N_vertex; i++) printf("-   ");
			puts("");
			for (i=1; i<=N_vertex; i++)
			{
				printf("%c | ",alphabet[i]);
				for (int j=1; j<=N_vertex; j++) {
					printf("%d",matrix[i][j]);

					if (matrix[i][j] >= 10 && matrix[i][j] <=99) printf("  ");
					else if (matrix[i][j] >= 100 && matrix[i][j] <=999) printf(" ");
					else if (matrix[i][j] < 10) printf("   ");
				}
				puts("");
			}
		}

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

		void checkRoute (int n) {
			if (visit[n]) return;
			visit[n] = true;
			for (int i=0; i<list[n].size(); i++) {
				checkRoute(list[n][i].first);
			}
		}
		void findShortestPathFrom (int A) {
			priority_queue < node, vector<node>, comp > pQ;
			vertex[A].first = 0;
			vertex[A].second = A;
			node temp;
			temp.vertex = A; temp.dist = 0; temp.prev = A;
			pQ.push(temp);

			while (!pQ.empty()) {
				temp = pQ.top();
				pQ.pop();

				int v_now = temp.vertex, dist_now = temp.dist;
				int sze = list[v_now].size();
				for (int i=0; i<sze; i++)
				{
					int cost = list[v_now][i].second;
					int v_next = list[v_now][i].first;
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

		void findPath (int from, int goal) {
			stack <int> st;
			int now = from;
			while (now != goal) {
				st.push(now);
				now = vertex[now].second;
			}
			st.push(goal);
			printf(" melalui ");
			while (!st.empty()) {
				now = st.top();
				printf("%c",alphabet[now]);
				if (now != from) printf(" -> ");
				st.pop();
			}
		}

		void findShortestPath (int from, int to) {
			if (!visit[to]) printf("<> Tidak ditemukan rute dari %c menuju %c\n",alphabet[from], alphabet[to]);
			else {
				printf("<> Rute terpendek dari %c menuju %c adalah %d",alphabet[from], alphabet[to], vertex[to].first);
				findPath(to, from);
				puts("");
			}
		}
};

int main ()
{
	buildAlphabet();
	int N_vertex, M_edge, x, a, b;
	char u, v;

	do {
		printf("Masukkan jumlah vertex pada graf : ");
		cin >> N_vertex;
		if (N_vertex < 1) puts("[Jumlah vertex tidak boleh negatif atau 0!]\n");
		else if (N_vertex > 26) puts("[Jumlah vertex maksimal 26!]\n");
	} while(N_vertex < 1 || N_vertex > 26);

	do {
		printf("Masukkan jumlah edge pada graf   : ");
		cin >> M_edge;
		if (M_edge < 0) puts("[Jumlah edge tidak boleh negatif!]\n");
	} while(M_edge < 0);

	printf("\n");
	puts("Setiap vertex dinotasikan dengan huruf abjad kapital sebagai berikut :");

	int i;
	for (i=1; i<=N_vertex; i++) {
		cout << alphabet[i] << " ";
	}
	printf("\n\nUntuk setiap edge, format masukan berupa U, V dan X (dipisahkan spasi).\nDimana vertex U terhubung ke vertex V dengan jarak X.\n\n");

	graph G(N_vertex);

	for (int i=1; i<=M_edge; i++) {
		do {
			printf("Edge %d : ",i);
			cin >> u >> v >> x;
			if (x < 0) printf("[Jarak X tidak boleh negatif!]\n\n");
			else if (x >= 999) printf("[Jarak X harus kurang dari 1000!]\n\n");
		} while (x < 0 || x >= 999);

		a = alpha[u];
		b = alpha[v];
		G.addEdge(a,b,x);
	}
	printf("\n----------------------------------------------------------------------");
	printf("\nRepresentasi graf menggunakan Adjacency Matrix adalah sebagai berikut :\n\n");
	G.printMatrix();

	printf("\n----------------------------------------------------------------------");
	printf("\nRepresentasi graf menggunakan Adjacency List adalah sebagai berikut :\n\n");
	G.printList();
	printf("\n======================================================================\n");

	printf("\nMenentukan rute terpendek dari titik awal\nTentukan titik awal vertex : ");
	cin >> u;
	a = alpha[u];
	G.findShortestPathFrom(a);

	printf("\nHasilnya adalah sebagai berikut :\n");
	for (int i=1; i<=N_vertex; i++) {
		if (i == a) continue;
		G.findShortestPath(a,i);
	}
	return 0;
}

