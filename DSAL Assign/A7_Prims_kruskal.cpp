#include<iostream>
using namespace std;

class Graph{
	int noOfVertex;
	int noOfEdges;
	int* *adjacencyMatrix;
    int* *result;
	int *parent;
	int *visited;

public:
	Graph(int nov, int noe){
		noOfVertex = nov;
		noOfEdges = noe;
		adjacencyMatrix = new int* [nov];
		result = new int* [nov];
//		Creating adj Matrix
		for(int i=0; i<nov; i++){
			adjacencyMatrix[i] = new int[nov];
			result[i] = new int[nov];
		}
//      Initialising adjMatrix 
        for(int r = 0; r<nov; r++){
            for(int c = 0; c< nov; c++){
                adjacencyMatrix[r][c] = 0;
                // result[r][c] = 0;
            }
        }
        // allocating memeory to parent array dynamically
		parent = new int[nov];
		visited = new int[nov];
	}
	void acceptGraph();
	void displayAdjMatrix(int which);
    void Kruskal();
    void Prims(int startVertex);
    void initialize0Result();
};

void Graph :: acceptGraph(){
	int source, destinatn, weight;
	for(int i=0; i< noOfEdges; i++){
		cout<<"Enter the source: ";
		cin>>source;
		cout<<"Enter the destination: ";
		cin>>destinatn;
		cout<<"Enter the weight: ";
		cin>>weight;
		adjacencyMatrix[source][destinatn] = adjacencyMatrix[destinatn][source] = weight;
	}
}

void Graph :: displayAdjMatrix(int which){
    if(which == 1){
        for(int r = 0; r < noOfVertex; r++){
            cout<<r<<" : [ ";
            for (int c = 0; c < noOfVertex; c++){
                cout<<adjacencyMatrix[r][c]<<" ";
            }
            cout<<"]\n";
        }
    }
    if(which == 2){
        for(int r = 0; r < noOfVertex; r++){
            cout<<r<<" : [ ";
            for (int c = 0; c < noOfVertex; c++){
                cout<<result[r][c]<<" ";
            }
            cout<<"]\n";
        }
    }
}

void Graph :: initialize0Result(){
    for(int r = 0; r<noOfVertex; r++){
            for(int c = 0; c< noOfVertex; c++){
                result[r][c] = 0;
            }
        }
}

void Graph ::Kruskal(){
    int* *tempadjacencyMatrix = new int*[noOfVertex];
    for(int i = 0; i < noOfVertex; i++){
        tempadjacencyMatrix[i] = new int[noOfVertex];
    }
    for (int j = 0; j < noOfVertex; j++){
        for (int k = 0; k < noOfVertex; k++){
            tempadjacencyMatrix[j][k] = adjacencyMatrix[j][k];
        }
    }
    initialize0Result();// result[][] = {0};
    int count = 0, min, wt = 0;
    for(int i = 0; i < noOfVertex; i++){
        parent[i] = -1;
    }
    while (count < noOfVertex - 1){
        int t1, t2, temp1, temp2;
        min = 999;
        for(int i = 0; i < noOfVertex; i++){
            for(int j = 0; j < noOfVertex; j++){
                if(tempadjacencyMatrix[i][j] != 0 && tempadjacencyMatrix[i][j] < min){
                    min = tempadjacencyMatrix[i][j];
                    t1 = i; t2 = j;
                }
            }
        }
        temp1 = t1; temp2 = t2;
        tempadjacencyMatrix[t1][t2] = tempadjacencyMatrix[t2][t1] = 0;
        int root_temp1, root_temp2;
        while(t1 >= 0){
            root_temp1 = t1;
            t1 = parent[t1];
        }
        while(t2 >= 0){
            root_temp2 = t2;
            t2 = parent[t2];
        }
        if(root_temp1 != root_temp2){
            result[temp1][temp2] = result[temp2][temp1] = min;
            wt += min;
            parent[root_temp2] = root_temp1;
            count++;
        }
    }
    cout<<"The weight of MST by Kruskal's ALgorithm is "<<wt<<endl;
    cout<<"The resultant matrix after Kruskal of MST is: \n";
    displayAdjMatrix(2);
}

void Graph ::Prims(int startVertex){
    int* *tempadjacencyMatrix = new int*[noOfVertex];
    for(int i = 0; i < noOfVertex; i++){
        tempadjacencyMatrix[i] = new int[noOfVertex];
    }
    for (int j = 0; j < noOfVertex; j++){
        for (int k = 0; k < noOfVertex; k++){
            tempadjacencyMatrix[j][k] = adjacencyMatrix[j][k];
        }
    }
    initialize0Result();// result[][] = {0};
    int count = 0,count1 = 0, min, wt = 0;
    int t1, t2, temp1, temp2;
    int root_temp1, root_temp2;
    // Making parent array entries -1;
    for(int i = 0; i < noOfVertex; i++){
        parent[i] = -1; visited[i] = 0;
    }
    visited[count1] = startVertex;
    count1++;
    while (count < noOfVertex - 1){
        min = 999;
        for(int v1 = 0; v1 < count1; v1++){
            for(int v2 = 0; v2 < noOfVertex; v2++){
                if(tempadjacencyMatrix[visited[v1]][v2] != 0 && tempadjacencyMatrix[visited[v1]][v2] < min){
                    min = tempadjacencyMatrix[visited[v1]][v2];
                    t1 = visited[v1]; t2 = v2;
                }
            }
        }
        temp1 = t1; temp2 = t2;
        tempadjacencyMatrix[t1][t2] = tempadjacencyMatrix[t2][t1] = 0;
        while(t1 >= 0){
            root_temp1 = t1;
            t1 = parent[t1];
        }
        while(t2 >= 0){
            root_temp2 = t2;
            t2 = parent[t2];
        }
        if(root_temp1 != root_temp2){
            result[temp1][temp2] = result[temp2][temp1] = min;
            wt += min;
            parent[root_temp2] = root_temp1;
            count++;
            visited[count1] = root_temp2;
            count1++;
        }
    }
    cout<<"The weight of MST by Prims's ALgorithm is "<<wt<<endl;
    cout<<"The resultant matrix after Prim's of MST is: \n";
    displayAdjMatrix(2);
}

int main(){
	int V, E;
	int start_ver, which;
	Graph *G;
	int ch;
	cout<<"MENU\n1. Accept graph\n2. Display graph\n3. DFS\n4. BFS\n";
	do{
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch){
		case 1:{
			cout<<"Enter no. of vertices in your graph: ";
			cin>>V;
			cout<<"Enter no. of Edges in your graph: ";
			cin>>E;
			G = new Graph(V, E);
			G->acceptGraph();
			break;
		}
		case 2:{
			G->displayAdjMatrix(1);
			break;
		}
		case 3:{
			cout<<"Kruskal's Algorithm to find MST\n";
			G->Kruskal();
			break;
		}
		case 4:{
			cout<<"Prim's Algorithm to find MST\n";
            cout<<"Enter the starting vertex finding MST by Prim's algo: ";
            cin>>start_ver;
			G->Prims(start_ver);
			break;
		}
		case -1:{
			cout<<"Program end !\n";
			break;
		}
		default:{
			cout<<"Invalid choice\n";
			break;
		}
		}
	}while(ch != -1);
	return 0;
}