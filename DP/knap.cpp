#include<iostream>
#include<algorithm>	//for max function
using namespace std;

int main(){
	int n,m;
	//cout<<"Size of knapsack:";
	cin>>m;
	//cout<<"Number of items:";
	cin>>n;
	int W[n],P[n];
	//cout<<"Enter weigth and profit for each element:";
	for(int i=0;i<n;i++)
		cin>>W[i]>>P[i];
	int max_prof[n+1][m+1];
	for(int i=0;i<=m;i++)
		max_prof[0][i]=0;
	for(int i=0;i<=n;i++)
		max_prof[i][0]=0;
	for(int i=1;i<=m;i++)
	{
		if(W[0]<=i)
			max_prof[1][i]=P[0];
		else
			max_prof[1][i]=0;
	}
	//now for each ith item
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(j-W[i-1]>=0)
				max_prof[i][j]=max((P[i-1]+max_prof[i-1][j-W[i-1]]),max_prof[i-1][j]);
			else
				max_prof[i][j]=max_prof[i-1][j];
		}
	}
	/*for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
			cout<<max_prof[i][j]<<" ";
		cout<<endl;
	}*/
	//backtracking
	cout<<"Elements in knapsack:";
	int i=n,j=m;
	while(i!=0 && j!=0)
	{
		if(max_prof[i][j]!=max_prof[i-1][j])	//ith item added
		{
			cout<<i<<" ";
			j-=W[i-1];	
			i--;
		}
		else
			i--;	//ith item not added
	}
	cout<<endl<<"max profit:"<<max_prof[n][m];
	return 0;
}
