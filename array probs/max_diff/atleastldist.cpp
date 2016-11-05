//Program to print max(aj-ai) such that j>i+l
#include<iostream>
using namespace std;
int main(){
	int len,l;
	cin>>len;
	cin>>l;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	int i=0;
	int j=l+1;
	int max=A[j]-A[i];
	cout<<"i,j,max:"<<i<<" "<<j<<" "<<max<<endl;
	while(j<len){
		if((A[j]-A[i]) >max){
			max=A[j]-A[i];
			cout<<"max is now:"<<max<<endl;
		}
		if(A[i]>A[j-l])
		{
			i=j-l;	//update min
			cout<<"i is now:"<<i<<endl;
		}
		j++;
	}
	cout<<max;
	return 0;
}
