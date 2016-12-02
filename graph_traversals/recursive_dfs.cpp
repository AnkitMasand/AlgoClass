#include<iostream>
#include<vector>
#include "graph.h"
using namespace std;

int t=0;
void dfs_visit(Graph&, Node*, int *,int*, int*,bool*);

int* dfs(Graph &G){
	int pi[G.getno_of_nodes()];
	int disc[G.getno_of_nodes()];
	int finish[G.getno_of_nodes()];
	bool recStack[G.getno_of_nodes()];
	for(int i=0;i<G.getno_of_nodes();i++)
	{
		pi[i]=-1;
		recStack[i]=false;
	}
	for(int i=0;i<G.getno_of_nodes();i++){
		if(!G.NodeList[i].getvisited())
			dfs_visit(G,&G.NodeList[i],pi,disc,finish,recStack);
	}
	cout<<"start time"<<endl;
	for(int i=0;i<G.getno_of_nodes();i++)
		cout<<disc[i]<<" ";
	cout<<endl;
	for(int i=0;i<G.getno_of_nodes();i++)
		cout<<finish[i]<<" ";
	return finish;
}

void dfs_visit(Graph &G, Node *u, int *pi,int *disc, int *finish,bool *recStack){
	t++;
	disc[u->getlabel()]=t;
	cout<<u->getlabel()<<" ";
	u->setvisited(true);
	recStack[u->getlabel()]=true;
	for(int i=0;i<G.adjList[u->getlabel()].size();i++){
		if(!G.adjList[u->getlabel()][i].n->getvisited() && !recStack[G.adjList[u->getlabel()][i].n->getlabel()]){
			pi[G.adjList[u->getlabel()][i].n->getlabel()]=u->getlabel();
			dfs_visit(G,G.adjList[u->getlabel()][i].n,pi,disc,finish,recStack);
		}
		else if(recStack[G.adjList[u->getlabel()][i].n->getlabel()])
			cout<<"Cycle in graph"<<G.adjList[u->getlabel()][i].n->getlabel()<<endl;
	}
	recStack[u->getlabel()]=false;
	t++;
	finish[u->getlabel()]=t;		
}

int main(){
	Graph G;
	G.construct();
	G.display();
	int *f=dfs(G);
}
