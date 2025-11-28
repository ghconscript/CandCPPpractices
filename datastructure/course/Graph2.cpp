#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#define NumVertices 50  // 最大顶点数
#define INF 1e5         // 表示无穷大（无边）
using namespace std;

// 邻接表边节点
typedef struct node {
	int adjvex;         // 邻接顶点序号
	int cost;           // 边的权值
	struct node *next;  // 下一个边节点
} EdgeNode;

// 邻接表顶点节点
typedef struct {
	int vertex;         // 顶点数据（此处用序号表示）
	EdgeNode *firstedge;// 边表头指针
} VertexNode;

// 邻接表结构
typedef struct {
	VertexNode vexlist[NumVertices];
	int n, e;           // 顶点数和边数
} AdjGraph;

// 全局变量：用于搜索算法的辅助存储
bool visited[NumVertices];  // 访问标记
int dfsSeq[NumVertices], bfsSeq[NumVertices];  // 搜索序列
int dfsNo = 0, bfsNo = 0;   // 序列计数
int parent[NumVertices];    // 生成树/森林的父节点数组


// 1. 邻接矩阵建立（无向图）
void createAdjMatrix(int matrix[][NumVertices], int &n, int &e) {
	cout << "\n===== 建立邻接矩阵 =====" << endl;
	cout << "输入顶点数n和边数e: ";
	cin >> n >> e;
	
	// 初始化矩阵（自身为0，其余为INF）
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (i == j) ? 0 : INF;
		}
	}
	
	// 输入边信息
	cout << "输入" << e << "条边（起点 终点 权值）: " << endl;
	for (int k = 0; k < e; k++) {
		int i, j, w;
		cin >> i >> j >> w;
		matrix[i][j] = w;  // 无向图对称
		matrix[j][i] = w;
	}
}

// 1. 邻接表建立（无向图）
void createAdjList(AdjGraph &G) {
	cout << "\n===== 建立邻接表 =====" << endl;
	cout << "输入顶点数n和边数e: ";
	cin >> G.n >> G.e;
	
	// 初始化顶点
	for (int i = 0; i < G.n; i++) {
		G.vexlist[i].vertex = i;  // 顶点序号作为数据
		G.vexlist[i].firstedge = NULL;
	}
	
	// 输入边信息并构建边表
	cout << "输入" << G.e << "条边（起点 终点 权值）: " << endl;
	for (int k = 0; k < G.e; k++) {
		int i, j, w;
		cin >> i >> j >> w;
		
		// 插入i->j的边
		EdgeNode *p = new EdgeNode;
		p->adjvex = j;
		p->cost = w;
		p->next = G.vexlist[i].firstedge;
		G.vexlist[i].firstedge = p;
		
		// 无向图：插入j->i的边
		EdgeNode *q = new EdgeNode;
		q->adjvex = i;
		q->cost = w;
		q->next = G.vexlist[j].firstedge;
		G.vexlist[j].firstedge = q;
	}
}


// 2. 邻接矩阵转邻接表
void matrixToAdjList(int matrix[][NumVertices], int n, AdjGraph &G) {
	G.n = n;
	G.e = 0;  // 统计边数
	
	// 初始化顶点
	for (int i = 0; i < n; i++) {
		G.vexlist[i].vertex = i;
		G.vexlist[i].firstedge = NULL;
	}
	
	// 遍历矩阵构建边表（避免重复计算，只处理i<j）
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (matrix[i][j] != INF && matrix[i][j] != 0) {
				G.e++;  // 每条边计数一次
				
				// 插入i->j的边
				EdgeNode *p = new EdgeNode;
				p->adjvex = j;
				p->cost = matrix[i][j];
				p->next = G.vexlist[i].firstedge;
				G.vexlist[i].firstedge = p;
				
				// 插入j->i的边
				EdgeNode *q = new EdgeNode;
				q->adjvex = i;
				q->cost = matrix[i][j];
				q->next = G.vexlist[j].firstedge;
				G.vexlist[j].firstedge = q;
			}
		}
	}
}

