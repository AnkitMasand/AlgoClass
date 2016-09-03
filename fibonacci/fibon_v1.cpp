//Program to calculate F(n) for F(n)=(F(n-1)+F(n-2))mod m
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
void Divby2(short*,int);
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
	while(NZero!=1){
		if(n[len-1]%2==1)
		{
			MatMul(y,A,m);
			//cout<<"ymul"<<" "<<y[0][0]<<y[0][1]<<y[1][0]<<y[1][1]<<"\n";
		}
		MatMul(A,A,m);
		//cout<<"mul"<<" "<<A[0][0]<<A[0][1]<<A[1][0]<<A[1][1]<<"\n";
		Divby2(n,len);
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

void Divby2(short *n,int len){
	int pcarry=0;
	int carry;
	int zero=1;
	int d;
	for(int i=start;i<len;i++){
		d=(pcarry*10)+n[i];
		carry=(d)%2;
		n[i]=(d)/2;
		pcarry=carry;
		if(n[i]!=0)
			zero=0;
	}
	if(n[start]==0)
		start++;
	NZero=zero;
}
