#include<iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#define NUM 70        // 最大节点数
#define MAXCODE 100   // 最大编码长度
using namespace std;

// 哈夫曼树节点结构
typedef struct {
	double weight;    // 权重(频率)
	int lchild;       // 左孩子索引
	int rchild;       // 右孩子索引
	int parent;       // 父节点索引
} HTNODE;

// 最小堆节点结构
typedef struct {
	int index;        // 哈夫曼树节点的索引
	double weight;    // 权重
} MinHeapNode;

// 最小堆结构
typedef struct {
	MinHeapNode data[NUM + 1];  // 1-based索引
	int n;                      // 堆中元素数量
} MinHeap;
// 哈夫曼树类型
typedef HTNODE HuffmanT[2 * NUM - 1];  // 总节点数=2*叶子数-1

// 堆初始化函数
void InitHP(MinHeap& M) {
	M.n = 0;  // 堆大小初始化为0(1-based索引)
}

// 堆插入函数
void Insert(MinHeap& heap, int index, double weight) {
	if (heap.n >= NUM) {
		cout << "堆已满" << endl;
		return;
	} else {
		int i = ++heap.n;  // 新元素位置
		while ((i != 1) && (weight < heap.data[i / 2].weight || (weight == heap.data[i / 2].weight && index < heap.data[i / 2].index))) {
			heap.data[i] = heap.data[i / 2];  // 父节点下移
			i /= 2;
		}
		heap.data[i] = {index, weight};  // 插入新元素
	}
}

// 哈夫曼树初始化函数
void InitHT(HuffmanT T) {
	for (int i = 0; i <= 2 * NUM - 2; i++) {
		T[i] = {0, -1, -1, -1};  // 权重0，无孩子和父节点
	}
}

// 哈夫曼树权重设置函数
void InputW(HuffmanT T, int cnt[]) {
	for (int i = 0; i < NUM; i++) {
		T[i].weight = cnt[i];
	}
}

// 堆删除最小元素函数
int DeleteMin(MinHeap& heap) {
	int parent = 1, child = 2;
	int min_idx = heap.data[1].index;  // 堆顶是最小元素
	if (heap.n == 0) return -1;
	MinHeapNode tmp = heap.data[heap.n--];  // 取最后一个元素
	
	while (child <= heap.n) {
		if (child < heap.n) {
			if (heap.data[child].weight > heap.data[child + 1].weight ||
				(heap.data[child].weight == heap.data[child + 1].weight && 
				 heap.data[child].index > heap.data[child + 1].index)) {
				child++;
			}
		}
		// 若tmp"小于等于"子节点，无需继续下移
		if (tmp.weight < heap.data[child].weight ||
			(tmp.weight == heap.data[child].weight && tmp.index <= heap.data[child].index)) {
			break;
		}
		// 子节点上移
		heap.data[parent] = heap.data[child];
		parent = child;
		child *= 2;
	}
	heap.data[parent] = tmp;
	return min_idx;
}


//统计文件字符频率
void CountCharFrequency(const char* filename, char chars[], int cnt[], int& m, int& total) {
	memset(cnt, 0, sizeof(int) * 128);
	total = 0;
	m = 0;
	
	ifstream fin(filename, ios::binary);
	if (!fin) { cerr << "无法打开文件: " << filename << endl; exit(1); }
	
	char c;
	while (fin.get(c)) {
		unsigned char uc = (unsigned char)c;
		cnt[uc]++;
		total++;
	}
	fin.close();
	
	// 按ASCII升序收集有效字符（确保顺序一致）
	for (int i = 0; i < 128; i++) {
		if (cnt[i] > 0) {
			chars[m++] = (char)i;
			if (m > NUM) { cerr << "字符种类超过上限(" << NUM << ")" << endl; exit(1); }
		}
	}
}

//构建哈夫曼树
void BuildHuffmanTree(HuffmanT ht, int cnt[], int m, const char chars[]) {
	InitHT(ht);
	InputW(ht, cnt);
	MinHeap heap;
	InitHP(heap);
	// 插入有效叶子节点（0~m-1）
	for (int i = 0; i < m; i++) {
		ht[i].weight = cnt[(unsigned char)chars[i]];  // 仅初始化有效字符的权重
		Insert(heap, i, ht[i].weight);
	}
	// 合并节点（确保左右孩子顺序一致）
	for (int i = m; i < 2 * m - 1; i++) {
		int i1 = DeleteMin(heap);  // 第一个最小节点（左孩子）
		int i2 = DeleteMin(heap);  // 第二个最小节点（右孩子）
		ht[i].lchild = i1;
		ht[i].rchild = i2;
		ht[i].weight = ht[i1].weight + ht[i2].weight;
		ht[i1].parent = i;
		ht[i2].parent = i;
		Insert(heap, i, ht[i].weight);
	}
}

