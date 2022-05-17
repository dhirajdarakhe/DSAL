#include <bits/stdc++.h>

using namespace std;

class Graph
{
    int vertices;
    int **graph;

public:
    Graph()
    {
        vertices = 0;
    }
    Graph(int v)
    {
        vertices = v;
        graph = new int *[vertices];
        for (int i = 0; i < vertices; i++)
        {
            graph[i] = new int[vertices];
        }
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                graph[i][j] = 0;
            }
        }
    }

    void insert()
    {
        int a, b,w;
        cout << "Enter the vertices in which edge exist and its weight:\n";
        cin >> a >> b>>w;
        // int *temp1 = graph[a];
        // int *temp2 = graph[b];
        // temp1[b] = 1;
        // temp2[a] = 1;
        graph[a][b] = w;
        graph[b][a] = w;
    }

    void display()
    {
        cout << "Graph is:\n";
        for (int i = 0; i < vertices; i++)
        {
            int *temp = graph[i];
            for (int j = 0; j < vertices; j++)
            {
                cout << temp[j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }

    void prims()
    {
        int ans[vertices][vertices];
        for(int i=0;i<vertices;i++)
        {
            for(int j=0;j<vertices;j++)
            {
                ans[i][j] = 0;
            }
        }

        int father[vertices] = {-1};
        int reached[vertices] = {-1};
        reached[0] = 0;
        int cnt1 = 1, cnt = 0, t1, t2;
        while (cnt < vertices - 1)
        {
            int min = 999;
            for (int v1 = 0; v1 < cnt1; v1++)
            {
                for (int v2 = 0; v2 < vertices; v2++)
                {
                    if (graph[reached[v1]][v2] != 0 and graph[reached[v1]][v2] < min)
                    {
                        min = graph[reached[v1]][v2];
                        t1 = reached[v1];
                        t2 = v2;
                    }
                }
            }
            int temp1 = t1, temp2 = t2;
            graph[t1][t2] = 0;
            graph[t2][t1] = 0;
            int root1, root2;
            while (t1 >= 0)
            {
                root1 = t1;
                t1 = father[t1];
            }
            while(t2>=0)
            {
                root2 = t2;
                t2 = father[t2];
            }

            if(root1 != root2)
            {
                father[root2] = root1;
                reached[cnt1] = temp2;
                cnt1++;
                cnt++;
                ans[temp1][temp2] = graph[temp1][temp2];
                ans[temp2][temp1] = graph[temp2][temp1];
            }
        }

        cout<<"Minimum spanning tree is:\n";
        for(int i=0;i<vertices;i++)
        {
            for(int j=0;j<vertices;j++)
            {
                cout<<ans[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main()
{
    int v, e;
    cout << "Enter the number of edges:\n";
    cin >> e;
    cout << "Enter the number of vertices:\n";
    cin >> v;
    Graph g(v);
    for (int i = 0; i < e; i++)
    {
        g.insert();
    }
    g.display();
    g.prims();
}