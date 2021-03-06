// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<memory.h>
#include <iostream>
using namespace std;

#include "BinTree.hpp"
#include"HuffmanTree.hpp"


int main()
{
	//BinTree *tree;
	//int index = 0;
	//
	////测试前序创建
	//tree = BinTree::create("AB##CDF###E##", index);
	//cout << tree->deep();
	//cout << endl;

	////测试output函数
	//tree->output();

	////测试先序遍历
	//tree->preOrder();
	//cout << endl;

	////测试后序遍历
	//tree->postOrder();
	//cout << endl;

	////测试使用先序和后序,重构树
	//tree = BinTree::rebuildByPreIn("abdgcefh", "dgbaechf", 8);
	//tree->output();

	////测试中序遍历二叉排序树,得到升序排列的第k个结点
	//tree->output(0);//理论上应该是d
	//tree->output(4);//理论上应该是e

	//测试创建Huffman树
	HuffmanTree hTree(4);
	const char *str = "abcd";
	int weight[] = { 7,5,2,4 };
	hTree.create(str, weight);
	hTree.output();

	//测试编码
	char hcode[100];
	hTree.encode("dad", hcode);
	cout << "编码结果:" << hcode << endl;



	char code[100];
	hTree.decode(hcode, code);
	cout << "解码结果为:" << code;
	

	return 0;
}

    

