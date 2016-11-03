#include<iostream>
#include<queue>
#include "graph.h"
using namespace std;


int visit(Graph &G){
	int pi[G.no_nodes];
	G.display();
	queue <Node> trav;
	cout<<G.start->getlabel()<<":"<<G.start->getadjno()<<endl;
	trav.push(*G.start);
	G.start.setvisited(true);
	pi[G.start.getlabel()]=-1;
	while(!trav.empty()){
		Node u=trav.front();
		cout<<trav.front().getlabel()<<":"<<trav.front().getadjno()<<endl;
		trav.pop();
		cout<<u.getlabel()<<" :-"<<u.getadjno()<<endl;
		for(int i=0;i<u.getadjno();i++){
			if(G.list[u.adj[i]].getvisited()==false){
				trav.push(G.list[u.adj[i]]);
				pi[G.list[u.adj[i]].getlabel()]=u.getlabel();
			}
		}
		cout<<u.getlabel()<<" ";
	}
}

int main(){
	Graph G(5);
	G.construct();
	G.display();
	visit(G);
	return 0;
}
