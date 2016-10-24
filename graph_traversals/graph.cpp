#define MAXLEN 100
#include<iostream>
using namespace std;
class Node {
	private:
		int label;
		bool visited;
		int no_of_adj;
	public:
		int *adj;
		Node(){
			label=0;
			visited=false;	
			adj=NULL;
			no_of_adj=0;
		}
		Node(int n){
			label=n;
			visited=false;
			adj=NULL;
			no_of_adj=0;
		}
		bool getvisited(){
			return visited;
		}
		int getlabel(){
			return label;
		}
		void setvisited(bool b){
			visited=b;
		}	
		void setlabel(int l){
			label=l;
		}
		void setadjlist(int *adjlist,int adjlen){
			adj=adjlist;	
			no_of_adj=adjlen;
			for(int i=0;i<adjlen;i++)
				cout<<adj[i]<<" "<<adjlist[i]<<endl;
		}
		int getadjno(){
			return no_of_adj;	
		}
		int getadj(int no){
			cout<<adj[no]<<",";
			return adj[no];
		}
		void dispadj(){
			for(int i=0;i<no_of_adj;i++)
				cout<<adj[i]<<" ";
			cout<<endl;
		}	
};

class Graph{
	public:
		Node list[MAXLEN];
		int no_nodes;
		Node start;
		Graph(int n){
			no_nodes=n;
			start=list[0];
		}
		void construct();
		void display();
};

void Graph::construct(){
	int adjno;
	for(int i=0;i<no_nodes;i++){
		cout<<"Adjacent to "<<i<<":"<<endl;
		cin>>adjno;
		int *adjlist=new int[adjno];
		for(int j=0;j<adjno;j++){
			cin>>adjlist[j];
		}
		list[i].setlabel(i);
		list[i].setadjlist(adjlist,adjno);
		list[i].dispadj();
	}
}
void Graph::display(){
	for(int i=0;i<no_nodes;i++){
		cout<<list[i].getlabel()<<":";
		list[i].dispadj();
	}
	//for(int i=0;i<no_nodes;i++){
	//	cout<<i<<":";
	//	cout<<list[i].getlabel();
	//	list[i].dispadj();
		//for(int j=0;j<list[i].getadjno();j++){
		//	cout<<list[i].getadj(j)<<" ";
		//}
		//cout<<endl;
	//}
}
/*
int main()
{	
	Graph G(4);
	G.construct();
	G.display();
	return 0;
}*/
