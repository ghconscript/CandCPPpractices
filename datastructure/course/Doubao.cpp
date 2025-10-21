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
	M.n = 0;  // 堆大小初始化为0(1-based索引，data[1..n]有效)
}

// 堆插入函数
void Insert(MinHeap& heap, int index, double weight) {
	if (heap.n >= NUM) {
		cout << "堆已满" << endl;
		return;
	} else {
		int i = ++heap.n;  // 新元素位置(1-based)
		// 向上调整：与父节点比较，若更小则交换
		while ((i != 1) && (weight < heap.data[i / 2].weight)) {
			heap.data[i] = heap.data[i / 2];  // 父节点下移
			i /= 2;
		}
		heap.data[i] = {index, weight};  // 插入新元素
	}
}

// 哈夫曼树初始化函数
void InitHT(HuffmanT T) {
	for (int i = 0; i <= 2 * NUM - 2; i++) {  // 初始化所有可能节点
		T[i] = {0, -1, -1, -1};  // 权重0，无孩子和父节点
	}
}

// 哈夫曼树权重设置函数
void InputW(HuffmanT T, int cnt[]) {
	for (int i = 0; i < NUM; i++) {  // 为前NUM个节点设置权重(叶子节点)
		T[i].weight = cnt[i];
	}
}

// 堆删除最小元素函数
int DeleteMin(MinHeap& heap) {
	int parent = 1, child = 2;
	int min_idx = heap.data[1].index;  // 堆顶是最小元素，记录其索引
	if (heap.n != 0) {
		MinHeapNode tmp = heap.data[heap.n--];  // 取最后一个元素，堆大小减1
		// 向下调整：找到tmp的正确位置
		while (child <= heap.n) {
			// 选择左右孩子中较小的一个
			if ((child < heap.n) && (heap.data[child].weight > heap.data[child + 1].weight)) {
				child++;
			}
			// 若tmp小于等于子节点，无需继续下移
			if (tmp.weight <= heap.data[child].weight) {
				break;
			}
			// 子节点上移
			heap.data[parent] = heap.data[child];
			parent = child;
			child *= 2;  // 移动到左孩子
		}
		heap.data[parent] = tmp;  // 放置tmp
		return min_idx;  // 返回最小元素的索引
	}
	return -1;  // 堆为空
}


/**
 * 统计文件字符频率
 * @param filename 输入文件
 * @param chars 存储有效字符(非零频率)
 * @param cnt 频率数组(下标对应ASCII，值为出现次数)
 * @param m 有效字符数量(输出)
 * @param total 总字符数(输出)
 */
void CountCharFrequency(const char* filename, char chars[], int cnt[], int& m, int& total) {
	memset(cnt, 0, sizeof(int) * 128);  // 初始化频率数组
	total = 0;
	m = 0;
	
	ifstream fin(filename, ios::binary);
	if (!fin) {
		cerr << "无法打开文件: " << filename << endl;
		exit(1);
	}
	
	char c;
	while (fin.get(c)) {  // 读取所有字符(包括控制字符)
		unsigned char uc = (unsigned char)c;
		cnt[uc]++;
		total++;
	}
	fin.close();
	
	// 提取有效字符(频率>0)，最多NUM个
	for (int i = 0; i < 128; i++) {
		if (cnt[i] > 0) {
			chars[m++] = (char)i;
			if (m > NUM) {  // 不超过NUM
				cerr << "字符种类超过上限(" << NUM << ")" << endl;
				exit(1);
			}
		}
	}
}

/**
 * 构建哈夫曼树
 * @param ht 哈夫曼树
 * @param cnt 频率数组
 * @param m 有效字符数量(叶子节点数)
 * @param chars 有效字符数组（新增参数）
 */
void BuildHuffmanTree(HuffmanT ht, int cnt[], int m, const char chars[]) {  // 新增chars参数
	// 1. 初始化哈夫曼树
	InitHT(ht);
	// 2. 设置叶子节点权重
	InputW(ht, cnt);
	
	// 3. 初始化最小堆
	MinHeap heap;
	InitHP(heap);
	
	// 4. 将有效叶子节点插入堆
	for (int i = 0; i < m; i++) {
		// 使用传入的chars数组获取字符，计算权重
		ht[i].weight = cnt[(unsigned char)chars[i]];  // 现在可以正确访问chars
		Insert(heap, i, ht[i].weight);
	}
	
	// 5. 合并节点构建哈夫曼树
	for (int i = m; i < 2 * m - 1; i++) {  // 新节点索引从m开始
		// 提取两个最小权重节点
		int i1 = DeleteMin(heap);
		int i2 = DeleteMin(heap);
		
		// 设置新节点的左右孩子和权重
		ht[i].lchild = i1;
		ht[i].rchild = i2;
		ht[i].weight = ht[i1].weight + ht[i2].weight;
		
		// 设置孩子节点的父节点
		ht[i1].parent = i;
		ht[i2].parent = i;
		
		// 将新节点插入堆
		Insert(heap, i, ht[i].weight);
	}
}

