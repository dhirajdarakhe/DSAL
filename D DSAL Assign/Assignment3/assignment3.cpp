/*
    The  Anonymous
*/
#include <bits/stdc++.h>
using namespace std;

class Node
{

    int data;
    Node *left_child;
    Node *right_child;
    bool left;
    bool right;

public:
    Node()
    {
        data = 0;
        left_child = NULL;
        right = 0;
        right_child = NULL;
        left = 0;
    }
    Node(int x)
    {
        data = x;
        left_child = NULL;
        right = 0; // 0 stands for link and 1 stands for child
        right_child = NULL;
        left = 0;
    }
    friend class Threaded_BST;
};

class Threaded_BST
{
    Node *root;

public:
    Threaded_BST()
    {
        root = NULL;
    }

    void Insert(int key);
    Node *get_root();
    void Traverse_Inorder();
    void Traverse_Preorder();
    Node *inSuccesor(Node *ptr);
    Node *inPredecesor(Node *ptr);
    Node *LeafNodeTobeDeleted(Node *root, Node *par, Node *ptr);
    Node *NodeHasOneChild(Node *root, Node *par, Node *ptr);
    Node *NodeHasBothChilds(Node *root, Node *par, Node *ptr);
    Node *deleftedBST(Node *root, int dkey);
};

Node *Threaded_BST::inSuccesor(Node *ptr)
{
    if (ptr->right == 0)
        return ptr->right_child;

    ptr = ptr->right_child;
    while (ptr->left == 1)
        ptr = ptr->left_child;

    return ptr;
}

Node *Threaded_BST::inPredecesor(Node *ptr)
{
    if (ptr->left == 0)
        return ptr->left_child;

    ptr = ptr->left_child;
    while (ptr->right == 1)
        ptr = ptr->right_child;
    return ptr;
}

Node *Threaded_BST::LeafNodeTobeDeleted(Node *root, Node *par, Node *ptr)
{
    if (par == NULL)
        root = NULL;

    else if (ptr == par->left_child)
    {
        par->left = 0;
        par->left_child = ptr->left_child;
    }
    else
    {
        par->right = 0;
        par->right_child = ptr->right_child;
    }
    delete (ptr);
    return root;
}

Node *Threaded_BST::NodeHasOneChild(Node *root, Node *par, Node *ptr)
{
    Node *child;
    if (ptr->left == 1)
        child = ptr->left_child;
    else
        child = ptr->right_child;

    if (par == NULL)
        root = child;

    else if (ptr == par->left_child)
        par->left_child = child;
    else
        par->right_child = child;

    Node *s = inSuccesor(ptr);
    Node *p = inPredecesor(ptr);

    if (ptr->left == 1)
        p->right_child = s;
    else
    {
        if (ptr->right == 1)
            s->left_child = p;
    }

    delete (ptr);
    return root;
}

Node* Threaded_BST::NodeHasBothChilds(Node *root, Node *par, Node *ptr)
{
    Node *parsucc = ptr;
    Node *succ = ptr->right_child;

    while (succ->left == 1)
    {
        parsucc = succ;
        succ = succ->left_child;
    }

    ptr->data = succ->data;

    if (succ->left == 0 && succ->right == 0)
        root = LeafNodeTobeDeleted(root, parsucc, succ);
    else
        root = NodeHasOneChild(root, parsucc, succ);

    return root;
}

Node* Threaded_BST::deleftedBST(Node *root, int dkey)
{
    Node *par = NULL, *ptr = root;
    int found = 0;
    while (ptr != NULL)
    {
        if (dkey == ptr->data)
        {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->data)
        {
            if (ptr->left == 1)
                ptr = ptr->left_child;
            else
                break;
        }
        else
        {
            if (ptr->right == 1)
                ptr = ptr->right_child;
            else
                break;
        }
    }

    if (found == 0)
        printf("dkey not present in tree\n");

    else if (ptr->left == 1 && ptr->right == 1)
        root = NodeHasBothChilds(root, par, ptr);

    else if (ptr->left == 1)
        root = NodeHasOneChild(root, par, ptr);

    else if (ptr->right == 1)
        root = NodeHasOneChild(root, par, ptr);

    else
        root = LeafNodeTobeDeleted(root, par, ptr);

    return root;
}

Node *Threaded_BST::get_root()
{
    return root;
}

void Threaded_BST::Insert(int key)
{

    if (root == NULL)
    {
        root = new Node(key);
        return;
    }

    Node *temp = root;

    while (temp != NULL)
    {

        if (key > temp->data)
        {

            if (temp->right == 1)
            {
                temp = temp->right_child;
            }
            else
            {
                Node *new_node = new Node(key);
                new_node->left_child = temp;
                new_node->right_child = temp->right_child;
                temp->right = 1;
                temp->right_child = new_node;
                return;
            }
        }
        else if (key < temp->data)
        {

            if (temp->left == 1)
            {
                temp = temp->left_child;
            }
            else
            {
                Node *new_node = new Node(key);
                new_node->right_child = temp;
                new_node->left_child = temp->left_child;
                temp->left = 1;
                temp->left_child = new_node;
                return;
            }
        }
        else
        {
            cout << "Entered data is already present" << endl;
            return;
        }
    }
}

void Threaded_BST::Traverse_Inorder()
{

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "Inorder Traversal: ";
    Node *current = root;
    bool flag = 0;
    while (current != NULL)
    {

        while (current->left == 1 && flag == 0)
        {
            current = current->left_child;
        }

        cout << current->data << " ";

        if (current->right == 1)
        {
            flag = 0;
            current = current->right_child;
        }
        else
        {
            flag = 1;
            current = current->right_child;
        }
    }
    cout << endl;
}

void Threaded_BST::Traverse_Preorder()
{

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "Preorder Traversal: ";
    Node *temp = root;
    bool flag = 0;

    while (temp != NULL)
    {

        while (temp->left == 1 && flag == 0)
        {
            cout << temp->data << " ";
            temp = temp->left_child;
        }

        if (flag == 0)
        {
            cout << temp->data << " ";
        }

        if (temp->right == 1)
        {
            flag = 0;
            temp = temp->right_child;
        }
        else
        {
            flag = 1;
            temp = temp->right_child;
        }
    }
    cout << endl;
}

int main()
{

    Threaded_BST T;
    cout << "Enter the number of elements in tree: ";
    int n;
    cin >> n;
    while (n--)
    {
        int data;
        cout << "Enter the data: ";
        cin >> data;
        T.Insert(data);
    }
    cout << "Do you want to print elements(y/n): ";
    char c;
    cin >> c;
    if (c == 'y')
    {
        T.Traverse_Inorder();
        T.Traverse_Preorder();
    }
    cout << "Do you want to delete any element(y/n): ";
    char x;
    cin >> x;
    while (x == 'y')
    {
        cout << "Enter the data of node to be deleted: ";
        int d;
        cin >> d;
        Node* root = T.get_root();
        root = T.deleftedBST(root,d);
        cout << "Data deleted successfully" << endl;
        cout << "Do you want to print the elements(y/n): ";
        char f;
        cin >> f;
        if (f == 'y')
        {
            T.Traverse_Inorder();
        }
        cout << "Do you want to continue(y/n): ";
        cin >> x;
    }
    return 0;
}