void GenerateCodes(HuffmanT ht, int m, const char chars[], string codes[]) {
	for (int i = 0; i < m; i++) {
		int cur = i;
		int parent = ht[cur].parent;
		string code;
		while (parent != -1) {
			if (ht[parent].lchild == cur) code = "0" + code;
			else code = "1" + code;
			cur = parent;
			parent = ht[cur].parent;
		}
		codes[i] = code;
	}
}
void Encode(const char* src, const char* dst, const char chars[], const string codes[], int m, int cnt[]) {
	ofstream fout(dst, ios::binary);
	ifstream fin(src, ios::binary);
	if (!fout || !fin) { cerr << "文件打开失败" << endl; exit(1); }
	
	// 写入头信息（确保解码时能重建相同的字符表）
	fout.write((char*)&m, sizeof(int));
	for (int i = 0; i < m; i++) {
		unsigned char c = (unsigned char)chars[i];
		int freq = cnt[c];
		fout.write((char*)&c, sizeof(unsigned char));
		fout.write((char*)&freq, sizeof(int));
	}
	// 位打包：按编码顺序，有效位放在高位
	char bitBuf = 0;  // 位缓冲区
	int bitCnt = 0;   // 已缓存位数
	char c;
	while (fin.get(c)) {
		unsigned char uc = (unsigned char)c;
		// 查找字符索引（确保唯一匹配）
		int idx = -1;
		for (int i = 0; i < m; i++) {
			if ((unsigned char)chars[i] == uc) {
				idx = i;
				break;
			}
		}
		if (idx == -1) { cerr << "编码错误：未找到字符" << endl; exit(1); }
		// 处理每个bit，左移补位（有效位在高位）
		const string& code = codes[idx];
		for (char bit : code) {
			bitBuf = (bitBuf << 1) | (bit == '1' ? 1 : 0);
			bitCnt++;
			if (bitCnt == 8) {  // 满8位写入
				fout.put(bitBuf);
				bitBuf = 0;
				bitCnt = 0;
			}
		}
	}
	// 处理最后不足8位的bit（左移补0，确保有效位在高位）
	if (bitCnt > 0) {
		bitBuf <<= (8 - bitCnt);  // 补0至8位
		fout.put(bitBuf);
	}
	// 记录最后一个字节的有效位数（0表示满8位）
	fout.put((char)bitCnt);
	fin.close();
	fout.close();
}
void Decode(const char* src, const char* dst) {
	ifstream fin(src, ios::binary);
	ofstream fout(dst, ios::binary);
	if (!fin || !fout) { cerr << "文件打开失败" << endl; exit(1); }
	// 读取头信息，重建字符表和频率
	int m, total = 0;
	fin.read((char*)&m, sizeof(int));
	if (m <= 0 || m > NUM) { cerr << "压缩文件格式错误" << endl; exit(1); }
	char chars[NUM];
	int cnt[128] = {0};
	for (int i = 0; i < m; i++) {
		unsigned char c;
		int freq;
		fin.read((char*)&c, sizeof(unsigned char));
		fin.read((char*)&freq, sizeof(int));
		chars[i] = (char)c;
		cnt[c] = freq;
		total += freq;
	}
	// 重建哈夫曼树（与编码时完全一致）
	HuffmanT ht;
	BuildHuffmanTree(ht, cnt, m, chars);
	int root = 2 * m - 2;  // 根节点索引
	// 定位编码数据和有效位数
	long long headerSize = fin.tellg();  // 头信息大小
	fin.seekg(0, ios::end);
	long long totalSize = fin.tellg();
	char lastBitCnt;
	fin.seekg(-1, ios::end);
	fin.read(&lastBitCnt, 1);
	long long codeSize = totalSize - headerSize - 1;  // 编码数据字节数
	// 解码过程
	int curNode = root;  // 从根节点开始
	unsigned char byte;
	long long bytesRead = 0;
	
	fin.seekg(headerSize, ios::beg);  // 跳到编码数据起始位置
	while (bytesRead < codeSize) {
		fin.read((char*)&byte, 1);
		bytesRead++;
		// 解析当前字节的有效位（从高位到低位，与编码时一致）
		int bitsToProcess = (bytesRead == codeSize) ? lastBitCnt : 8;
		for (int i = 7; i >= (8 - bitsToProcess); i--) {  // 高位优先
			int bit = (byte >> i) & 1;  // 提取第i位（0~7，7是最高位）
			// 按bit移动：0->左孩子，1->右孩子
			curNode = (bit == 0) ? ht[curNode].lchild : ht[curNode].rchild;
			// 到达叶子节点，输出字符
			if (ht[curNode].lchild == -1 && ht[curNode].rchild == -1) {
				fout.put(chars[curNode]);  // 叶子节点索引对应chars
				curNode = root;  // 回到根节点
			}
		}
	}
	fin.close();
	fout.close();
}