/**
 * 生成哈夫曼编码表
 * @param ht 哈夫曼树
 * @param m 有效字符数量
 * @param chars 有效字符数组
 * @param codes 编码表(输出)
 */
void GenerateCodes(HuffmanT ht, int m, const char chars[], string codes[]) {
	for (int i = 0; i < m; i++) {  // 遍历每个叶子节点(对应chars[i])
		int cur = i;  // 当前节点索引(叶子节点索引0..m-1)
		int parent = ht[cur].parent;
		string code;
		
		// 从叶子节点向上追溯到根节点
		while (parent != -1) {
			if (ht[parent].lchild == cur) {
				code = "0" + code;  // 左孩子编码为0
			} else {
				code = "1" + code;  // 右孩子编码为1
			}
			cur = parent;
			parent = ht[cur].parent;
		}
		codes[i] = code;  // 保存编码
	}
}

/**
 * 压缩文件(哈夫曼编码)
 */
void Encode(const char* src, const char* dst, const char chars[], const string codes[], int m, int cnt[]) {
	ofstream fout(dst, ios::binary);
	ifstream fin(src, ios::binary);
	if (!fout || !fin) {
		cerr << "文件打开失败" << endl;
		exit(1);
	}
	
	// 写入头信息
	fout.write((char*)&m, sizeof(int));
	for (int i = 0; i < m; i++) {
		unsigned char c = (unsigned char)chars[i];
		int freq = cnt[c];
		fout.write((char*)&c, sizeof(unsigned char));
		fout.write((char*)&freq, sizeof(int));
	}
	
	// 编码数据
	char bitBuf = 0;  // 位缓冲区(8位)
	int bitCnt = 0;   // 已缓存位数
	
	char c;
	while (fin.get(c)) {  // 读取源文件字符
		unsigned char uc = (unsigned char)c;
		// 查找字符在chars中的索引
		int idx = -1;
		for (int i = 0; i < m; i++) {
			if ((unsigned char)chars[i] == uc) {
				idx = i;
				break;
			}
		}
		if (idx == -1) {
			cerr << "编码错误：未找到字符" << endl;
			exit(1);
		}
		
		// 处理该字符的编码
		const string& code = codes[idx];
		for (char bit : code) {
			bitBuf = (bitBuf << 1) | (bit == '1' ? 1 : 0);  // 左移补位
			bitCnt++;
			if (bitCnt == 8) {  // 缓冲区满，写入
				fout.put(bitBuf);
				bitBuf = 0;
				bitCnt = 0;
			}
		}
	}
	
	// 处理剩余不足8位的比特
	if (bitCnt > 0) {
		bitBuf <<= (8 - bitCnt);  // 左移补0
		fout.put(bitBuf);
	}
	// 写入最后一个字节的有效位数
	fout.put((char)bitCnt);
	
	fin.close();
	fout.close();
}

/**
 * 解压文件(哈夫曼译码)
 */
