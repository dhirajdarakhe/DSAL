#include <bits/stdc++.h>
using namespace std;

class Node
{

public:
    Node *left, *right;
    int data;
    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class BT
{
    Node *root;

public:
    BT()
    {
        root = NULL;
    }
    Node *getroot()
    {
        return root;
    }

    void insert()
    {
        int d;
        cout << "Enter root:\n";
        cin >> d;
        if (d == -1)
        {
            return;
        }
        root = new Node(d);
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            int l, r;
            cout << "Enter left child of " << temp->data;
            cin >> l;
            cout << "Enter right child of " << temp->data;
            cin >> r;
            if (l != -1)
            {
                Node *lnode = new Node(l);
                temp->left = lnode;
                q.push(lnode);
            }
            if (r != -1)
            {
                Node *rnode = new Node(r);
                temp->right = rnode;
                q.push(rnode);
            }
        }
    }

    void inorderrecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorderrecursive(root->left);
        cout << root->data << " ";
        inorderrecursive(root->right);
    }

    void preorderrecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preorderrecursive(root->left);
        preorderrecursive(root->right);
    }

    void postorderrecursive(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        postorderrecursive(root->left);
        postorderrecursive(root->right);
        cout << root->data << " ";
    }

    int height(Node *root)
    {
        if (root == NULL)
        {
            return -1;
        }
        int l = height(root->left);
        int r = height(root->right);
        return 1 + max(l, r);
    }

    void inorederiterative(Node *root)
    {
        stack<Node *> st;
        Node *temp = root;

        while (!st.empty() || temp != NULL)
        {
            while (temp != NULL)
            {
                // st.push(temp->right);
                st.push(temp);
                temp = temp->left;
            }
            Node *t = st.top();
            st.pop();
            cout << t->data << " ";
            temp = t->right;
        }
    }

    void leafnodes(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        leafnodes(root->left);
        leafnodes(root->right);
        if (root->left == NULL and root->right == NULL)
        {
            cout << root->data << " ";
        }
    }

    void interiornodes(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        interiornodes(root->left);
        interiornodes(root->right);
        if (root->left != NULL or root->right != NULL)
        {
            cout << root->data << " ";
        }
    }

    void mirrorimg(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        mirrorimg(root->right);
        mirrorimg(root->left);

        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    void copytree(Node* root1,Node* root2)
    {
        if(root2->left != NULL)
        {
            root1->left = new Node(root2->left->data);
            copytree(root1->left,root2->left);
        }
        if(root2->right != NULL)
        {
            root1->right = new Node(root2->right->data);
            copytree(root1->right,root2->right);
        }
    }
    void operator=(BT &b)
    {
        if (b.root == NULL)
        {
            root = new Node();
            return;
        }
        else
        {
            this->root = new Node(b.root->data);
            copytree(this->root,b.root);
        }
    }

    void iterativepreorder(Node* root)
    {
        stack<Node*> st;
        Node* temp = root;
        st.push(temp);
        while(!st.empty())
        {
            temp = st.top();
            st.pop();
            cout<<temp->data<<" ";
            st.push(temp->right);
            st.push(temp->left);
        }
    }

    Node *deletetree(Node *root, int t)
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
        Node *target = NULL;
        Node *parent = NULL, *deepest = NULL;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
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
        return root;
    }
};
int main()
{
    BT t;
    t.insert();
    Node *root = t.getroot();
    t.inorderrecursive(root);
    cout << endl;
    // t.preorderrecursive(root);
    // cout << endl;
    // t.postorderrecursive(root);
    // cout << endl;
    // // t.inorederiterative(root);
    // t.leafnodes(root);
    // cout << endl;
    // t.interiornodes(root);
    // cout << endl;
    // t.mirrorimg(root);
    root = t.deletetree(root,10);
    t.inorderrecursive(root);
    cout << endl;
}