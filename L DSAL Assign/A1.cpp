#include <iostream>
using namespace std;

class treeNode
{
private:
    int info;
    treeNode *lChild, *rChild;

public:
    treeNode()
    {
        // info = 0;
        lChild = rChild = NULL;
    }
    treeNode(int x)
    {
        info = x;
        lChild = rChild = NULL;
    }
    friend class bTree;
    friend class Stack;
};

class bTree
{
    treeNode *root;
    treeNode *makeTree();
    void Rpreorder(treeNode *);
    void Rpostorder(treeNode *);
    void Rinorder(treeNode *);
    void NRpreorder(treeNode *);
    void NRpostorder(treeNode *);
    void NRinorder(treeNode *);
    treeNode *copyTree(treeNode *);
    int totalnode;
    int interlnode= 0;
public:
    bTree()
    {
        root = NULL;
    }
    void createTree()
    {
        root = makeTree();
    }
    treeNode *getRoot()
    {
        return root;
    }
    void Rtraversal(int choice);
    void NRtraversal(int choice);
    void mirrorImage(treeNode *tempRoot);
    void operator=(bTree &t)
    {
        this->root = t.copyTree(t.getRoot());
    }
    void deleteTree(treeNode *);
    int heightOfTree(treeNode *); // Recursive
    int Leafnode(treeNode *);
    int Internlnode(treeNode*);
    void setRoot(treeNode *val)
    {
        root = val;
    }
};

class Node
{
    treeNode *data;
    Node *next;

public:
    Node()
    {
        data = NULL;
        next = NULL;
    }
    Node(treeNode *x)
    {
        data = x;
        next = NULL;
    }
    friend class Stack;
    // friend class treeNode;
};

class Stack
{
    Node *top;

public:
    Stack()
    {
        top = NULL;
    }
    void push(treeNode *m);
    treeNode *pop();
    bool isEmpty();
    void displayElements();
};

bool Stack ::isEmpty()
{
    if (top == NULL)
        return true;
    else
        return false;
}

void Stack ::displayElements()
{
    Node *tempTop = top;
    while (tempTop != NULL)
    {
        cout << (tempTop->data)->info << " ";
        tempTop = tempTop->next;
    }
}

