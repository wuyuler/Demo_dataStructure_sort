
#define LIST_INIT_SIZE 100//���Ա��洢�ռ�ĳ�ʼ������
#define LIST_INCREMNT 2 //���Ա��洢�ռ�ķ�������
#define LIST_SHRINK 2 //���Ա���������
template<typename T>
struct List
{
	T *elem;  //�洢�ռ��ַ
	int length; //��ǰ����
	int listsize; //��ǰ����Ĵ洢����

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
	bool listInsert(int i, T a);         //����
	bool listDelete(int i);             //ɾ��
	void outPut();                      //���
	void resize(int c) {
		//�����洢�ռ�
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
	void append(T e)//׷��Ԫ��
	{
		if (length == listsize)//Ԫ������
			resize(listsize + LIST_INCREMNT);
		elem[length++] = e;
	}
};
template<typename T>
bool List<T>::listInsert(int i, T a)        //�ڵ�iλ�ò���a
{
	if (i<0 || i>length)
		return false;
	if (length == listsize)
	{
		T*p = new T[listsize + LIST_INCREMNT];
		for (int j = 0, k = 0; k < length; j++, k++)      //j��ʾ�µ���Ҫ����aԪ�ص����Ա���Ԫ��,k��ʾԭ�������Ա���Ԫ��
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
		if (length <= listsize - 2 * LIST_INCREMNT)         //�������������ķ�������ʱ����
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