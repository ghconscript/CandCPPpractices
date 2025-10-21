#include<iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#define NUM 128       // 最大不同字符数(覆盖ASCII码)
#define MAXCODE 100   // 最大编码长度
using namespace std;

// 哈夫曼树节点结构
typedef struct {
	double weight;    // 权重(频率)
	int lchild;       // 左孩子索引
	int rchild;       // 右孩子索引
	int parent;       // 父节点索引
} HTNODE;

// 最小堆节点结构(存储哈夫曼树节点的索引和权重)
typedef struct {
	int index;        // 哈夫曼树节点的索引
	double weight;    // 权重
} MinHeapNode;

// 最小堆结构
typedef struct {
	MinHeapNode data[NUM];  // 堆数据
	int n;                  // 堆中元素数量
} MinHeap;

// 哈夫曼树类型(节点数组)
typedef HTNODE HuffmanT[2*NUM-1];

/**
 * 统计文件中各字符的出现频率
 * @param filename 输入文件名
 * @param count 频率计数数组
 * @param total 总字符数
 * @param m 不同字符的数量
 * @param chars 存储不同字符的数组
 */
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

/**
 * 最小堆的向下调整操作
 * @param heap 最小堆
 * @param i 要调整的节点索引
 */
void adjustHeap(MinHeap& heap, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int smallest = i;
	
	// 找到当前节点、左孩子、右孩子中的最小值
	if (left < heap.n && heap.data[left].weight < heap.data[smallest].weight)
		smallest = left;
	if (right < heap.n && heap.data[right].weight < heap.data[smallest].weight)
		smallest = right;
	
	// 如果最小值不是当前节点，交换并递归调整
	if (smallest != i) {
		swap(heap.data[i], heap.data[smallest]);
		adjustHeap(heap, smallest);
	}
}

/**
 * 初始化最小堆
 * @param heap 最小堆
 * @param ht 哈夫曼树
 * @param m 叶子节点数量
 */
void initMinHeap(MinHeap& heap, HuffmanT ht, int m) {
	heap.n = m;
	for (int i = 0; i < m; i++) {
		heap.data[i].index = i;
		heap.data[i].weight = ht[i].weight;
	}
	// 从最后一个非叶子节点开始构建堆
	for (int i = (heap.n - 2) / 2; i >= 0; i--) {
		adjustHeap(heap, i);
	}
}

/**
 * 提取堆中最小元素
 * @param heap 最小堆
 * @return 最小堆节点
 */
MinHeapNode extractMin(MinHeap& heap) {
	if (heap.n <= 0) {
		cerr << "堆为空，无法提取元素" << endl;
		exit(1);
	}
	
	MinHeapNode minNode = heap.data[0];
	heap.data[0] = heap.data[heap.n - 1];  // 用最后一个元素替换堆顶
	heap.n--;
	adjustHeap(heap, 0);  // 调整堆
	
	return minNode;
}

/**
 * 向堆中插入节点
 * @param heap 最小堆
 * @param node 要插入的节点
 */
void insertHeap(MinHeap& heap, MinHeapNode node) {
	if (heap.n >= NUM) {
		cerr << "堆已满，无法插入" << endl;
		exit(1);
	}
	
	// 插入到堆的末尾
	int i = heap.n;
	heap.data[i] = node;
	heap.n++;
	
	// 向上调整堆
	while (i > 0) {
		int parent = (i - 1) / 2;
		if (heap.data[i].weight < heap.data[parent].weight) {
			swap(heap.data[i], heap.data[parent]);
			i = parent;
		} else {
			break;
		}
	}
}

/**
 * 构建哈夫曼树
 * @param ht 哈夫曼树
 * @param heap 最小堆
 * @param m 叶子节点数量
 */
void buildHuffmanTree(HuffmanT ht, MinHeap& heap, int m) {
	// 初始化非叶子节点
	for (int i = m; i < 2 * m - 1; i++) {
		ht[i].weight = 0;
		ht[i].lchild = -1;
		ht[i].rchild = -1;
		ht[i].parent = -1;
	}
	
	// 合并m-1次创建非叶子节点
	for (int i = m; i < 2 * m - 1; i++) {
		MinHeapNode s1 = extractMin(heap);  // 提取第一个最小节点
		MinHeapNode s2 = extractMin(heap);  // 提取第二个最小节点
		
		int i1 = s1.index;
		int i2 = s2.index;
		
		// 创建新节点
		ht[i].weight = s1.weight + s2.weight;
		ht[i].lchild = i1;
		ht[i].rchild = i2;
		ht[i1].parent = i;
		ht[i2].parent = i;
		
		// 将新节点插入堆
		MinHeapNode newNode = {i, ht[i].weight};
		insertHeap(heap, newNode);
	}
}

