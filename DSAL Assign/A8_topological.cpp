#include<iostream>
using namespace std;

class Node{
	int des_ver;
	Node *next;
public:
	Node(){
		des_ver = 0;
		next = NULL;
	}
	Node(int dv){
		des_ver = dv;
		next = NULL;
	}
	friend class Graph;
};

class Graph{
	int noOfVertex;
	int noOfEdges;
	Node* *adjacencyList;
	int *indegree;
	void inDegree();
    void NodeWithIndegree0();
    bool checkIndegreeArray();

public:
	Graph(int nov, int noe){
		noOfVertex = nov;
		noOfEdges = noe;
		adjacencyList = new Node* [nov];
//		Initializing adj list
		for(int i=0; i<nov; i++){
			adjacencyList[i] = NULL;
		}
		indegree = new int[nov];
		// Initializing visit array
		for(int i = 0; i<nov; i++){
			indegree[i] = 0;
		}
	}
	void acceptGraph();
	void displayAdjList();
    void Topological();
};

void Graph :: acceptGraph(){
	int source, destinatn;
	for(int i=0; i< noOfEdges; i++){
		cout<<"Enter the source: ";
		cin>>source;
		cout<<"Enter the destination: ";
		cin>>destinatn;
		Node *n = new Node(destinatn);
		Node *temp = adjacencyList[source];
		if(temp == NULL){
			adjacencyList[source] = n;
			cout<<"Inserted first element of each index\n";
		}
		else{
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = n;
			cout<<"Inserted at end\n";
		}
	}
}

void Graph :: displayAdjList(){
	Node *temp;
	for(int i = 0; i < noOfVertex; i++){
		temp = adjacencyList[i];
		cout<<"["<<i<<"] : ";
		while(temp != NULL){
			cout<<temp->des_ver<<" --> ";
			temp = temp->next;
		}
		cout<<"NULL\n";
	}
}

void Graph :: inDegree(){
    Node *temp;
    for(int i = 0; i< noOfVertex; i++){
        temp = adjacencyList[i];
        while(temp != NULL){
            indegree[temp->des_ver]++; 
            temp = temp->next;
        }
    }
}

bool Graph :: checkIndegreeArray(){
    int count = 0;
    for(int i = 0; i < noOfVertex; i++){
        if(indegree[i] == -1)
            count++;
    }
    if(count == noOfVertex)
        return 0;
    else return 1;
}

void Graph :: NodeWithIndegree0(){
    int zeroIDVertex[noOfVertex] = {0};
    int count = 0;
    for(int i = 0; i < noOfVertex; i++){
        if(indegree[i] == 0){
            indegree[i] = -1;
            cout<<i<<"-->";
            zeroIDVertex[count] = i;
            count++;
        }
    }
    for(int i = 0; i < count; i++){
        Node* temp = adjacencyList[zeroIDVertex[i]];
        while (temp != NULL){
            indegree[temp->des_ver]--;
            temp = temp->next;
        }
    }
}

void Graph :: Topological(){
    inDegree();
    while(checkIndegreeArray()){
        NodeWithIndegree0();
    }
    cout<<"\n";
}

int main(){
	int V, E;
	Graph *G;
	int ch;
	cout<<"MENU\n1. Accept graph\n2. Display graph\n3. Topological ordering\n";
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
			G->displayAdjList();
			break;
		}
		case 3:{
			cout<<"Topological ordering of the Graph is:\n";
            G->Topological();
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