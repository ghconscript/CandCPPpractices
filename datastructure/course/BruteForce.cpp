//简单枚举算法
#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
	int BF(string S,string T) {
		int i=0;
		int j=0;
		while(i<=S.size(),j<=T.size()){
			if(S[i]==T[j]){
				++i;
				++j;
			}
			else {i=i-j+1;j=0;}
		}
		if(j>T.size()){
			return i-j+1;
		}else return -1;
	}
};
int main(){
	string S = "abaaba";
	string T = "aba";
	Solution sol;
	cout<<sol.BF(S,T)<<endl;
	return 0;

}
