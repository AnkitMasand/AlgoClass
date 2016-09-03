#include<iostream>
#include<algorithm>
using namespace std;

int len;
int partition(int *A,int l,int r,int p){
	int i=l;
	int j=r;
	if((r-l)==1){
		if(A[l]>A[r])
			swap(A[l],A[r]);
		return l;
	}
	while(i<j){
		while(A[i]<=p)
			i++;
		while(A[j]>p)
			j--;
		if(i<j)
		{
			swap(A[i],A[j]);
			i++;
			j--;
		}
	}
	return j;	
}

void QuickSort(int *A,int l,int r){
	if(l>=r)
		return;
	int p=A[l + (rand()%(r-l+1))];
	cout<<"pivot:"<<p<<endl;
	int k=partition(A,l,r,p);
	if(k==r){ 	//check if all elements same!
		int flag=0;
		for(int i=l;i<r;i++)
			if(A[i]!=A[i+1])
				flag=1;
		if(flag==0)
			return;
	}
	cout<<"after partition:"<<l<<" "<<r<<endl;
	for(int i=0;i<len;i++)
		cout<<A[i]<<" ";
	QuickSort(A,l,k);
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
