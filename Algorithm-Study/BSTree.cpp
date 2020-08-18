#include <iostream>
#include <cstdio>
#include <string.h>


struct DataNode
{
	int data;
	DataNode* pLeft;
	DataNode* pRight;
};

class BSTree
{
public:
	explicit BSTree();
	~BSTree();

public:
	void Insert(const int newValue);
	bool Find(const int newValue) const;
	bool Delete(const int value);


private:
	DataNode* MakeNode(const int newValue);

private:
	int m_height;
	int m_nodeSize;
	DataNode *m_node;
};

BSTree::BSTree()
	: m_height(0)
	, m_nodeSize(0)
	, m_node(NULL)
{
	
}

BSTree::~BSTree()
{

}

DataNode* BSTree::MakeNode(const int newValue)
{
	DataNode* newNode = new DataNode();
	newNode->data = newValue;
	newNode->pLeft = NULL;
	newNode->pRight = NULL;

	return newNode;
}

void BSTree::Insert(const int newValue)
{
	if(NULL == m_node)
	{
		DataNode* newNode = BSTree::MakeNode(newValue);

		m_node = newNode;
		std::cout << newValue << " is Inserted !" << std::endl;
	}
	else
	{
		DataNode* currNode = m_node;
		DataNode* prevNode = NULL;
		while(true)
		{
			bool bIsLeft = false;
			if(currNode->data > newValue)
			{
				prevNode = currNode;
				currNode = currNode->pLeft;

				bIsLeft = true;
			}
			else if(currNode->data < newValue)
			{	
				prevNode = currNode;
				currNode = currNode->pRight;
			}
			else
			{
				std::cout << "equal Value !" << std::endl;
				break;
			}

			if(currNode == NULL)
			{
				DataNode* newNode = BSTree::MakeNode(newValue);
				currNode = newNode;
				
				if(true == bIsLeft)
				{
					prevNode->pLeft = currNode;
				}
				else
				{
					prevNode->pRight = currNode;
				}

				std::cout << newValue << " is Inserted !" << std::endl;
				break;
			}
		}
	}
}

bool BSTree::Find(const int newValue) const
{
	bool retValue = false;
	int moveCount = 0;

	DataNode* currNode = m_node;
	while(true)
	{
		if(currNode->data == newValue)
		{
			retValue = true;
			break;
		}
		else if(currNode->data > newValue)
		{
			currNode = currNode->pLeft;			
		}
		else
		{
			currNode = currNode->pRight;
		}
		moveCount++;

		if(NULL == currNode)
		{
			break;
		}
	}
	
	if(true == retValue)
	{
		std::cout << newValue << " is Find ! (moveCount : " << moveCount << " )" << std::endl;
	}
	else
	{
		std::cout << "Not Found !" << std::endl;
	}
	
	return retValue;
}

