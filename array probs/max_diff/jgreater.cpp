//Program to find max(aj-ai) such that j>i
#include<iostream>
using namespace std;
int main(){
	int len;
	cin>>len;		//n of elements in array
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	int max=A[1]-A[0];
	int i=0;
	int j=1;
	while(j<len){
		if((A[j]-A[i])>max){
			max=A[j]-A[i];
		}
		if(A[j]<A[i]){
			i=j;	//update min
		}
		j++;
	}
	cout<<max;
	return 0;
}
