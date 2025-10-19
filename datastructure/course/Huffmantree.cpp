#include<iostream>
#include<fstream>
#include<string>
#define NUM 52
using namespace std;
//把所有节点依次建立 然后建立一个最小堆 建立最小堆后 依次把最小堆堆顶元素提取出来作为Huffman树的最小节点
typedef struct {
	double weight;
	int lchild;
	int rchild;
	int parent;
} HTNODE;
typedef struct {
	HTNODE data[NUM];
	int n;//有效节点的数量
} MinHeap;
typedef HTNODE HuffmanT[NUM];//表示 “一个包含 51 个HTNODE元素的数组”。
void InitHP(MinHeap M) {
	M.n = 0;
}
void Insert(MinHeap&heap, HTNODE N) {
	int i;
	if (heap.n >= 52) {
		cout << "full" << endl;
		return;
	} else {
		i = heap.n + 1;
		while ((i != 1) && (N.weight < heap.data[2 / i].weight)) { //非空且 N比父节点小
			heap.data[i] = heap.data[2 / i]; //把上面的节点下移一个
			i /= 2;
		}
		heap.data[i] = N;//将N插入指定位置
	}
}
void InitHT(HuffmanT T) {
	for (int i = 0; i <= NUM - 1; i++) {
		T[i] = {0, -1, -1, -1};
	}
}
void InputW(HuffmanT T, int cnt[]) {
	for (int i = 0; i <= NUM - 1; i++) {
		T[i].weight = cnt[i];
	}
}
void CreatHT(HuffmanT T, int cnt[]) {
	int i, p1, p2;
	InitHT(T);
	InputW(T, cnt);
}
HTNODE DeleteMax(MinHeap &heap){//见课件的P121
	int parent =1 ,child=2;
	HTNODE elem,tmp;
	if(heap.n!=0){
		elem = heap.data[1];
		tmp=heap.data[heap.n--];
		while(child<=heap.n){
			
		}
		
	}
	
}
void SelectMin(HuffmanT T){
	
}
int main() {
	ifstream inFile;
	int cnt[52] = {0};
	int total = 0;
	inFile.open("data.txt");
	char c;
	while (inFile.get(c)) {
		if (c >= 'a' && c <= 'z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'a';
			cnt[index]++;  // 对应字母计数+1
			total++;
		}
		if (c >= 'A' && c <= 'Z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'A' + 26;
			cnt[index]++;  // 对应字母计数+1
			total++;
		}
	}

}
