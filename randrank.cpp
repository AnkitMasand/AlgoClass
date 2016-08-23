#include<iostream>
#include<cstdlib>
#define MAXLEN 1000000
int len;
using namespace std;
int partition(int *A,int l,int r, int p){
	int i=l;
	int j=r;
	while(i<j){
		while(A[i]<p)
			i++;
		while(A[j]>p)
			j--;
		if(i<j){
			//cout<<"swapping "<<A[i]<<" "<<A[j]<<endl;
			A[i]+=A[j];
			A[j]=A[i]-A[j];
			A[i]=A[i]-A[j];
			i++; j--;
		}
		//cout<<"i:"<<i<<"j:"<<j<<endl;
	}
	return j;
}
int findRank(int *A,int i, int j, int r){
	int p=A[i+(rand()%(j-i+1))];//RANDOM PIVOT 
	//cout<<"pivot:"<<p<<endl;
	int k=partition(A,i,j,p);
	//cout<<"partition:"<<k<<"i:"<<i<<"j:"<<j<<"r:"<<r<<endl;
	/*for(int l=i;l<=j;l++)
		cout<<A[l]<<" ";*/
	//cout<<endl;
	if(r==(j-k+1))
		return p;
	else if(r<(j-k+1))
		findRank(A,k+1,j,r);
	else
		findRank(A,i,k-1,r-j+k-1);
}
int main(){
	cin>>len;
	int A[len];
	int ele;
	for(int i=0;i<len;i++)
		cin>>A[i];
	int m;
	cin>>m;
	int rank;
	for(int i=0;i<m;i++)
	{
		cin>>rank;
		ele=findRank(A,0,len-1,rank);
		cout<<ele<<endl;
	}
}
