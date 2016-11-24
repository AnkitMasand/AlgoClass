#include<vector>
#include<iostream>
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
Node::Node(int l){
	label=l;
	visited=false;
	no_of_adj=0;
	prio=999;
}
Node::Node(){
	label=0;
	visited=false;
	no_of_adj=0;
	prio=999;
}
int Node::getlabel(){
	return label;
}
void Node::setlabel(int i){
	label=i;
}
void Node::setvisited(bool b){
	visited=b;
}
bool Node::getvisited(){
	return visited;
};

bool comp(const Node *l, const Node *r) {
                return l->prio > r->prio;
        }

class Graph{
   public:
	vector<Node> NodeList;
	vector< vector<Adj> > adjList;
	void construct();
	void display();
	int getno_of_nodes();
};

int Graph::getno_of_nodes(){
	return NodeList.size();
}

void Graph::construct(){
	int l,n,c,w;
	cout<<"Enter number of nodes:";
	cin>>n;
	for(int i=0;i<n;i++){
		NodeList.push_back(Node(i));
	}
	for(int i=0;i<n;i++)
		cout<<NodeList[i].getlabel()<<" ";
	//adjacency list now
	for(int i=0;i<n;i++)
	{
		cout<<"Number of nodes adjacent to "<<i;
		cin>>c;
		adjList.push_back(vector<Adj>());
		for(int j=0;j<c;j++){
			cin>>l;
			cin>>w;
			cout<<NodeList[l].getlabel()<<",";
			Node *t=&NodeList[l];
			cout<<t->getlabel()<<" ";
			Adj a={t,w};
			adjList[i].push_back(a);
		}
	}
}

void Graph::display(){
	for(int i=0;i<NodeList.size();i++)
	{
		cout<<NodeList[i].getlabel()<<":";
		for(int j=0;j<adjList[i].size();j++){
			cout<<adjList[i][j].n->getlabel()<<" ";
		}
		cout<<endl;
	}
}

