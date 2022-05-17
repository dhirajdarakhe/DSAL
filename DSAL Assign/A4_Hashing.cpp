/*
 * Hashing.cpp
 *
 *  Created on: 13-Apr-2022
 *      Author: pict
 */
/*Consider telephone book database of N client . Make use of a hash table implementation to quickly look up client‘s telephone number. Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers (use linear probing with replacement and without replacement)
 */

#include <iostream>
#define size 10
typedef long long ll;

using namespace std;
class Hash
{
    ll phone;
    string Name;
    public:
    Hash()
    {
        phone = 0;
        Name = "";
    }
    friend class DataBase;
};
class DataBase
{
    Hash HashTable_withoutRlc[size];
    Hash HashTable_withreplacement[size];

public:
    DataBase()
    {
        for (int i = 0; i < size; i++)
        {
            HashTable_withoutRlc[i].phone = 0;
            HashTable_withoutRlc[i].Name = "";
            HashTable_withreplacement[i].phone = 0;
            HashTable_withreplacement[i].Name = "";
        }
    }
    int hashkey(ll phn)
    {
        return (phn) % size;
    }
    void Insert_withoutrepalcement(ll phn, string name)
    {
        int key = hashkey(phn);
        int constant_key = key;
        if (HashTable_withoutRlc[key].phone == 0)
        {
            HashTable_withoutRlc[key].phone = phn;
            HashTable_withoutRlc[key].Name = name;
        }
        else
        {
            while (HashTable_withoutRlc[key].phone != 0)
            {


              key = (key+1)% size;
              if(constant_key == key){
            	  cout<<"Hash table overflow!";
            	  break;
              }
            }
            if(key != constant_key){
            HashTable_withoutRlc[key].phone = phn;
            HashTable_withoutRlc[key].Name = name;
            cout << "\nData Added Successfully!" << endl;
            }
        }
    }
    void Inser_withreplacement(ll phn, string name)
    {
        int key = hashkey(phn);
        int const_key = key;
        if (HashTable_withreplacement[key].phone == 0)
        {
            HashTable_withreplacement[key].phone = phn;
            HashTable_withreplacement[key].Name = name;
        }
        else
        {
            int x = hashkey(HashTable_withreplacement[key].phone);
            if (key == x)
            {
                while (HashTable_withreplacement[key].phone != 0)
                {

                  key =(key+1) % size;
                  if(const_key == key){
                      cout<<"Hash table overflow!";
                      break;
                  }
                }
                if(const_key != key){
                HashTable_withreplacement[key].phone = phn;
                HashTable_withreplacement[key].Name = name;
                }
            }
            else
            {
//            	int refkey = key;   // key for probing

                while (HashTable_withreplacement[key].phone != 0)
                {
                	key = (key+1) % size;            // finding the correct position for probing
                    if(const_key == key){
                    	cout<<"Hash table overflow!";
                        break;
                    }
                }
                if(key != const_key)
                {// shifting the false value to other position by linear probing
                HashTable_withreplacement[key].phone = HashTable_withreplacement[const_key].phone;
                HashTable_withreplacement[key].Name = HashTable_withreplacement[const_key].Name;
                // inserting the data at it's actual location
                HashTable_withreplacement[const_key].phone = phn;
                HashTable_withreplacement[const_key].Name = name;
                cout << "\nData Added Successfully!" << endl;
                }

            }
        }
    }
    void Display_withoutreplacement()
    {
        for (int i = 0; i < size; i++)
        {
        	if(HashTable_withoutRlc[i].phone == 0 ){
        		cout<<"Empty bucket !"<<endl;
        	}
        	else{
        	cout <<"At "<< i <<". Name: "<< HashTable_withoutRlc[i].Name << "\nPhone no: "
        			<< HashTable_withoutRlc[i].phone << "\n";
        	}
        }
    }
    void Display_withrepalcement()
    {
    	for (int i = 0; i < size; i++)
    	{
    	    if(HashTable_withreplacement[i].phone == 0 ){
    	        cout<<"Empty bucket !"<<endl;
    	    }
    	    else{
    	        cout <<"At "<< i <<". Name: "<< HashTable_withreplacement[i].Name << "\nPhone no: "
    	        			<< HashTable_withreplacement[i].phone << "\n";
    	    }
    	}
    }
    void Search_withoutreplacement(ll phn)
    {

        bool flag = false;
        int key = hashkey(phn);
        int key1 = key - 1;
        int cnt = 0;
        while (!flag)
        {
            cnt++;
            if (HashTable_withoutRlc[key].phone == phn)
            {
                cout << HashTable_withoutRlc[key].Name << "  <==>  " << HashTable_withoutRlc[key].phone << endl;
                cout << "Number of Comparison - " << cnt << endl;
                flag = true;
            }
            else if (key1 == key)
            {
                cout << "Invalid Data!" << endl;
                break;
            }
            else
            {
                key = (key + 1) % size;
            }
        }
    }
    void Search_withReplacement(ll phn)
    {
        int key = hashkey(phn);
        int key1 = key - 1;
        bool flag = false;
        int cnt = 0;
        while (!flag)
        {
            cnt++;
            if (HashTable_withreplacement[key].phone  == phn)
            {
                cout << HashTable_withreplacement[key].Name  << "  <==>  " <<HashTable_withreplacement[key].phone  << endl;
                cout << "Number of Comparison :- " << cnt << endl;
                flag = true;
            }
            else if (key1 == key)
            {
                cout << "Invalid Data!" << endl;
                break;
            }
            else
            {
                key = (key + 1) % size;
            }
        }
    }
};
int main()
{
    DataBase d1, d2;
    int ch;
    ll phn;
    string s;
    do
    {   cout<<"Menu\n";
        cout << "1.Insert Data For Hashing Without Replacement - " << endl;
        cout << "2.Insert Data For Hashing With Replacement - " << endl;
        cout << "3.Display Data For Without Replacement Probing - " << endl;
        cout << "4.Display Data For With Replacement Probing - " << endl;
        cout << "5.Search In Without Replacement Table - " << endl;
        cout << "6.Search In With Replacement Table - " << endl;
        cout << "\nEnter the Choice - ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nEnter the Phone Number - ";
            cin >> phn;
            cout << "\nEnter the Name - ";
            cin >> s;
            d1.Insert_withoutrepalcement(phn, s);
            break;
        case 2:
            cout << "\nEnter the Phone Number - ";
            cin >> phn;
            cout << "\nEnter the Name - ";
            cin >> s;
            d2.Inser_withreplacement(phn, s);
            break;
        case 3:
            d1.Display_withoutreplacement();
            break;
        case 4:
            d2.Display_withrepalcement();
            break;
        case 5:
            cout << "\nEnter the Phone Need to Be Search(WithoutRepalcemt) - ";
            cin >> phn;
            d1.Search_withoutreplacement(phn);
            break;
        case 6:
            cout << "\nEnter the Phone Need to Be Search(WithRepalcement) - ";
            cin >> phn;
            d2.Search_withReplacement(phn);
            break;
        default:
            break;
        }
    } while (ch != 0);

    return 0;
}