void Stack ::push(treeNode *m)
{
    Node *newNode = new Node(m);
    if (isEmpty())
    {
        top = newNode;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}

treeNode *Stack ::pop()
{
    if (!isEmpty())
    {
        Node *temp = top;
        top = temp->next;
        temp->next = NULL;
        return temp->data;
        // delete temp;
    }
    else
        return NULL;
}

treeNode *bTree ::makeTree()
{
    treeNode *temp = new treeNode;
    char ch;
    cout << "Enter the data: "; // Root
    cin >> temp->info;
    // Left child
    cout << "Does " << temp->info << " have Lchild present? (y/n): ";
    cin >> ch;
    if (ch == 'y')
        temp->lChild = makeTree();
    // Right child
    cout << "Does " << temp->info << " have Rchild present? (y/n): ";
    cin >> ch;
    if (ch == 'y')
        temp->rChild = makeTree();

    return temp;
}

void bTree ::Rtraversal(int choice)
{
    treeNode *tempRoot = root;
    if (choice == 1)
        Rpreorder(tempRoot);
    if (choice == 2)
        Rpostorder(tempRoot);
    if (choice == 3)
        Rinorder(tempRoot);
}
void bTree ::NRtraversal(int choice)
{
    treeNode *tempRoot = root;
    if (choice == 1)
        NRpreorder(tempRoot);
    if (choice == 2)
        NRpostorder(tempRoot);
    if (choice == 3)
        NRinorder(tempRoot);
}

void bTree ::Rpreorder(treeNode *tempRoot)
{
    if (tempRoot != NULL)
    {
        cout << tempRoot->info << " ";
        Rpreorder(tempRoot->lChild);
        Rpreorder(tempRoot->rChild);
    }
}
void bTree ::Rinorder(treeNode *tempRoot)
{
    if (tempRoot != NULL)
    {
        Rinorder(tempRoot->lChild);
        cout << tempRoot->info << " ";
        Rinorder(tempRoot->rChild);
    }
}
void bTree ::Rpostorder(treeNode *tempRoot)
{
    if (tempRoot != NULL)
    {
        Rpostorder(tempRoot->lChild);
        Rpostorder(tempRoot->rChild);
        cout << tempRoot->info << " ";
    }
}

void bTree ::NRpreorder(treeNode *tempNode)
{
    Stack s;
    s.push(tempNode);
    treeNode *smpl;
    while (!(s.isEmpty()))
    {
        smpl = s.pop();
        cout << smpl->info << " ";
        if (smpl->rChild != NULL)
            s.push(smpl->rChild);
        if (smpl->lChild != NULL)
            s.push(smpl->lChild);
    }
    cout << endl;
}
void bTree ::NRpostorder(treeNode *tempNode)
{
    Stack s1, s2;
    s1.push(tempNode);
    treeNode *smpl;
    while (!(s1.isEmpty()))
    {
        smpl = s1.pop();
        s2.push(smpl);
        if (smpl->lChild != NULL)
            s1.push(smpl->lChild);
        if (smpl->rChild != NULL)
            s1.push(smpl->rChild);
    }
    s2.displayElements();
}

void bTree ::NRinorder(treeNode *tempNode)
{
    Stack s3;
    treeNode *current = tempNode;
    while (current != NULL)
    {
        s3.push(current);
        current = current->lChild;
        while (current == NULL && !(s3.isEmpty()))
        {
            current = s3.pop();
            cout << current->info << " ";
            current = current->rChild;
        }
    }
}

void bTree ::mirrorImage(treeNode *tempRoot)
{
    if (tempRoot == NULL)
        return;
    else
    {
        mirrorImage(tempRoot->lChild);
        mirrorImage(tempRoot->rChild);
        treeNode *temp = tempRoot->lChild;
        tempRoot->lChild = tempRoot->rChild;
        tempRoot->rChild = temp;
    }
}

treeNode *bTree ::copyTree(treeNode *temproot)
{
    treeNode *copyNode = NULL;
    if (temproot != NULL)
    {
        copyNode = new treeNode(temproot->info);
        copyNode->lChild = copyTree(temproot->lChild);
        copyNode->rChild = copyTree(temproot->rChild);
    }
    return copyNode;
}

void bTree ::deleteTree(treeNode *tempRoot)
{
    if (tempRoot != NULL)
    {
        deleteTree(tempRoot->lChild);
        deleteTree(tempRoot->rChild);
        delete tempRoot;
    }
}

int bTree ::heightOfTree(treeNode *temp)
{
    if (temp == NULL)
        return 0;
    else
    {
        int lf_h = heightOfTree(temp->lChild);
        int rh_h = heightOfTree(temp->rChild);
        return (1 + max(lf_h, rh_h));
    }
} // actual height = height - 1

int bTree ::Internlnode(treeNode *p)
{
    if(p == NULL)
        return interlnode;
    else if (p->lChild != NULL || p->rChild != NULL){
        interlnode++;
        interlnode = Internlnode(p->lChild);
        interlnode = Internlnode(p->rChild);
        return interlnode;
    }
    else
        return interlnode;
}  // interlnode = actual no. of internal nodes - 1(root);

int bTree ::Leafnode(treeNode *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else if (p->lChild == NULL && p->rChild == NULL)
        return 1;
    else
        return Leafnode(p->lChild) + Leafnode(p->rChild);
}

int main()
{
    bTree T1, T2;
    int calculatedHeight, actualHeight;
    int count_in, count_lf, total;
    int ch, ch1;
    cout << "Menu" << endl;
    cout << "1. Create binary tree\n2. Recursive Traversal\n3. Non-recursive traversal\n4. Create "
         << "Mirror Image of tree\n5. Copy tree\n6. Height of the tree\n7. No. of leaf and internal nodes\n"
         << "8. Delete tree\n9. Exit\n";
    do
    {
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            // Create tree
            T1.createTree();
            break;
        case 2:
            // Recursive Traversal
            cout << "Which traversal you want?\n1. Preorder\n2. Postorder\n3. Inorder\n";
            cin >> ch1;
            T1.Rtraversal(ch1);
            break;
        case 3:
            // Non recursive traversal
            cout << "Which traversal you want?\n1. Preorder\n2. Postorder\n3. Inorder\n";
            cin >> ch1;
            T1.NRtraversal(ch1);
            break;
        case 4:
            //  Mirror Image
            T1.mirrorImage(T1.getRoot());
            cout << "We have done the mirror image of binary tree, you can check it by traversal.." << endl;
            break;
        case 5:
            // Copying tree
            T2 = T1;
            char ch2;
            cout << "Tree is copied. Do you want to traverse preorder? (y/n): ";
            cin >> ch2;
            if (ch2 == 'y')
                T2.Rtraversal(1);
            else
                continue;
            break;

        case 6:
            // height of tree
            calculatedHeight = T1.heightOfTree(T1.getRoot());
            actualHeight = calculatedHeight - 1;
            cout << "Height of the tree is: " << actualHeight << endl;
            break;
        case 7:
            // count of leaf node and internal node
            count_lf = T1.Leafnode(T1.getRoot());
            cout << "Number of leaf nodes in the tree: " << count_lf << endl;
            count_in = T1.Internlnode(T1.getRoot()); 
            cout << "Number of internal nodes in the tree: " << count_in - 1/*root*/ << endl;
            break;
        case 8:
            // delete tree
            T1.deleteTree(T1.getRoot());
            T1.setRoot(NULL);
            cout << "Tree is deleted!!!" << endl;
            break;
        case 9:
            cout<<"Program terminated !!"<<endl;
            break;
        default:
            cout<<"Invalid choice"<<endl;
            break;
        }
    } while (ch != 9);

    return 0;
}
