//Program to calculate F(n) for F(n)=(F(n-1)+F(n-2))mod m
//Uses fact that above function is periodic
//./fibon_v5 {input file havin n} {m}
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
int periodic_solve(short*,int,int);
int mod(short*,int,int);
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
	cout<<periodic_solve(n,nlen,m);
	return 0;
}

int periodic_solve(short *n, int len, int m){
	int seq[10*m];
	int a=0;seq[0]=a;	//f(0)
	int b=1;seq[1]=b;	//f(1)
	int c;	
	int i=2;
	int pperiod;	//probable period
	int period;
	while(1){
		c=(a+b)%m;
		seq[i]=c;
		if(c==0){
			pperiod=i;
		}
		else if(pperiod==i-1 && c==1){
			period=pperiod;
			break;
		}
		a=b;
		b=c;
		i++;
	}
	cout<<period<<endl;
	for(int i=0;i<period;i++)
		cout<<i<<":"<<seq[i]<<",";
	cout<<endl;
	return seq[mod(n,period,len)];	
}

int mod(short *n,int period, int len){
	int pcarry=0;
	int carry;
	for(int i=start;i<len;i++)
		cout<<n[i];
	cout<<endl;
	int d;
	for(int i=start;i<len;i++){
		d=(pcarry*10)+n[i];
		carry=d%period;
		n[i]=d/period;	
		pcarry=carry;
	}
	cout<<"carry:"<<carry<<endl;
	return carry;
}
