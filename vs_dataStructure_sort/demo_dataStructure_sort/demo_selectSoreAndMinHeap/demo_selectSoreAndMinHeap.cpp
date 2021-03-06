// demo_selectSoreAndMinHeap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include"MinHeap.hpp"



void selectSort(int a[], int left, int right) {
	//对[left,right)进行排序
	int size = sizeof(a) / sizeof(int);
	for (int i = left; i < right; i++) {
		int min = a[i];
		int index_min = i;
		for (int j = i + 1; j < right; j++) {
			if (a[j] < min) {
				min = a[j];
				index_min = j;
			}

		}
		
		a[index_min] = a[i];
		a[i] = min;
		
	}
}

void show(int a[], int left, int right) {
	for (int i = left; i < right; i++) {
		cout << " " << a[i];
	}
}
int main()
{	
	int a[] = { 36,42,65,98,76,14,57,36 };
	int n = sizeof(a) / sizeof(int);
	show(a, 0, n);
	cout << endl;
	//selectSort(a, 0, n);
	MinHeap<int> H;
	H.sort(a, 0, n);
	show(a, 0, n);
    return 0;
}

