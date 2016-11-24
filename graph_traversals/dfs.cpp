#include<iostream>
#include<stack>
#include "graph.h"
using namespace std;


int visit(Graph &G){
	int pi[G.getno_of_nodes()];
	char ch;
	//G.display();
	stack <Node*> trav;
	//Node *st=G.start;
	//Node s=*st;
	cout<<G.NodeList[0].getlabel()<<endl;
	trav.push(&G.NodeList[0]);
	//G.NodeList[0].setvisited(true);
	pi[G.NodeList[0].getlabel()]=-1;
	while(!trav.empty()){
		Node *u=trav.top();
		//cout<<trav.front().getlabel()<<":"<<trav.front().getadjno()<<endl;
		trav.pop();
		if(!u->getvisited()){
		u->setvisited(true);
		//cout<<u->getlabel()<<" :-"<<G.adjList[u->getlabel()].size()<<endl;
		for(int i=0;i<G.adjList[u->getlabel()].size();i++){
			//cout<<G.adjList[u->getlabel()][i]->getlabel()<<endl;
			if(!G.adjList[u->getlabel()][i].n->getvisited()){
				trav.push(G.adjList[u->getlabel()][i].n);
				pi[G.adjList[u->getlabel()][i].n->getlabel()]=u->getlabel();
			}
		}
		cout<<u->getlabel()<<" ";
		//cin>>ch;
		}
	}
}

int main(){
	Graph G;
	G.construct();
	G.display();
	visit(G);
	return 0;
}