// 2. 邻接表转邻接矩阵
void adjListToMatrix(AdjGraph G, int matrix[][NumVertices]) {
	int n = G.n;
	// 初始化矩阵
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (i == j) ? 0 : INF;
		}
	}
	
	// 遍历边表填充矩阵
	for (int i = 0; i < n; i++) {
		EdgeNode *p = G.vexlist[i].firstedge;
		while (p != NULL) {
			int j = p->adjvex;
			matrix[i][j] = p->cost;  // 无向图对称
			matrix[j][i] = p->cost;
			p = p->next;
		}
	}
}


// 3. 邻接表DFS递归
void dfsRecursiveAdjList(AdjGraph G, int v) {
	visited[v] = true;
	dfsSeq[dfsNo++] = v;  // 记录访问序列
	EdgeNode *p = G.vexlist[v].firstedge;
	while (p != NULL) {
		int w = p->adjvex;
		if (!visited[w]) {
			parent[w] = v;  // 记录父节点（生成树）
			dfsRecursiveAdjList(G, w);
		}
		p = p->next;
	}
}

// 3. 邻接表DFS非递归
void dfsNonRecursiveAdjList(AdjGraph G) {
	memset(visited, 0, sizeof(visited));
	memset(parent, -1, sizeof(parent));
	dfsNo = 0;
	stack<int> s;
	
	for (int i = 0; i < G.n; i++) {
		if (!visited[i]) {
			s.push(i);
			visited[i] = true;
			dfsSeq[dfsNo++] = i;
			while (!s.empty()) {
				int v = s.top();
				EdgeNode *p = G.vexlist[v].firstedge;
				bool found = false;
				// 查找未访问的邻接顶点
				while (p != NULL) {
					int w = p->adjvex;
					if (!visited[w]) {
						visited[w] = true;
						dfsSeq[dfsNo++] = w;
						parent[w] = v;
						s.push(w);
						found = true;
						break;
					}
					p = p->next;
				}
				if (!found) s.pop();  // 无未访问顶点则出栈
			}
		}
	}
}

// 3. 邻接矩阵DFS递归
void dfsRecursiveMatrix(int matrix[][NumVertices], int n, int v) {
	visited[v] = true;
	dfsSeq[dfsNo++] = v;
	for (int w = 0; w < n; w++) {
		if (matrix[v][w] != INF && matrix[v][w] != 0 && !visited[w]) {
			parent[w] = v;
			dfsRecursiveMatrix(matrix, n, w);
		}
	}
}

// 3. 邻接表BFS
void bfsAdjList(AdjGraph G) {
	memset(visited, 0, sizeof(visited));
	memset(parent, -1, sizeof(parent));
	bfsNo = 0;
	queue<int> q;
	
	for (int i = 0; i < G.n; i++) {
		if (!visited[i]) {
			q.push(i);
			visited[i] = true;
			bfsSeq[bfsNo++] = i;
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				EdgeNode *p = G.vexlist[v].firstedge;
				while (p != NULL) {
					int w = p->adjvex;
					if (!visited[w]) {
						visited[w] = true;
						bfsSeq[bfsNo++] = w;
						parent[w] = v;
						q.push(w);
					}
					p = p->next;
				}
			}
		}
	}
}

// 3. 邻接矩阵BFS
void bfsMatrix(int matrix[][NumVertices], int n) {
	memset(visited, 0, sizeof(visited));
	memset(parent, -1, sizeof(parent));
	bfsNo = 0;
	queue<int> q;
	
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			q.push(i);
			visited[i] = true;
			bfsSeq[bfsNo++] = i;
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				for (int w = 0; w < n; w++) {
					if (matrix[v][w] != INF && matrix[v][w] != 0 && !visited[w]) {
						visited[w] = true;
						bfsSeq[bfsNo++] = w;
						parent[w] = v;
						q.push(w);
					}
				}
			}
		}
	}
}


