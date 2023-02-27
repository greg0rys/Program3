//
// Created by shene on 2/18/2023.
//

#include "Phone.h"
void test()
{
    auto * ms = new msgTree();
    vector<Contact> ct1;
    vector<Message> msg;
    string names[] = {"greg","marcos","dexter","rocko"};
    string ctype[] ={"facebook", "twitter", "reddit", "insta"};
    string chandle[] = {"@gs","@mv", "@ds", "@rs"};
    string content[] = {"g","m","d","r"};
    Contact ct;
    Message mess;
    for(auto x = 0; x < 4; x++)
    {
        string name = names[x];
        string type = ctype[x];
        string handle = chandle[x];
        string mss = content[x];


        ct.setName(&name);
        ct.setType(&type);
        ct.setHandle(&handle);

        mess.setSender(name);
        mess.setMsgType(type);
        mess.setMsgContent(mss);
        ct1.push_back(ct);
        cout << mess.getMNum() << endl;
        msg.push_back(mess);
        ms->insert(ct,mess);
        if(x != 3)
            mess.generateNewNum();


    }

    auto * p1 = new Phone(ct1,msg,(const string &) "Greg",ms,true);
    p1->displayContacts();
    *p1 -= ct;
    p1->displayContacts();
    *p1 + ct;
    cout << "Added one contact " << ct.getName() << endl;
    p1->displayContacts();
    *p1 -= mess;



//    auto * t2 = new msgTree(*ms);
//    t2->insert(ct,mess);
//    t2->printOrdered();
//    cout << "\t total nodes: " << t2->getCount() << endl;
//    cout << ms << "\t" << t2 << endl;
//    ms->printOrdered();
//    cout << "\t total nodes: " << ms->getCount();
//
//    cout << "\nTotal heights:\n\t";
//    cout << "ms: " << ms->getHeight() << "\t t2: " << t2->getHeight() << endl;
   delete ms;
   delete p1;
//    delete t2;

}
int main()
{
    test();
    return 0;
}