double GetCompressionRate(const char* orig, const char* comp) {
	ifstream finOrig(orig, ios::binary | ios::ate);
	ifstream finComp(comp, ios::binary | ios::ate);
	if (!finOrig || !finComp) return -1.0;
	long long origSize = finOrig.tellg();
	long long compSize = finComp.tellg();
	return (origSize == 0) ? 0.0 : (double)compSize / origSize * 100;
}
bool CompareFiles(const char* file1, const char* file2) {
	// 打开两个文件（二进制模式）
	ifstream f1(file1, ios::binary);
	ifstream f2(file2, ios::binary);
	
	// 检查文件是否打开成功
	if (!f1.is_open()) { cerr << "无法打开文件: " << file1 << endl; return false; }
	if (!f2.is_open()) { cerr << "无法打开文件: " << file2 << endl; return false; }
	
	// 比较文件大小（大小不同直接返回false）
	f1.seekg(0, ios::end);
	f2.seekg(0, ios::end);
	if (f1.tellg() != f2.tellg()) {
		cout << "文件大小不同：" << file1 << "(" << f1.tellg() << "字节)，" 
		<< file2 << "(" << f2.tellg() << "字节)" << endl;
		return false;
	}
	
	// 回到文件开头，逐字节比较
	f1.seekg(0, ios::beg);
	f2.seekg(0, ios::beg);
	
	char c1, c2;
	long long pos = 0;  // 记录当前比较的位置
	while (f1.get(c1) && f2.get(c2)) {
		if (c1 != c2) {
			cout << "文件在位置 " << pos << " 处不同：" 
			<< file1 << "为" << (int)(unsigned char)c1 << "，" 
			<< file2 << "为" << (int)(unsigned char)c2 << endl;
			return false;
		}
		pos++;
	}
	
	// 所有字节相同
	cout << "两个文件完全一致！" << endl;
	return true;
}

char chars[NUM];  // 存储有效字符

int main() {
	const char* origFile = "source.txt";    // 原文件
	const char* compFile = "compressed.bin";// 压缩文件
	const char* decoFile = "decoded.txt";   // 解压文件
	
	int cnt[128] = {0};
	int m, totalChars;
	string codes[NUM];
	
	// 1. 统计频率
	CountCharFrequency(origFile, chars, cnt, m, totalChars);
	cout << "1. 字符频率统计完成：" << m << "种字符，共" << totalChars << "个字符" << endl;
	
	// 2. 构建哈夫曼树
	HuffmanT ht;
	BuildHuffmanTree(ht, cnt, m, chars);
	cout << "2. 哈夫曼树构建完成" << endl;
	
	// 3. 生成编码表
	GenerateCodes(ht, m, chars, codes);
	cout << "3. 哈夫曼编码表生成完成" << endl;
	for(int i=0;i<m;i++){
		cout<<chars[i]<<":"<<codes[i]<<endl;
	}
	// 4. 压缩文件
	Encode(origFile, compFile, chars, codes, m, cnt);
	cout << "4. 压缩完成：" << compFile << endl;
	
	// 5. 计算压缩率
	double rate = GetCompressionRate(origFile, compFile);
	cout << "5. 压缩率：" << rate << "%" << endl;
	
	// 6. 解压文件
	Decode(compFile, decoFile);
	cout << "6. 解压完成：" << decoFile << endl;
	
	cout<<CompareFiles(origFile,decoFile);
	
	return 0;
}
