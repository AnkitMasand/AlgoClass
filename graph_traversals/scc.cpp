#include<iostream>
#include<vector>
#include<algorithm>
#include "graph.h"
using namespace std;

int t=0;
void dfs_visit(Graph&, Node*, int *,int*, vector<int>&);

vector<int> dfs(Graph &G){
	int pi[G.getno_of_nodes()];
	int disc[G.getno_of_nodes()];
	vector<int> finish(G.getno_of_nodes());
	for(int i=0;i<G.getno_of_nodes();i++)
		pi[i]=-1;
	for(int i=0;i<G.getno_of_nodes();i++){
		if(!G.NodeList[i].getvisited())
			dfs_visit(G,&G.NodeList[i],pi,disc,finish);
	}
	cout<<"start time"<<endl;
	for(int i=0;i<G.getno_of_nodes();i++)
		cout<<disc[i]<<" ";
	cout<<endl;
	for(int i=0;i<G.getno_of_nodes();i++)
		cout<<finish[i]<<" ";
	return finish;
}

void dfs_visit(Graph &G, Node *u, int *pi,int *disc, vector<int> &finish){
	t++;
	disc[u->getlabel()]=t;
	cout<<u->getlabel()<<" ";
	u->setvisited(true);
	for(int i=0;i<G.adjList[u->getlabel()].size();i++){
		if(!G.adjList[u->getlabel()][i].n->getvisited()){
			pi[G.adjList[u->getlabel()][i].n->getlabel()]=u->getlabel();
			dfs_visit(G,G.adjList[u->getlabel()][i].n,pi,disc,finish);
		}
	}
	t++;
	finish[u->getlabel()]=t;		
}

void dfs_visit_scc(Graph &G,Node *u){
	u->setvisited(true);
	cout<<u->getlabel()<<" ";
	for(int i=0;i<G.adjList[u->getlabel()].size();i++){
		if(!G.adjList[u->getlabel()][i].n->getvisited()){
			dfs_visit_scc(G,G.adjList[u->getlabel()][i].n);
		}
	}
	
}

struct nodetime{
	int nodelabel;
	int fintime;
	bool operator<(const nodetime &rhs) const{return fintime<rhs.fintime;}
};

void SCC(Graph &G){
	vector<int> fin=dfs(G);
	vector<nodetime> nodes(G.getno_of_nodes());
	for(int i=0;i<G.getno_of_nodes();i++)
	{
		nodes[i].nodelabel=i;
		nodes[i].fintime=fin[i];
	}	
	sort(nodes.begin(),nodes.end());
	Graph GT=G.transpose();
	cout<<"SCCs:"<<endl;
	while(!nodes.empty()){
		nodetime n=nodes.back();
		nodes.pop_back();
		if(!GT.NodeList[n.nodelabel].getvisited()){
			dfs_visit_scc(GT,&GT.NodeList[n.nodelabel]);
			cout<<endl;
		}
	}	
}

int main(){
	Graph G;
	G.construct();
	G.display();
	SCC(G);
}
