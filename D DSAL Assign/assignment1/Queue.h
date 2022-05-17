#include <iostream>
using namespace std;

template <typename T>
class Node{



	Node *next;
	T data;


public:

	Node(){
		next = NULL;
	}

	Node(T d){
		next = NULL;
		data = d;
	}

	template <typename U> friend class Queue;
};

template <typename T>
class Queue{
    Node<T> *front, *back;

    public:

    Queue(){
        front = NULL;
        back = NULL;
    }

    void push(T data){
        if(front == NULL){
            front = new Node<T>(data);
            back = front;
        }
        else{
            back->next = new Node<T>(data);
            back = back->next;
        }
    }

    void pop(){

        if(front == NULL){
            cout << "Queue is already empty" << endl;
            return;
        }

        Node<T> *temp = front;
        front = front->next;
        delete temp;
    }

    T frontData(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return 0;
        }
        else{
            return front->data;
        }
    }

    bool isEmpty(){
        return front == NULL;
    }

    int size(){
        int len = 0;
        Node<T> *temp = front;

        while(temp != NULL){
            temp = temp->next;
            len++;
        }

        return len;
    }
};