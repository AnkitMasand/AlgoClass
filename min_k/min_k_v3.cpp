//Program to find min k elements given n numbers.
//Uses random partition and also for each iteration when partitioned to right
//of k, finds rank for n1-k and substitutes n1-k elements and reiterates.
//
//Method to run: similar as earlier version
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
	int p=i+ (rand()%(j-i+1));	//random pivot
	int k=partition(A,i,j,p);
	if(r==(j-k+1))
		return k;
	else if(r<(j-k+1))
		return findRank(A,k+1,j,r);
	else
		return findRank(A,i,k-1,r-j+k-1);
}
int main(){
	//len = 2*k ie if k elements are to be found 
	int n,k;
	cin>>n>>k;
	len=(2*k);
	int A[len];
	int index;
	int ele_no=0;	//no of elements scanned
	for(int i=0;i<len;i++){
		cin>>A[i];
		ele_no++;
	}//2k elements scanned, ele_no=2k
	while(ele_no <= n)
	{
		int p= (rand()%(len-1));	
		//cout<<"pivot:"<<A[p];
		int n1=partition(A,0,len-1,p);
		if(n1>k)
		{
			if(ele_no==n)
				break;
			index=findRank(A,0,n1,n1-k);
			for(int i=index;i<len;i++){
				if(ele_no==n)
					break;
				cin>>A[i];
				ele_no++;
			}
		}
		else
			continue;
	}
	for(int i=0;i<k;i++)
		cout<<A[i]<<" ";
	return 0;
}
