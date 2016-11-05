//Program to find max(aj-ai) such that j<=i+l
#include<iostream>
#include<deque>
using namespace std;
//Requires deque to keep track of minimum.
//Every new j seen, the front of deque checkd to keep track of only elements in window
//if new j seen is smaller tha previous elements, the previous elements are useless!
int main(){
	int len,l;
	cin>>len>>l;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	deque<int> MinQ;	//deque of indices
	int i=0;
	while(i<len)
	{
		if((i-l)>=0)
			cout<<A[MinQ.front()]<<" ";
		while(!MinQ.empty() && A[i]<=A[MinQ.back()]){
			MinQ.pop_back();
		}
		if(!MinQ.empty() && MinQ.front()<=(i-l)){
			MinQ.pop_front();	//element out of l length
		}
		MinQ.push_back(i);
		i++;
	}
	cout<<A[MinQ.front()];
}
