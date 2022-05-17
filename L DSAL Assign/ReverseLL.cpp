#include<iostream>
using namespace std;

class Node{
    int data;
    Node *next;
public:
    Node(){
        data = 0;
        next = NULL;
    }
    Node(int x){
        data = x;
        next = NULL;
    }
    friend class SLL;
};

class SLL{
    Node *start, *end;
public:
    SLL(){
        start = end = NULL;
    }
    void insertAtEnd(int x);
    void display();
    void reverseLL();
};

void SLL ::insertAtEnd(int x){
    Node *temp = new Node(x);
    if (start == NULL){
        start = end = temp;
    }
    else{
        end->next = temp;
        end = temp;
    }
};

void SLL:: display(){
    Node *temp = start;
    while (temp != NULL)
    {
        cout<<temp->data<<" -> ";
        temp = temp->next;
    }
    cout<<"NULL\n";
}

void SLL::reverseLL(){
    Node *current, *temp_start;
    current = temp_start = start;
    Node *prev, *necxt;
    prev = necxt = NULL;
    while (current != NULL)
    {
        necxt = current->next;
        current->next = prev;
        prev = current;
        current = necxt;
    }
    start = prev;  //****
    end = temp_start;
};

int main(){
    SLL obj;
    cout<<"1. Insert the element at end\n2. Reverse the linked list\n3. Exit\n";
    int choice;
    do
    {
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                int number;
                cout<<"Enter the number you want to insert: ";
                cin>> number;
                obj.insertAtEnd(number);
                obj.display();
                break;
            case 2:
                obj.reverseLL();
                obj.display();
                break;
            case 3:
                cout<<"Program terminated"<<endl;
                break;
            default:
                cout<<"Invalid choice!!"<<endl;
                break;
        }
    } while (choice != 3);
    
    return 0;
}