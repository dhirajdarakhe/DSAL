/*
    The  Anonymous
*/
#include <bits/stdc++.h>
#define size 100
using namespace std;

class Hash_Entry
{
	int number;
	string name;

public:
	Hash_Entry()
	{
		number = 0;
		name = "";
	}
	Hash_Entry(int x, string name)
	{
		number = x;
		this->name = name;
	}
	friend class Telephone_Directory;
};

class Telephone_Directory
{

	Hash_Entry hash_table[size];

public:
	int Hash_function(int key);
	void Insert_without_replacement(int key, string name);
	void Insert_with_replacement(int key, string name);
	void Display_hash_table();
	void Search_hash_table(int key);
};

int Telephone_Directory::Hash_function(int key)
{

	return (key % 100);
}

void Telephone_Directory::Insert_without_replacement(int key, string name)
{

	int index = Hash_function(key);

	if (hash_table[index].number == 0)
	{
		hash_table[index].number = key;
		hash_table[index].name = name;
	}
	else
	{
		int i = index + 1;
		while (i % size != index && hash_table[i % size].number != 0)
		{
			i++;
		}
		if(i==index){
			cout<<"Hash table is full\n";
			return;
		}
		hash_table[i % size].number = key;
		hash_table[i % size].name = name;
	}
}

void Telephone_Directory::Insert_with_replacement(int key, string name)
{

	int index = Hash_function(key);
	int i = index;

	if (hash_table[index].number == 0)
	{
		hash_table[index].number = key;
		hash_table[index].name = name;
	}
	else
	{

		if ((hash_table[index].number) % 100 == index)
		{

			int k = index + 1;
			while (k % size != index && hash_table[k%size].number != 0)
			{
				k++;
			}
			hash_table[k%size].number = key;
			hash_table[k%size].name = name;
		}
		else
		{
			int value = hash_table[index].number;
			string names = hash_table[index].name;
			hash_table[index].number = key;
			hash_table[index].name = name;

			int i = index+1;
			while(i%size != index and hash_table[i%size].number !=0)
			{
				i++;
			}
			hash_table[i%size].name = names;
			hash_table[i%size].number = value;
		}
	}
}

void Telephone_Directory::Display_hash_table()
{

	for (int i = 0; i < size; i++)
	{
		if (hash_table[i].number != 0)
			cout << "Index: " << i << " " << hash_table[i].name << "->" << hash_table[i].number << endl;
	}
}

void Telephone_Directory::Search_hash_table(int key)
{

	int value = Hash_function(key);
	int count = 0;
	if (hash_table[value].number == key)
	{
		count++;
		cout << "value to be searched is found in " << count << " no. of comparisons: ";
		cout << hash_table[value].name << "->" << hash_table[value].number << endl;
	}
	else
	{
		int index = value + 1;
		count++;
		while (index % size != value)
		{
			count++;
			if (hash_table[index % size].number == key) 
			{
				cout << "value to be searched is found in " << count << " no. of comparisons: ";
				cout << hash_table[index % size].name << "->" << hash_table[index % size].number << endl;
				return;
			}
			index++;
		}
		cout << "Given value does not present in hash table!!!\n";
	}
}

int main()
{

	Telephone_Directory T;
	int c;
	cout << "Enter number of values to be inserted: ";
	cin >> c;
	int d;
	cout << "option 1 -> insert without replacement" << endl;
	cout << "option 2 -> insert with replacement" << endl;
	cout << "Enter the method in which you want to insert: ";
	cin >> d;
	while (c--)
	{
		cout << "Enter the number and name: ";
		int n;
		string s;
		cin >> n >> s;
		if (d == 1)
		{
			T.Insert_without_replacement(n, s);
		}
		else
		{
			T.Insert_with_replacement(n, s);
		}
	}
	char s;
	cout << "Do you wanna print hash table(y/n): ";
	cin >> s;
	if (s == 'y')
	{
		T.Display_hash_table();
	}
	char x;
	cout << "Do you want to search any number(y/n): ";
	cin >> x;
	while (x == 'y')
	{
		cout << "Enter the number to be searched: ";
		int v;
		cin >> v;
		T.Search_hash_table(v);
		cout << "Do you wanna continue(y/n): ";
		cin >> x;
	}

	return 0;
}
