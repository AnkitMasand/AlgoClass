#include<iostream>
#include<algorithm>
#include "graph.h"
#include<vector>
using namespace std;


int shortest(Graph &G,int node_no){
	int pi[G.getno_of_nodes()];
	for(int i=0;i<G.getno_of_nodes();i++)
		pi[i]=-1;
	char ch;
	//G.display();
	//priority_queue<Node*, vector<Node*>, GreaterThanPrio> trav;
	vector<Node*> trav;
	//Node *st=G.start;
	//Node s=*st;
	cout<<G.NodeList[node_no].getlabel()<<endl;
	//Adj a={&G.NodeList[node_no],0,0};
	trav.push_back(&G.NodeList[node_no]);
	//G.NodeList[0].setvisited(true);
	pi[G.NodeList[node_no].getlabel()]=-1;
	G.NodeList[node_no].prio=0;
	int prev_node=-1;	//fr start node
	while(!trav.empty()){
		Node *u=trav.front();
		//cout<<trav.front().getlabel()<<":"<<trav.front().getadjno()<<endl;
		pop_heap(trav.begin(),trav.end(),comp);
		trav.pop_back();
		if(!u->getvisited()){
		u->setvisited(true);
		//pi[u->getlabel()]=prev_node;
		//cout<<u->getlabel()<<" :-"<<G.adjList[u->getlabel()].size()<<endl;
		for(int i=0;i<G.adjList[u->getlabel()].size();i++){
			//cout<<G.adjList[u->getlabel()][i]->getlabel()<<endl;
			if(!G.adjList[u->getlabel()][i].n->getvisited()){
				//Adj a={G.adjList[u.n->getlabel()][i].n,0,u.prio+G.adjList[u.n->getlabel()][i].weight};
				if(G.adjList[u->getlabel()][i].n->prio>(u->prio+G.adjList[u->getlabel()][i].weight)){
					//trav.push(a);
					G.adjList[u->getlabel()][i].n->prio = u->prio + G.adjList[u->getlabel()][i].weight;
					if(pi[G.adjList[u->getlabel()][i].n->getlabel()]==-1){	//if node is not yet explored
						trav.push_back(G.adjList[u->getlabel()][i].n);
						push_heap(trav.begin(),trav.end(),comp);
					}
					else
						make_heap(trav.begin(),trav.end(),comp);
					pi[G.adjList[u->getlabel()][i].n->getlabel()]=u->getlabel();
				}
			}
		}
		cout<<u->getlabel()<<" "<<u->prio<<endl;
		prev_node=u->getlabel();
		}
	}
	for(int i=0;i<G.getno_of_nodes();i++){
		cout<<pi[i]<<" ";
	}
}

int main(){
	Graph G;
	G.construct();
	G.display();
	shortest(G,0);
	return 0;
}
