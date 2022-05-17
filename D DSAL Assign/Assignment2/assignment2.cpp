/*
    The  Anonymous
*/
#include <bits/stdc++.h>
using namespace std;
class Node
{
    Node *left, *right;
    string key, meaning;
public:
    Node()
    {
        left = right = NULL;
    }
    Node(string Key, string value)
    {
        left = NULL;
        right = NULL;
        key = Key;
        meaning = value;
    }
    friend class BST;
};
class BST
{
    Node *root;
public:
    BST()
    {
        root = NULL;
    }
    Node *insert(Node *root, string key, string meaning)
    {
        if (root == NULL)
        {
            root = new Node(key, meaning);
        }
        else if (key <= root->key)
        {
            root->left = insert(root->left, key, meaning);
        }
        else
        {
            root->right = insert(root->right, key, meaning);
        }
        return root;
    }
    void inorderRecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorderRecursive(root->left);
        cout << root->key << " => " << root->meaning << endl;
        inorderRecursive(root->right);
    }
    void Descending(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        Descending(root->right);
        cout << root->key << " => " << root->meaning << endl;
        Descending(root->left);
    }
    Node *FindMin(Node *temp)
    {
        Node *cur = temp;
        while (cur != NULL && cur->left != NULL)
        {
            cur = cur->left;
        }
        return cur;
    }
    Node *Delete(Node *root, string key)
    {
        if (root == NULL)
            return root;
        else if (root->key > key)
        {
            root->left = Delete(root->left, key);
        }
        else if (root->key < key)
        {
            root->right = Delete(root->right, key);
        }
        else
        {
            if ((root->left == NULL) && (root->right == NULL))
            {
                delete root;
                root = NULL;
                return root;
            }
            else if (root->left == NULL)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                Node *temp = FindMin(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = Delete(root->right, temp->key);
            }
        }
        return root;
    }
    void findKeyandUpdate(Node *root, string key, string meaning)
    {
        if (root == NULL)
        {
            return;
        }
        else if (root->key == key)
        {
            root->meaning = meaning;
        }
        else if (key < root->key)
        {
            findKeyandUpdate(root->left, key, meaning);
        }
        else
        {
            findKeyandUpdate(root->right, key, meaning);
        }
    }
    void findKey(Node *root, string key)
    {
        static int cmp = 0;
        if (root == NULL)
        {
            return;
        }
        else if (root->key == key)
        {
            cout << "Key is present in tree!\n";
            cout << root->key << " => " << root->meaning << endl;
            cout << "Key found in " << cmp << " comparisons.\n";
        }
        else if (key < root->key)
        {
            cmp++;
            findKey(root->left, key);
        }
        else
        {
            cmp++;
            findKey(root->right, key);
        }
    }
    Node *getRoot()
    {
        return root;
    }
};
int main()
{
    cout << "-----------Main Menu---------------\n";
    cout << "1.Insert a word in dictionary\n2.Find a word in dictionary\n";
    cout << "3.Updating the existing data\n4.Printing in ascending and descending order\n";
    cout << "5.Deleting data from dictionary.\n";
    BST B;
    int choice;
    char flag;
    string key, meaning;
    Node *root = B.getRoot();
    do
    {
        cout << "Enter choice:\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the key:\n";
            cin >> key;
            cout << "Enter the meaning for key:\n";
            cin >> meaning;
            root = B.insert(root, key, meaning);
            break;
        case 2:
            cout << "Enter the key which is to be found:\n";
            cin >> key;
            B.findKey(root, key);
            break;
        case 3:
            cout << "Enter the key which is wanted to be updated:\n";
            cin >> key;
            cout << "Enter the new meaning for this key:\n";
            cin >> meaning;
            B.findKeyandUpdate(root, key, meaning);
            break;
        case 4:
            cout << "Ascending order:\n";
            B.inorderRecursive(root);
            cout << endl;
            cout << "Descending order:\n";
            B.Descending(root);
            break;
        case 5:
            cout << "Enter the key which is to be deleted:\n";
            cin >> key;
            root = B.Delete(root, key);
            break;
        }
        cout << "Do you want to continue?\n";
        cin >> flag;
    } while (flag != 'n');
}