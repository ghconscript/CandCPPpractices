#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef struct{
	double weight;
	int lchild;
	int rchild;
	int parent;
}HTNODE;
typedef HTNODE HuffmanT[51];//表示 “一个包含 51 个HTNODE元素的数组”。
void InitHT(HuffmanT){
	for(int i=0;i<=0;i++){
		//TODO
	}
}
void CreatHT(HuffmanT T){
	int i,p1,p2;
	
}
int main(){
	ifstream inFile;
	int cnt[26]={0};
	int Cnt[26]={0};
	int total=0;
	inFile.open("data.txt");
	char c;
	while(inFile.get(c)){
		if (c >= 'a' && c <= 'z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'a';
			cnt[index]++;  // 对应字母计数+1
			total++;
		}
		if (c >= 'A' && c <= 'Z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'A';
			Cnt[index]++;  // 对应字母计数+1
			total++;
		}
	}
	
}
