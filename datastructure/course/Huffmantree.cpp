#include<iostream>
#include<fstream>
#include<string.h>
#define NUM 52
#define MAXPATH 6
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
void InitHP(MinHeap &M) {//初始化堆
	M.n = 0;
}
void Insert(MinHeap&heap, HTNODE &N) {
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
		heap.n++;
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
HTNODE DeleteMin(MinHeap &heap) { //见课件的P121
	int parent = 1, child = 2;
	HTNODE elem, tmp;
	if (heap.n != 0) {
		elem = heap.data[1];
		tmp = heap.data[heap.n--]; //取出最后一个数 存入tmp再删除之
		while (child <= heap.n) {
			if ((child < heap.n) && (heap.data[child].weight > heap.data[child + 1].weight)) {
				child ++;//找孩子的小者
			}
			if (tmp.weight <= heap.data[child].weight) {
				break;//若tmp小于当前子节点child的值 就可以把tmp放入现在的这个parent
			}
			//如果tmp大于这个数字 就需要将较小子节点的值上移到parent的位置 child移动到新paren的左孩子
			heap.data[parent] = heap.data[child];
			parent = child;
			child *= 2;
		}
		heap.data[parent] = tmp;
		return elem;
	}
}
void CreatHT(HuffmanT T, int cnt[]) {
	int p1, p2;
	MinHeap H;
	InitHT(T);
	InitHP(H);
	InputW(T, cnt);
	for (int i = 0; i <= NUM - 1; i++) {
		Insert(H, T[i]);
		//建立最小堆
	}
	for (int i = H.n; i < 2 * (H.n) -1; i++) {
		p1 = DeleteMin(H).weight;
		p2 = DeleteMin(H).weight;
		T[p1].parent = i;
		T[p2].parent = i;
		T[i].lchild = p1;
		T[i].lchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight;
		Insert(H, T[i]);
	}

}
char** Code(HuffmanT T) {
	int cur, parent;
	char path[MAXPATH];
	char code[MAXPATH];
	int len = 0;
	char** codes = (char**)malloc(NUM * sizeof(char*));
	for (int i = 0; i < NUM; i++) {
		cur = i;
		parent = T[cur].parent;
		while(parent != 1){
			if(T[parent].lchild==cur){
				path[len++]='0';
			}else{
				path[len++]='1';
			}
			cur = parent;
			parent = T[cur].parent;
		}
		for (int j = 0; j < len; j++) {
			code[j] = path[len - 1 - j];  // 反转
		}
		code[len] = '\0';  // 字符串结束符
		codes[i]=(char*)malloc((len+1)*sizeof(char));
		strcpy(codes[i],code);
	}	
	return codes;
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
	HuffmanT T;//节点数组
	CreatHT(T, cnt);
	for(int i=0;i<=NUM;i++){
		cout<<Code(T)<<endl;
	}



}
