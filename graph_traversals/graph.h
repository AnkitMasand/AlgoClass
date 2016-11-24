#ifndef GRAPH_H
#define GRAPH_H
#define MAXLEN 100
#include<vector>
using namespace std;
class Node{
	int label;
	int no_of_adj;
	bool visited;
   public:
	int prio;
	Node(int l);
	Node();
	int getlabel();
	void setlabel(int);
	void setvisited(bool);
	bool getvisited();
};

typedef struct Adj{
        Node* n;
        int weight;
};

bool comp(const Node *l, const Node *r);

typedef struct GreaterThanPrio{
        bool operator()(const Node *l, const Node *r) const{
                return l->prio > r->prio;
        }
};

class Graph{
   public:
	vector<Node> NodeList;
	vector< vector<Adj> > adjList;
	void construct();
	void display();
	int getno_of_nodes();
};
#endif

