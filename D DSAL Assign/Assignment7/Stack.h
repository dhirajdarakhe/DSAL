#include <iostream>
using namespace std;

template <typename T>
class NodeS{

	NodeS *next;
	T data;

public:

	NodeS(){
		next = NULL;
	}

	NodeS(T d){
		next = NULL;
		data = d;
	}

	template <typename U> friend class Stack;
};

template <typename T>
class Stack{
    NodeS<T> *top;

    public:

    Stack(){
        top = NULL;
    }

    void push(T data){

        NodeS<T> *newNode = new NodeS<T>(data);
        newNode->next = top;
        top = newNode;
        
    }

    void pop(){
        if(top == NULL){
            cout << "Stack is already empty" << endl;
        }
        else{
            NodeS<T> *temp = top;
            top = top->next;
            delete temp;
        }
    }

    T topData(){
        if(top == NULL){
            cout << "Stack is empty" << endl;
            return 0;
        }
        else{
            return top->data;
        }
    }

    bool isEmpty(){
        return top == NULL;
    }

    int size(){
        int len = 0;
        NodeS<T> *temp = top;

        while(temp != NULL){
            temp = temp->next;
            len++;
        }

        return len;
    }
};