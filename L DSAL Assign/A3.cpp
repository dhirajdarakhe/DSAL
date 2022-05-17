/*
 * A3_TBT.cpp
 *
 *  Created on: 23-Feb-2022
 *      Author: pict
 */
#include <iostream>
using namespace std;

class Node
{
	int data;
	Node *lchild, *rchild;
	bool lbit, rbit;

public:
	Node()
	{
		data = 0;
		lchild = rchild = NULL;
		lbit = rbit = false;
	}
	Node(int x)
	{
		data = x;
		lchild = rchild = NULL;
		lbit = rbit = false;
	}

	friend class TBT;
};

class TBT
{
	Node *root;
	Node *header = new Node();

public:
	TBT()
	{
		root = NULL;
		header->rchild = header;
		header->lchild = root;
	}
	void searchTBT(int key, Node *&loc, Node *&par);
	void insertTBT(int key);
	void inorder();
	void preorder();
	void delete_TBT_Node(Node *&loc, Node *&par);
};

void TBT ::insertTBT(int key)
{
	if (root == NULL)
	{
		root = new Node(key);
		root->lchild = header;
		root->rchild = header;
	}
	else
	{
		Node *ptr = root;
		Node *temp = new Node(key);
		while (1)
		{
			if (key < ptr->data)
			{
				if (ptr->lbit != 0)
				{
					ptr = ptr->lchild;
				}
				else
				{
					temp->rchild = ptr;
					temp->lchild = ptr->lchild;
					ptr->lchild = temp;
					ptr->lbit = 1;
					break;
				}
			}
			else
			{
				if (ptr->rbit != 0)
				{
					ptr = ptr->rchild;
				}
				else
				{
					temp->lchild = ptr;
					temp->rchild = ptr->rchild;
					ptr->rchild = temp;
					ptr->rbit = 1;
					break;
				}
			}
		}
	}
}

void TBT ::inorder()
{
	Node *temp = root;

	while (temp->lbit != 0)
	{
		temp = temp->lchild;
	}
	while (temp != header)
	{
		cout << temp->data << " ";
		if (temp->rbit != 0)
		{
			temp = temp->rchild;
			while (temp->lbit != 0)
			{
				temp = temp->lchild;
			}
		}
		else
		{
			temp = temp->rchild;
		}
	}
	cout << "\n";
}

void TBT ::preorder()
{
	Node *temp = root;
	while (temp != header)
	{
		cout << temp->data << " ";
		if (temp->lbit == 1)
			temp = temp->lchild;
		else
		{
			if (temp->rbit == 1)
				temp = temp->rchild;
			else
			{
				while (temp->rbit != 1 && temp != header)  // or we can do such that lbit of header is 1
				{
					temp = temp->rchild;
				}
				temp = temp->rchild;
			}
		}
	}
	cout << "\n";
}

void TBT ::searchTBT(int key, Node *&loc, Node *&par)
{
	// key is the value to be searched. loc gives address of key, par gives address of parent of key.
	//	count_comp = 0;
	if (root == NULL)
	{
		return;
	}
	Node *ptr = root;
	while (1)
	{
		if (ptr->data == key)
		{
			if (ptr == root)
				par = header;
			loc = ptr;
			break;
		}
		else if (key < ptr->data && ptr->lbit == 1)
		{
			par = ptr;
			ptr = ptr->lchild;
		}
		else if (key > ptr->data && ptr->rbit == 1)
		{
			par = ptr;
			ptr = ptr->rchild;
		}
		else
		{
			par = ptr;
			loc = NULL;
			// ptr = NULL;
			// free(ptr);
			break;
		}
	}
}

void TBT ::delete_TBT_Node(Node *&loc, Node *&par)
{
	if (loc == NULL && par != NULL)
		cout << "Node doesn't exits\n";
	if (loc->lbit == 1 && loc->rbit == 1)
	{
		Node *succ = loc->rchild;
		if (succ->lbit == 0)
			par = loc;
		else
		{
			while (succ->lbit != 0)
			{
				par = succ;
				succ = succ->lchild;
			}
		}
		loc->data = succ->data;
		loc = succ;
		delete_TBT_Node(loc, par);
		return;
	}
	if (loc->lbit == 0 && loc->rbit == 0)
	{
		if (par->lchild == loc)
		{
			par->lchild = loc->lchild;
			par->lbit = 0;
		}
		else if (par->rchild == loc)
		{
			par->rchild = loc->rchild;
			par->rbit = 0;
		}
		loc = NULL;
		free(loc);
		cout << "Succsessfully\n";
		return;
	}
	if (loc->lbit == 1 && loc->rbit == 0)
	{
		Node *temp = loc->lchild;
		if (par->lchild == loc)
		{
			par->lchild = temp;
		}
		else
		{
			par->rchild = temp;
		}
		while (temp->rbit == 1)
		{
			temp = temp->rchild;
		}
		temp->rchild = loc->rchild;
		free(loc);
		cout << "Succsessfully\n";
		return;
	}
	if (loc->lbit == 0 && loc->rbit == 1)
	{
		Node *temp = loc->rchild;
		if (par->lchild == loc)
		{
			par->lchild = temp;
		}
		else
		{
			par->rchild = temp;
		}
		while (temp->lbit == 1)
		{
			temp = temp->lchild;
		}
		temp->lchild = loc->lchild;
		free(loc);
		cout << "Succsessfully\n";
		return;
	}
}

int main()
{
	TBT T;
	int ch, n, key, data_delete;
	Node *LOC, *PAR;
	cout << "1. Insert element in TBT\n2. Inorder traversal\n3. Preorder traversal\n4. Delete\n5. Exit\n";
	do
	{
		cout << "Enter your choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "Enter how many elements you want to insert in TBT: ";
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "Enter the value:";
				cin >> key;
				T.insertTBT(key);
			}
			break;

		case 2:
			cout << "Inorder traversal is:\n";
			T.inorder();
			break;

		case 3:
			cout << "Preorder traversal is:\n";
			T.preorder();
			break;

		case 4:
			cout << "Enter the data you want to delete: ";
			cin >> data_delete;
			T.searchTBT(data_delete, LOC, PAR);
			// if(LOC == NULL && PAR == NULL)
			// 	cout<<"TBT does not exists."<<endl;
			T.delete_TBT_Node(LOC, PAR);
			break;

		case 5:
			cout << "End!!" << endl;
			break;

		default:
			cout << "Invalid choice !!" << endl;
			break;
		}
	} while (ch != 5);

	return 0;
}
