//Program to calculate number with given rank from an array of numbers n
//using random pivot and subsequent partition.In this approach, the array 
//with input of the ranks is sorted and elements corresponding to middle rank 
//is found and then subsequently shorter array passed for rank determination.
//
//./rand_find_v3 < randip1/2/3/4/5
//Generate the input file for IOredirection using rand_ip
//The input should be of format:-
//no of elements in array
//The elements of array
//No of elements whose ranks are to be calculate
//the ranks for which corresponding elements are to be searched
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXLEN 1000000
int len;
using namespace std;

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

int findRank(int *A,int i, int j, int r){
	//pivot is passed as index of the element only!
	int p=i + (rand()%(j-i+1));	//deterministic pivot selection 
	int k=partition(A,i,j,p);
	if(r==(j-k+1))
		return k;
	else if(r<(j-k+1))
		return findRank(A,k+1,j,r);
	else
		return findRank(A,i,k-1,r-j+k-1);
}

void QuickSort(int *A, int l,int r){
	if(l>=r)
		return;
	int p=l+ (rand()%(r-l+1));
	int k=partition(A,l,r,p);
	QuickSort(A,l,k-1);
	QuickSort(A,k+1,r);
}

int main(){
	cin>>len;
	int A[len];
	int ele;
	for(int i=0;i<len;i++)
		cin>>A[i];
	int m;
	cin>>m;	//no of ranks to be calculated
	int ranks[m];
	for(int i=0;i<m;i++)
	{
		cin>>ranks[i];
	}
	QuickSort(ranks,0,m-1);
	int elem_rank[m];	//elements at rank given in array ranks
	int index=findRank(A,0,len-1,ranks[m/2]);
	elem_rank[m/2]=A[index];
	int i=index;
	int B_index=m/2;
	//first left hand side of mid of B ie ranks array
	while(B_index>0)
	{
		B_index--;	
		i=findRank(A,i,len-1,ranks[B_index]);				
		elem_rank[B_index]=A[i];
	}
	//computation for right hand side of mid of B
	B_index=m/2;
	i=index;
	while(B_index<m-1){
		B_index++;
		i=findRank(A,0,i-1,ranks[B_index]-(len-i));
		elem_rank[B_index]=A[i];
	}
	for(int q=0;q<m;q++)
		cout<<ranks[q]<<": "<<elem_rank[q]<<", ";
}
