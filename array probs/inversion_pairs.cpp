//Program to count no of inversion pairs
#include<iostream>
using namespace std;
//int ip_no=0;	//number of inversion pairs
int MergeSort(int *A,int l, int r);
int MergeIP(int *A,int l,int k,int r);
int main(){
	int len;
	cin>>len;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	cout<<endl<<"Inv count is:"<<MergeSort(A,0,len-1)<<endl;
	for(int i=0;i<len;i++)
		cout<<A[i]<<" ";
	return 0;
}

int MergeSort(int *A, int l, int r){
	int inv_count=0;
	if(l==r)
		return 0;
	if(l<r){
		int k=(l+r)/2;
		cout<<"Merge sort"<<l<<" "<<k<<endl;
		inv_count+=MergeSort(A,l,k);
		cout<<"Merge sort"<<k+1<<" "<<r<<endl;
		inv_count+=MergeSort(A,k+1,r);
		cout<<"Merge Ip"<<endl;
		inv_count+=MergeIP(A,l,k,r);
		return inv_count;
	}
}

int MergeIP(int *A,int l, int mid, int r){
	int inv_count=0;
	int i=l,j=mid+1,k=0;
	int temp[r-l+1];
	cout<<"Merging from :"<<l<<" "<<mid<<" "<<r<<endl;
	for(int q=l;q<=r;q++)
		cout<<A[q]<<" ";
	cout<<endl;
	while(i<=mid && j<=r){
		if(A[i]<=A[j]){
			temp[k]=A[i];
			cout<<"1.temp["<<k<<"] is "<<A[i]<<endl;
			k++;i++;
		}
		else{
			temp[k]=A[j];
			cout<<"2.temp["<<k<<"] is "<<A[j]<<endl;
			k++;j++;
			inv_count+=(mid-i+1);
		}
	}	
	while(i<=mid)
	{
		temp[k]=A[i];
		k++;i++;
		cout<<"3.temp["<<k<<"] is "<<A[i]<<endl;
	}
	while(j<=r)
	{
		temp[k]=A[j];
		k++;j++;
		cout<<"4.temp["<<k<<"] is "<<A[j]<<endl;
	}
	k=0;
	for(int q=l;q<=r;q++)
		A[q]=temp[k++];
	for(int q=l;q<=r;q++)
		cout<<A[q]<<" ";
	return inv_count;
}
