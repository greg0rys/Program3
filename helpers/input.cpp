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