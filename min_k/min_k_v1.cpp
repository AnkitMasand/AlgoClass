#include<iostream>
#include<fstream>
#include "heap.h"
using namespace std;

int main(){
	Heap H;
	int elem_count=0;	//0 elements scanned
	int ele;
	int n;//no of elements
	int k;
	cin>>n;
	cin>>k;
	while(elem_count<k){
		cin>>ele;
		H.add_elem(ele);
		elem_count++;
	}	//loop over when elem scanned=k
	//for every next element, add to heap only if elem<max of heap
	while(elem_count<n){
		cin>>ele;
		if(ele<H.get_max()){
			H.decrease_key(0,ele);
		}
		elem_count++;
	}
	cout<<"Min elements:"<<endl;
	H.display();
	return 0;
}
