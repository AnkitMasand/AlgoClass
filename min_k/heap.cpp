//Program to construct max heap
#include<iostream>
#include<algorithm>
#define MAXLEN 100000
using namespace std;
class Heap{
	private:
		int A[MAXLEN];
		int last;//enter last eelm here
		void top_down_heapify(int pos);
		void bottom_up_heapify(int pos);
	public:
		Heap(){
			for(int i=0;i<MAXLEN;i++)
				A[i]=0;
			last=0;
		}
		void display();
		void add_elem(int i);
		int delete_max();
		int get_max();
		void decrease_key(int pos,int val);
};

void Heap::display(){
	for(int i=0;i<last;i++)
		cout<<A[i]<<" ";
	cout<<endl;
}

void Heap::decrease_key(int pos,int val){
	A[pos]=val;
	top_down_heapify(pos);
}

int Heap::get_max(){
	return A[0];
}

void Heap::add_elem(int i){
	A[last]=i;
	bottom_up_heapify(last);
	last++;
}

int Heap::delete_max(){
	if(last==0){
		cout<<"Underflow";
		return -1;
	}
	int max=A[0];
	A[0]=A[last-1];
	if(last>0)
		last--;
	top_down_heapify(0);
	return max;
}

void Heap::top_down_heapify(int pos){
	//2i+1 is left child and 2i+2 is right child
	int left=(2*pos)+1;
	int right=(2*pos)+2;
	int max=(A[left]>A[right]?left:right);
	if(right==last)
		max=left;
	else if(left>=last)	//no children;
		return;
	if(A[pos]<A[max]){
		swap(A[pos],A[max]);
		top_down_heapify(max); //the max index is same but now contains 
		//what was previously in pos index which has to be checked 
		//for heapify
	}
}

void Heap::bottom_up_heapify(int pos){
	int root=(pos-1)/2;
	if(root<0)
		return;
	if(A[root]<A[pos]){
		//cout<<A[root]<<endl;
		swap(A[root],A[pos]);
		//cout<<A[root]<<endl;
		bottom_up_heapify(root);
	}
}/*
int main(){
	Heap H;
	char ch;
	int ele;
	while(1){
		cout<<"Choose:"<<endl
		    <<"1. Add"<<endl
		    <<"2. Delete Max"<<endl
		    <<"3. Decrease root"<<endl
		    <<"4. Display"<<endl;
		cin>>ch;
		switch(ch){
		case '1': cin>>ele;	
			  H.add_elem(ele);
			  break;
		case '2': cout<<H.delete_max()<<endl;
			  break;
		case '3': cin>>ele;
			  H.decrease_key(0,ele);
			  break;	
		case '4': H.display();
			  break;
		default: cout<<"Enter valid choice!"<<endl;
			 exit(0);
		}
	}
}*/
