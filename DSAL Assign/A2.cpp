#include<iostream>
#include<string>
using namespace std;

class Node{
	string keyword, mean;
	Node *lchild, *rchild;
public:
	Node(){
		// keyword = mean = 0;
		lchild = rchild = NULL;
	}
	Node(string k, string m){
		keyword = k;
		mean = m;
		lchild = rchild = NULL;
	}
	friend class BST;
};

class BST{
	Node *root;
public:
int count_comp;
	BST(){
		root = NULL;
		count_comp = 0;
	}
	Node* getRoot(){
		return root;
	}
	void setRoot(Node *val){
		root = val;
	}
	void searchBST(string key, Node* &loc, Node* &par);
	void insert();
	void delete1BST(Node* &loc, Node* &par);
	void delete2BST(Node* &loc, Node* &par);
	void deleteBST(Node* &loc,Node* &par);
	void createDictionary(int n);
	void display_ascend(Node *p);
	void display_descend(Node *p);
};

void BST :: searchBST(string key, Node* &loc, Node* &par){
	//key is the value to be searched. loc gives address of key, par gives address of parent of key.
	count_comp = 0;
	if (root == NULL){
		count_comp++;
		cout<<"Tree does not exists."<<endl;
		return;
	}
	Node *ptr = root;
	while(ptr != NULL){
		count_comp++;
		if(ptr->keyword == key){
			// count++;
			loc = ptr;
			break;
		}
		else if(key < ptr->keyword){
			// count++;
			par = ptr;
			ptr = ptr->lchild;
		}
		else{
			// count++;
			par = ptr;
			ptr = ptr->rchild;
		}
	}
	if(loc == NULL){
		cout<<"Element not found in searching (can be inserted) !"<<endl;
	}
}

void BST :: insert(){
	string k; string m;
	cout<<"Enter keyword: ";
	cin>> k;
	cout<<"Enter meaning: ";
	cin>> m;
	Node *newNode = new Node(k, m);

	Node* loc = NULL; Node* par = NULL;
	searchBST(k, loc, par);

	if(loc == NULL && par == NULL)
		root = newNode;
	else if(loc == NULL){
		if(k< par->keyword)
			par->lchild = newNode;
		else
			par->rchild = newNode;
	}
	else
		cout<<"Cannot insert the duplicate element... \nPlease try to insert another keyword"<<endl;
}

void BST :: createDictionary(int n){// n is number of elements to be inserted
	Node *loc, *par;
	for (int i = 0; i< n; i++){
		loc = par = NULL;
		insert();
	}
}

void BST::display_ascend(Node *p){
	if (p != NULL){
		display_ascend(p->lchild);
		cout<<"KEY  = "<<p->keyword<<"\nMEAN = "<<p->mean<<endl;
		display_ascend(p->rchild);
	}
}

void BST::display_descend(Node *p){
	if (p != NULL){
		display_descend(p->rchild);
		cout<<"KEY  = "<<p->keyword<<"\nMEAN = "<<p->mean<<endl;
		display_descend(p->lchild);
	}
}

void BST :: delete1BST(Node* &loc, Node* &par){
	Node *child;
	if(loc->lchild == NULL && loc->rchild == NULL)// leaf node
		child = NULL;
	else if(loc->lchild != NULL){// have lchild
		child = loc->lchild;
		loc->lchild == NULL;
	}
	else{// have rchild
		child = loc->rchild;
		loc->rchild == NULL;
	}
	if(par != NULL){
		if(loc == par->lchild)
			par->lchild = child;
		else
			par->rchild = child;
	}
	else// if parent is NULL node to be deleted is root
		root = child;
}

void BST :: delete2BST(Node* &loc, Node* &par){
	Node *ptr1 = loc;
	Node *ptr2 = loc->rchild;
	while(ptr2->lchild != NULL){
		ptr1 = ptr2;
		ptr2 = ptr2->lchild;
	}
	delete1BST(ptr2, ptr1);
	if(par != NULL){
		if(loc == par->lchild)
			par->lchild = ptr2;
		else
			par->rchild = ptr2;
	}
	else	root = ptr2;
	ptr2->lchild = loc->lchild;
	ptr2->rchild = loc->rchild;
}

void BST ::deleteBST(Node* &loc,Node* &par){
	if(loc != NULL){
		if(loc->lchild != NULL && loc->rchild != NULL)
			delete2BST(loc, par);
		else	delete1BST(loc, par);
	}
	else
		cout<<"Element not found !"<<endl;
}

int main(){
	BST T;
	string key_search, key_delete, key_update;
	Node *LOC, *PAR;
	// int n;
	cout<<"1. Create dictionary\n2. Inserting new element\n3. Searching\n"<<
	"4. Deleting the element\n5. Updating the value\n6. Display elements in ascend\n"
	<<"7. Display elements in descend\n8. Exit\n"<<endl;
	int ch;
	do
	{
		cout<<"\nEnter your choice: ";
		cin>>ch;
		switch (ch)
		{
		case 1:
			int n;
			cout<<"Enter the number of elements to be inserted in dictionary: ";
			cin>> n;
			T.createDictionary(n);
			break;

		case 2:
			T.insert();
			break;

		case 3:
			LOC = PAR = NULL;
			cout<<"Enter the value you want to search: ";
			cin>>key_search;
			T.searchBST(key_search, LOC, PAR);
			cout<<"Number of comparisons made to find the element are: "<<T.count_comp<<endl;
			break;

		case 4:
			LOC = PAR = NULL;
			cout<<"Enter the keyword of element you want to delete: ";
			cin>>key_delete;
			T.searchBST(key_delete, LOC, PAR);
			T.deleteBST(LOC, PAR);
			cout<<"Element deleted..You can check by choice 6 or 7"<<endl;
			break;

		case 5:
			LOC = PAR = NULL;
			cout<<"Enter the keyword of element you want to update: ";
			cin>>key_update;
			T.searchBST(key_update, LOC, PAR);
			T.deleteBST(LOC, PAR);
			cout<<"**Enter the values of new element**"<<endl;
			T.insert();
			break;

		case 6:
			T.display_ascend(T.getRoot());
			break;

		case 7:
			T.display_descend(T.getRoot());
			break;

		case 8:
			cout<<"Terminated !!"<<endl;
			break;

		default:
			cout<<"Invalid choice"<<endl;
			break;
		}
	} while (ch != 8);
	return 0;
}

