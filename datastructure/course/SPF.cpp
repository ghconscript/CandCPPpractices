#include<iostream>
#define NumVertices 50
#define INF 1e5
using namespace std;
typedef struct node {
	int adjvex;//相连的边的序号
	int cost;//权
	struct node *next;//下一个边表结点
} EdgeNode; //边节点
typedef struct {
	int vertex;//顶点的数据域
	EdgeNode *firstedge;//顶点的边表
} VertexNode;
typedef struct {
	VertexNode vexlist[NumVertices];
	int n, e; //顶点个数和边个数
} AdjGraph;
void CreateGraph(AdjGraph G) {
	int tail, head, weight;
	cin >> G.n >> G.e;
	for (int i = 0; i < G.n; i++) {
		cin >> G.vexlist[i].vertex;
		G.vexlist[i].firstedge = nullptr;
	}
	for (int i = 0; i < G.e; i++) {
		cin >> tail >> head >> weight; //一条边从tail指向head
		EdgeNode*p = new EdgeNode;
		p->cost = weight;
		p->adjvex = head;
		p->next = G.vexlist[tail].firstedge;
		G.vexlist[tail].firstedge = p;
	}
}

class Dij{
public:
	static int v, e;
	static void Create(int*&D, int*&V, bool*&S, int**&graph) {
		cout<<"输入顶点和边的个数"<<endl;
		cin >>v>>e;
		D = new int[v]; //存放源点到I的最短路径长度
		V = new int[v]; //存放到i最后经过的节点
		S = new bool[v]; //存放S：最短路径顶点集
		graph = new int*[v];
		for (int i = 0; i < v; ++i) {
			graph[i] = new int[v]; // 为第i行申请v列
		}
		for (int i = 0; i < v; ++i) {
			for (int j = 0; j < v; ++j) {
				if (i == j) {
					graph[i][j] = 0; // 自身到自身权重为0
				} else {
					graph[i][j] = INF; // 初始无边，设为INF
				}
			}
		}
		for(int i=0;i<v;i++){
			D[i]=graph[0][i];
			V[i]=0;
		}
		int tail, head, weight;
		for (int i = 0; i < e; i++) {
			cout<<"依次输入tail head weight"<<endl;
			cin >> tail >> head >> weight;
			tail--; // 转换为0-based索引
			head--;
			graph[tail][head] = weight;
		}
	}

	static int MinCost(int*D, bool*S) {
		int temp = INF;
		int w=0;
		for (int i = 1; i < v; i++) {
			if (!S[i] && D[i] < temp) { //顶点不在S里面并且权值最小
				temp = D[i];
				w = i;
			}
		}
		return w;
	}
	static void doDijkstra(int**graph, int*D, int*V, bool*S) {
		int w,sum;
		for (int i = 0; i < v;i++) {
			D[i]=graph[0][i];S[i]=false;
		}
		S[0]=true;
		for(int i=0;i< v-1;i++){
			w=MinCost(D,S);
			S[w]=true;//把w纳入到S中
			for(int j=1;i<v;i++){
				if(S[j]!=true){
					sum=D[w]+graph[w][j];
					if(sum<D[j]){D[i]=sum;S[i]=w;}
				}
			}
		}
	}
	static void release(int*&D, int*&V, bool*&S, int**&graph){
		delete[] D;
		delete[] V;
		delete[] S;
		for(int i=0;i<Dij::v;i++){
			delete[] graph[i];
		}
		delete[] graph;
	}
};
int Dij::v=-1;
int Dij::e=-1;
int main(){

	int*D=nullptr;
	int*V=nullptr;
	bool*S=nullptr;
	int**graph=nullptr;
	Dij::Create(D,V,S,graph);
	Dij::doDijkstra(graph,D,V,S);
	for(int i=0;i<Dij::v;i++){
		cout<<"到第"<<i+1<<"个点的最短距离是"<<D[i]<<endl;
		cout<<"源点到第"<<i+1<<"个点的最短路径上最后经过的顶点"<<V[i];
	}
	Dij::release(D,V,S,graph);
}

