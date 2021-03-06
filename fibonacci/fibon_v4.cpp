//Program to calculate F(n) for F(n)=(F(n-1)+F(n-2))mod m
//./fibon_v4 {input_file} {m}
//modified alo for decimal - divide by 10
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<sys/stat.h>
using namespace std;
int A[2][2]={1,1,
	     1,0};
int y[2][2]={1,0,
	     0,1};
int NZero=1;
int pow(short*,int,int);
void MatMul(int (&dest)[2][2],int mat[2][2],int m);
void PowMat(int (&dest)[2][2],int n,int m);
int start=0;
using namespace std;
int main(int argc,char *argv[]){
	int m;
	char cn[1000100];
	int nlen=0;
	char temp;
	ifstream f;
	struct stat buffer1;
	f.open(argv[1],ios::in);
	f>>cn;
	stat(argv[1],&buffer1);
	short n[buffer1.st_size];
	for(int i=0;i<buffer1.st_size;i++){
		if(cn[i]=='\0')
			break;
		else{
			n[i]=cn[i]-'0';
			if(n[i]!=0)
				NZero=0;
			nlen++;
		}
	}
	//cin>>m;
	m=atoi(argv[2]);
	while(n[start]==0)
		start++;
	cout<<pow(n,nlen,m);
	return 0;
}

int pow(short *n,int len,int m){
	int Atemp[2][2];
	while(len-start>0){
		cout<<len<<" "<<n[len-1]<<endl;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
			{
				Atemp[i][j]=A[i][j];
			}
		if(n[len-1]%10!=0)
		{
			PowMat(Atemp,n[len-1],m);
			MatMul(y,Atemp,m);
			cout<<"ymul"<<" "<<y[0][0]<<y[0][1]<<y[1][0]<<y[1][1]<<"\n";
		}
		PowMat(A,10,m);
		//MatMul(A,A,m);
		cout<<"mul"<<" "<<A[0][0]<<A[0][1]<<A[1][0]<<A[1][1]<<"\n";
		len--;//div by 10
	}
	return y[1][0];
}

void MatMul(int (&dest)[2][2],int mat[2][2],int m){
	int temp[2][2];
	temp[0][0]=(dest[0][0]*mat[0][0])+(dest[0][1]*mat[1][0]);	
	temp[0][1]=(dest[0][0]*mat[0][1])+(dest[0][1]*mat[1][1]);
	temp[1][0]=(dest[1][0]*mat[0][0])+(dest[1][1]*mat[1][0]);
	temp[1][1]=(dest[1][0]*mat[0][1])+(dest[1][1]*mat[1][1]);
	dest[0][0]=temp[0][0]%m;
	dest[0][1]=temp[0][1]%m;
	dest[1][0]=temp[1][0]%m;
	dest[1][1]=temp[1][1]%m;
}

void PowMat(int (&dest)[2][2],int n,int m){
	int X[2][2],Aback[2][2];
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
		{
			X[i][j]=dest[i][j];
			Aback[i][j]=dest[i][j];
		}
	MatMul(X,X,m);	//square of matrix
	/*int unit[2][2]={1,0,
			0,1};*/
	cout<<"PowMat:"<<X[0][0]<<X[0][1]<<X[1][0]<<X[1][1]<<"n:"<<n<<endl;
	if(n==1)
		return;
	else if(n%2==1){
		MatMul(dest,X,m);
		n-=3;
	}
	else{
		dest[0][0]=X[0][0]%m;
		dest[0][1]=X[0][1]%m;
		dest[1][0]=X[1][0]%m;
		dest[1][1]=X[1][1]%m;
		n-=2;	
		cout<<"PowMat:"<<dest[0][0]<<dest[0][1]<<dest[1][0]<<dest[1][1]<<endl;
	}
	while(n>0){
		MatMul(dest,X,m);
		n-=2;
		//MatMul(dest,Aback,m);
		cout<<"PowMat:"<<dest[0][0]<<dest[0][1]<<dest[1][0]<<dest[1][1]<<endl;
		//n--;
	}
	cout<<"PowMat:"<<dest[0][0]<<dest[0][1]<<dest[1][0]<<dest[1][1]<<endl;
}
