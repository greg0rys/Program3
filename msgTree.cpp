//
// Created by shene on 2/19/2023.
//

#include "msgTree.h"

msgTree::msgTree():root(nullptr), nodeCount(0),height(0)
{
}


msgTree::msgTree(const msgTree &aCopy):root(nullptr),nodeCount(0),height(0)
{
    *this = aCopy;
}


msgTree& msgTree::operator=(const msgTree &copy)
{
    // self assignment gaurd
    if(this == &copy)
        return *this;

    if(root)
        destroy(root);
    if(!copy.root)
    {
        root = nullptr;
        height = copy.height;
        nodeCount = copy.nodeCount;
        return (*this);
    }

    copyTree(root, copy.root);
    height = copy.height;
    nodeCount = copy.nodeCount;

    return *this;
}


void msgTree::copyTree(msgTree::node *&dest, msgTree::node *source)
{
    if(!source) return;

    dest = new node();
    copyTree(dest->left, source->left);
    copyTree(dest->right, source->right);
}


msgTree::~msgTree()
{
    destroy();
}


bool msgTree::destroy()
{
    if(!root)
        return false;
    destroy(root);

    return true;
}


/*
 * Recurse in order to delete all nodes in this tree
 */
void msgTree::destroy(node *&tRoot)
{
    if(!tRoot)
        return;
    destroy(tRoot->left);
    destroy(tRoot->right);
    delete tRoot;

    tRoot = nullptr;
}


// take a string ref for a buffer to output the users search query
bool msgTree::search(int & matches, string &buffer)
{
    static string input_buffer;
    _getSearchType(input_buffer);

    if(input_buffer == "1")
    {
        cout << "Please enter the contacts name: ";
        input_buffer = getInput();
        buffer = input_buffer;
        return searchByContact(root,matches, input_buffer);
    }

    if(input_buffer == "2") {
        cout << "Please enter a message type to search for\n";
        cout << "(EX Facebook or Text): ";
        input_buffer = getInput();
        buffer = input_buffer;
        return searchbyMsgType(input_buffer, matches);
    }

    cout << "Please enter the message number: ";
    getInt(matches);
    buffer = to_string(matches);
    return searchByMsgNum(matches);
}


bool msgTree::searchByContact(node * head,int &matches, string &cName)
{
    if(!head)
        return false;
    string sender;
    bool found = false;

    head->sender->getName(sender);

    if(sender == cName)
    {
        matches++;
        found = true;
    }

    // search left if sender is greater than cName
    if(sender > cName)
        return searchByContact(head->left, matches, cName);


    return  searchByContact(head->right, matches, cName);

}


bool msgTree::insert(const Contact &ct, const Message &msg)
{
    int currentCount, updatedCount;

    currentCount = getCount();
    root = _insert(root, ct, msg);
    updatedCount = getCount();

    return currentCount != updatedCount;
}


msgTree::node* msgTree::_insert(msgTree::node *& head,
                                const Contact & cont,
                                const Message & msg)
{
    if(!head)
    {
        nodeCount++;
        return new node(msg.getMNum(),cont,msg);
    }

    if(head->getKey() > msg.getMNum())
        head->left = _insert(head->left, cont, msg);
    else
        head->right = _insert(head->right, cont, msg);

    return head;
}