#ifndef GRAPH_H
#define GRAPH_H
#define MAXLEN 100
class Node {
	private:
		int label;
		bool visited;
		int no_of_adj;
	public:
		int *adj;
		Node();
		Node(int n);
		bool getvisited();
		int getlabel();
		void setvisited(bool b);
		void setlabel(int l);
		void setadjlist(int *adjlist,int adjlen);
		int getadjno();
		int getadj(int no);
		void dispadj();
};

class Graph{
	public:
		Node list[MAXLEN];
		int no_nodes;
		Node start;
		Graph(int n);
		void construct();
		void display();
};
#endif

