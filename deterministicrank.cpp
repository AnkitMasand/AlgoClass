#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXLEN 1000000
int len;
using namespace std;
/*void swap(int &no1,int &no2){
	no1=no1+no2;
	no2=no1-no2;
	no1=no1-no2;
}*/
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
		/*if(A[i]==p)
			pivotindex=i;
		if(A[j]==p)
			pivotindex=j;*/
		if(i<j){
			//cout<<"swapping "<<A[i]<<" "<<A[j]<<endl;
			/*A[i]+=A[j];
			A[j]=A[i]-A[j];
			A[i]=A[i]-A[j];*/
			swap(A[i],A[j]);
			i++; j--;
		}
		//cout<<"i:"<<i<<"j:"<<j<<endl;
	}
	swap(A[j+1],A[r]);
	j++;
	/*if j has partition ensure the partition is the pivot element
	if(j!=pivotindex && j!=r){
		swap(A[j+1],A[pivotindex]);
		j++;
	}
	else if(j!=pivotindex && j==r){
		swap(A[j],A[pivotindex]);
	}*/
	return j;
}
int median(int *A,int i,int j){
	if(j-i == 4)
		return (i+2);
	else return (i+((j-i)/2));
}
void bubblesort(int *A,int i,int j){
	int sorted=0;
	cout<<"before sort"<<i<<j<<endl;
	for(int r=i;r<=j;r++)
		cout<<A[r]<<" ";
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
	cout<<"after sort"<<endl;
	for(int r=i;r<=j;r++)
		cout<<A[r]<<" ";
	cout<<flush;
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
		cout<<"doing bubblesort from "<<ptr<<" to"<<endptr<<endl;
		bubblesort(A,ptr,endptr);
		ptr+=5;
		if(j-endptr>0 && j-endptr<5)
			endptr=j;
		else
			endptr+=5;
		cout<<endptr<<flush;
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
	cout<<"rray:"<<endl;
	for(int q=0;q<len;q++)
		cout<<A[q]<<" ";
	cout<<"index"<<index<<endl;
	return goodPivot(A,i,index-1);
}
int findRank(int *A,int i, int j, int r){
	//pivot is passed as index of the element only!
	int p=goodPivot(A,i,j);	//deterministic pivot selection 
	cout<<"pivot:"<<p<<endl;
	int k=partition(A,i,j,p);
	cout<<"partition:"<<k<<"i:"<<i<<"j:"<<j<<"r:"<<r<<endl;
	for(int l=0;l<len;l++)
		cout<<A[l]<<" ";
	cout<<endl;
	if(r==(j-k+1))
		return p;
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
		cout<<ele<<endl;
	}
}
