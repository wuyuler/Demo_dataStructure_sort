// demo_Hash.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include"HashMap.hpp"


int main()
{	
	HashMap<string, string> map(5);
	map.put("秦王", "李世民");
	map.put("唐太宗", "李世民");
	map.put("隋炀帝", "杨广");
	map.put("宋太祖", "赵匡胤");
	map.put("宋高宗", "赵构");
	map.put("秦王", "嬴政");
	map.put("清太祖", "努尔哈赤");

	map.output();
    return 0;
}

