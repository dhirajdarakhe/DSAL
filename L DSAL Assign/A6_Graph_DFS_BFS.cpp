/*
 * Graph_DFS_BFS.cpp
 *
 *  Created on: 29-Apr-2022
 *      Author: pict
 */
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
	friend class Queue;
	friend class Graph;
};

class Graph{
	int noOfVertex;
	int noOfEdges;
	Node* *adjacencyList;

public:
	bool *visit;
	Graph(int nov, int noe){
		noOfVertex = nov;
		noOfEdges = noe;
		adjacencyList = new Node* [nov];
//		Initializing adj list
		for(int i=0; i<nov; i++){
			adjacencyList[i] = NULL;
		}
		visit = new bool[nov];
//		Initializing visit array
		// for(int i = 0; i<nov; i++){
		// 	visit[i] = 0;
		// }
	}
	void acceptGraph();
	void displayAdjList();
	void DFS_caller(int);
	void DFS(int);
	void BFS(int);
};

class queueNode{
    private:
    int info;
    queueNode *right;
public:
    queueNode(){
        info = 0;
        right = NULL;
    }
    queueNode(int x){
        info = x;
        right = NULL;
    }
    friend class Queue;
};

class Queue{
    queueNode *front, *rear;
public:
    Queue(){
        front = rear = NULL;
    }
    void enq(int toinsert);
    int deq();
    bool isEmpty();
	friend class Graph;
};

void Queue :: enq(int toinsert){
    queueNode* newnode = new queueNode(toinsert);
    if (isEmpty()){
        front = rear = newnode;
    }else{
        rear->right = newnode;
        rear = newnode;
    }
}

bool Queue :: isEmpty(){
    if(front == NULL && rear == NULL) return true;
    else return false;
}

int Queue :: deq(){
    int popdata = front->info;
    queueNode* popNode = front;
	// for single node remaining
	if(popNode->right == NULL){
		front = NULL;  //front->right
		rear = NULL;
	}else
    	front = front->right;
    popNode->right = NULL;
	free(popNode);
    return popdata;
}

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

void Graph :: DFS(int start_vert){
	visit[start_vert] = 1;
	cout<<start_vert<<" --> ";
		Node *temp = adjacencyList[start_vert];
		while(temp != NULL){
			if(visit[temp->des_ver] == 0)
				DFS(temp->des_ver);
			temp = temp->next;
		}
}

void Graph :: DFS_caller(int start_vert){
	for (int i = 0; i < noOfVertex; i++){
		visit[i] = 0;
	}
	DFS(start_vert);
}

void Graph :: BFS(int start){
	for (int i = 0; i < noOfVertex; i++){
		visit[i] = 0;
	}
	Queue q;
	visit[start] = 1;
	q.enq(start);
	while (!q.isEmpty())
	{
		start = q.deq();
		cout<<start<<"-->";
		Node* temp = adjacencyList[start];
		while (temp != NULL)
		{
			if(visit[temp->des_ver] == 0){
				q.enq(temp->des_ver);
				visit[temp->des_ver] = 1;
			}
			temp = temp->next;
		}
	}
	cout<<"\n";
}

int main(){
	int V, E;
	int start_ver;
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
			G->displayAdjList();
			break;
		}
		case 3:{
			cout<<"Enter the starting vertex from where you want DFS traversal: ";
			cin>>start_ver;
			cout<<"DFS of the tree is: ";
			G->DFS_caller(start_ver);
			cout<<"\n";
			break;
		}
		case 4:{
			cout<<"Enter the starting vertex from where you want BFS traversal: ";
			cin>>start_ver;
			cout<<"BFS of the tree is: ";
			G->BFS(start_ver);
			// cout<<"\n";
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



