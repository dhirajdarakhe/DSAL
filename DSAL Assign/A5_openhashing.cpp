/*
 * openhashing.cpp
 *
 *  Created on: 22-Apr-2022
 *      Author: pict
 */


#include<iostream>
#define size 26
using namespace std;

class node{
	string word , meaning ;
	node * next;
public:
	node(){
		word = meaning = " ";
        next =NULL;
	}
	node(string w , string m){
			word = w ;
			meaning = m;
			next=NULL;
		}
	friend class dictionary;
};

class dictionary{
	node* array[size];

public:
	dictionary(){
		for(int i= 0 ; i< size ; i++){
			array[i]= NULL;
		}

	}
	int hashfunction(string key){
		int index= 0 , l=key.length();
		for(int i= 0 ; i< l ;i++){
            index += (int)key[i] * i ;
		}
		return index%size;
	}
	void insert(string key , string value);
	bool find(string key);
	void delete_pair(string key);
	void display();
};
void dictionary::display(){
	for(int i =0 ; i < size ; i++){
		cout<<"|"<< i <<"| ";
		node* temp =array[i];
		while(temp!=NULL){
			cout<<" ===> { "<<temp->word<<"--"<<temp->meaning<<" }";
			temp =temp->next;
		}
		cout<<endl;
	}
}
void dictionary::delete_pair(string key){
	int index = hashfunction(key);
	if(key == array[index]->word){
		node *temp = array[index];
		array[index]= array[index]->next;
		delete temp;
		cout<<"Key value pair deleted successfully...\n";
	}
	else{
		node* prev = array[index];
		while(prev->next!=NULL ){
			if(prev->next->word == key){
				node *temp = prev->next;
				prev->next = temp->next ;
				delete temp;
				cout<<"Key value pair deleted successfully...\n";
				break;
			}
		}
	}
}
bool dictionary::find(string key){
	int index = hashfunction(key);
	int count = 0;
	if(array[index] != NULL ){
		node * temp = array[index];
		while(temp!=NULL){
			count++;
			if(temp->word == key){
				cout<<"The key is found :=> "<<temp->word<<"-->"<<temp->meaning<<endl;
				cout<<"The total no of comparison required are:=>"<<count<<endl;
				return true;
			}
			else{
				temp = temp->next;
			}
		}
		cout<<"In find function : Not found"<<endl;
		return false;
	}
	cout<<"In find function : Not found"<<endl;
	return false;
}
void dictionary::insert(string key , string value){
	node *newpair = new node(key , value);
	int index= hashfunction(key);
	if(array[index]== NULL){
	 array[index] = newpair ;
 	}
	else{
       node *temp= array[index];
       while(temp->next !=NULL){
    	   temp = temp->next;
       }
       temp->next = newpair ;
	}
}
int main(){
	dictionary D;
	int ch;
	string word ,meaning;
do{	cout<<"Menu \n1.Insert the word in dictionary \n2. Find the word in the dictionary \n3. Delete the word-meaning pair in dictionary \n4. Display the dictionary \n5.Exit \n";
	cout<<"Enter the choice :=>";
	cin>>ch;
	switch(ch){
	case 1:
		cout<<"Insertion Operation...............\n";
		cout<<"Enter the word :-";
		cin>>word;
		cout<<"Enter the meaning:-";
		cin>>meaning;
		D.insert(word ,meaning);
		break;

	case 2:
		cout<<"Searching Operation...............\n";
		cout<<"Enter the word :-";
		cin>>word;
		D.find(word);
		break;

	case 3:
		cout<<"Deletion Operation...............\n";
		cout<<"Enter the word :-";
		cin>>word;
		if(D.find(word))
			D.delete_pair(word);
		else cout<<"Not found. So, can't be deleted !"<<endl;
		break;

	case 4:
		cout<<"The dictionary is :\n";
		D.display();
		break;

	case 5:
		cout<<"End of program"<<endl;
		break;

	default:
		cout<<"Wrong choice..! Please enter the correct choice \n";
		break;

	}
}while(ch!=5);
	return 0;
}






