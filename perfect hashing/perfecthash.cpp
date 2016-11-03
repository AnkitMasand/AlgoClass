#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<string>
#define MIN -999999
#define SIZE 1502

using namespace std;

int hashh(long long int e, int a,int b, int p,int m){
	long long int x= (a*e)+b;
	x=x%p;
	return (int)x%m;
}

//Bucket class for each bucket in the primary hashh table
class Bucket{
	int a;
	int b;
	int m;	//size of sec hashh
	int prime;
	vector<long long int> sec;
   public:
	Bucket(){
		prime=991;
		a=rand()%prime;
		b=rand()%prime;
		while(b==a)
			b=rand()%prime;	//to ensure different a and b	
		m=0;	//size 0 initially
	}
	void add(vector<long long int> &ele,int len);
	void display();
};

class Table{
	vector<Bucket> pri;
	int a;
	int b;
	int size;
	int prime_p;
   public:
	Table(){
		pri.assign(SIZE,Bucket());
		prime_p=997;;
		a=rand()%prime_p;
		b=rand()%prime_p;
		while(b==a)
			b=rand()%prime_p;
		size=SIZE;	
	}
	void add(char *filenm,int n);
	void display();
};

void Bucket::add(vector<long long int> &ele, int len){
	m=len*len;
	sec.clear();
	sec.assign(m,MIN);	
	int hashh_key,flag=0;// flag 0 for starting for loop
	rehashh:
	for(int i=0;i<len;i++){
		flag=1;
		hashh_key=hashh(ele[i],a,b,prime,m);
		if(sec[hashh_key]!=MIN)
		{
			a=rand()%prime;
			while(b==a)
				b=rand()%prime;
			sec.clear();
			sec.assign(m,MIN);
			goto rehashh;
		}
		sec[hashh_key]=ele[i];	
	}	
}

void Table::add(char *filenm,int n){
	fstream fp(filenm,ios::in);
	//first primary hashh into arrays then verify function
	vector< vector<long long int> > eles (size,vector<long long int>());
	int hashh_key,flag=1;
	long long int ele;
	string str;
	for(int i=0;i<n;i++){
		fp>>str;
		cout<<str;
		ele=stoll(str);		
		hashh_key=hashh(ele,a,b,prime_p,size);
		eles[hashh_key].push_back(ele);
	}
	for(int i=0;i<n;i++)
	{
		if((2*n)< (eles[i].size() * eles[i].size()))
		{
			flag=0;
			break;
		}
	}
	if(flag==0){
		a=rand()%prime_p;
		while(b==a)
			b=rand()%prime_p;
		fp.close();
		add(filenm,n);
		return;	
	}
	else{
		pri.assign(size,Bucket());
		for(int i=0;i<size;i++){
			pri[i].add(eles[i],eles[i].size());
		}			
	}
	fp.close();
}

void Bucket::display(){
	for(int i=0;i<sec.size();i++)
		cout<<sec[i]<<" ";
}

void Table::display(){
	for(int i=0;i<pri.size();i++)
	{
		cout<<i<<":";
		pri[i].display();
		cout<<endl;
	}	
}		

int main(int argc, char *argv[]){
	Table T;
	int no_of_elems;
	no_of_elems=atoi(argv[1]);
	T.add(argv[2],no_of_elems);
	T.display();
}
