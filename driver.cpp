//
// Created by shene on 2/18/2023.
//
#include "Contact.h"
#include "Message.h"
#include<iostream>
using namespace std;

int main()
{
    auto * gs = new string("GREG");
    auto * m1 = new Contact();
    m1->setName(gs);
    auto * m2 = new Contact(*m1);



    cout << *m1 <<"\t\n"<< *m2 << endl;
    delete m1;
    delete m2;
    delete gs;

    cout << "MSG TEST:\n";
    auto * ms1 = new Message();
    auto * ms2 = new Message(*ms1);
    string s1, s2;
    s1 = "fag";
    ms1->setSender(s1);
    ms1->getSender(s1);
    ms2->getSender(s2);

    cout << s1 << "\t" << s2 << endl;
    delete ms1;
    delete ms2;

    return 0;
}