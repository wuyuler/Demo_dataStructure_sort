
#define LIST_INIT_SIZE 100//线性表存储空间的初始分配量
#define LIST_INCREMNT 2 //线性表存储空间的分配增量
#define LIST_SHRINK 2 //线性表收缩的量
template<typename T>
struct List
{
	T *elem;  //存储空间基址
	int length; //当前长度
	int listsize; //当前分配的存储容量

	List(int a = LIST_INIT_SIZE)
	{
		elem = new T[a];
		length = 0;
		listsize = a;
	}
	~List()
	{
		delete[] elem;
	}
	bool listInsert(int i, T a);         //插入
	bool listDelete(int i);             //删除
	void outPut();                      //输出
	void resize(int c) {
		//调整存储空间
		listsize = c;
		T*newdata = new T[listsize];
		if (elem != NULL) {
			memcpy(newdata, elem, length * sizeof(T));
			delete[]elem;
		}
		elem = newdata;
	}
	T &operator[](int index) {
		return elem[index];
	}
	void append(T e)//追加元素
	{
		if (length == listsize)//元素满了
			resize(listsize + LIST_INCREMNT);
		elem[length++] = e;
	}
};
template<typename T>
bool List<T>::listInsert(int i, T a)        //在第i位置插入a
{
	if (i<0 || i>length)
		return false;
	if (length == listsize)
	{
		T*p = new T[listsize + LIST_INCREMNT];
		for (int j = 0, k = 0; k < length; j++, k++)      //j表示新的需要插入a元素的线性表的元素,k表示原来的线性表的元素
		{
			if (j == i)
			{
				p[j] = a;
				j++;
			}
			p[j] = elem[k];

		}
		delete[] elem;
		elem = p;
		listsize += LIST_INCREMNT;
		return true;
	}
	for (int j = length; j > i; j--)
		elem[j] = elem[j - 1];
	elem[i] = a;
	length++;
	return true;

}
template<typename T>
bool List<T>::listDelete(int i)
{
	if (i<0 || i>length)
		return false;
	else
	{
		for (int j = i; j < length; j++)
			elem[j] = elem[j + 1];
		length--;
		if (length <= listsize - 2 * LIST_INCREMNT)         //余量多于两倍的分配增量时收缩
		{
			T*p = new T[listsize - LIST_SHRINK];
			for (int i = 0; i < length; i++)
			{
				p[i] = elem[i];

			}
			delete[] elem;
			elem = p;
			listsize -= LIST_SHRINK;
		}

		return true;

	}

};
template<typename T>
void List<T>::outPut()
{
	cout << "List:" << endl;
	for (int i = 0; i <length; i++)
		cout << elem[i] << ' ';
	cout << endl;
	cout << "ListSize:" << listsize << endl;
}