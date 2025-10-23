#include<iostream>
#include<fstream>
#include<string.h>
#define NUM 70
#define MAXPATH 7
#define MAXCODE 100
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
void countFrequency(const char* filename, int count[], int& total, int& m, char chars[]) {
	memset(count, 0, sizeof(int)*128);
	total = 0;
	m = 0;
	
	ifstream fin(filename, ios::binary);
	if (!fin) {
		cerr << "无法打开文件: " << filename << endl;
		exit(1);
	}
	
	char c;
	while (fin.get(c)) {  // 逐个读取字符(包括所有ASCII字符)
		count[(unsigned char)c]++;  // 处理无符号字符
		total++;
	}
	fin.close();
	
	// 收集所有出现过的字符
	for (int i = 0; i < 128; i++) {
		if (count[i] > 0) {
			chars[m++] = (char)i;
		}
	}
}
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
	const char* originalFile = "original.txt";    // 原文件
	const char* compressedFile = "compressed.bin";// 压缩文件
	const char* decodedFile = "decoded.txt";      // 解压文件
	
	int count[128], totalChars, m;
	char chars[NUM];
	char code[128][MAXCODE] = {0};
	
	// 1. 统计字符频率
	countFrequency(originalFile, count, totalChars, m, chars);
	cout << "1. 字符频率统计完成" << endl;
	cout << "   不同字符数: " << m << ", 总字符数: " << totalChars << endl;
	
	// 2. 构建哈夫曼树
	HuffmanT ht;
	for (int i = 0; i < m; i++) {
		ht[i].weight = count[(unsigned char)chars[i]] / (double)totalChars;
		ht[i].lchild = ht[i].rchild = ht[i].parent = -1;
	}
	MinHeap heap;
	InitHP(heap, ht, m);
	buildHuffmanTree(ht, heap, m);
	cout << "2. 哈夫曼树构建完成" << endl;
	
	// 3. 生成哈夫曼编码并显示
	generateHuffmanCode(ht, m, chars, code);
	cout << "3. 哈夫曼编码生成完成" << endl;
	cout << "   编码表如下:" << endl;
	for (int i = 0; i < m; i++) {
		char c = chars[i];
		cout << "   '";
		if (c == ' ') cout << "空格";
		else if (c == '\n') cout << "换行";
		else if (c == '\t') cout << "制表";
		else cout << c;
		cout << "': " << code[(unsigned char)c] << endl;
	}
	
	// 4. 编码文件(压缩)
	if (encodeFile(originalFile, compressedFile, code, chars, m, count)) {
		cout << "4. 文件压缩完成，保存为: " << compressedFile << endl;
	}
	
	// 5. 计算压缩率
	double rate = calculateCompressionRate(originalFile, compressedFile);
	if (rate >= 0) {
		cout << "5. 压缩率: " << rate << "%" << endl;
	}
	
	// 6. 译码文件(解压)
	if (decodeFile(compressedFile, decodedFile)) {
		cout << "6. 文件解压完成，保存为: " << decodedFile << endl;
	}
	
	// 7. 比较原文件与解压文件
	if (compareFiles(originalFile, decodedFile)) {
		cout << "7. 验证结果: 原文件与解压文件完全一致，压缩解压成功!" << endl;
	} else {
		cout << "7. 验证结果: 原文件与解压文件不一致，出现错误!" << endl;
	}
	
	return 0;



}
