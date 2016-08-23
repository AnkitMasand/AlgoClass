#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
	for(int i=0;i<100000;i++)
		cout<<rand()%10;
}
