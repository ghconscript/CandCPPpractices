#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<cstring>
#define NumVertices 50  // 最大顶点数
#define INF 1e5         // 表示无边（无穷大）
using namespace std;
typedef struct {
	int elements[NumVertices];// elemtype == char
	int top;//顶值对应的索引
} STACK;
void InitStack(STACK &S) {
	S.top = -1;
}
bool Empty(STACK S) {
	if (S.top < 0)
		return true;
	else
		return false;
}
int Top(STACK S) {
	if (Empty(S))
		return -1;
	else
		return (S.elements[S.top]);
}
void Pop(STACK &S) {
	if (Empty(S)) {
		cout << "栈空" << endl;
		return;
	} else
		S.top = S.top - 1;
}
void Push(int x, STACK &S) {
	if (S.top == NumVertices - 1) {
		cout << "栈满" << endl;
		return;
	} else {
		S.top = S.top + 1;
		S.elements[S.top] = x;
		return;
	}
}
// 邻接表边节点
typedef struct EdgeNode {
	int adjvex;         // 邻接顶点序号
	int cost;           // 边权值
	struct EdgeNode *next; // 下一条边
} EdgeNode;

// 邻接表顶点节点
typedef struct {
	int vertex;         // 顶点编号
	EdgeNode *firstedge;// 边表表头指针
} VertexNode;

// 邻接表结构
typedef struct {
	VertexNode vexlist[NumVertices];
	int n, e;           // 顶点数、边数
} AdjGraph;

// 邻接矩阵结构
typedef struct {
	int vertex[NumVertices];
	int edge[NumVertices][NumVertices];
	int n, e;           // 顶点数、边数
} MTgraph;
bool visited[NumVertices]; //访问标记数组
int cnt;
int dfsSeq[NumVertices], bfsSeq[NumVertices];  // 搜索序列
// 建立邻接矩阵（directed=false为无向图，true为有向图）
void CreateMTgraph(MTgraph &G, bool directed = false) {
	cout << "输入顶点数和边数：";
	cin >> G.n >> G.e;
	// 初始化：自身到自身为0，其余为INF
	for (int i = 0; i < G.n; i++) {
		for (int j = 0; j < G.n; j++) {
			G.edge[i][j] = (i == j) ? 0 : INF;
		}
	}
	cout << "输入每条边的两个顶点及权值（顶点从0开始）：" << endl;
	for (int k = 0; k < G.e; k++) {
		int i, j, w;
		cin >> i >> j >> w;
		G.edge[i][j] = w;
		if (!directed) G.edge[j][i] = w; // 无向图对称
	}
}
// 邻接表插入边（头插法）
void InsertEdge(AdjGraph &G, int i, int j, int w, bool directed = false) {
	EdgeNode *p = new EdgeNode;
	p->adjvex = j;
	p->cost = w;
	p->next = G.vexlist[i].firstedge;
	G.vexlist[i].firstedge = p;
	if (!directed) { // 无向图需双向插入
		EdgeNode *q = new EdgeNode;
		q->adjvex = i;
		q->cost = w;
		q->next = G.vexlist[j].firstedge;
		G.vexlist[j].firstedge = q;
	}
}

// 建立邻接表
void CreateAdjGraph(AdjGraph &G, bool directed = false) {
	cout << "输入顶点数和边数：";
	cin >> G.n >> G.e;
	// 初始化顶点表
	for (int i = 0; i < G.n; i++) {
		G.vexlist[i].vertex = i;
		G.vexlist[i].firstedge = NULL;
	}
	cout << "输入每条边的两个顶点及权值（顶点从0开始）：" << endl;
	for (int k = 0; k < G.e; k++) {
		int i, j, w;
		cin >> i >> j >> w;
		InsertEdge(G, i, j, w, directed);
	}
}

void MTtoAdj(MTgraph &G, AdjGraph &AG, bool directed = false) {
	AG.n = G.n;
	AG.e = G.e;
	// 初始化顶点表
	for (int i = 0; i < AG.n; i++) {
		AG.vexlist[i].vertex = i;
		AG.vexlist[i].firstedge = NULL;
	}
	// 遍历矩阵，插入边
	for (int i = 0; i < G.n; i++) {
		for (int j = 0; j < G.n; j++) {
			if (G.edge[i][j] != INF && G.edge[i][j] != 0) {
				InsertEdge(AG, i, j, G.edge[i][j], directed);
			}
		}
	}
}
void AdjtoMT(AdjGraph &AG, MTgraph &G, bool directed = false) {
	G.n = AG.n;
	G.e = AG.e;
	// 初始化矩阵
	for (int i = 0; i < G.n; i++) {
		for (int j = 0; j < G.n; j++) {
			G.edge[i][j] = (i == j) ? 0 : INF;
		}
	}
	// 遍历邻接表，填充矩阵
	for (int i = 0; i < AG.n; i++) {
		EdgeNode *p = AG.vexlist[i].firstedge;
		while (p) {
			int j = p->adjvex;
			G.edge[i][j] = p->cost;
			if (!directed) G.edge[j][i] = p->cost;
			p = p->next;
		}
	}
}
void recursivedfs(AdjGraph &G,int source){
	EdgeNode *cur;
	cout<<"访问"<<G.vexlist[source].vertex<<"号顶点"<<endl;
	visited[source]=true;
	dfsSeq[source]=cnt++;
	cur=G.vexlist[source].firstedge;
	while(cur){
		if(!visited[cur->adjvex]){
			recursivedfs(G,cur->adjvex);
			cur=cur->next;
		}
	}
}//adjgraph版本的dfs
void recursivedfs(MTgraph &G,int source){
	int cur;
	cout<<"访问"<<G.vertex[cur]<<"号顶点"<<endl;
	visited[source]=true;
	dfsSeq[source]=cnt++;
	for(int i=0;i<G.n;i++){
		if(G.edge[source][cur]==1&&!visited[cur]){
			recursivedfs(G,i);
		}
	}
}//MTgraph 版本的dfs

void dfs(AdjGraph &G,int source){
	for(int i=0;i<G.n;i++){
		visited[i]=false;
	}
	for(int i=0;i<G.n;i++){
		if(!visited[i]){
			recursivedfs(G,source);
		}
	}
	
}
void dfs(MTgraph &G,int source){
	for(int i=0;i<G.n;i++){
		visited[i]=false;
	}
	for(int i=0;i<G.n;i++){
		if(!visited[i]){
			recursivedfs(G,source);
		}
	}
}
