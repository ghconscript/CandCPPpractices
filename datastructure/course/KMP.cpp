#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
void GetNext (string T,vector<int>&next){
	int len=T.size();
	int j=0;
	int k=-1;
	next.push_back(-1);
	while(j<len){
		if(k==-1||T[j]==T[k]){
			j++;
			k++;
			next.push_back(k);
		}else k=next[k];
	}
}
int main(){
	string T = "abaaba";
	vector<int>next;
	GetNext(T,next);
	for(int i=0;i<6;i++){
		cout<<next[i]<<endl;
	}
	return 0;
}
