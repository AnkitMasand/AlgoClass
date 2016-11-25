#include<iostream>
#include<vector>
#include<algorithm>
#include "graph.h"
using namespace std;

void floydwarsh(Graph &G){
	vector< vector<int> > dist(G.getno_of_nodes(), vector<int>(G.getno_of_nodes(), 99999));
	for(int i=0;i<G.getno_of_nodes();i++){
		for(int j=0;j<G.adjList[i].size();j++){
			dist[i][G.adjList[i][j].n->getlabel()]=G.adjList[i][j].weight;
		}
	}
	for(int i=0;i<G.getno_of_nodes();i++)
		dist[i][i]=0;
	for(int k=0;k<G.getno_of_nodes();k++){
		for(int i=0;i<G.getno_of_nodes();i++){
			for(int j=0;j<G.getno_of_nodes();j++)
				dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
		}
	}
	for(int i=0;i<G.getno_of_nodes();i++){
		for(int j=0;j<G.getno_of_nodes();j++)
			cout<<dist[i][j]<<" ";
		cout<<endl;
	}
}

int main(){
	Graph G;
	G.construct();
	G.display();
	floydwarsh(G);
	return 0;
}
