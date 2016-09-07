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
	/*for(int l=0;l<len;l++)
		cout<<A[l]<<" ";
	cout<<"swapping j+1 and r:"<<j+1<<" "<<r<<endl;*/
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
	//cout<<"pivot:"<<p<<endl;
	int k=partition(A,i,j,p);
	//cout<<"partition:"<<k<<"i:"<<i<<"j:"<<j<<"r:"<<r<<endl;
	//for(int l=0;l<len;l++)
	//	cout<<A[l]<<" ";
	//cout<<endl;
	if(r==(j-k+1))
		return k;
	else if(r<(j-k+1))
		return findRank(A,k+1,j,r);
	else
		return findRank(A,i,k-1,r-j+k-1);
}
int main(){
	cin>>len;
	int A[len];
	int ele;
	for(int i=0;i<len;i++)
		cin>>A[i];
	int m;
	cin>>m;	//no of ranks to be calculated
	int rank;
	for(int i=0;i<m;i++)
	{
		cin>>rank;
		ele=A[findRank(A,0,len-1,rank)];
		cout<<ele<<" ";
	}
}
