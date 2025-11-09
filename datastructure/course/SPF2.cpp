#include<iostream>
#include<fstream>
#include<string>
#define INF 1e9
using namespace std;
//打印的
void printPathHelper(int* path, int len) {
	for (int i = 0; i < len; i++) {
		if (i > 0) cout << "->";
		cout << path[i] + 1;  // 转回1-based
	}
}

class Dijkstra {
private:
	int v;                  // 顶点数
	int** graph;            // 邻接矩阵：ppt里的C
	int* dist;              // 源点到各顶点的距离：ppt里的D
	int* prev;              // 前驱顶点数组（记录路径）：ppt里的P
	bool* visited;          // 访问标记数组：ppt里的S
	
public:
	Dijkstra(int vertices, int** adjMatrix) : v(vertices), graph(adjMatrix) {
		dist = new int[v];
		prev = new int[v];
		visited = new bool[v];
	}
	
	//（源点为start，0-based）
	void run(int start) {
		// 初始化
		for (int i = 0; i < v; i++) {
			dist[i] = graph[start][i];
			prev[i] = (dist[i] != INF) ? start : -1;  // 前驱初始化
			visited[i] = false;
		}
		visited[start] = true;
		
		// 迭代更新最短路径
		for (int i = 0; i < v - 1; i++) {
			// 找未访问的最小距离顶点
			int minDist = INF, u = -1;//u是ppt里的w 也就是前一个顶点
			for (int j = 0; j < v; j++) {//MinCost
				if (!visited[j] && dist[j] < minDist) {
					minDist = dist[j];
					u = j;
				}
			}
			if (u == -1) break;  // 无可达顶点
			visited[u] = true;
			for (int j = 0; j < v; j++) {//更新dist 
				if (!visited[j] && graph[u][j] != INF && dist[u] + graph[u][j] < dist[j]) {
					dist[j] = dist[u] + graph[u][j];
					prev[j] = u;
				}
			}
		}
	}
	
	void printResult(int start) {
		cout << "\n=== Dijkstra单源最短路径（源点：" << start + 1 << "） ===" << endl;
		for (int i = 0; i < v; i++) {
			if (i == start) continue;
			cout << "到顶点" << i + 1 << "的距离：";
			if (dist[i] == INF) {
				cout << "不可达" << endl;
				continue;
			}
			cout << dist[i] << "，路径：";
			
			// 计算路径长度（从i回溯到start）
			int len = 0;
			int cur = i;
			while (cur != -1) {
				len++;
				if (cur == start) break;
				cur = prev[cur];
			}
			
			// 创建数组存储路径（从start到i）
			int* path = new int[len];
			cur = i;
			for (int k = len - 1; k >= 0; k--) {  // 反向填充
				path[k] = cur;
				if (cur == start) break;
				cur = prev[cur];
			}
			
			// 打印路径并释放数组
			printPathHelper(path, len);
			delete[] path;
			cout << endl;
		}
	}
	
	// 解决单目标最短路径
	void singleTarget(int target) {
		cout << "\n=== Dijkstra单目标最短路径（所有顶点到目标" << target + 1 << "） ===" << endl;
		// 反向图（边的方向反转）
		int** reverseGraph = new int*[v];
		for (int i = 0; i < v; i++) {
			reverseGraph[i] = new int[v];
			for (int j = 0; j < v; j++) {
				reverseGraph[i][j] = graph[j][i];  // 反转边
			}
		}
		
		// 以target为源点在反向图上运行Dij
		Dijkstra reverseDijkstra(v, reverseGraph);
		reverseDijkstra.run(target);
		
		// 输出结果（原顶点i到target的路径 = 反向图中target到i的路径）
		for (int i = 0; i < v; i++) {
			if (i == target) continue;
			cout << "顶点" << i + 1 << "到" << target + 1 << "的距离：";
			int d = reverseDijkstra.getDist()[i];
			if (d == INF) {
				cout << "不可达" << endl;
				continue;
			}
			cout << d << "，路径：";
			
			// 计算路径长度
			int len = 0;
			int cur = i;
			int* rPrev = reverseDijkstra.getPrev();
			while (cur != -1) {
				len++;
				if (cur == target) break;
				cur = rPrev[cur];
			}
			
			// 存储路径
			int* path = new int[len];
			cur = i;
			for (int k = len - 1; k >= 0; k--) {
				path[k] = cur;
				if (cur == target) break;
				cur = rPrev[cur];
			}
			
			// 打印并释放
			printPathHelper(path, len);
			delete[] path;
			cout << endl;
		}
		
		// 释放反向图
		for (int i = 0; i < v; i++) delete[] reverseGraph[i];
		delete[] reverseGraph;
	}
	
