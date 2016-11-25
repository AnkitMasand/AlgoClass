#include<iostream>
#include<vector>
#include<algorithm>
#include "graph.h"
using namespace std;

struct NodeKrusk{
	Node *n;
	int set;
};

struct EdgeKrusk{
	NodeKrusk *n1;
	NodeKrusk *n2;
	int weight;
};

bool cmp_wt(EdgeKrusk &l, EdgeKrusk &r){
	return l.weight>r.weight;
}

bool sameset(NodeKrusk *n,int pos1,int pos2){
	cout<<"Checking for nodes"<<pos1<<" "<<pos2<<" "<<n[pos1].set<<" "<<n[pos2].set<<endl;
	if(n[pos1].set==n[pos2].set)
		return true;	
	while(n[pos1].set!=n[pos2].set){
		if(n[pos1].set==pos1 && n[pos2].set==pos2)
			return false;	//nodes belongs to its own set and other not equal to it
		if(n[pos1].set!=pos1)
			pos1=n[pos1].set;
		else
			pos2=n[pos2].set;
	}
	return true;
}

void unionset(NodeKrusk *n, int pos1, int pos2){
	if(n[pos1].set==pos1){
		n[pos1].set=n[pos2].set;
		return;
	}
	if(n[pos2].set==pos2){
		n[pos2].set=n[pos1].set;
		return;
	}
	//if both nodes in diff sets but not individual sets, join the roots
	while(n[pos1].set!=pos1){
		pos1=n[pos1].set;
	}//reached root of set of node1
	n[pos1].set=n[pos2].set;
}

void kruskal(Graph &G){
	NodeKrusk nodes[G.getno_of_nodes()];
	for(int i=0;i<G.getno_of_nodes();i++)
		nodes[i]={&G.NodeList[i], i};
	//count no of edges in graph
	int no_of_edges=0;
	for(int i=0;i<G.getno_of_nodes();i++){
		no_of_edges+=G.adjList[i].size();	
	}
	no_of_edges/=2;	//it is always undirected graph for mst!
	vector<EdgeKrusk> edges(no_of_edges);
	int n=0;
	for(int i=0;i<G.getno_of_nodes() && n<no_of_edges;i++){
		for(int j=0;j<G.adjList[i].size();j++){
			if(G.adjList[i][j].n->getlabel() > G.NodeList[i].getlabel()){
				edges[n].n1=&nodes[i];
				edges[n].n2=&nodes[G.adjList[i][j].n->getlabel()];
				edges[n].weight=G.adjList[i][j].weight;
				n++;
			}
		}
	}
	make_heap(edges.begin(), edges.end(),cmp_wt);
	int i=0;
	int mincost=0;
	while(i<(G.getno_of_nodes()-1)	&& !edges.empty()){
		EdgeKrusk e=edges.front();
		pop_heap(edges.begin(),edges.end(),cmp_wt);
		edges.pop_back();
		if(!sameset(nodes,e.n1->n->getlabel(),e.n2->n->getlabel())){
			i++;
			mincost+=e.weight;
			unionset(nodes,e.n1->n->getlabel(), e.n2->n->getlabel());
			cout<<e.n1->n->getlabel()<<"-"<<e.n2->n->getlabel()<<" "<<e.weight<<endl;
		}
	}
	if(i!=(G.getno_of_nodes()-1))
		cout<<"No MST!"<<endl;
	else
		cout<<"MinCost of MST:"<<mincost<<endl;
}

int main(){
	Graph G;
	G.construct();
	G.display();
	kruskal(G);
	return 0;
}
