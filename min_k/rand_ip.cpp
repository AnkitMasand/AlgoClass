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
