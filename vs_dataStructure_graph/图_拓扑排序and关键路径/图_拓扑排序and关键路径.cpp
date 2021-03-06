// 图_拓扑排序and关键路径.cpp: 定义控制台应用程序的入口点。
//
/*
作者:唐永金
邮箱:971680807@qq.com

*/

#include "stdafx.h"
#include<iostream>
using namespace std;
#include"Queue.hpp"
#include "ALGraph.hpp"
#include"Stack.hpp"
#define N 6

int vl[N];//事件最晚开始时间

int ve[N] = {0};//事件最早开始时间

void findInDegree(ALGraph &G, int *in) {//将传入的图的结点的入度统计出来
	
	for (int i = 0;i < G.vexnum;i++) {
		ArcNode*p = G.vertices[i].firstarc;
		while (p) {
			in[p->adjvex]++;
			p = p->nextarc;
		}

	}

}
void topSort(ALGraph&G) {//拓扑排序,借助队列或栈,打印排序结果

	//int numOfArc = G.getNumOfArc;//边的数目,用来判断是否存在环
	int indegree[N] = {0};
	int count = 0;
	int resultOfTopSort[N];
	Queue<int> setOfZeroIndegree(N);//存储入度为零的结点
	findInDegree(G, indegree);
	for (int i = 0;i < N;i++) {//初始化入度为零的队列
		if (indegree[i] == 0)
			setOfZeroIndegree.enqueue(i);
	}
	//for (int i = 0;i < N;i++)
		//cout << indegree[i]<<endl;
	while (setOfZeroIndegree.length != 0) {
		int a = setOfZeroIndegree.dequeue();
		resultOfTopSort[count] = a;
		count++;
		ArcNode *p = G.vertices[a].firstarc;
		while (p) {
			indegree[p->adjvex]--;
			if (indegree[p->adjvex] == 0) {
				setOfZeroIndegree.enqueue(p->adjvex);
			}
			p = p->nextarc;
			
		}
	}
	if (count == G.vexnum) {
		for (int i = 0;i <count;i++)
			cout << "V" << resultOfTopSort[i]+1 << "->";

	}
	else {
		//cout <<"可以找到" <<count<<"个顶点";
		//for (int i = 0;i<count;i++)
			//cout << "V" << resultOfTopSort[i] + 1 << "->";
		cout<<("该图有回路存在");
	}}
	void topSort(ALGraph&G, Stack<int> &T) {//拓扑排序,同时更新每个顶点的最早开始时间
		//为什么栈和队列均能完成拓扑排序:因为入度为0的结点的选取本来就是无序的			
		int indegree[N] = { 0 };
		int count = 0;
		int resultOfTopSort[N];
		Queue<int> setOfZeroIndegree(N);//存储入度为零的结点

		findInDegree(G, indegree);
		for (int i = 0;i < N;i++) {//初始化入度为零的队列
			if (indegree[i] == 0)
				setOfZeroIndegree.enqueue(i);
		}
		//for (int i = 0;i < N;i++)
		//cout << indegree[i]<<endl;
		while (setOfZeroIndegree.length != 0) {
			int a = setOfZeroIndegree.dequeue();
			resultOfTopSort[count] = a;
			count++;
			T.push(a);
			ArcNode *p = G.vertices[a].firstarc;
			while (p) {
				indegree[p->adjvex]--;//对a顶点的每个直接后继结点的入度减1
				if(ve[a] + p->info>ve[p->adjvex])//更新最早开始时间(即到达该结点最长路径长度)
				ve[p->adjvex] = ve[a] + p->info;
				if (indegree[p->adjvex] == 0) {
					setOfZeroIndegree.enqueue(p->adjvex);
				}
				p = p->nextarc;

			}
		}
		if (count == G.vexnum) {
			for (int i = 0;i < count;i++)
				cout << "V" << resultOfTopSort[i] + 1 << "->";
			cout << endl;

		}
		else cout << ("拓扑排序:图有回路存在")<<endl;
		
	}

	void criticalPath(ALGraph&G) {//关键路径算法
		Stack<int>T(N);
		topSort(G, T);
		//逆拓扑排序
		for (int i = 0;i < N;i++)
			vl[i] = ve[N - 1];//初始化所有事件最晚开始时间都是项目结束事件的最晚开始时间
		if (T.top != N) {
			cout << "关键路径算法:存在环";
		}
		else {
			while (T.top != 0) {
				int a = T.pop();
				ArcNode*p = G.vertices[a].firstarc;
				while (p) {
					if (vl[p->adjvex] - p->info < vl[a])//最晚开始时间应该是所有后继结点p->adjvex减去p边权重中最小的
					vl[a] = vl[p->adjvex] - p->info;
					p = p->nextarc;
				}
			}
			/*for (int i = 0;i < N;i++) {
				cout << vl[i]<<endl;
		}*/
			int ee, el;
			for (int i = 0;i < G.vexnum;i++) {
				ArcNode*p = G.vertices[i].firstarc;
				while (p) {
					ee = ve[i];
					el = vl[p->adjvex] - p->info;
					cout << "<" << i + 1 << "," << p->adjvex + 1 << ">" << "=" << p->info << " " << ee << " " << el << " ";
					if (ee == el) {//如果活动的最早开始时间等于最晚开始时间,就是关键活动
						cout << "*";
					}
					cout << endl;
					p = p->nextarc;

				}


			}
		}
	}




int main()
{
	/*ALGraph g("123456789",1);
	g.addArc(0, 1);g.addArc(0, 2);g.addArc(0, 3);
	g.addArc(1, 4);g.addArc(2, 4);g.addArc(3, 5);
	g.addArc(4,6 );g.addArc(4, 7);g.addArc(5, 7);
	g.addArc(6, 8);g.addArc(7, 8);*/
	//测试环存在
	//g.addArc(5, 0);
	//g.addArc(3, 0);
	//g.output();
	/*Queue<char> Q(5);
	Q.enqueue('a');
	Q.enqueue('b');
	Q.enqueue('c');
	Q.dequeue();
	Q.output();*/
	//测试计算图中所有点的入度
	/*int indegree[4] = {0};
	findInDegree(g, indegree);
	for(int i = 0;i < 4;i++)
		cout << indegree[i];*/
	//验证获取图的边数
	//cout << g.getNumOfArc();
	
		//topSort(g);
	//Stack<char> s;
	//s.push('a');
	//s.output();


	//测试关键路径算法
	ALGraph	G("123456", 1);
	G.addArc(0,1,3);G.addArc(0,2,2);G.addArc(1,3,2);G.addArc(1,4,3);
	G.addArc(2,3,4);G.addArc(2,5,3);G.addArc(3,5,2);G.addArc(4,5,1);
	criticalPath(G);
	//测试回路
	//G.addArc(3, 0, 2);
	//criticalPath(G);
	return 0;
}

