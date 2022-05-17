/*
    The  Anonymous
*/
#include <iostream>
using namespace std;
class Graph
{
    int v, e;
    int **matrix;
public:
    Graph()
    {
        v = 0;
        e = 0;
        matrix = NULL;
    }
    void acceptGraph()
    {
        cout << "Enter number of vertices: ";
        cin >> v;
        cout << "Enter number of edges: ";
        cin >> e;
        matrix = new int *[v];
        for (int i = 0; i < v; i++)
        {
            matrix[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < e; i++)
        {
            int s, d, w;
            cout << "Enter 1st vertex of edge " << i + 1 << ": ";
            cin >> s;
            cout << "Enter 2nd vertex of edge " << i + 1 << ": ";
            cin >> d;
            cout << "Enter weight of edge " << i + 1 << ": ";
            cin >> w;
            matrix[s][d] = w;
            matrix[d][s] = w;
        }
    }
    void display()
    {
        cout << "Adjacency Matrix:\n";
        cout << "   ";
        for (int i = 0; i < v; i++)
        {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i << ": ";
            for (int j = 0; j < v; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void prims()
    {
        int startVertex = 0;
        cout << "Minimum spanning tree: \n";
        if (v == 0)
        {
            return;
        }
        int *minDist = new int[v]; // array of minimum distances..
        int *connectingVertex = new int[v]; // -1 if not taken in MST, -2 if vertex is visited.
        int **mst = new int*[v];
        //below code is kind of initialisation using start vertex = 0.
        for (int i = 0; i < v; i++)
        {
            if (matrix[startVertex][i] != 0)
            {
                connectingVertex[i] = startVertex;
                minDist[i] = matrix[startVertex][i];
            }
            else
            {
                connectingVertex[i] = -1;
                minDist[i] = 1e8;
            }
        }
        connectingVertex[startVertex] = -2; // set 0 as visited.
        // setting all nodes of MST as empty mamtrix(initialisation).
        for (int i = 0; i < v; i++)
        {
            mst[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                mst[i][j] = 0;
            }
        }
        while (true)
        {
            int currMinDist = 1e8;
            int minDistVertex = -1;
            //below code is for traversing min distance array and extracting minimum distance and node with minimum distance. 
            for (int i = 0; i < v; i++)
            {
                if (minDist[i] != -1)
                {
                    if (minDist[i] < currMinDist)
                    {
                        currMinDist = minDist[i];
                        minDistVertex = i;
                    }
                }
            }
            if (currMinDist == 1e8) // represent graph is fully traversed no nodes are remaining.
            {
                break;
            }
            // mindisatancevertex contain node wih minimum distance at this instance and connectingvertex[mindistvertex] will contain from which node this node is at minimum distance.. 
            mst[minDistVertex][connectingVertex[minDistVertex]] = minDist[minDistVertex];
            mst[connectingVertex[minDistVertex]][minDistVertex] = minDist[minDistVertex];
            minDist[minDistVertex] = 1e8;
            //below code represent setting current vertex as visited
            connectingVertex[minDistVertex] = -2;
            //traversing all neighbouring nodes of MinVertex and changing mindistace array and connectingvertex array;
            for (int i = 0; i < v; i++)
            {
                int m = matrix[minDistVertex][i], md = minDist[i];
                if (matrix[minDistVertex][i] != 0 && connectingVertex[i] != -2)
                {
                    if (minDist[i] > matrix[minDistVertex][i])
                    {
                        minDist[i] = matrix[minDistVertex][i];
                        connectingVertex[i] = minDistVertex;
                    }
                }
            }
        }
        cout << "   ";
        for (int i = 0; i < v; i++)
        {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i << ": ";
            for (int j = 0; j < v; j++)
            {
                cout << mst[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph *g = new Graph();
    bool flag = true;
    int choice;
    string k;

    while (flag)
    {
        cout << "\n-----------------MENU-----------------\n"
             << "1. Accept Graph.\n"
             << "2. Display.\n"
             << "3. Minimum spanning tree(Prim's Algorithm).\n"
             << "4. Exit.\n"
             << "Enter your choice: ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            g->acceptGraph();
            break;

        case 2:
            g->display();
            break;

        case 3:
            g->prims();
            break;

        default:
            cout << "EXIT..";
            flag = false;
            break;
        }
    }

    return 0;
}