	int* getDist() { return dist; }
	int* getPrev() { return prev; }
	
	~Dijkstra() {
		delete[] dist;
		delete[] prev;
		delete[] visited;
	}
};



class Floyd {
private:
	int v;                  // 顶点数
	int** graph;            // 邻接矩阵 C
	int** dist;             // 最短距离矩阵 D
	int** path;             // 路径矩阵（记录中间顶点）ppt里的P
	
public:
	// 构造函数
	Floyd(int vertices, int** adjMatrix) : v(vertices), graph(adjMatrix) {
		dist = new int*[v];
		path = new int*[v];
		for (int i = 0; i < v; i++) {
			dist[i] = new int[v];
			path[i] = new int[v];
			for (int j = 0; j < v; j++) {
				dist[i][j] = graph[i][j];
				path[i][j] = (graph[i][j] != INF) ? -1 : -2;  // -1:直接可达；-2:不可达 方便输出
			}
		}
	}
	
	// 执行Floyd算法
	void run() {
		for (int k = 0; k < v; k++) {  // 中间顶点
			for (int i = 0; i < v; i++) {  // 起点
				for (int j = 0; j < v; j++) {  // 终点
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						path[i][j] = k;  // 记录中间顶点
					}
				}
			}
		}
	}
	
	// 输出全局最短距离矩阵
	void printDistMatrix() {
		cout << "\n=== Floyd全局最短距离矩阵（行->列，1-based） ===" << endl;
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
				if (dist[i][j] == INF) cout << "INF\t";
				else cout << dist[i][j] << "\t";
			}
			cout << endl;
		}
	}
	
	// 输出任意两点的最短路径
	void printPath(int i, int j) {
		if (i == j) {
			cout << i + 1;
			return;
		}
		int k = path[i][j];
		if (k == -1) {  // 直接可达
			cout << i + 1 << "->" << j + 1;
			return;
		}
		if (k == -2) {  // 不可达
			cout << "不可达";
			return;
		}
		printPath(i, k);    // 递归打印i->k
		cout << "->" << j + 1;  // 拼接k->j
	}
	
	// 解决单顶点对最短路径
	void singlePair(int u, int v) {
		cout << "\n=== Floyd单顶点对最短路径（" << u + 1 << "与" << v + 1 << "） ===" << endl;
		// u到v
		cout << u + 1 << "到" << v + 1 << "的距离：" << dist[u][v] << "，路径：";
		printPath(u, v);
		cout << endl;
		// v到u
		cout << v + 1 << "到" << u + 1 << "的距离：" << dist[v][u] << "，路径：";
		printPath(v, u);
		cout << endl;
	}
	
	~Floyd() {
		for (int i = 0; i < v; i++) {
			delete[] dist[i];
			delete[] path[i];
		}
		delete[] dist;
		delete[] path;
	}
};


// 从文件
void loadGraphFromFile(const string& filename, int& v, int& e, int**& graph) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		cerr << "错误：无法打开文件 " << filename << endl;
		exit(1);
	}
	
	// 读取顶点数和边数
	fin >> v >> e;
	cout << "从文件读取：顶点数=" << v << "，边数=" << e << endl;
	
	// 初始化邻接矩阵
	graph = new int*[v];
	for (int i = 0; i < v; i++) {
		graph[i] = new int[v];
		for (int j = 0; j < v; j++) {
			graph[i][j] = (i == j) ? 0 : INF;
		}
	}
	
	// 读取边信息 1based转为0based
	int tail, head, weight;
	for (int i = 0; i < e; i++) {
		fin >> tail >> head >> weight;
		tail--;
		head--;
		graph[tail][head] = weight; 
	}
	fin.close();
}

int main() {
	int v, e;
	int** graph = nullptr;
	loadGraphFromFile("graph_data.txt", v, e, graph);
	
	Dijkstra dij(v, graph);
	dij.run(0);
	dij.printResult(0);
	
	dij.singleTarget(5);
	
	Floyd floyd(v, graph);
	floyd.run();
	floyd.printDistMatrix();
	
	floyd.singlePair(2, 7);
	
	for (int i = 0; i < v; i++) delete[] graph[i];
	delete[] graph;
	
	return 0;
}