/**
 * 生成哈夫曼编码
 * @param ht 哈夫曼树
 * @param m 叶子节点数量
 * @param chars 字符数组
 * @param code 存储编码的二维数组
 */
void generateHuffmanCode(HuffmanT ht, int m, const char chars[], char code[128][MAXCODE]) {
	for (int i = 0; i < m; i++) {
		char temp[MAXCODE];
		int current = i;
		int parent = ht[current].parent;
		int index = 0;
		
		// 从叶子节点向上追溯到根节点
		while (parent != -1) {
			if (ht[parent].lchild == current) {
				temp[index++] = '0';  // 左孩子为0
			} else {
				temp[index++] = '1';  // 右孩子为1
			}
			current = parent;
			parent = ht[current].parent;
		}
		temp[index] = '\0';
		
		// 反转临时数组得到正确编码
		int len = strlen(temp);
		for (int j = 0; j < len; j++) {
			code[(unsigned char)chars[i]][j] = temp[len - 1 - j];
		}
		code[(unsigned char)chars[i]][len] = '\0';
	}
}

/**
 * 对文件进行哈夫曼编码(压缩)
 * @param srcFile 源文件
 * @param dstFile 压缩文件
 * @param code 哈夫曼编码表
 * @param chars 字符数组
 * @param m 字符数量
 * @param count 频率计数
 * @return 编码成功返回true
 */
bool encodeFile(const char* srcFile, const char* dstFile, 
				const char code[128][MAXCODE], const char chars[], int m, int count[]) {
	ofstream fout(dstFile, ios::binary);
	ifstream fin(srcFile, ios::binary);
	if (!fout || !fin) {
		cerr << "文件打开失败" << endl;
		return false;
	}
	
	// 写入头部信息：字符数量
	fout.write((char*)&m, sizeof(int));
	
	// 写入每个字符及其出现次数
	for (int i = 0; i < m; i++) {
		char c = chars[i];
		int cnt = count[(unsigned char)c];
		fout.write(&c, sizeof(char));
		fout.write((char*)&cnt, sizeof(int));
	}
	
	// 编码字符并写入
	char bitBuffer[8];
	int bitCount = 0;
	char c;
	
	while (fin.get(c)) {
		const char* codestr = code[(unsigned char)c];
		int len = strlen(codestr);
		
		// 处理每个编码位
		for (int i = 0; i < len; i++) {
			bitBuffer[bitCount++] = codestr[i];
			if (bitCount == 8) {  // 满8位则转换为字节写入
				unsigned char byte = 0;
				for (int j = 0; j < 8; j++) {
					byte = (byte << 1) | (bitBuffer[j] == '1' ? 1 : 0);
				}
				fout.write((char*)&byte, sizeof(unsigned char));
				bitCount = 0;
			}
		}
	}
	
	// 处理剩余的位
	unsigned char lastByte = 0;
	int remainingBits = bitCount;
	if (remainingBits > 0) {
		for (int j = 0; j < remainingBits; j++) {
			lastByte = (lastByte << 1) | (bitBuffer[j] == '1' ? 1 : 0);
		}
		lastByte <<= (8 - remainingBits);  // 填充剩余位
		fout.write((char*)&lastByte, sizeof(unsigned char));
	}
	
	// 写入最后一个字节的有效位数
	fout.write((char*)&remainingBits, sizeof(char));
	
	fin.close();
	fout.close();
	return true;
}

/**
 * 获取文件大小(字节)
 * @param filename 文件名
 * @return 文件大小
 */
long long getFileSize(const char* filename) {
	ifstream fin(filename, ios::binary | ios::ate);
	if (!fin) {
		cerr << "无法获取文件大小: " << filename << endl;
		return -1;
	}
	long long size = fin.tellg();
	fin.close();
	return size;
}

/**
 * 计算压缩率
 * @param original 原文件
 * @param compressed 压缩文件
 * @return 压缩率(百分比)
 */
double calculateCompressionRate(const char* original, const char* compressed) {
	long long origSize = getFileSize(original);
	long long compSize = getFileSize(compressed);
	
	if (origSize <= 0 || compSize <= 0) return -1.0;
	return (double)compSize / origSize * 100;
}

