/*
    The  Anonymous
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iomanip>
using namespace std;
class Student
{
	int roll;
    char div[6];
	char name[50],address[50];
	public:
	Student()
	{
		roll = -1;
        div[0] = '\0';
		name[0]=address[0]='\0';
	}
	Student(int r,char d[6],char n[50],char adr[50])
	{
		roll=r;
		strcpy(div,d);
		strcpy(name,n);
		strcpy(address,adr);
	}
	void displayRecord()
	{
		cout<<name<<"\t\t"<<roll<<"\t\t"<<div<<"\t\t"<<address<<"\n";
	}
	friend class Record;
};
class Record
{
	char fname[50];
	public:
	Record()
	{
		fname[0]='\0';
	}
	Record(char fn[50])
	{
		strcpy(fname,fn);
	}
	void displayAll();
	void insertRec(int,char[],char[],char[]);
	void removeRec(char[]);
	void showData(char[]);
};
void Record::insertRec(int roll,char div[4],char name[50],char address[50])
{
	ofstream fptr(fname,ios::app);
	Student temp(roll,div,name,address);
	fptr.write((char*)&temp,sizeof(temp));
	fptr.close();
}
void Record::showData(char name[50])
{
	ifstream fptr(fname,ios::in);
	Student T1;
	bool found=false;
	fptr.seekg(0,ios::beg);
	while(fptr.read((char*)&T1,sizeof(T1)))
	{
		if(strcmp(T1.name,name)==0)
		{
			found=true;
			break;
		}
	}
	if(!found)
	{
		cout<<"Record not present in the database\n";
		return;
	}
	cout<<"Name\t\tRoll no\t\tDiv\t\tAddress\n";
	T1.displayRecord();
	fptr.close();
}
void Record::displayAll()
{
	ifstream fptr(fname);
	Student T1;
	if(fptr.good())
		cout<<"Name\t\tRoll\t\tDiv\t\tAddress\n";
	while(!fptr.eof())
	{
		fptr.read((char*)&T1,sizeof(T1));
		if(!fptr.eof())
		{
			T1.displayRecord();
		}
	}
	fptr.close();
}
void Record::removeRec(char name[50])
{
	bool found=false;
	Student T1;
	ifstream fptr(fname);
	ofstream fout("temp.txt");
	fptr.seekg(0,ios::beg);
	while(fptr.good())
	{
		fptr.read((char*)&T1,sizeof(T1));
		if(strcmp(T1.name,name)!=0&&!fptr.eof())
		{
			fout.write((char*)&T1,sizeof(T1));
		}
		else
			found=true;
	}
	fout.close();
	if(!found)
	{
		remove("temp.txt");
		cout<<"Record is not present in the database\n";
		return;
	}
    else{
        cout << "\nRecord deleted successfully!!";
    }
	fptr.close();
	remove("Database.txt");
	rename("temp.txt","Database.txt");
	fptr.open("Database.txt",ios::in|ios::out|ios::ate);
	fptr.close();
}
int main()
{
    int ch,roll;
    char batch[6];
	ofstream fout("Database.txt");
	fout.close();
	Record R1((char*)"Database.txt");
    char name[50],address[50];
    bool repeatAgain = true;
    while(repeatAgain)
    {
        cout<<"\n\n\n<-------------------- MAIN MENU -------------------->";
        cout<<"\n\n1. Insert Record \n2.Find Record \n3. Display Record \n4. Delete Record \n5. Exit"<<endl;
        cout<<"\nEnter your choice : ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                 cout<<"\nEnter Name : ";
                 cin >> name;
                
                cout<<"\nEnter Address : ";
                cin.ignore();
                 cin.getline(address,48);
                cout<<"\nEnter Roll no : ";
                cin>>roll;
                cout << "\nEnter Class : ";
                cin>>batch;
                R1.insertRec(roll,batch,name,address);
                cout << "\n\nData entered successfully!!";
			    break;
            case 2:
                cout<<"\nEnter Name : ";
        		cin >> name;
        		R1.showData(name);
        		break;
            case 3:
                R1.displayAll();
			    break;       
            case 4:
                cout<<"\nEnter Name : ";
        		cin >> name;
        		R1.removeRec(name);
        		break;
            case 5:
                repeatAgain = false;
                break;
            default:
                cout<<"\n\nWrong choice! Please enter number between 1 - 4";
                break;
        }
    }
}