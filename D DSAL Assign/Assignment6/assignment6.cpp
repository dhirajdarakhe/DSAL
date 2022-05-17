/*
    The  Anonymous
*/
#include <bits/stdc++.h>
#include "Queue.h"
#include "Stack.h"

using namespace std;

class GraphNode
{
    int data;
    GraphNode *next;

public:
    GraphNode()
    {
        data = 0;
        next = NULL;
    }
    GraphNode(int d)
    {
        data = d;
        next = NULL;
    }
    friend class Graph;
};

class Graph
{
    int vertices;
    GraphNode **graph;

public:
    Graph()
    {
        vertices = 0;
    }
    Graph(int v)
    {
        vertices = v;
        graph = new GraphNode *[vertices];
        for (int i = 0; i < vertices; i++)
        {
            graph[i] = NULL;
        }
    }

    void BFS(int start)
    {
        cout << "BFS traversal is:\n";
        int *visited = new int[vertices];
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = 0;
        }
        queue<int> q;
        q.push(start);
        visited[start] = 1;
        while (!q.empty())
        {
            int p = q.front();
            q.pop();
            cout << p << " ";
            GraphNode *temp = graph[p];
            while (temp != NULL)
            {
                if (visited[temp->data] == 0)
                {
                    q.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout << "\n";
    }

    void dfs(int start)
    {
        cout << "DFS traversal is:\n";
        int *visited = new int[vertices];
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = 0;
        }
        stack<int> st;
        st.push(start);
        visited[start] = 1;
        while (!st.empty())
        {
            int p = st.top();
            st.pop();
            cout << p << " ";
            GraphNode *temp = graph[p];
            while (temp != NULL)
            {
                if (visited[temp->data] == 0)
                {
                    st.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout << "\n";
    }

    void display()
    {
        cout << "Graph is:\n";
        for (int i = 0; i < vertices; i++)
        {
            GraphNode *temp = graph[i];
            cout << i << ":";
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void insert()
    {
        int a, b;
        cout << "Enter the vertices in which edge is present:\n";
        cin >> a >> b;
        GraphNode *temp1 = graph[a];
        if (temp1 == NULL)
        {
            // cout<<"h\n";
            GraphNode *node = new GraphNode(b);
            graph[a] = node;
        }
        else
        {
            GraphNode *node = new GraphNode(b);
            while (temp1->next != NULL)
            {
                temp1 = temp1->next;
            }
            temp1->next = node;
        }
    }
};

int main()
{
    int v;
    int ed;
    cout << "ENter number of edges:\n";
    cin >> ed;
    cout << "ENter number of vertices:\n";
    cin >> v;
    Graph g(v);
    for (int i = 0; i < ed; i++)
    {
        g.insert();
    }
    g.dfs(0);
    g.display();
    g.BFS(0);
}