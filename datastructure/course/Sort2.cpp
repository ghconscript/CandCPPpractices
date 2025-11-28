#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 动态数组结构体（支持大数据量）
struct LIST {
	int n;          // 元素个数
	int* data;      // 动态数组
	
	LIST(int size) : n(size) {
		if (size < 0) throw invalid_argument("Size cannot be negative");
		data = new int[size];
	}
	
	LIST(const LIST& other) : n(other.n) {
		data = new int[n];
		for (int i = 0; i < n; ++i) {
			data[i] = other.data[i];
		}
	}
	
	~LIST() {
		delete[] data;
		data = nullptr;
		n = 0;
	}
	
	LIST& operator=(const LIST&) = delete;
};

// 从文件读取数据
void ReadFromFile(const string& filename, int& n, int*& sequence) {
	n = 0;
	sequence = nullptr;
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		throw runtime_error("无法打开文件");
	}
	
	inFile >> n;
	if (n <= 0 || n > 100000) {
		throw runtime_error("n的值必须为0 < n ≤ 100000");
	}
	
	sequence = new int[n];
	for (int i = 0; i < n; ++i) {
		if (!(inFile >> sequence[i]) || sequence[i] < 0) {
			delete[] sequence;
			sequence = nullptr;
			throw runtime_error("文件中包含无效数据（必须是非负整数）");
		}
	}
	inFile.close();
}

// 归并排序：合并两个子数组 [begin1, end1] 和 [end1+1, end2]
void Merge(int begin1, int end1, int end2, LIST& A, LIST& B) {
	int cur1 = begin1, cur2 = end1 + 1, p = begin1;
	while (cur1 <= end1 && cur2 <= end2) {
		B.data[p++] = (A.data[cur1] <= A.data[cur2]) ? A.data[cur1++] : A.data[cur2++];
	}
	while (cur1 <= end1) B.data[p++] = A.data[cur1++];
	while (cur2 <= end2) B.data[p++] = A.data[cur2++];
}

// 归并排序：一趟归并（按长度len合并）
void MergePass(int n, int len, LIST& A, LIST& B) {
	int i = 0;
	while (i + 2 * len - 1 < n) {
		Merge(i, i + len - 1, i + 2 * len - 1, A, B);
		i += 2 * len;
	}
	if (i + len < n) {
		Merge(i, i + len - 1, n - 1, A, B);
	} else {
		for (int j = i; j < n; ++j) B.data[j] = A.data[j];
	}
}

// 归并排序入口
void MergeSort(LIST& A) {
	if (A.n <= 1) return;
	LIST B(A.n);
	int len = 1;
	while (len < A.n) {
		MergePass(A.n, len, A, B);
		len *= 2;
		if (len >= A.n) {
			for (int i = 0; i < A.n; ++i) A.data[i] = B.data[i];
			break;
		}
		MergePass(A.n, len, B, A);
		len *= 2;
	}
}

// 快速排序：分区操作（选末尾元素为枢轴，简化逻辑）
int Partition(int begin, int end, LIST& A) {
	int pivot = A.data[end];
	int i = begin - 1;
	for (int j = begin; j < end; ++j) {
		if (A.data[j] < pivot) {
			i++;
			swap(A.data[i], A.data[j]);
		}
	}
	swap(A.data[i + 1], A.data[end]);
	return i + 1;
}

// 快速排序入口
void QuickSort(int begin, int end, LIST& A) {
	if (begin < end) {
		int p = Partition(begin, end, A);
		QuickSort(begin, p - 1, A);
		QuickSort(p + 1, end, A);
	}
}

// 选择排序
void SelectionSort(LIST& A) {
	for (int i = 0; i < A.n - 1; ++i) {
		int minIdx = i;
		for (int j = i + 1; j < A.n; ++j) {
			if (A.data[j] < A.data[minIdx]) minIdx = j;
		}
		swap(A.data[i], A.data[minIdx]);
	}
}

// 计时工具函数（返回秒数）
template <typename Func, typename... Args>
double MeasureTime(Func func, Args&&... args) {
	auto start = high_resolution_clock::now();
	func(forward<Args>(args)...);
	auto end = high_resolution_clock::now();
	return duration<double>(end - start).count();
}

