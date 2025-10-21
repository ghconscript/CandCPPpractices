#include<iostream>
#include<fstream>
#include<string.h>
#define NUM 70
#define MAXPATH 7
#define MAX 500
using namespace std;
//把所有节点依次建立 然后建立一个最小堆 建立最小堆后 依次把最小堆堆顶元素提取出来作为Huffman树的最小节点
typedef struct {
	double weight;
	int lchild;
	int rchild;
	int parent;
} HTNODE;
/*typedef struct {
HTNODE data[NUM];
int n;//有效节点的数量
} MinHeap;*/
typedef struct {
	int index; //存储Huffman树节点的索引 相当于堆的实际内容
	double weight;
}MinHeapNode;
typedef struct{
	MinHeapNode data[NUM];
	int n;
}MinHeap;
typedef HTNODE HuffmanT[2*NUM-1];
void InitHP(MinHeap &M) {//初始化堆
	M.n = 0;
}
void Insert(MinHeap&heap,int index,double weight) {
	if (heap.n >= NUM) {
		cout << "full" << endl;
		return;
	}
	else{
		int i = ++heap.n;
		while ((i != 1) && (weight < heap.data[i / 2].weight)) { //非空且 N比父节点小
			heap.data[i] = heap.data[i / 2]; //把上面的节点下移一个
			i /= 2;
		}
		heap.data[i] = {index,weight};//将N插入指定位置
		
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
int DeleteMin(MinHeap &heap) { //见课件的P121
	int parent = 1, child = 2;
	int min_idx =heap.data[1].index;
	if (heap.n != 0) {
		MinHeapNode tmp = heap.data[heap.n--];
		 //取出最后一个数 存入tmp再删除之
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
		return min_idx;
	}
}
void CreatHT(HuffmanT T, int cnt[]) {//生成Huffman树
	int p1, p2;
	MinHeap H;
	InitHT(T);
	InitHP(H);
	InputW(T, cnt);
	int leaf_cnt = 0;//叶子节点个数
	
	for (int i = 0; i <= NUM - 1; i++) {
		if(T[i].weight>0){
			Insert(H,i,T[i].weight);//建立最小堆
			leaf_cnt++;
		}
	}
	int total_cnt= (leaf_cnt)*2-1;
	for (int i = leaf_cnt; i < total_cnt; i++) {
		p1 = DeleteMin(H);
		p2 = DeleteMin(H);
		T[p1].parent = i;
		T[p2].parent = i;
		T[i].lchild = p1;
		T[i].lchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight;
		Insert(H,i,T[i].weight);
	}

}
char** Code(HuffmanT T ,int leaf_cnt) {
	char** codes = (char**)malloc(leaf_cnt * sizeof(char*));
	int idx = 0;
	for (int i = 0; i < NUM; i++) {
		// 只处理叶子节点（原错误：对所有节点生成编码，包括中间节点）
		if (T[i].lchild == -1 && T[i].rchild == -1 && T[i].weight > 0) {
			char path[MAXPATH] = {0};
			char code[MAXPATH] = {0};
			int len = 0;
			int cur = i;
			int parent = T[cur].parent;
			
			// 回溯到根节点（原错误：终止条件parent != 1改为parent != -1）
			while (parent != -1) {
				if (T[parent].lchild == cur) {
					path[len++] = '0';
				} else {
					path[len++] = '1';
				}
				cur = parent;
				parent = T[cur].parent;
			}
			
			// 反转路径
			for (int j = 0; j < len; j++) {
				code[j] = path[len - 1 - j];
			}
			code[len] = '\0';
			
			codes[idx] = (char*)malloc((len + 1) * sizeof(char));
			strcpy(codes[idx], code);
			idx++;
		}
	}
	return codes;
}
int main() {
	ifstream inFile;
	int cnt[NUM] = {0};
	int total = 0;
	int idx;
	inFile.open("data.txt");
	char c;
	while (inFile.get(c)) {
		if (c >= 'a' && c <= 'z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'a';
			cnt[index]++;  // 对应字母计数+1
			total++;
		}else if (c >= 'A' && c <= 'Z') {
			// 计算对应下标（例如 'a' - 'a' = 0，'b'-'a'=1 ...）
			int index = c - 'A' + 26;
			cnt[index]++;  // 对应字母计数+1
			total++;
		}else if(strchr(".,;!?\"'()", c)){
			int p_idx = 52 + strchr(".,;!?\"'()", c) - ".,;!?\"'()";  // 52-60
			cnt[p_idx]++;
			total++;
		}else if (c >= '0' && c <= '9') {  
			int num_idx = 61 + (c - '0');  // 数字0-9：索引60-69
			if (num_idx < NUM) cnt[num_idx]++;
		}
	}
	inFile.close();
	int leaf_cnt = 0;
	for (int i = 0; i < NUM; i++) {
		if (cnt[i] > 0) leaf_cnt++;
	}
	HuffmanT T;//节点数组
	CreatHT(T, cnt);
	char** codes = Code(T, leaf_cnt);
	idx = 0;  // 用于遍历编码数组
	cout << "字符编码表：" << endl;
	for (int i = 0; i < NUM; i++) {
		if (T[i].lchild == -1 && T[i].rchild == -1 && T[i].weight > 0) {
			if (i < 26) cout << (char)('a' + i) << "：";
			else if (i < 52) cout << (char)('A' + i - 26) << "：";
			else cout << "标点" << (i - 52) << "(" << ".,;!?\"'()"[i-52] << ")：";
			cout << codes[idx++] << endl;
		}
	}
	
	// 释放内存
	for (int i = 0; i < leaf_cnt; i++) {
		free(codes[i]);
	}
	free(codes);
	
	return 0;



}