void Decode(const char* src, const char* dst) {
	ifstream fin(src, ios::binary);
	ofstream fout(dst, ios::binary);
	if (!fin || !fout) {
		cerr << "文件打开失败" << endl;
		exit(1);
	}
	
	// 读取头信息：有效字符数m
	int m, total = 0;
	fin.read((char*)&m, sizeof(int));
	if (m <= 0 || m > NUM) {
		cerr << "压缩文件格式错误" << endl;
		exit(1);
	}
	
	// 读取字符和频率，重建chars、cnt数组
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
	
	// 重建哈夫曼树（传入chars参数）
	HuffmanT ht;
	BuildHuffmanTree(ht, cnt, m, chars);  // 新增chars实参
	int root = 2 * m - 2;  // 根节点索引(最后一个节点)
	
	// 读取编码数据大小和最后一个字节的有效位数
	long long fileSize = fin.tellg();
	fin.seekg(0, ios::end);
	long long totalSize = fin.tellg();
	char lastBitCnt;
	fin.seekg(-1, ios::end);
	fin.read(&lastBitCnt, 1);
	long long codeSize = totalSize - fileSize - 1;  // 编码数据字节数
	
	// 定位到编码数据开始处
	fin.seekg(fileSize, ios::beg);
	
	// 译码过程
	int curNode = root;  // 从根节点开始
	unsigned char byte;
	long long bytesRead = 0;
	
	while (bytesRead < codeSize) {
		fin.read((char*)&byte, 1);
		bytesRead++;
		
		// 确定当前字节需要处理的位数(最后一个字节特殊处理)
		int bitsToProcess = (bytesRead == codeSize) ? lastBitCnt : 8;
		for (int i = 7; i >= (8 - bitsToProcess); i--) {  // 从高位到低位
			int bit = (byte >> i) & 1;  // 提取第i位
			// 移动到子节点：0->左孩子，1->右孩子
			curNode = (bit == 0) ? ht[curNode].lchild : ht[curNode].rchild;
			
			// 到达叶子节点，输出对应字符
			if (ht[curNode].lchild == -1 && ht[curNode].rchild == -1) {
				fout.put(chars[curNode]);  // 叶子节点索引对应chars的索引
				curNode = root;  // 回到根节点
			}
		}
	}
	
	fin.close();
	fout.close();
}

/**
 * 计算压缩率
 */
double GetCompressionRate(const char* orig, const char* comp) {
	ifstream finOrig(orig, ios::binary | ios::ate);
	ifstream finComp(comp, ios::binary | ios::ate);
	if (!finOrig || !finComp) return -1.0;
	
	long long origSize = finOrig.tellg();
	long long compSize = finComp.tellg();
	return (origSize == 0) ? 0.0 : (double)compSize / origSize * 100;
}

/**
 * 比较两个文件是否一致
 */
bool Compare(const char* f1, const char* f2) {
	ifstream fin1(f1, ios::binary);
	ifstream fin2(f2, ios::binary);
	if (!fin1 || !fin2) return false;
	
	char c1, c2;
	while (fin1.get(c1) && fin2.get(c2)) {
		if (c1 != c2) return false;
	}
	return fin1.eof() && fin2.eof();  // 必须都到达文件末尾
}

// 全局变量：存储有效字符
char chars[NUM];

int main() {
	const char* origFile = "source.txt";    // 原文件
	const char* compFile = "compressed.bin";// 压缩文件
	const char* decoFile = "decoded.txt";   // 解压文件
	
	int cnt[128] = {0};  // 频率数组(ASCII范围)
	int m;               // 有效字符种类
	int totalChars;      // 总字符数
	string codes[NUM];   // 哈夫曼编码表
	
	// 1. 统计字符频率
	CountCharFrequency(origFile, chars, cnt, m, totalChars);
	cout << "1. 字符频率统计完成：" << m << "种字符，共" << totalChars << "个字符" << endl;
	
	// 2. 构建哈夫曼树（传入chars参数）
	HuffmanT ht;
	BuildHuffmanTree(ht, cnt, m, chars);  // 新增chars实参
	cout << "2. 哈夫曼树构建完成" << endl;
	
	// 3. 生成哈夫曼编码表
	GenerateCodes(ht, m, chars, codes);
	cout << "3. 哈夫曼编码表：" << endl;
	for (int i = 0; i < m; i++) {
		char c = chars[i];
		cout << "   '" << (c == ' ' ? "空格" : (c == '\n' ? "换行" : string(1, c))) << "': " << codes[i] << endl;
	}
	
	// 4. 压缩文件
	Encode(origFile, compFile, chars, codes, m, cnt);
	cout << "4. 压缩完成，保存为" << compFile << endl;
	
	// 5. 计算压缩率
	double rate = GetCompressionRate(origFile, compFile);
	cout << "5. 压缩率：" << rate << "%" << endl;
	
	// 6. 解压文件
	Decode(compFile, decoFile);
	cout << "6. 解压完成，保存为" << decoFile << endl;
	
	// 7. 验证正确性
	if (Compare(origFile, decoFile)) {
		cout << "7. 验证成功：原文件与解压文件完全一致" << endl;
	} else {
		cout << "7. 验证失败：文件不一致" << endl;
	}
	
	return 0;
}
