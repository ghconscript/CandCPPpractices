#include<iostream>
#include<fstream>
#include<stdexcept>
#define MAX 100
using namespace std;
struct LIST {
	int n;//个数
	int data[MAX];
	LIST(int value):
		n(value), data({0}) {}
};
void ReadFromFile(const string&filename, int &n, int *&sequence) {
	n = 0;
	sequence = nullptr;
	ifstream inFile(filename);//构造函数创建
	inFile >> n;

	sequence = new int[n];
	for (int i = 0; i < n; i++) {
		inFile >> sequence[i];
	}
	inFile.close();
}
void Merge(int begin1, int end1, int end2, LIST &A, LIST &B) {
	int cur1 = begin1; //第一个序列的游标
	int cur2 = end1 + 1; //第二的
	int p = begin1;
	while (cur1 < end1 && cur2 < end2) {
		B.data[p++] = (A.data[cur1] < A.data[cur2]) ? A.data[cur1++] : A.data[cur2++];
	}
	while (cur1 < end1) {
		B.data[p++] = A.data[cur1++];
	}
	while (cur2 < end2) {
		B.data[p++] = A.data[cur2++];
	}
}
void MergePass(int n, int len, LIST &A, LIST &B) {
	int i;
	for (i = 0; i + 2 * len - 1 < n; i += 2 * len) {
		Merge(i, i + len - 1, i + 2 * len - 1, A, B);
	}
	if (i + len < n) {
		Merge(i, i + len - 1, n, A, B);
	} else {
		for (int j = 0; j <= n; j++) {
			B.data[j] = A.data[j];
		}
	}
}
void MergeSort(int n, LIST &A) {
	int len = 1;
	LIST B(n);
	while (len < n) {
		MergePass(n, len, A, B);
		len *= 2;
		MergePass(n, len, B, A);
		len *= 2;
	}
}
int FindPivot(int begin, int end, LIST &A) {
	//在begin end之间找关键字
	int firstkey = A.data[begin];
	for (int i = begin + 1; i < end; i++) {
		if (firstkey < A.data[i]) {
			return i;
		} else if (firstkey > A.data[i]) {
			return begin;
		}
	}
	return 0;
}
int Partition(int begin, int end, int pivot, LIST &A) {
	int l = begin, r = end;
	do {
		while (A.data[l] < pivot) {
			l++;
		}
		while (A.data[r] >= pivot) {
			r--;
		}
		if (l < r) {
			swap(A.data[l], A.data[r]);
		}
	} while (l <= r);
	return l;//返回换完之后的右子列的起始下标
}
void QuickSort(int begin, int end, LIST &A) {
	int pivot;
	int pivotindex = FindPivot(begin, end, A);
	int k;
	if (pivotindex != 0) {
		pivot = A.data[pivotindex];
		k = Partition(begin, end, pivot, A);
		QuickSort(begin, k - 1, A);
		QuickSort(k, end, A);
	}
}
void selection_sort(LIST A, int n) {
	for (int i = 1; i < n; ++i) {
		int ith = i;
		for (int j = i + 1; j <= n; ++j) {
			if (A.data[j] < A.data[ith]) {
				ith = j;
			}
		}
		std::swap(A.data[i], A.data[ith]);
	}
}

