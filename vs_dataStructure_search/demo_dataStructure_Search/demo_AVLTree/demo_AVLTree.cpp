// demo_AVLTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

#include"AVLTree.hpp"
int main()
{	
	AVLTree bst;
	bst.insert('a');
	bst.insert('b');
	bst.insert('c');
	bst.insert('f');
	bst.insert('e');
	bst.insert('d');

	bst.output();

    return 0;
}

