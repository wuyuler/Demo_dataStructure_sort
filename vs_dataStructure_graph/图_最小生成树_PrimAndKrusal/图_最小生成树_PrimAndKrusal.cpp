// 图_最小生成树_PrimAndKrusal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include "ALGraph.hpp"
#define	MAX_VERTEX_NUM 6
#define	MAX_VERTEX_VALUE 10000

void Prim(ALGraph&G) {
	char adjvex[MAX_VERTEX_NUM];//存储所有结点的值,并以此附上序号
	int lowcost[MAX_VERTEX_NUM];//V-U中i结点到U中最小边的值,值为0表示该边已进入最小边,MAX表示不连通
	int mst[MAX_VERTEX_NUM];//lowcost中求的最小边,i为V-U里,对应值为U里的,值为0表示已经进入U里
	//初始化adjvex
	int min,minid;
	for (int i = 0;i < G.vexnum;i++) {
		adjvex[i] = G.vertices[i].data;
	}
	//初始化lowcost,序号0结点为第一个
	for (int i = 0;i < G.vexnum;i++) {
		lowcost[i] = MAX_VERTEX_VALUE;
	}
	lowcost[0] = 0;
	mst[0] = 0;
	//ArcNode*p = G.vertices[0].firstarc;
	/*while (p) {
		lowcost[p->adjvex] = p->info;
		p = p->nextarc;
	}*/
	ArcNode*p;
	/*for (int i = 0;i < G.vexnum;i++)
		cout << lowcost[i]<<endl;*/
	for (int i = 1;i < G.vexnum;i++) {
		min = MAX_VERTEX_VALUE;
		minid = 0;
		for (int j = 1;j < G.vexnum;j++) {
			if (lowcost[j] != 0) {//遍历所有未加入U的结点
				p = G.vertices[j].firstarc;
				while (p) {
					if (lowcost[p->adjvex] == 0 && p->info < min) {//如果该结点所连接的边中,有在U里的,取其中最小的一个
						min = p->info;
						minid = p->adjvex;
					}
					p = p->nextarc;
				}
				lowcost[j] = min;
				mst[j] = minid;
				//cout << min;
			}

		}
		min = MAX_VERTEX_VALUE;
		for (int k = 0;k < G.vexnum;k++) {//找到一组lowcost中最小的一个,将其进入U中
			if (lowcost[k] != 0 && lowcost[k] < min) {
				min = lowcost[k];
				minid = k;
			}

		}
		lowcost[minid] = 0;
		cout << "v" << adjvex[minid] << "-" << "v"<< adjvex[mst[minid]] << ":" << min<<endl;
	}

	

	


}
struct Arc {

	int preNode, nextNode, info;
	Arc(int perNode, int nextNode, int info):preNode(preNode),nextNode(nextNode),info(info) {
		
	}
	Arc(Arc& a) {
		preNode = a.preNode;
		nextNode = a.nextNode;
		info = a.info;
	}
	Arc() {};
	void setArc(int p,int n, int i) {
		preNode = p;
		nextNode = n;
		info = i;
	}
};


//并查集三大函数
int find(int v, int union_set[]) {
	if (v == union_set[v])
		return v;
	return find(union_set[v], union_set);

}
void unite(int x, int y, int* union_set,int*rank) {
	x = find(x, union_set);
	y = find(y, union_set);
	if (rank[x] < rank[y])
		union_set[x] = y;
	else {
		union_set[y] = x;
		if (rank[x] == rank[y])
			rank[x]++;
	}


}
bool same(int x,int y,int*union_set) {
	return find(x, union_set) == find(y, union_set);
	}
void Krusal(ALGraph&G) {//Krusal算法实现图的最小生成树
	//利用并查集实现Krusal算法
	int min_arc_value=0;//存储最小边值
	int union_set[MAX_VERTEX_NUM];
	int rank[MAX_VERTEX_NUM];//存储树的深度(根节点为0)
	ArcNode *p;
	Arc minArc;//每次查找到的最小边

	//初始化并查集
	for (int v = 0;v < G.vexnum;v++) {
		union_set[v] = v;
		rank[v] = 0;
	}
		
	while (min_arc_value != MAX_VERTEX_VALUE) {
		min_arc_value = MAX_VERTEX_VALUE;
		for (int i = 0;i < G.vexnum;i++) {
			p = G.vertices[i].firstarc;
			while (p) {
				if (!same(i, p->adjvex, union_set) && p->info < min_arc_value) {
					minArc.setArc(i, p->adjvex, p->info);
					min_arc_value = p->info;
				}
				p = p->nextarc;
			}

		}
		if (min_arc_value != MAX_VERTEX_VALUE) {
			unite(minArc.preNode, minArc.nextNode, union_set, rank);
			cout << "v" << minArc.preNode+1 << "-v" << minArc.nextNode+1 << ":" << minArc.info<<endl;
		}
	}


}



int main()
{
	ALGraph g("123456",0);
	g.addArc(0, 1, 6);g.addArc(0, 2, 1);g.addArc(0, 3, 5);
	g.addArc(1, 2, 5);g.addArc(1, 4, 3);
	g.addArc(2, 3, 5);g.addArc(2, 4, 6);g.addArc(2, 5, 4);
	g.addArc(3, 5, 2);g.addArc(4, 5, 6);
	
	//Prim(g);
	Krusal(g);
    return 0;
}

