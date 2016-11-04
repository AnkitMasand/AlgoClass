#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<string>
#define MIN -999999

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
		prime=6700417;
		a=rand()%prime;
		b=rand()%prime;
		while(b==a)
			b=rand()%prime;	//to ensure different a and b	
		m=0;	//size 0 initially
	}
	int add(vector<long long int> &ele,int len);
	void display();
	void lookup(long long int);
	void diff1();
};

class Table{
	vector<Bucket> pri;
	int a;
	int b;
	int size;
	int prime_p;
   public:
	Table(int Size){
		pri.assign(Size,Bucket());
		prime_p=2147483647;;
		a=rand()%prime_p;
		b=rand()%prime_p;
		while(b==a)
			b=rand()%prime_p;
		size=Size;	
	}
	void add(char *filenm,int n);
	void display();
	void lookup(long long int);
	void diff1();
};

void Table::diff1(){
	for(int i=0;i<size;i++){
		pri[i].diff1();
	}
}

void Bucket::diff1(){
	for(int i=0;i<m;i++){
		if(sec[i]!=MIN){
			for(int j=0;j<m;j++)
			{
				if(sec[j]==(sec[i]+1))
					cout<<sec[i]<<" and "<<sec[j]<<endl;
			}
		}
	}	
}
	
void Bucket::lookup(long long int val){
	if(m==0)
	{
		cout<<"Element not found!"<<endl;
		return;
	}
	int hashkey=hashh(val,a,b,prime,m);
	cout<<"sec hash:"<<hashkey<<" "<<m<<endl;
	if(sec[hashkey]==val)
		cout<<"Element found in location :"<<hashkey<<" of secondary hash table"<<endl;
	else
		cout<<"Element not found in secondary hash!"<<endl;
}

void Table::lookup(long long int val){
	int hashkey=hashh(val,a,b,prime_p,size);
	cout<<"Primary hash to bucket number:"<<hashkey<<endl;
	if(hashkey<0){
		cout<<"Element not found!"<<endl;
		return;
	}
	pri[hashkey].lookup(val);
}

int Bucket::add(vector<long long int> &ele, int len){
	m=len*len;
	sec.clear();
	sec.assign(m,MIN);	
	int hashh_key,flag=0;// flag 0 for starting for loop
	for(int i=0;i<len;i++){
		flag=1;
		hashh_key=hashh(ele[i],a,b,prime,m);
		if(sec[hashh_key]!=MIN)
		{
			cout<<"elem present:"<<sec[hashh_key]<<" nd to be hadshd:"<<ele[i]<<" "<<a<<" "<<b<<" "<<m<<endl;
			if(sec[hashh_key]==ele[i]){
				cout<<"repetition:"<<ele[i]<<endl;
				continue;
			}
			a=rand()%prime;
			b=rand()%prime;
			while(b==a)
				b=rand()%prime;
			cout<<"need to rehash!"<<endl;
			//sec.assign(m,MIN);
			return -1;
		}
		sec[hashh_key]=ele[i];	
	}
	return 0;	
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
		cout<<i<<" ";
		ele=stoll(str);		
		hashh_key=hashh(ele,a,b,prime_p,size);
		eles[hashh_key].push_back(ele);
	}
	cout<<"finished reading!"<<endl;
	long sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=(eles[i].size() * eles[i].size());
	}
	if((2*n) < sum){
		flag=0;
		cout<<"rehash pri"<<endl;
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
		int status;
		pri.assign(size,Bucket());
		for(int i=0;i<size;i++){
			cout<<"adding to bucket no:"<<i<<endl;
			status=pri[i].add(eles[i],eles[i].size());
			while(status==-1)
				status=pri[i].add(eles[i],eles[i].size());
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
	int no_of_elems;
	no_of_elems=atoi(argv[1]);
	Table T(no_of_elems);
	T.add(argv[2],no_of_elems);
	//T.display();
	cout<<"Elemenets to be searched:"<<endl;
	long long int key;
	for(int i=0;i<2;i++)
	{
		cin>>key;
		T.lookup(key);
	}
	cout<<"Pairs with diff 1:"<<endl;
	T.diff1();
	return 0;
}
