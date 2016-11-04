#include<iostream>

using namespace std;

int main(){
	int len;	
	cin>>len;
	int a[len];
	for(int i=0;i<len;i++)
		cin>>a[i];
	int c1=0,c2=0,A=-99,B=-99;
	for(int i=0;i<len;i++){
		if(c1>0 && A==a[i])
			c1++;
		else if(c2>0 && B==a[i])
			c2++;
		else if(c1==0){
			c1=1;
			A=a[i];
		}
		else if(c2==0){
			c2=1;
			B=a[i];
		}
		else{
			c1--;
			c2--;
		}
	}
	if(c1!=0)
		cout<<A<<endl;
	else if(c2!=0)
		cout<<B<<endl;
	else
		cout<<"None"<<endl;
	return 0;
}
