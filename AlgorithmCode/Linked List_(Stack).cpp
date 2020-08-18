#include <iostream>
#include <cstdio>
#include <string.h>


#define INIT_VALUE 0

template <typename T>
struct DataNode
{
	T data;
	DataNode<T>* pPrev;
	DataNode<T>* pNext;
};

template <typename T>
class LinkedList
{
public:
	LinkedList(const int length = 3);
	~LinkedList();

public:
	void Push(const T& newValue);
	T Pop();

private:
	int m_size;

	DataNode<T>* m_ptr;
};

template <typename T>
LinkedList<T>::LinkedList(const int _length)
	: m_size(INIT_VALUE)
	, m_ptr(NULL)
{
	m_ptr = new DataNode<T>();
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	DataNode<T>* pDelNode = m_ptr;

	for(int size = 0; size < (m_size - 1); size++)
	{
		pDelNode = pDelNode->pNext;
	}

	for(int size = 0; size < (m_size -1); size++)
	{
		DataNode<T>* pPrevNode = pDelNode->pPrev;
		
		delete[] pDelNode;
		pDelNode = NULL;

		pDelNode = pPrevNode;
	}

	delete[] pDelNode;
	pDelNode = NULL;
}

template <typename T>
void LinkedList<T>::Push(const T& newValue)
{
	DataNode<T> *temp = new DataNode<T>();
	temp->data = newValue;
	temp->pNext = NULL;
	temp->pPrev = NULL;

	if( INIT_VALUE == m_size)
	{
		m_ptr = temp;
	}
	else
	{
		DataNode<T>* pHeader = m_ptr;
		while(NULL != pHeader->pNext)
		{
			pHeader = pHeader->pNext;
		}
		pHeader->pNext = temp;
		pHeader->pNext->pPrev = pHeader;
	}

	m_size++;
}

template <typename T>
T LinkedList<T>::Pop()
{
	T tempData = NULL;
	DataNode<T>* pHeader = m_ptr;
	for(int sizeIdx = 0; sizeIdx < (m_size - 1); sizeIdx++)
	{
		pHeader = pHeader->pNext;
	}
	tempData = pHeader->data;

	delete[] pHeader;
	pHeader = NULL;

	m_size--;
	return tempData;
}

template <typename T>
void Resize(const int length)
{

}

int main()
{
	LinkedList<int> stack;

	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);

	std::cout << stack.Pop() << std::endl;
	std::cout << stack.Pop() << std::endl;
	std::cout << stack.Pop() << std::endl;


	return 0;
}