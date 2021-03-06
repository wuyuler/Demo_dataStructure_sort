// 图_单源最短路径and所有点对最短路径.cpp: 定义控制台应用程序的入口点。
//

/*
author:唐永金

*/
#include "stdafx.h"
#include<iostream>
using namespace std;
#pragma warning(disable:4996)
#define MAX_VERTEX_NUM 6
#define INFINITY 100000
#include"Graph.hpp"
#include<string>



void ShortestPath_Dijkstra(Graph&G, int v0) {
	int D[MAX_VERTEX_NUM];//D[i]表示在迭代计算过程中,当前时刻,v0到顶点i的最短距离
	int P[MAX_VERTEX_NUM];//P[i]表示在最短路径中,顶点i的前驱结点
	bool S[MAX_VERTEX_NUM];//S[i]表示顶点i是否在集合内
	memset(S, 0, sizeof(S));
	S[v0] = true;

	for (int i = 0;i < G.vexnum;i++) {
		if (G.arcs[v0][i] < INFINITY) {
			D[i] = G.arcs[v0][i];
			P[i] = v0;
		}
		else {
			D[i] = INFINITY;
			P[i] = -1;//-1表示前驱结点未确定
		}
	}
	
	cout << "算法开始 选择了:";
	int v = v0;
	for (int i = 1;i < G.vexnum;i++) {
		int min = INFINITY;

		for (int j = 0;j < G.vexnum;j++) {//遍历除当前时刻到v0最小的结点
			if (!S[j]) {
				if (D[j] < min) {
					min = D[j];
					v = j;
				}

			}
		}
		if (S[v])break;
		S[v] = true;
		cout << "v" << v << " ";
		for (int k = 0;k < G.vexnum;k++) {
			if (D[v] + G.arcs[v][k] < D[k]) {//通过新加入集合的v,更新D[i]
				D[k] = D[v] + G.arcs[v][k];
				P[k] = v;
			}
		}


	}
	for (int i = 0;i < G.vexnum;i++) {
		cout << endl;
		if (D[i] != INFINITY&&i!=v0) {
			cout << "v" << i << "的前驱结点是:v" << P[i] << endl;
		}
		else cout << "v" << i << "的前驱结点是" << "无" << endl;
	}

	int i = 3;
	cout << "v3->";
	while (P[i] != v0) {
		cout << "->" << P[i];
		i = P[i];
		cout << "->" << P[i];
	}
	


}

void ShortestPath_Floyd(Graph& G) {//Floyd算法求点对之间的最短路径
	int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//点对之间的最短距离
	string P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//点对之间的路径

	//初始化点对之间的距离
	for(int i=0;i<G.vexnum;i++)
		for (int j = 0;j < G.vexnum;j++) {
			D[i][j] = G.arcs[i][j];
			if (D[i][j] == INFINITY)
				P[i][j] = "无";
			//else P[i][j] = string(&G.vertices[i],1)+string("->")+ string(&G.vertices[j],1);//注意char类型转化为string
			else P[i][j] = "";
		}

	
	for(int k=0;k<G.vexnum;k++)
		for(int v=0;v<G.vexnum;v++)
			for (int w = 0;w < G.vexnum;w++) {//k为中心点,更新v->w
				if (D[v][w] > (D[v][k] + D[k][w])) {
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k]+string(&G.vertices[k], 1)+string("->")+P[k][w];

				}


			}
		
	for (int i = 0;i < G.vexnum;i++) {
	for (int j = 0;j < G.vexnum;j++)
	cout <<"v"<<i<<"->"<<"v"<<j<<"之间:"<< P[i][j]<<"距离:"<<D[i][j]<<endl;
	cout << endl;
	}


}
int main()
{
	Graph G("012345");
	G.addArc(0, 2, 10);G.addArc(0, 4, 30);G.addArc(0, 5, 100);
	G.addArc(1, 2,5);G.addArc(2, 3, 50);G.addArc(3, 5, 10);
	G.addArc(4, 3, 20);G.addArc(4, 6, 60);
	//cout << G.arcs[0][2];
	ShortestPath_Dijkstra(G, 0);
	//ShortestPath_Floyd(G);
	return 0;
}

