/*
    The  Anonymous
*/
#include <iostream>
#include <bits/stdc++.h>
#include "Queue.h"
#include "Stack.h"
using namespace std;
class TreeNode
{
    int data;
    TreeNode *left, *right;
public:
    TreeNode()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
    TreeNode(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
    friend class BinaryTree;
};
class BinaryTree
{
    TreeNode *root;
public:
    BinaryTree()
    {
        root = NULL;
    }
    void insert()
    {
        Queue<TreeNode *> q;
        int rootData;
        cout << "Enter data of root: ";
        cin >> rootData;
        if (rootData == -1)
        {
            return;
        }
        root = new TreeNode(rootData);
        q.push(root);
        while (!q.isEmpty())
        {
            int leftD;
            int rightD;
            TreeNode *temp = q.frontData();
            q.pop();
            cout << "Enter left child of " << temp->data << ": ";
            cin >> leftD;
            cout << "Enter right child of " << temp->data << ": ";
            cin >> rightD;
            if (leftD != -1) //             10
            {                //        20         30
                TreeNode *leftNode = new TreeNode(leftD);
                temp->left = leftNode; // queue= 10
                q.push(leftNode);      // queue = 20 30
            }
            if (rightD != -1)
            {
                TreeNode *rightNode = new TreeNode(rightD);
                temp->right = rightNode;
                q.push(rightNode);
            }
        }
    }
    void insertRecursive(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        int leftD;
        int rightD;
        cout << "Enter left child of " << root->data << ": ";
        cin >> leftD;
        cout << "Enter right child of " << root->data << ": ";
        cin >> rightD;
        if (leftD != -1)
        {
            TreeNode *leftNode = new TreeNode(leftD);
            root->left = leftNode;
        }
        if (rightD != -1)
        {
            TreeNode *rightNode = new TreeNode(rightD);
            root->right = rightNode;
        }
        insertRecursive(root->left);
        insertRecursive(root->right);
    }
    void insertRecursive() // this function is just to create root
    {
        int rootData;
        cout << "Enter data of root: ";
        cin >> rootData;
        if (rootData == -1)
        {
            return;
        }
        root = new TreeNode(rootData);
        insertRecursive(root);
    }
    void inorderRecursive(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorderRecursive(root->left);
        cout << root->data << " ";
        inorderRecursive(root->right);
    }
    void postorderRecursive(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        cout << root->data << " ";
    }
    void preorderRecursive(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }
    void preorderIterative()
    {
        Stack<TreeNode *> s;
        s.push(root);
        while (!s.isEmpty())
        {
            TreeNode *temp = s.topData();
            s.pop();
            if (temp != NULL)
            {
                cout << temp->data << " ";
                s.push(temp->right);
                s.push(temp->left);
            }
        }
    }
    void postorderIterative()
    {
        if (root == NULL)
        {
            return;
        }
        Stack<TreeNode *> s1;
        Stack<TreeNode *> s2;
        TreeNode *current;
        s1.push(root);
        while (!s1.isEmpty())
        {
            current = s1.topData();
            s1.pop();
            s2.push(current);
            if (current->left != NULL)
            {
                s1.push(current->left);
            }
            if (current->right != NULL)
            {
                s1.push(current->right);
            }
        }
        while (!s2.isEmpty())
        {
            cout << s2.topData()->data << " ";
            s2.pop();
        }
    }
    void inorderIterative()
    {
        Stack<TreeNode *> s;
        TreeNode *current;
        if (root == NULL)
        {
            return;
        }
        current = root;
        while (current != NULL || !s.isEmpty())
        {
            while (current != NULL)
            {
                s.push(current);
                current = current->left;
            }
            current = s.topData();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }
    TreeNode *getRoot()
    {
        return root;
    }
    void leafchild(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        leafchild(root->left);
        leafchild(root->right);
        if ((root->left == NULL) && (root->right == NULL))
        {
            cout << root->data << " ";
        }
    }
    void interiorChild(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        interiorChild(root->left);
        interiorChild(root->right);
        if ((root->left != NULL) || (root->right != NULL))
        {
            cout << root->data << " ";
        }
    }
    void mirrorImg(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        mirrorImg(root->right);
        mirrorImg(root->left);
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    TreeNode *deletetree(TreeNode *root, int t)
    {
        if (root == NULL)
        {
            return root;
        }
        if (root->right == NULL and root->left == NULL)
        {
            delete (root);
            return NULL;
        }
        TreeNode *target = NULL;
        TreeNode *parent = NULL, *deepest = NULL;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *temp = q.front();
            q.pop();
            if (temp->data == t)
            {
                target = temp;
            }
            if (temp->left != NULL)
            {
                q.push(temp->left);
                parent = temp;
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
                parent = temp;
            }
            deepest = temp;
        }
        if (target == NULL)
        {
            cout << "target is not present.\n";
        }
        else
        {
            target->data = deepest->data;
            if(parent->left == deepest)
            {
                delete(deepest);
                parent->left = NULL;
            }
            else{
                delete(deepest);
                parent->right = NULL;
            }
        }
    }
    void copyTree(TreeNode *root1, TreeNode *root2)
    {
        if (root2->left != NULL)
        {
            root1->left = new TreeNode(root2->left->data);
            copyTree(root1->left, root2->left);
        }
        if (root2->right != NULL)
        {
            root1->right = new TreeNode(root2->right->data);
            copyTree(root1->right, root2->right);
        }
    }
    void operator=(const BinaryTree &B)
    {
        if (B.root == NULL)
        {
            root = new TreeNode();
        }
        else
        {
            this->root = new TreeNode(B.root->data);
            copyTree(this->root, B.root);
        }
    }
    int heightofTree(TreeNode *root)
    {
        if (root == NULL)
        {
            return -1;
        }
        int left = heightofTree(root->left);
        int right = heightofTree(root->right);

        return 1 + max(left, right);
    }
};

int main()
{
    cout << "----------Main Menu-----------\n";
    cout << "1.inoreder recursive\n2.Preoreder recursive\n3.Postoreder recursive\n";
    cout << "4.Inoreder iterative\n5.Preoreder iterative\n6.Postoreder Iterative\n";
    cout << "7.Find all leaf childs\n8.Find all interior childs\n";
    cout << "9.Find height of tree\n10.Copy tree\n11.insert element in tree\n";
    cout<<"12.Delete element from tree.\n";
    int choice, h,temp;
    char flag;
    BinaryTree T, A;
    TreeNode *root,*root1;
    do
    {
        cout << "Enter choice:\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            T.inorderRecursive(root);
            cout << endl;
            break;
        case 2:
            T.preorderRecursive(root);
            cout << endl;
            break;
        case 3:
            T.postorderRecursive(root);
            cout << endl;
            break;
        case 4:
            T.inorderIterative();
            cout << endl;
            break;
        case 5:
            T.preorderIterative();
            cout << endl;
            break;
        case 6:
            T.postorderIterative();
            cout << endl;
            break;
        case 7:
            T.leafchild(root);
            cout << endl;
            break;
        case 8:
            T.interiorChild(root);
            cout << endl;
            break;
        case 9:
            h = T.heightofTree(root);
            cout << h << endl;
            break;
        case 10:
            A = T;
            cout<<"New Tree is:\n";
            root1 = A.getRoot();
            A.inorderRecursive(root1);
            cout << endl;
            break;
        case 11:
            T.insertRecursive();
            root = T.getRoot();
            break;
        case 12:
            cout<<"Enter element to be deleted:\n";
            cin>>temp;
            A.deletetree(root,temp);
        default:
            break;
        }
        cout << "Do you want to continue?\n";
        cin >> flag;
    } while (flag != 'n');
}
