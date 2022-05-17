#include <iostream>
using namespace std;

class Node
{
    int data;
    Node *next;

public:
    Node()
    {
        data = 0;
        next = NULL;
    }
    Node(int a)
    {
        data = a;
        next = NULL;
    }
    friend class SLL;
};

class SLL
{
    Node *start, *end;

public:
    SLL()
    {
        start = end = NULL;
    }
    void insertAtStart(int x);
    void insertAtEnd(int x);
    int addition_OddPlaces();
    int addition_EvenPlaces();
    bool isPrime(int num);
    int addition_PrimeNum();
    void delete_Odd_and_Prime();
    int addition_Even_or_odd(int num);
    void display();
    void sort();
};

void SLL :: display(){
    Node *temp = start;
    while (temp != NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<"\n";
}

void SLL ::insertAtEnd(int x)
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

void SLL ::insertAtStart(int x)
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

int SLL::addition_Even_or_odd(int num)
{
    int sum = 0;
    while (num != 0)
    {
        int digit = num % 10;
        sum += digit;
        num = num / 10;
    }
    if (sum % 2 == 0)
        return 0;
    else
        return 1;
};

int SLL ::addition_EvenPlaces()
{
    int count = 1;
    int sum_e = 0;
    Node *temp = start;
    while (temp != NULL)
    {
        if (count % 2 == 0)
        {
            sum_e += temp->data;
        }
        temp = temp->next;
        count++;
    }
    return sum_e;
}
int SLL ::addition_OddPlaces()
{
    int count = 1;
    int sum_o = 0;
    Node *temp = start;
    while (temp != NULL)
    {
        if (count % 2 != 0)
        {
            sum_o += temp->data;
        }
        temp = temp->next;
        count++;
    }
    return sum_o;
};

bool SLL::isPrime(int num)
{
    int count = 0;
    for (int i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)
            count++;
    }
    if (count == 1)
        return 1;
    else
        return 0;
};

int SLL ::addition_PrimeNum()
{
    Node *temp = start;
    int sum_prime = 0;
    while (temp != NULL)
    {
        if (isPrime(temp->data))
        {
            sum_prime += temp->data;
        }
        temp = temp->next;
    }
    return sum_prime;
};

void SLL ::delete_Odd_and_Prime()
{
    Node *temp = start;
    Node *prev = NULL;
    while (temp != NULL)
    {
        if ((temp->data != 2) && (isPrime(temp->data)))
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

void SLL :: sort(){
    Node *temp = start;
    Node *itarator;
    while (temp->next != NULL)
    {
        itarator = temp->next;
        while (itarator != NULL)
        {
            if(itarator->data < temp->data){
                int forSwap = temp->data;
                temp->data = itarator->data;
                itarator->data = forSwap;
            }
            itarator = itarator->next;
        }
        
        temp = temp->next;
    }
    
}

int main()
{
    int number, num, odd, even, prime;

    int choice;
    SLL obj;
    cout << "Menu \n1. Insert the element \n2.Add at odd \n3.Add at even \n4.Add prime \n"<<
    "5.Delete odd and prime \n7. Sort\n8.Exit \n";
    do
    {
        cout << "Enter the choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the number:";
            cin >> number;
            if (!obj.addition_Even_or_odd(number))
            {
                obj.insertAtStart(number);
            }
            else
                obj.insertAtEnd(number);
            obj.display();
            break;

        case 2:
            odd = obj.addition_OddPlaces();
            cout << "Sum of odd places is :" << odd << endl;
            break;

        case 3:
            even = obj.addition_EvenPlaces();
            cout << "Sum of even places is :" << even << endl;
            break;

        case 4:
            prime = obj.addition_PrimeNum();
            cout << "Sum of prime numbers is :" << prime << endl;
            break;
        case 5:
            obj.delete_Odd_and_Prime();
            obj.display();
            break;

        case 6:
            cout << "Program finished";
            break;
        case 7:
            obj.sort();
            cout<<"Sorted linked list is:\n";
            obj.display();
            break;

        default:
            cout << "Enter the correct choice..." << endl;
            break;
        }

    } while (choice != 8);

    return 0;
}