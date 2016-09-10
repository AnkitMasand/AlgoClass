//Proram to generate random test input for fibonacci problem
//./test_ip {no of digits in n}
#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc, char *argv[]){
	int n_digits=atoi(argv[1]);
	for(int i=0;i<n_digits;i++)
		cout<<rand()%10;
}
