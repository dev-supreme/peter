#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum _NODETYPE
{
	TWO_NODE,
	THREE_NODE,
	FOUR_NODE
};

typedef struct _node
{
	int data[3];
	int nodeType;
	struct _node* child[4];
	struct _node* parent;
}NODE;

NODE* createNode(int data)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	memset(newNode, 0, sizeof(NODE));
	newNode->data[0] = data;

	return newNode;
}

int insertNode(NODE** root, int data) 
{
	NODE* pNode = *root;
	if (NULL == pNode)
	{
		*root = createNode(data);
	}
	else
	{
		// search a leaf node
		while (1)
		{
			// consider a path 
			if (TWO_NODE == pNode->nodeType)
			{
				if (NULL == pNode->child[0])
				{
					// insert data
					if (data < pNode->data[0])
					{
						// shift
						pNode->data[1] = pNode->data[0];
						pNode->data[0] = data;
					}
					else if (data > pNode->data[0])
					{
						pNode->data[1] = data;
					}
					pNode->nodeType = THREE_NODE;
					break;
				}
				else
				{
					if (data < pNode->data[0])
						pNode = pNode->child[0];
					else if (data > pNode->data[0])
						pNode = pNode->child[1];
				}
				
			}
			else if (THREE_NODE == pNode->nodeType)
			{
				if (NULL == pNode->child[0])
				{
					// insert data
					if (data < pNode->data[0])
					{
						pNode->data[2] = pNode->data[1];
						pNode->data[1] = pNode->data[0];

						pNode->data[0] = data;
					}
					else if (data > pNode->data[0] && data < pNode->data[1])
					{
						pNode->data[2] = pNode->data[1];

						pNode->data[1] = data;
					}					
					else if (data > pNode->data[1])
					{
						pNode->data[2] = data;
					}

					pNode->nodeType = FOUR_NODE;

					break;
				}
				else
				{
					if (data < pNode->data[0])
						pNode = pNode->child[0];
					else if (data > pNode->data[0] && data < pNode->data[1])
						pNode = pNode->child[1];
					else if (data > pNode->data[1])
						pNode = pNode->child[2];
				}
			}
			else if (FOUR_NODE == pNode->nodeType)
			{
				// split
				if (NULL == pNode->parent)
				{
					NODE* newNode1 = createNode(pNode->data[0]);
					NODE* newNode2 = createNode(pNode->data[2]);

					pNode->nodeType = TWO_NODE;
					pNode->data[0] = pNode->data[1];
					pNode->data[1] = pNode->data[2] = 0;
					pNode->child[0] = newNode1;
					pNode->child[1] = newNode2;

					newNode1->parent = pNode;
					newNode2->parent = pNode;						
				}
				else
				{
					// split implementation
					if (TWO_NODE == pNode->parent->nodeType)
					{
						if (pNode == pNode->parent->child[0])
						{
							// shift
							pNode->parent->data[1] = pNode->parent->data[0];
							pNode->parent->data[0] = pNode->data[1];

							pNode->parent->child[2] = pNode->parent->child[1];
							pNode->parent->child[1] = pNode->parent->child[0]; 
							pNode->parent->nodeType = THREE_NODE;

							// newnode == left
							NODE* newNode = createNode(pNode->data[0]);
							newNode->parent = pNode->parent;
							pNode->parent->child[0] = newNode;

							pNode->nodeType = TWO_NODE;

							if (NULL != pNode->child[0])
							{
								newNode->child[0] = pNode->child[0];
								newNode->child[1] = pNode->child[1];
								pNode->child[0] = pNode->child[2];
								pNode->child[1] = pNode->child[3];
							}

							if (data < pNode->parent->data[0])
								pNode = pNode->parent->child[0];
							else if (data > pNode->parent->data[0])
								pNode = pNode->parent->child[1];

						}
						else if(pNode == pNode->parent->child[1])
						{
							pNode->parent->data[1] = pNode->data[1];
							pNode->parent->nodeType = THREE_NODE;

							// newnode == right
							NODE* newNode = createNode(pNode->data[2]);
							newNode->parent = pNode->parent;
							pNode->parent->child[2] = newNode;

							pNode->nodeType = TWO_NODE;

							if (NULL != pNode->child[0])
							{
								newNode->child[0] = pNode->child[2];
								newNode->child[1] = pNode->child[3];
							}

							if (data < pNode->parent->data[1])
								pNode = pNode->parent->child[1];
							else if (data > pNode->parent->data[1])
								pNode = pNode->parent->child[2];
						}
					}
					else if (THREE_NODE == pNode->parent->nodeType)
					{
						// need implement
					}

				}
			}
		}		
	}


	return 0;
}

int main(void)
{
	NODE* root = NULL;

	insertNode(&root, 5);
	insertNode(&root, 1);
	insertNode(&root, 19);
	insertNode(&root, 25);
	insertNode(&root, 17);
	insertNode(&root, 22);
	insertNode(&root, 4);



	return 0;
}