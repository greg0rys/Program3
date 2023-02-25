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

        node(const int& k, const Contact & ct, const mssg &ms)
        {
            key = k;
            sender = new Contact(ct);
            msg = new Message(ms);
            left = right = nullptr;
        }

         int& getKey() {return this->key;}

        ~node()
        {
            if(sender)
                delete sender;
            if(msg)
                delete msg;
            sender = nullptr;
            msg = nullptr;
            left = right = nullptr;
        }
    };
    int nodeCount;
    int height;
    node * root;

    // use a static int as a counter to assign message nums
     // saves space in case more than 1 tree is made.

    void inorderDisplay(node *);
    node * _insert(node *&, const Contact &, const Message &);
    map<int, Contact&> getMessageByContact(string &);
    map<int, Message&> getMessagesByType(string &);
    bool searchByContact(node *,int &, string &);
    bool searchByMsgNum(const int &);
    bool searchbyMsgType(const string &, int &);
    void copyTree(node *&, node *);
    void destroy(node *&);
public:
    msgTree();
    msgTree(const msgTree &);
    msgTree& operator=(const msgTree &);
    ~msgTree();
    bool destroy();
    bool search(int &, string &);
    bool insert(const Contact &, const mssg &);
    int& getCount() {return nodeCount;}
    bool removeMsgNum(mssg &, int &); // use a ref to display deleted msg.
    bool removeByContact(Contact &, int &);
    bool removeByType(int &);
};
#endif //PROGRAM3_MSGTREE_H