bool BSTree::Delete(const int value)
{
	bool retValue = false;

	DataNode* currNode = m_node;
	DataNode* prevNode = NULL;
	while(true)
	{
		if(currNode->data == value)
		{
			retValue = true;

			if( (NULL != currNode->pLeft) &&
				(NULL != currNode->pRight) )
			{
				// 오른쪽 서브트리에서 최소 값을 가지는 노드를 옮김.
				// 오른쪽 서브트리가 없다면 왼쪽 서브트리에서 최대값을 가진 노드를 tarGetNode로
				DataNode* targetNode = NULL;
				DataNode* parentNode = currNode; // targetNode의 parent
				bool bIsRightChild = false;
				if(NULL != currNode->pRight)
				{
					targetNode = currNode->pRight;
					bIsRightChild = true;
				}
				else
				{
					targetNode = currNode->pLeft;
				}

				while(true)
				{
					if( (NULL == targetNode->pLeft) && (NULL == targetNode->pRight) )
					{
						// 마지막 레벨
						break;
					}

					if(true == bIsRightChild)
					{
						if( NULL != targetNode->pLeft)
						{
							parentNode = targetNode;
							targetNode = targetNode->pLeft;
						}
						else
						{
							// 현재 targetNode 가 가장 작은 값
							break;
						}
					}
					else
					{
						if(NULL != targetNode->pLeft)
						{
							parentNode = targetNode;
							targetNode = targetNode->pRight;
						}
						else
						{
							// 현재 targetNode가 가장 큰 값
							break;
						}
					}
				}

				/*
				* targetNode에 삭제할 노드의 Left, Right 를 연결시켜야함.
				* 삭제할 노드의 부모노드를 targetNode에 연결시켜야 함.
				* targetNode를 이미 가리키고 있던 부모노드에 대해 NULL 처리 해줘야함.
				*/

				// 삭제되는 currNode 의 부모 노드에 연결
				if(prevNode->pLeft->data == currNode->data)
				{
					prevNode->pLeft = targetNode;
				}
				else
				{
					prevNode->pRight = targetNode;
				}

				// currNode의 left, right 연결
				if(NULL != currNode->pLeft)
				{
					if(currNode->pLeft->data != targetNode->data)
					{
						targetNode->pLeft = currNode->pLeft;
					}

					currNode->pLeft = NULL;
				}

				if(NULL != currNode->pRight)
				{
					if(currNode->pRight->data != targetNode->data)
					{
						targetNode->pRight = currNode->pRight;
					}

					currNode->pRight = NULL;
				}

				// parentNode 에서 targetNode 에 해당되는 주소값 NULL
				if( (NULL != parentNode->pLeft) && (targetNode->data == parentNode->pLeft->data))
				{ 
					parentNode->pLeft = NULL;
				}
				else if((NULL != parentNode->pRight) && (targetNode->data == parentNode->pRight->data))
				{
					parentNode->pRight = NULL;
				}
				
			}
			else if( (NULL != currNode->pLeft) ||
					 (NULL != currNode->pRight) )
			{
				if(prevNode->pLeft->data == currNode->data)
				{
					if(NULL != currNode->pLeft)
					{
						prevNode->pLeft = currNode->pLeft;
					}
					else if(NULL != currNode->pRight)
					{
						prevNode->pLeft = currNode->pRight;
					}
				}
				else if(prevNode->pRight->data == currNode->data)
				{
					if(NULL != currNode->pLeft)
					{
						prevNode->pRight = currNode->pLeft;
					}
					else if(NULL != currNode->pRight)
					{
						prevNode->pRight = currNode->pRight;
					}
				}
			}
			else
			{
				if( (NULL != prevNode->pLeft) &&
					(prevNode->pLeft->data == currNode->data ))
				{
					prevNode->pLeft = NULL;
				}
				else if( (NULL != prevNode->pRight) &&
						 (prevNode->pRight->data == currNode->data))
				{
					prevNode->pRight = NULL;
				}
			}

			currNode->pLeft = NULL;
			currNode->pRight = NULL;
			delete[] currNode;
			currNode = NULL;
			
			break;
		}
		else if(currNode->data > value)
		{
			prevNode = currNode;
			currNode = currNode->pLeft;
		}
		else if(currNode->data < value)
		{
			prevNode = currNode;
			currNode = currNode->pRight;
		}

		if(NULL == currNode)
		{
			std::cout << "currNode is NULL ~!" << std::endl;
			break;
		}

	}

	if(true == retValue)
	{
		std::cout << value << " is Deleted ~!" << std::endl;
	}
	else
	{
		std::cout << value << " is NOT Deleted ~!" << std::endl;
	}

	return retValue;
}

int main()
{
	// 이진 탐색 트리
	BSTree bsTree;

	bsTree.Insert(35);
	bsTree.Insert(18);
	bsTree.Insert(68);
	bsTree.Insert(7);
	//bsTree.Insert(26);
	bsTree.Insert(3);
	bsTree.Insert(12);
	//bsTree.Insert(22);
	//bsTree.Insert(30);
	bsTree.Insert(99);

	//std::cout << "Find Start ~!" << std::endl;

	//(void)bsTree.Find(3);
	//(void)bsTree.Find(1);
	//(void)bsTree.Find(9);

	std::cout << "Delete Start ~!" << std::endl;

	// Right's Sub Tree
	//(void)bsTree.Delete(18);
	//(void)bsTree.Delete(22);
	//(void)bsTree.Delete(26);

	// Left's Sub Tree
	(void)bsTree.Delete(18);
	(void)bsTree.Delete(7);

	return 0;
}