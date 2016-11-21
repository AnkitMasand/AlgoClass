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
	Node(int l);
	Node();
	int getlabel();
	void setlabel(int);
	void setvisited(bool);
	bool getvisited();
};
class Graph{
   public:
	vector<Node> NodeList;
	vector< vector<Node*> > adjList;
	void construct();
	void display();
	int getno_of_nodes();
};
#endif