/**
 * 从压缩文件读取频率信息
 * @param filename 压缩文件名
 * @param count 频率计数数组
 * @param m 字符数量
 * @param chars 字符数组
 * @param total 总字符数
 */
void readFrequencyFromCompressed(const char* filename, int count[], int& m, char chars[], int& total) {
	ifstream fin(filename, ios::binary);
	if (!fin) {
		cerr << "无法打开压缩文件: " << filename << endl;
		exit(1);
	}
	
	memset(count, 0, sizeof(int)*128);
	total = 0;
	
	// 读取字符数量
	fin.read((char*)&m, sizeof(int));
	
	// 读取每个字符及其计数
	for (int i = 0; i < m; i++) {
		char c;
		int cnt;
		fin.read(&c, sizeof(char));
		fin.read((char*)&cnt, sizeof(int));
		chars[i] = c;
		count[(unsigned char)c] = cnt;
		total += cnt;
	}
	fin.close();
}

/**
 * 对压缩文件进行译码(解压)
 * @param srcFile 压缩文件
 * @param dstFile 解压文件
 * @return 译码成功返回true
 */
bool decodeFile(const char* srcFile, const char* dstFile) {
	// 读取频率信息
	int count[128], m, total;
	char chars[NUM];
	readFrequencyFromCompressed(srcFile, count, m, chars, total);
	
	// 重建哈夫曼树
	HuffmanT ht;
	for (int i = 0; i < m; i++) {
		ht[i].weight = count[(unsigned char)chars[i]] / (double)total;
		ht[i].lchild = ht[i].rchild = ht[i].parent = -1;
	}
	
	MinHeap heap;
	initMinHeap(heap, ht, m);
	buildHuffmanTree(ht, heap, m);
	int root = 2 * m - 2;  // 根节点索引
	
	// 读取编码数据
	ifstream fin(srcFile, ios::binary);
	ofstream fout(dstFile, ios::binary);
	if (!fin || !fout) {
		cerr << "译码文件打开失败" << endl;
		return false;
	}
	
	// 定位到编码数据开始位置
	fin.seekg(4 + 5 * m, ios::beg);  // 4字节(m) + m*(1+4)字节(字符+计数)
	
	// 读取最后一个字节的有效位数
	char remainingBits;
	fin.seekg(-sizeof(char), ios::end);
	fin.read(&remainingBits, sizeof(char));
	
	// 计算编码数据大小
	long long totalSize = getFileSize(srcFile);
	long long codeSize = totalSize - (4 + 5 * m) - 1;
	if (codeSize < 0) {
		cerr << "压缩文件格式错误" << endl;
		return false;
	}
	
	// 读取编码字节
	fin.seekg(4 + 5 * m, ios::beg);
	unsigned char* codeBytes = new unsigned char[codeSize];
	fin.read((char*)codeBytes, codeSize);
	
	// 译码过程
	int currentNode = root;
	int totalBits = codeSize * 8;
	if (codeSize > 0) totalBits -= (8 - remainingBits);
	
	int bitIndex = 0;
	for (int i = 0; i < codeSize; i++) {
		unsigned char byte = codeBytes[i];
		for (int j = 7; j >= 0; j--) {  // 从高位到低位处理
			if (bitIndex >= totalBits) break;
			
			int bit = (byte >> j) & 1;
			// 根据bit移动到相应子节点
			currentNode = (bit == 0) ? ht[currentNode].lchild : ht[currentNode].rchild;
			
			// 到达叶子节点，输出字符
			if (ht[currentNode].lchild == -1 && ht[currentNode].rchild == -1) {
				for (int k = 0; k < m; k++) {
					if (k == currentNode) {
						fout.put(chars[k]);
						break;
					}
				}
				currentNode = root;  // 回到根节点
			}
			bitIndex++;
		}
		if (bitIndex >= totalBits) break;
	}
	
	delete[] codeBytes;
	fin.close();
	fout.close();
	return true;
}

/**
 * 比较两个文件是否完全相同
 * @param file1 第一个文件
 * @param file2 第二个文件
 * @return 相同返回true
 */
bool compareFiles(const char* file1, const char* file2) {
	ifstream fin1(file1, ios::binary);
	ifstream fin2(file2, ios::binary);
	if (!fin1 || !fin2) return false;
	
	char c1, c2;
	while (fin1.get(c1) && fin2.get(c2)) {
		if (c1 != c2) return false;
	}
	
	// 检查是否都到达文件末尾
	return fin1.eof() && fin2.eof();
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
	initMinHeap(heap, ht, m);
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
