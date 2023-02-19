//
// Created by shene on 2/18/2023.
//
#include "Contact.h"


int main()
{
    auto * gs = new string("GREG");
    auto * m1 = new Contact();
    m1->setName(gs);
    auto * m2 = new Contact(*m1);



    cout << *m1 <<"\t\n"<< *m2 << endl;


    cout << "MSG TEST:\n";
    auto * ms1 = new Message();
    string s1, s2;
    s1 = "fag";
    ms1->setSender(s1);
    m1->addMessage(ms1);
    auto * ms2 = new Message(*ms1);
    cout << m1->getMsgCount() << endl;
    cout << m2->getMsgCount() << endl;
    ms1->getSender(s1);
    ms2->getSender(s2);



    cout << s1 << "\t" << s2 << endl;
    delete ms1;
    delete ms2;
    delete m1;
    delete m2;
    delete gs;

    return 0;
}