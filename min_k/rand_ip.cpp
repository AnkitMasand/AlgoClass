//Program to generate random input for min_k problems:
//Run using ./rand_ip {n} {k} > randip1/2/3/4/5...
#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc,char *argv[])
{	
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	cout<<n<<endl;
	cout<<k<<endl;
	for(int i=0;i<n;i++)
		cout<<rand()<<" ";
	return 0;
}
