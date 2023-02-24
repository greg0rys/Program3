//
// Created by shene on 2/19/2023.
//

#ifndef PROGRAM3_MSGTREE_H
#define PROGRAM3_MSGTREE_H
#include "Contact.h"
#include "helpers/input.cpp"

// use the message num field as the key

class msgTree
{
private:
    typedef Message mssg;
    struct node
    {
        int key;
        Contact * sender;
        Message * msg;
        node *left, *right;

        node()
        {
            key = 0;
            sender = nullptr;
            msg = nullptr;
            left = right = nullptr;
        }

        node(const int &k, const Contact & ct, const mssg &ms)
        {
            key = k;
            sender = new Contact(ct);
            msg = new Message(ms);
            left = right = nullptr;
        }


        ~node()
        {
            if(sender)
                delete sender;
            if(msg)
                delete msg;
            key = 0;
            sender = nullptr;
            msg = nullptr;
            left = right = nullptr;
        }
    };
    int nodeCount;
    int height;
    node * root;

    void inorderDisplay(node *);
    node * insert(int &, node *&);
    map<int, Contact&> getMessageByContact(string &);
    bool searchByContact(const Contact &);
    bool searchByMsgNum(const int &);
    bool searchbyMsgType(const string &);
    void copyTree(node *&, node *);
    void destroy(node *&);
public:
    msgTree();
    msgTree(const msgTree &);
    msgTree& operator=(const msgTree &);
    ~msgTree();
    bool destroy();
    bool search();
    bool insert(const Contact &, const mssg &);
    int& getCount() {return nodeCount;}
    bool remove(mssg &); // use a ref to display deleted msg.
};
#endif //PROGRAM3_MSGTREE_H
