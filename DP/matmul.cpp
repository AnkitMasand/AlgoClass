#include<iostream>
#include<vector>
using namespace std;

int no_of_mat;

void print(vector<vector<int> > const &s, int i, int j){
	if(i==j){
		cout<<"A"<<i;
	}
	else{
		cout<<"(";
		print(s,i,s[i][j]);
		print(s,s[i][j]+1,j);
		cout<<")";
	}
}

int main(){
	cin>>no_of_mat;
	int P[no_of_mat+1],num;
	for(int i=0;i<=no_of_mat;i++)
		cin>>P[i];
	vector< vector<int> > m(no_of_mat+1,vector<int>(no_of_mat+1));
	vector< vector<int> > t(no_of_mat+1, vector<int>(no_of_mat+1));
	for(int i=1;i<=no_of_mat;i++)
		m[i][i]=0;
	for(int diff=1;diff<no_of_mat;diff++){
		for(int i=1;i<=no_of_mat-diff;i++){
			m[i][i+diff]=99999;
			for(int k=i;k<i+diff;k++){
				num=m[i][k]+m[k+1][i+diff]+(P[i-1]*P[k]*P[i+diff]);
				if(num<m[i][i+diff]){
					m[i][i+diff]=num;
					t[i][i+diff]=k;	
				}
			}
		}
	}
	for(int i=0;i<=no_of_mat;i++){
		for(int j=0;j<=no_of_mat;j++)
			cout<<m[i][j]<<" ";
		cout<<endl;
	}
	for(int i=0;i<=no_of_mat;i++){
		for(int j=0;j<=no_of_mat;j++)
			cout<<t[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl<<"Min no of multiplications:"<<m[1][no_of_mat]<<endl;
	print(t,1,no_of_mat);
	return 0;
}
