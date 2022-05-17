#include<iostream>
#include<string>
using namespace std;

class Node{
    char alphab8;
    Node *next;
public:
    Node(){
        alphab8 = '\0';
        next = NULL;
    }
    Node(char x){
        alphab8 = x;
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
    bool isLower(char x); 
    bool isUpper(char X); 
    bool isVowel(char x);
    bool isUpperConsonant(char x);
    void insertAtEnd(char x); 
    void insertAtStart(char x);  
    void insert_hash_After();
    void deleteNode();
    void display();
    void CreateLL(string);
    void afterEveryVowel();
    void deleteConsonants_Upper();
};

void SLL :: display(){
    Node *temp = start;
    while (temp != NULL){
        cout<<temp->alphab8<<" --> ";
        temp = temp->next;
    }
    cout<<"NULL\n";
}

void SLL ::insertAtEnd(char x)
{
    Node *temp = new Node(x);
    if (start == NULL)
    {
        start = end = temp;
    }
    else
    {
        end->next = temp;
        end = temp;
    }
};

void SLL ::insertAtStart(char x)
{
    Node *temp = new Node(x);
    if (start == NULL)
    {
        start = end = temp;
    }
    else
    {
        temp->next = start;
        start = temp;
    }
};

bool SLL :: isLower(char x){
    int ASCII_x = x;
    if((ASCII_x >= 97) && (ASCII_x <= 122)) return true;
    else return false;  
};

bool SLL :: isUpper(char X){
    int ascii_X = X;
    if((ascii_X >= 65) && (ascii_X <= 90)) return true;
    else return false;
};

void  SLL :: CreateLL(string word){
    for(int i = 0; i<word.length(); i++){
        if(isLower(word[i])){
            insertAtStart(word[i]);}
        if(isUpper(word[i])) { insertAtEnd(word[i]); }
    }
};

bool SLL :: isVowel(char x){
    if( x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' )
    return 1;
    else return 0;
};

bool SLL :: isUpperConsonant(char x){
    if(isUpper(x) && (x != 'A' && x != 'E' && x != 'I' && x != 'O' && x != 'U')) return 1;
    else return 0;
};

void SLL :: insert_hash_After(){
    Node *temp = start;
    while(temp != NULL){
        if(isVowel(temp->alphab8)){
            Node *temp1 = new Node('#');
            temp1->next = temp->next;
            temp->next = temp1;
            temp = temp1;
        }
        temp = temp->next;
    }
};

void SLL ::deleteConsonants_Upper(){
    Node *temp = start;
    Node *prev = NULL;
    while (temp != NULL)
    {
        if (isUpperConsonant(temp->alphab8))
        {
            if (temp == start)
            {
                start = temp->next;
                temp->next = NULL;
                free(temp);
                temp = start;;
            }
            else
            {
                prev->next = temp->next;
                temp->next = NULL;
                free(temp);
                temp = prev;
                temp = temp->next;
            }
        }
        else{
            prev = temp;
            temp = temp->next;
        }
    }
};

int main(){
    SLL obj;
    cout<<"****MENU****"<<endl;
    cout<<"1.Accept string and create list as required\n2. After every vowel add new node with '#'\n3. Delete all consonants in Upper case\n4. Exit.\n"
    <<endl;
    int choice;
    string str;
    do
    {
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Enter your string: ";
            cin>>str;
            obj.CreateLL(str);
            obj.display();
            break;

        case 2:
            obj.insert_hash_After();
            obj.display();
            break;

        case 3:
            obj.deleteConsonants_Upper();
            obj.display();
            break;

        case 4:
            cout<<"Program terminated!!"<<endl;
            break;
        
        default:
            cout<<"Invalid choice!!"<<endl;
            break;
        }
    } while (choice != 4);
    
    return 0;
}