/*
    The  Anonymous
*/
#include <bits/stdc++.h>
#define size 100
using namespace std;

class Node
{
	string word;
	string meaning;
	Node *next;

public:
	Node()
	{
		word = "";
		meaning = "";
		next = NULL;
	}
	Node(string word, string meaning)
	{
		this->word = word;
		this->meaning = meaning;
		next = NULL;
	}
	friend class Dictionary;
};

class Dictionary
{

	Node *hash_table[size];

public:
	Dictionary()
	{
		for (int i = 0; i < size; i++)
		{
			hash_table[i] = NULL;
		}
	}

	int Hash_function(string key);
	void Insert(string key, string value);
	void Update_value(string value, string new_value);
	void Search_key(string key);
	void Delete_key(string key);
	void Display();
};

int Dictionary::Hash_function(string key)
{

	int value = 0;
	int length = key.length();
	for (int i = 0; i < length; i++)
	{
		value += (key[i] - 'a');
	}

	return (value % length);
}

void Dictionary::Insert(string key, string value)
{

	int index = Hash_function(key);
	cout<<index<<endl;
	Node *temp2 = hash_table[index];
	Node *new_node = new Node(key, value);
	if (temp2 == NULL)
	{
		hash_table[index] = new_node;
		return;
	}
	else
	{
		while (temp2->next != NULL)
		{
			temp2 = temp2->next;
		}
		temp2->next = new_node;
		return;
	}
}

void Dictionary::Display()
{

	for (int i = 0; i < size; i++)
	{
		Node *temp = hash_table[i];
		if (temp != NULL)
		{
			cout << "Index: " << i << endl;
			while (temp != NULL)
			{
				cout << temp->word << " => " << temp->meaning << endl;
				temp = temp->next;
			}
		}
	}
}

void Dictionary::Update_value(string word, string new_value)
{

	int index = Hash_function(word);
	Node *temp = hash_table[index];

	if (temp == NULL)
	{
		cout << "Entered key is not present in hash table" << endl;
		return;
	}
	else
	{

		while (temp != NULL && temp->word != word)
		{
			temp = temp->next;
		}
		if (temp != NULL && temp->word == word)
		{
			temp->meaning = new_value;
			cout << "Value is updated successfully" << endl;
		}
		else
		{
			cout << "Entered key is not present in hash table" << endl;
			return;
		}
	}
}

void Dictionary::Search_key(string key)
{

	int index = Hash_function(key);

	Node *temp = hash_table[index];

	int count = 1;
	if (temp == NULL)
	{
		cout << "The entered value is not present in dictionary" << endl;
		return;
	}
	else
	{
		while(temp != NULL and temp->word != key)
		{
			count++;
			temp = temp->next;
		}
		if(temp!=NULL and temp->word == key)
		{
			cout<<"Value found in "<<count<<".\n";
			cout<<temp->word<<" -> "<<temp->meaning<<endl;
		}
	}
}

void Dictionary::Delete_key(string key)
{

	int index = Hash_function(key);
	Node *temp = hash_table[index];
	if (temp == NULL)
	{
		cout << "Entered element is not present" << endl;
		return;
	}
	Node *prev = NULL;
	while (temp != NULL && temp->word != key)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		cout << "Entered element is not present" << endl;
		return;
	}
	prev->next = temp->next;
	delete(temp);
	cout << "Delete successful" << endl;
}

int main()
{

	Dictionary T;
	int c;
	cout << "Enter number of values to be inserted: ";
	cin >> c;
	while (c--)
	{
		string word;
		string meaning;
		cout << "Enter the word and meaning(e.g Apple Fruit): ";
		cin >> word >> meaning;
		T.Insert(word, meaning);
	}

	
	char x;
	cout << "Do you want to display the hash_table(y/n): ";
	cin >> x;
	if (x == 'y')
	{
		T.Display();
	}

	cout << "Do you want to update value(y/n): ";
	cin >> x;
	while (x == 'y')
	{
		cout << "Enter the word whose meaning is to be changed and enter new meaning(Apple Vegetable): ";
		string word;
		string new_meaning;
		cin >> word >> new_meaning;
		T.Update_value(word, new_meaning);
		cout << "Do you want to print the table(y/n): ";
		cin >> x;
		if (x == 'y')
		{
			T.Display();
		}
		cout << "Do you want to continue(y/n): ";
		cin >> x;
	}

	cout << "Do you want to search the element(y/n): ";
	cin >> x;
	while (x == 'y')
	{
		cout << "Enter the word to be searched: ";
		string word;
		cin >> word;
		T.Search_key(word);
		cout << "Do you want to continue(y/n): ";
		cin >> x;
	}

	cout << "Do you want to delete an element(y/n): ";
	cin >> x;
	while (x == 'y')
	{
		cout << "Enter the word to be deleted: ";
		string word;
		cin >> word;
		T.Delete_key(word);
		cout << "Do you want to print the elements(y/n): ";
		cin >> x;
		if (x == 'y')
		{
			T.Display();
		}
		cout << "Do you want to continue(y/n): ";
		cin >> x;
	}

	return 0;
}
