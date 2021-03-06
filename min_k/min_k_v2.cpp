//Program to calculate minimum k elements given n numbers.
//This version uses deterministic pivot to divide array of 2*k into k size and
//then reiterate after adding next k elements.
//
//Method to run:
//./min_k_v2 < randip1/2/3/4
//Generate the random input using ./rand_ip {n} {k} > randip1/2/3/4
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
int median(int *A,int i,int j){
	if(j-i == 4)
		return (i+2);
	else return (i+((j-i)/2));
}
void bubblesort(int *A,int i,int j){
	int sorted=0;
	for(int q=i;q<=j& sorted==0;q++)
	{
		sorted=1;
		for(int w=i;w<j;w++){
			if(A[w]>A[w+1])
			{
				swap(A[w],A[w+1]);
				sorted=0;
			}	
		}
	}
}
int goodPivot(int *A,int i,int j){
	//bubblesort 5 elements ie n/5 partitions
	if(j-i<5){
		bubblesort(A,i,j);
		return median(A,i,j);
	}
	int ptr=i;
	int endptr=i+4;//5 elems..this would be accessd
	while(endptr<=j){
		bubblesort(A,ptr,endptr);
		ptr+=5;
		if(j-endptr>0 && j-endptr<5)
			endptr=j;
		else
			endptr+=5;
	}
	int index=i;
	int median_index;
	ptr=i;
	endptr=i+4;
	while(endptr<=j){
		median_index=median(A,ptr,endptr);
		swap(A[index],A[median_index]);
		ptr+=5;
		if(endptr+5>j && endptr!=j)
			endptr=j;
		else
			endptr+=5;
		index++;
	}
	return goodPivot(A,i,index-1);
}
int findRank(int *A,int i, int j, int r){
	//pivot is passed as index of the element only!
	int p=goodPivot(A,i,j);	//deterministic pivot selection 
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
		index=findRank(A,0,len-1,k);
		if(ele_no==n)
			break;
		for(int i=index;i<len;i++){
			if(ele_no==n)
				break;
			cin>>A[i];
			ele_no++;
		}
		//for(int i=0;i<k;i++)
		//	cout<<A[i]<<" ";
		//cout<<endl;
	}
	for(int i=0;i<k;i++)
		cout<<A[i]<<" ";
	return 0;
}