// 4. 邻接表计算无向图顶点的度
void calculateDegree(AdjGraph G) {
	cout << "\n===== 顶点度计算 =====" << endl;
	for (int i = 0; i < G.n; i++) {
		int degree = 0;
		EdgeNode *p = G.vexlist[i].firstedge;
		while (p != NULL) {  // 边表长度即度
			degree++;
			p = p->next;
		}
		cout << "顶点" << i << "的度: " << degree << endl;
	}
}


// 辅助函数：打印邻接矩阵
void printMatrix(int matrix[][NumVertices], int n) {
	cout << "\n===== 邻接矩阵 =====" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == INF) cout << "INF\t";
			else cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// 辅助函数：打印邻接表
void printAdjList(AdjGraph G) {
	cout << "\n===== 邻接表 =====" << endl;
	for (int i = 0; i < G.n; i++) {
		cout << "顶点" << i << ": ";
		EdgeNode *p = G.vexlist[i].firstedge;
		while (p != NULL) {
			cout << "(" << p->adjvex << "," << p->cost << ") -> ";
			p = p->next;
		}
		cout << "NULL" << endl;
	}
}

// 辅助函数：打印搜索结果
void printSearchResult(string type, int seq[], int parent[], int n) {
	cout << "\n===== " << type << " 结果 =====" << endl;
	cout << "搜索序列: ";
	for (int i = 0; i < n; i++) cout << seq[i] << " ";
	cout << endl;
	cout << "生成森林（父节点数组，-1为根）: ";
	for (int i = 0; i < n; i++) cout << parent[i] << " ";
	cout << endl;
}


int main() {
	int n, e;
	int matrix[NumVertices][NumVertices];
	AdjGraph G, G_from_matrix;
	
	// 问题5：输入10个顶点，13条边
	cout << "===== 图数据输入（10顶点，13边） =====" << endl;
	// 手动预设输入数据（可替换为cin输入）
	n = 10; e = 13;
	int edges[13][3] = {  // 起点 终点 权值
		{0,1,1}, {0,2,2}, {1,3,3}, {1,4,4}, {2,5,5}, {2,6,6},
		{3,7,7}, {4,8,8}, {5,9,9}, {6,7,10}, {7,8,11}, {8,9,12}, {9,0,13}
	};
	
	// 初始化邻接矩阵
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			matrix[i][j] = (i == j) ? 0 : INF;
	for (int k = 0; k < e; k++) {
		int i = edges[k][0], j = edges[k][1], w = edges[k][2];
		matrix[i][j] = w;
		matrix[j][i] = w;
	}
	
	// 从矩阵转换为邻接表（避免重复输入）
	matrixToAdjList(matrix, n, G);
	
	// 展示存储结构
	printMatrix(matrix, n);
	printAdjList(G);
	
	// 转换算法验证
	int matrix_from_list[NumVertices][NumVertices];
	adjListToMatrix(G, matrix_from_list);
	cout << "\n===== 邻接表转矩阵验证 =====" << endl;
	printMatrix(matrix_from_list, n);
	
	// 搜索算法（邻接表）
	memset(parent, -1, sizeof(parent));
	dfsNo = 0;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < G.n; i++) 
		if (!visited[i]) dfsRecursiveAdjList(G, i);
	printSearchResult("邻接表DFS递归", dfsSeq, parent, G.n);
	
	dfsNonRecursiveAdjList(G);
	printSearchResult("邻接表DFS非递归", dfsSeq, parent, G.n);
	
	bfsAdjList(G);
	printSearchResult("邻接表BFS", bfsSeq, parent, G.n);
	
	// 搜索算法（邻接矩阵）
	memset(parent, -1, sizeof(parent));
	dfsNo = 0;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++) 
		if (!visited[i]) dfsRecursiveMatrix(matrix, n, i);
	printSearchResult("邻接矩阵DFS递归", dfsSeq, parent, n);
	
	bfsMatrix(matrix, n);
	printSearchResult("邻接矩阵BFS", bfsSeq, parent, n);
	
	// 顶点度计算
	calculateDegree(G);
	
	return 0;
}
