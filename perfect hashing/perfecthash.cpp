#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#define MIN -999999
#define SIZE 50

using namespace std;

int hash(long long int e, int a,int b, int p,int m){
	long long int x= (a*e)+b;
	x=x%p;
	return (int)x%m;
}

//Bucket class for each bucket in the primary hash table
class Bucket{
	int a;
	int b;
	int m;	//size of sec hash
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
	void add(long long int *ele,int n);
	void display();
};

void Bucket::add(vector<long long int> &ele, int len){
	m=len*len;
	sec.clear();
	sec.assign(m,MIN);	
	int hash_key,flag=0;// flag 0 for starting for loop
	rehash:
	for(int i=0;i<len;i++){
		flag=1;
		hash_key=hash(ele[i],a,b,prime,m);
		if(sec[hash_key]!=MIN)
		{
			a=rand()%prime;
			while(b==a)
				b=rand()%prime;
			sec.clear();
			sec.assign(m,MIN);
			goto rehash;
		}
		sec[hash_key]=ele[i];	
	}	
}

void Table::add(long long int *ele,int n){
	//first primary hash into arrays then verify function
	vector< vector<long long int> > eles (size,vector<long long int>());
	int hash_key,flag=1;
	for(int i=0;i<n;i++){
		hash_key=hash(ele[i],a,b,prime_p,size);
		eles[hash_key].push_back(ele[i]);
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
		add(ele,n);
		return;	
	}
	else{
		pri.assign(size,Bucket());
		for(int i=0;i<size;i++){
			pri[i].add(eles[i],eles[i].size());
		}			
	}
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
	cin>>no_of_elems;
	long long int ele[no_of_elems];
	for(int i=0;i<no_of_elems;i++)
	{
		cin>>ele[i];
	}
	T.add(ele,no_of_elems);
	T.display();
}
