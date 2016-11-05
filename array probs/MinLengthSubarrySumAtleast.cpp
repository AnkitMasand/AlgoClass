#include<iostream>

using namespace std;
	
int main(){
	int len;
	cout<<"lemngth:"<<endl;
	cin>>len;
	int nos[len];
	cout<<"array:"<<endl;
	for(int i=0;i<len;i++)
		cin>>nos[i];
	int max_sum;
	cout<<"sum atleast s";
	cin>>max_sum;
	int sum=0,minlen=len;
	int l=0,r=0;
	while(r<len){
		sum+=nos[r];
		if(sum>max_sum){
			if(minlen>(r-l))
				minlen=(r-l);
			sum-=nos[l++];
		}
		r++;
	}
	cout<<endl<<minlen;
	return 0;
}
