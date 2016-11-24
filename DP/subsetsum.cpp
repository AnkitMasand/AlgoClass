#include<iostream>
using namespace std;

int main(){
	int sum,n;
	cin>>sum>>n;
	int nos[n];
	for(int i=0;i<n;i++)
		cin>>nos[i];
	bool subset[n+1][sum+1];
	for(int i=1;i<=sum;i++)
		subset[0][i]=false;
	for(int i=0;i<=n;i++)
		subset[i][0]=true;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=sum;j++)
		{
			if(j-nos[i-1]>=0)
				subset[i][j]= subset[i-1][j] || subset[i-1][j-nos[i-1]];
			else
				subset[i][j]=subset[i-1][j];
		}
	}
	if(subset[n][sum]==true)
		cout<<"Subset exists!";
	else
		cout<<"Subset does not exist!";
	cout<<endl<<"Sum of nos:";
	int i=n,j=sum;
	while(i!=0 && j!=0)
	{
		if(subset[i][j]!=subset[i-1][j])
		{
			cout<<nos[i-1]<<" ";
			j-=nos[i-1];
			i--;
		}	
		else
			i--;
	}
	return 0;
}
