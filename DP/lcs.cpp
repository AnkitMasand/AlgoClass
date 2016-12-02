#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int main(int argc,char** argv){
	int len1=strlen(argv[1]);
	int len2=strlen(argv[2]);
	int dist[len1+1][len2+1];
	int add=5,del=7,replace=10;
	dist[0][0]=0;	//cost for null string to null string
	for(int i=1;i<=len1;i++)
		dist[i][0]=0;	//some string to null
	for(int i=1;i<=len2;i++)
		dist[0][i]=0;
	for(int i=1;i<=len1;i++)
	{
		for(int j=1;j<=len2;j++){
			if(argv[1][i-1]==argv[2][j-1]){
				//cout<<i<<" "<<j<<" "<<argv[1][i-1]<<" "<<argv[2][j-1]<<endl;
				dist[i][j]=1+dist[i-1][j-1];
			}
			else{
				dist[i][j]=max(dist[i-1][j],dist[i][j-1]);
			}
		}
	}
	for(int i=0;i<=len1;i++)
	{
		for(int j=0;j<=len2;j++)
			cout<<dist[i][j]<<" ";
		cout<<endl;
	}
	int i=len1,j=len2;
	while(i!=0 && j!=0){
		/*if(i==0){
			cout<<"add "<<argv[2][j-1]<<endl;
			j--;
		}
		else if(j==0){
			cout<<"delete "<<argv[1][i-1]<<endl;
			i--;
		}*/
		if(dist[i][j]==1+dist[i-1][j-1] && argv[1][i-1]==argv[2][j-1]){
			cout<<argv[1][i-1];
			i--;j--;
		}
		else if(dist[i][j]==dist[i][j-1]){
			//cout<<"add "<<argv[2][j-1]<<endl;
			j--;
		}
		else if(dist[i][j]==dist[i-1][j]){
			//cout<<"delete "<<argv[1][i-1]<<endl;
			i--;
		}
		/*else if(dist[i][j]==dist[i-1][j-1]+replace){
			cout<<"replace "<<argv[1][i-1]<<" to "<<argv[2][j-1]<<endl;
			i--;j--;
		}*/
	}
	return 0;
}
