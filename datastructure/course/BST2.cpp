#include<iostream>
#include<algorithm>
#include<chrono>
#include<random>
#include<cstring>
#include<cmath>
using namespace std;

struct TreeNode{
	int data;
	struct TreeNode *lchild,*rchild;
	TreeNode(int value)
	:data(value),lchild(nullptr),rchild(nullptr){}
};
typedef TreeNode* BST;
typedef TreeNode* pos;

// 带比较计数的查找函数
pos Search(int k, BST F, int &count) {
	if (F == nullptr) {
		return nullptr;
	}
	count++; // 比较k与当前节点数据
	if (k == F->data) {
		return F;
	}
	count++; // 比较大小决定方向
	if (k < F->data) {
		return Search(k, F->lchild, count);
	} else {
		return Search(k, F->rchild, count);
	}
}

BST Insert(int data, pos p) {
	if(p==nullptr){
		return new TreeNode(data);
	}else if(data<p->data){
		p->lchild=Insert(data,p->lchild);
	}else if(data>p->data){
		p->rchild=Insert(data,p->rchild);
	}else{
		// 忽略重复元素
	}
	return p;
}

pos findMinNode(BST root) {
	while(root->lchild!=nullptr){
		root = root->lchild;
	}
	return root;
}

BST Delete(BST root,int value) {
	if(root==nullptr){
		return root;
	}
	if(value<root->data){
		root->lchild=Delete(root->lchild,value);
	}else if(value>root->data){
		root->rchild=Delete(root->rchild,value);
	}else{
		if(root->lchild==nullptr){
			pos tmp= root->rchild;
			delete root;
			return tmp;
		}else if(root->rchild==nullptr){
			pos tmp = root->lchild;
			delete root;
			return tmp;
		}else{
			pos s = findMinNode(root->rchild);
			root->data=s->data;
			root->rchild=Delete(root->rchild,s->data);
		}
	}
	return root;
}

void inorderTraversal(BST root) {
	if(root==nullptr){
		return;
	}
	inorderTraversal(root->lchild);
	cout<<root->data<<" ";
	inorderTraversal(root->rchild);
}

// 计算BST查找成功ASL辅助函数
void calculateSuccessASL(BST root, int currentCount, int &successSum, int &successCount) {
	if (root == nullptr) return;
	successSum += currentCount + 1;  // 当前节点比较次数
	successCount++;
	calculateSuccessASL(root->lchild, currentCount + 2, successSum, successCount);
	calculateSuccessASL(root->rchild, currentCount + 2, successSum, successCount);
}

// 计算BST查找失败ASL辅助函数
void calculateFailedASL(BST root, int currentCount, int &failedSum, int &failedCount) {
	if (root == nullptr) return;
	// 左子树为空的失败位置
	if (root->lchild == nullptr) {
		failedSum += currentCount + 2;
		failedCount++;
	} else {
		calculateFailedASL(root->lchild, currentCount + 2, failedSum, failedCount);
	}
	// 右子树为空的失败位置
	if (root->rchild == nullptr) {
		failedSum += currentCount + 2;
		failedCount++;
	} else {
		calculateFailedASL(root->rchild, currentCount + 2, failedSum, failedCount);
	}
}

// 获取BST的ASL
void getBST_ASL(BST root, double &successASL, double &failedASL) {
	int successSum = 0, successCount = 0;
	int failedSum = 0, failedCount = 0;
	calculateSuccessASL(root, 0, successSum, successCount);
	calculateFailedASL(root, 0, failedSum, failedCount);
	successASL = successCount ? (double)successSum / successCount : 0;
	failedASL = failedCount ? (double)failedSum / failedCount : 0;
}

// 带比较计数的折半查找
int binarySearch(int arr[], int start, int end, int key, int &count) {
	int ret = -1;
	int mid;
	count = 0;
	while (start <= end) {
		mid = start + ((end - start) >> 1);
		count++;  // 记录比较次数
		if (arr[mid] < key) {
			start = mid + 1;
		} else if (arr[mid] > key) {
			end = mid - 1;
		} else {
			ret = mid;
			break;
		}
	}
	return ret;
}

// 获取折半查找的ASL
void getBinarySearch_ASL(int arr[], int n, double &successASL, double &failedASL) {
	// 计算成功ASL
	int totalSuccess = 0, count;
	for (int i = 0; i < n; i++) {
		binarySearch(arr, 0, n-1, arr[i], count);
		totalSuccess += count;
	}
	successASL = (double)totalSuccess / n;
	
	// 计算失败ASL
	int totalFailed = 0;
	// 小于第一个元素
	binarySearch(arr, 0, n-1, arr[0]-1, count);
	totalFailed += count;
	// 中间区间
	for (int i = 0; i < n-1; i++) {
		int key = (arr[i] + arr[i+1]) / 2;
		binarySearch(arr, 0, n-1, key, count);
		totalFailed += count;
	}
	// 大于最后一个元素
	binarySearch(arr, 0, n-1, arr[n-1]+1, count);
	totalFailed += count;
	
	failedASL = (double)totalFailed / (n + 1);
}

int main() {
	const int n = 1024;
	int sortedData[n], randomData[n];
	
	// 生成第1组数据：0-2048之间的奇数
	for (int i = 0; i < n; i++) {
		sortedData[i] = 1 + 2 * i;
	}
	
	// 生成第2组数据：随机序列
	memcpy(randomData, sortedData, sizeof(sortedData));
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(randomData, randomData + n, default_random_engine(seed));
	
	// 建立BST
	BST sortedBST = nullptr, randomBST = nullptr;
	for (int i = 0; i < n; i++) {
		sortedBST = Insert(sortedData[i], sortedBST);
		randomBST = Insert(randomData[i], randomBST);
	}
	
	// 计算各ASL
	double sBST_suc, sBST_fail, rBST_suc, rBST_fail;
	double bin_suc, bin_fail;
	getBST_ASL(sortedBST, sBST_suc, sBST_fail);
	getBST_ASL(randomBST, rBST_suc, rBST_fail);
	getBinarySearch_ASL(sortedData, n, bin_suc, bin_fail);
	
	// 输出结果
	cout << "=== 查找性能比较结果 ===" << endl;
	cout << "1. 有序数据构建的BST：" << endl;
	cout << "   成功ASL：" << sBST_suc << "  失败ASL：" << sBST_fail << endl;
	
	cout << "\n2. 随机数据构建的BST：" << endl;
	cout << "   成功ASL：" << rBST_suc << "  失败ASL：" << rBST_fail << endl;
	
	cout << "\n3. 折半查找（有序数据）：" << endl;
	cout << "   成功ASL：" << bin_suc << "  失败ASL：" << bin_fail << endl;
	
	// 理论值对比
	cout << "\n=== 理论值对比 ===" << endl;
	cout << "有序BST（近似单链表）：" << endl;
	cout << "   理论成功ASL：" << (n+1)/2.0 << "  理论失败ASL：" << (n+2)/2.0 << endl;
	
	cout << "随机BST（近似平衡树）：" << endl;
	cout << "   理论成功ASL：" << log2(n+1)-1 << endl;
	
	cout << "折半查找：" << endl;
	cout << "   理论成功ASL：" << log2(n+1)-1 << "  理论失败ASL：" << log2(n+2) << endl;
	
	return 0;
}