// 生成随机数据（0~1e6的非负整数）
void GenerateRandomData(int n, int*& data) {
	data = new int[n];
	for (int i = 0; i < n; ++i) {
		data[i] = rand() % 1000000;
	}
}

// 处理文件数据并输出排序结果
void ProcessFile(const string& filename) {
	int n;
	int* sequence = nullptr;
	try {
		ReadFromFile(filename, n, sequence);
	} catch (const exception& e) {
		cerr << "文件读取错误：" << e.what() << endl;
		return;
	}
	
	LIST mergeList(n), quickList(n), selectList(n);
	for (int i = 0; i < n; ++i) {
		mergeList.data[i] = sequence[i];
		quickList.data[i] = sequence[i];
		selectList.data[i] = sequence[i];
	}
	
	double mergeTime = MeasureTime(MergeSort, ref(mergeList));
	double quickTime = MeasureTime(QuickSort, 0, n - 1, ref(quickList));
	double selectTime = (n <= 10000) ? MeasureTime(SelectionSort, ref(selectList)) : -1;
	
	cout << "\n=== 文件数据排序结果 ===" << endl;
	cout << "归并排序（" << fixed << setprecision(6) << mergeTime << "秒）：";
	for (int i = 0; i < min(n, 20); ++i) cout << mergeList.data[i] << " ";
	if (n > 20) cout << "...";
	
	cout << "\n快速排序（" << fixed << setprecision(6) << quickTime << "秒）：";
	for (int i = 0; i < min(n, 20); ++i) cout << quickList.data[i] << " ";
	if (n > 20) cout << "...";
	
	if (n <= 10000) {
		cout << "\n选择排序（" << fixed << setprecision(6) << selectTime << "秒）：";
		for (int i = 0; i < min(n, 20); ++i) cout << selectList.data[i] << " ";
		if (n > 20) cout << "...";
	} else {
		cout << "\n选择排序：数据量过大（n > 10000），未执行";
	}
	cout << endl;
	
	delete[] sequence;
}

// 存储算法性能数据
struct PerformanceData {
	int size;
	double merge_time;
	double quick_time;
	double select_time;
};

// 运行算法对比实验
vector<PerformanceData> RunExperiments(const vector<int>& sizes) {
	vector<PerformanceData> results;
	
	cout << "\n=== 开始算法性能对比实验 ===" << endl;
	for (int n : sizes) {
		cout << "测试数据规模：" << n << "..." << flush;
		int* data;
		GenerateRandomData(n, data);
		
		LIST mergeList(n);
		copy(data, data + n, mergeList.data);
		double mergeTime = MeasureTime(MergeSort, ref(mergeList));
		
		LIST quickList(n);
		copy(data, data + n, quickList.data);
		double quickTime = MeasureTime(QuickSort, 0, n - 1, ref(quickList));
		
		double selectTime = -1;
		if (n <= 100000) {
			LIST selectList(n);
			copy(data, data + n, selectList.data);
			selectTime = MeasureTime(SelectionSort, ref(selectList));
		}
		
		results.push_back({n, mergeTime, quickTime, selectTime});
		delete[] data;
		cout << "完成" << endl;
	}
	
	return results;
}

// 打印实验数据表格
void printPerformanceTable(const vector<PerformanceData>& dataList) {
	if (dataList.empty()) return;
	
	cout << "\n=== 算法性能数据表（单位：秒） ===" << endl;
	cout << left 
	<< setw(12) << "数据规模" 
	<< setw(18) << "归并排序" 
	<< setw(18) << "快速排序" 
	<< setw(18) << "选择排序" 
	<< endl;
	cout << string(66, '-') << endl;
	
	for (const auto& data : dataList) {
		cout << left 
		<< setw(12) << data.size 
		<< setw(18) << fixed << setprecision(6) << data.merge_time 
		<< setw(18) << fixed << setprecision(6) << data.quick_time;
		
		if (data.select_time > 0) {
			cout << setw(18) << fixed << setprecision(6) << data.select_time;
		} else {
			cout << setw(18) << "未执行";
		}
		cout << endl;
	}
}

