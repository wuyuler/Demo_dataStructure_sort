// 图_最小生成树_PrimAndKrusal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include "ALGraph.hpp"
#define	MAX_VERTEX_NUM 8
#define	MAX_VERTEX_VALUE 100

void Prim(ALGraph&G) {
	char adjvex[MAX_VERTEX_NUM];//存储所有结点的值,并以此附上序号
	int lowcost[MAX_VERTEX_NUM];//V-U中i结点到U中最小边的值,值为0表示该边已进入最小边,100表示不连通
	int mst[MAX_VERTEX_NUM];//lowcost中求的最小边,i为V-U里,对应值为U里的,值为0表示已经进入U里
	//初始化adjvex
	int min,minid;
	for (int i = 0;i < G.vexnum;i++) {
		adjvex[i] = G.vertices[i].data;
	}
	//初始化lowcost,序号0结点为第一个
	for (int i = 0;i < G.vexnum;i++) {
		lowcost[i] = 100;
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

int main()
{
	ALGraph g("123456",0);
	g.addArc(0, 1, 6);g.addArc(0, 2, 1);g.addArc(0, 3, 5);
	g.addArc(1, 2, 5);g.addArc(1, 4, 3);
	g.addArc(2, 3, 5);g.addArc(2, 4, 6);g.addArc(2, 5, 4);
	g.addArc(3, 5, 2);g.addArc(4, 5, 6);
	Prim(g);
    return 0;
}

