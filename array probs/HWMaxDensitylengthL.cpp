//Program to find subarray with max density with atleast length l
#include<iostream>
using namespace std;
int main(){
	int len;
	int l;
	cin>>len>>l;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	//first calculate sums array /O(n)
	int sums[len+1];
	sums[0]=0;
	for(int i=1;i<=len;i++){
		sums[i]=sums[i-1]+A[i];
	}
	//sum[1]=A[0], sum[2]=A[0]+A[1] ie sum of first 2 elements
	int max=sums[l];//A[0] to A[l-1] sums
	int nos=l;
	float max_den=max/nos;
	int i=0;
	int j=l+1;
	int temp_sum;
	int temp_nos;
	while(j<len){
		temp_sum=sums[j]-sums[i];
		temp_nos=(j-i);
		if(((float)temp_sum/(float)(temp_nos))>max_den){
			max=temp_sum;
			nos=temp_nos;
			max_den=(float)temp_sum/(float)(temp_nos);
		}	
		if(sums[j-l]<sums[i])
			i=j-l;
		j++;
	}
	cout<<max<<" "<<nos<<" "<<max_den;
	return 0;
}
