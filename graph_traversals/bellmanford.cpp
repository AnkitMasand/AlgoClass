#include<iostream>
#include<vector>
#include "graph.h"
using namespace std;

bool bellford(Graph &G, int s){
	int dist[G.getno_of_nodes()],pi[G.getno_of_nodes()];
	for(int i=0;i<G.getno_of_nodes();i++){
		dist[i]=99999;
		pi[i]=-1;
	}	
	dist[s]=0;
	for(int i=0;i<G.getno_of_nodes();i++){
		for(int j=0;j<G.adjList[i].size();j++){
			if(dist[G.adjList[i][j].n->getlabel()] > (dist[G.NodeList[i].getlabel()]+G.adjList[i][j].weight)){
				dist[G.adjList[i][j].n->getlabel()]=(dist[G.NodeList[i].getlabel()]+G.adjList[i][j].weight);
				pi[G.adjList[i][j].n->getlabel()]=G.NodeList[i].getlabel();
			}
		}
	}
	for(int i=0;i<G.getno_of_nodes();i++){
		for(int j=0;j<G.adjList[i].size();j++){
			if(dist[G.adjList[i][j].n->getlabel()] > (dist[G.NodeList[i].getlabel()]+G.adjList[i][j].weight)){
				return false;
			}
		}
	}
	for(int i=0;i<G.getno_of_nodes();i++)
		cout<<dist[i]<<" ";
	return true;
}

int main(){
	Graph G;
	G.construct();
	G.display();
	bellford(G,0);
	return 0;
}
