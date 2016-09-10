//Program to find max(aj-ai) such that j<=i+l
#include<iostream>
#include<deque>
using namespace std;
//Requires two deques -  one for max element in the window
//other for min element.
int main(){
	int len,l;
	cin>>len>>l;
	int A[len];
	for(int i=0;i<len;i++)
		cin>>A[i];
	deque<int> MinQ;	//deque of indices
	int i=0;
	int max=A[1]-A[0];
	/*while(i<l){
		if(!MinQ.empty() && A[i]<=MinQ[back]{
			MinQ.pop_back();
		}
		MinQ.push_back(i);
		i++;
	}*/
	
	while(i<len)
	{
		//if((i-l)>=0)
		//	cout<<A[MinQ.front()]<<" ";
		while(!MinQ.empty() && A[i]<=A[MinQ.back()]){
			MinQ.pop_back();
		}
		if(!MinQ.empty() && MinQ.front()<=(i-l)){
			MinQ.pop_front();	//element out of l length
		}
		MinQ.push_back(i);
		if((i-l)>=-1){
			if((A[i]-A[MinQ.front()])>max)
				max=A[i]-A[MinQ.front()];
		}
		i++;
	}
	cout<<max;
}
