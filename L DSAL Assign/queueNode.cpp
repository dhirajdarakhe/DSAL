#include<iostream>
using namespace std;

class Node{
    private:
    int info;
    Node *left, *right;
    public:
    Node(){
        left = right = NULL;
    }

};

class Queue{
    Node *front, *rear;
    public:
    Queue(){
        front = rear = NULL;
    }
    void insert(Node*);
    Node* pop();
    bool isEmpty();
};

void Queue :: insert(Node *toinsert){
    if (isEmpty()){
        
    }
    
};

bool Queue :: isEmpty(){
    if(front == rear == NULL) return true;
    else return false;
}

int main(){
    
    return 0;
}