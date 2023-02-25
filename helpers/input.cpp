#pragma once
#include "string"
#include <iostream>

using namespace std;

string getInput()
{
    string input;
    getline(cin,input);

    while(input.empty())
    {
        cout << "Error empty inputs are not accepted: " << endl;
        cout << "Please try again: ";
        getline(cin,input);
    }

    return input;
}

void _getSearchType(string & dest)
{
    cout << "What would you like to serach by? "
            << "\n\t1.Contact\n\t2.Message Type.\n\t3. Message Number\n";
    cout << "Enter choice: ";
    getline(cin,dest);

    while(dest != "1" || dest != "2" || dest != "3")
    {
        dest.clear();
        cout << "Not a valid choice please please enter a valid choice\n";
        cout << "What would you like to search by? "
             << "\n\t1.Contact\n\t2.Message Type.\n\t3. Message Number\n";
        cout << "Enter choice: ";
        getline(cin,dest);

    }
}


void getInt(int &dest)
{

}