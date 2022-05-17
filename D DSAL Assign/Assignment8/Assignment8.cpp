/*
    The  Anonymous
*/
#include <bits/stdc++.h>
#include "Stack.h"

using namespace std;

class Graph
{
    int v, e;
public:
    int **matrix;
    Graph()
    {
        v = 0;
        e = 0;
        matrix = NULL;
    }

    void acceptGraph(int v, int e)
    {
        this->v = v;
        this->e = e;
        matrix = new int *[v];
        for (int i = 0; i < v; i++)
        {
            matrix[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                matrix[i][j] = 0;
            }
        }

        int x, y;
        for (int i = 0; i < e; i++)
        {
            cout << "Enter source for " << i + 1 << " node:\n";
            cin >> x;
            cout << "Enter destination for " << i + 1 << " node:\n";
            cin >> y;
            matrix[x][y] = 1;
            matrix[y][x] = -1;
        }
    }

    void display()
    {
        cout << "   ";
        for (int i = 0; i < v; i++)
        {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i << " ";
            for (int j = 0; j < v; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isLeaf(int node, bool *&vis)
    {
        for (int i = 0; i < v; i++)
        {
            if (matrix[node][i] == 1)
            {
                return false;
            }
        }
        return true;
    }

    bool isallvisited(int node, bool *&vis)
    {
        for (int i = 0; i < v; i++)
        {
            if (matrix[node][i] == 1)
            {
                if (vis[i] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void startSearchandDisplay()
    {
        bool *visited = new bool[v];
        for (int i = 0; i < v; i++)
        {
            visited[i] = 0;
        }
        stack<int> st;
        for (int i = 0; i < v; i++)
        {
            bool leafNode = true;
            if (!visited[i])
            {
                for (int j = 0; j < v; j++)
                {
                    if (matrix[i][j] == -1)
                    {
                        leafNode = false;
                        break;
                    }
                }

                if (leafNode)
                {
                    // cout<<i<<endl;
                    topoSort(i, visited, st);
                }
            }
        }

        while (!st.empty())
        {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }

    void topoSort(int node, bool *&visited, stack<int> &st)
    {
        visited[node] = 1;
        for (int i = 0; i < v; i++)
        {
            if (matrix[node][i] == 1)
            {
                if (!visited[i])
                {
                    topoSort(i, visited, st);
                }
                // st.push(node);
            }
        }
        if (isLeaf(node, visited) || isallvisited(node, visited))
        {
            st.push(node);
        }
    }
};
int main()
{
    Graph G;
    int v, e;
    cout << "Enter the number of vertices:\n";
    cin >> v;
    cout << "Enter the number of edges:\n";
    cin >> e;
    G.acceptGraph(v, e);
    G.display();
    G.startSearchandDisplay();
}