// 控制台字符折线图
void drawTextLineChart(const vector<PerformanceData>& dataList) {
	if (dataList.empty()) {
		cerr << "无实验数据可展示" << endl;
		return;
	}
	
	const int CHART_WIDTH = 80;
	const int CHART_HEIGHT = 20;
	const char EMPTY_CHAR = ' ';
	const char MERGE_CHAR = '*';
	const char QUICK_CHAR = '#';
	const char SELECT_CHAR = '+';
	
	int max_size = 0;
	double max_time = 0.0;
	for (const auto& data : dataList) {
		max_size = max(max_size, data.size);
		max_time = max(max_time, max(data.merge_time, data.quick_time));
		if (data.select_time > 0) max_time = max(max_time, data.select_time);
	}
	if (max_time <= 0) max_time = 1e-6;
	
	vector<vector<char>> chart(CHART_HEIGHT, vector<char>(CHART_WIDTH, EMPTY_CHAR));
	
	int dataCount = dataList.size();
	for (int i = 0; i < dataCount; ++i) {
		const auto& data = dataList[i];
		int x = (int)((double)i / (dataCount - 1) * (CHART_WIDTH - 1));
		x = max(0, min(x, CHART_WIDTH - 1));
		
		auto getY = [&](double time) {
			if (time <= 0) return CHART_HEIGHT - 1;
			double ratio = time / max_time;
			int y = (int)((1 - ratio) * (CHART_HEIGHT - 1));
			return max(0, min(y, CHART_HEIGHT - 1));
		};
		
		int y_merge = getY(data.merge_time);
		chart[y_merge][x] = MERGE_CHAR;
		
		int y_quick = getY(data.quick_time);
		if (chart[y_quick][x] == MERGE_CHAR) chart[y_quick][x] = 'M';
		else chart[y_quick][x] = QUICK_CHAR;
		
		if (data.select_time > 0) {
			int y_select = getY(data.select_time);
			if (chart[y_select][x] == MERGE_CHAR) chart[y_select][x] = 'm';
			else if (chart[y_select][x] == QUICK_CHAR) chart[y_select][x] = 'Q';
			else chart[y_select][x] = SELECT_CHAR;
		}
	}
	
	cout << "\n===== 排序算法性能对比（字符折线图） =====" << endl;
	cout << "注：横向为数据规模，纵向为时间（越靠上时间越小）" << endl;
	
	for (int y = 0; y < CHART_HEIGHT; ++y) {
		if (y % 5 == 0) {
			double time = max_time * (1 - (double)y / (CHART_HEIGHT - 1));
			cout << setw(8) << fixed << setprecision(3) << time << " | ";
		} else {
			cout << "        | ";
		}
		
		for (int x = 0; x < CHART_WIDTH; ++x) {
			cout << chart[y][x];
		}
		cout << endl;
	}
	
	cout << "----------+";
	for (int x = 0; x < CHART_WIDTH; ++x) cout << "-";
	cout << endl << "          ";
	int step = max(1, (CHART_WIDTH - 1) / 4);
	for (int i = 0; i <= 4; ++i) {
		int x = i * step;
		int size = (int)((double)i / 4 * max_size);
		cout << setw(x - cout.tellp() + 10) << size;
	}
	cout << endl << endl;
	
	cout << "图例：" << endl;
	cout << "  " << MERGE_CHAR << " : 归并排序" << endl;
	cout << "  " << QUICK_CHAR << " : 快速排序" << endl;
	cout << "  " << SELECT_CHAR << " : 选择排序" << endl;
	cout << "  M/m/Q : 点重叠" << endl;
}

int main() {
	srand(time(0));
	
	// 1. 处理文件数据
	string filename = "data.txt";
	ProcessFile(filename);
	
	// 2. 运行不同规模数据的对比实验
	vector<int> testSizes = {100, 500, 1000, 5000, 10000, 20000, 50000, 100000};
	vector<PerformanceData> performanceData = RunExperiments(testSizes);
	
	// 3. 输出实验数据表格
	printPerformanceTable(performanceData);
	
	// 4. 绘制字符折线图
	drawTextLineChart(performanceData);
	
	return 0;
}
