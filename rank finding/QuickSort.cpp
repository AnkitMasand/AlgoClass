//Program to perform quick sort on elements using randomized pivot
#include<iostream>
#include<algorithm>
using namespace std;

int len;
int partition(int *A,int l,int r, int pi){
	int i=l;
	int p=A[pi];	//pivot p is at pivtindex
	swap(A[pi],A[r]);
	int j=r-1;
	int pivotindex; // pivot p in our case exsists in the array
	while(i<j){
		while(A[i]<p)
			i++;
		while(A[j]>=p)
			j--;
		if(i<j){
			swap(A[i],A[j]);
			i++; j--;
		}
	}
	if(A[j]>=p){
		swap(A[j],A[r]);
	}
	else{
		swap(A[j+1],A[r]);
		j++;
	}
	return j;
}

void QuickSort(int *A,int l,int r){
	if(l>=r)
		return;
	int p=l + (rand()%(r-l+1));
	int k=partition(A,l,r,p);
	QuickSort(A,l,k-1);
	QuickSort(A,k+1,r);
}

int main()
{
	cin>>len;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	QuickSort(A,0,len-1);
	for(int i=0;i<len;i++)
		cout<<A[i]<<" ";
}	
