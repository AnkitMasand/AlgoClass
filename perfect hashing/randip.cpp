//Program to generate input file for rank finding problem
//./randip {no of elements in array} > randip1/2/3/4/5
#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc,char *argv[]){
	int n=atoi(argv[1]);
	cout<<n<<endl;
	for(int i=0;i<n;i++){
		cout<<rand()<<" ";
	}
	cout<<endl;
}
