//
// Created by shene on 2/19/2023.
//

#ifndef PROGRAM3_MSGTREE_H
#define PROGRAM3_MSGTREE_H
#include "Contact.h"
class msgTree{

protected:
    class node
    {
    private:
        int key, height;
        Contact *sender;
        Message *msg;
        node *left, *right;

        void _destruct();
        inline bool hasData()
        {
            bool data = false;
            if(sender || msg)
                data = true;
            return data;
        }

    public:
        typedef const Contact& c_cont;
        typedef const Message& c_message;
        typedef node* n_ptr;
        node();
        node(const int &, int, c_cont, c_message,
             n_ptr = nullptr, n_ptr = nullptr);
        node(const node &);
        node& operator=(const node &);
        ~node();
        friend bool operator>(node & curr, Message& mess)
        {
            return curr.getKey() > mess.getMNum();
        }
        friend bool operator<(node & curr, Message & mess)
        {
            return curr.getKey() < mess.getMNum();
        }
        void display();

        // make sure to update all methods to check against nullptr;
        [[maybe_unused]] void destroy();
        inline Contact& getSender(){return *sender;}
        inline Message& getMessage(){return *msg;}
        inline int& getKey(){return key;}
        inline int& getHeight(){return height;}
        inline string& getSenderName(){return sender->getName();}
        inline node*& getLeft(){return left;}
        inline node*& getRight(){return right;}
        inline void setHeight(int nHeight)
        {
            height = nHeight;
        }
        inline void setKey(int nKey){key = nKey;}

    };

public:
    typedef Message & mssg;
    msgTree();
    msgTree(const msgTree &);
    msgTree& operator=(const msgTree &);
    ~msgTree();
    // the prompting for search type can be moved to phone class
    bool search(int &, string &);
    bool insert(const Contact &,  mssg &);
    bool removeMsgNum(mssg &, int &); // use a ref to display deleted msg.
    bool removeByContact(Contact &, int &);
    bool removeByType(int &);
    void printOrdered();
    map<int, Contact&> getMessageByContact(string &);
    map<int, Message&> getMessagesByType(string &);

    inline int& getCount(){return nodeCount;}
    inline int& getHeight(){return height;}



private:
    int nodeCount;
    int height;
    node * root;

    void inorderDisplay(node *);
    node * _insert(node *&, const Contact &, const Message &);
    node * rightRotation(node *&);
    node * leftRotation(node *&);
    node * getSmallest(node *&);
    node * removeNode(node *&, const int &);
    void getContactsMap(map<int, Contact&> &, node *, string &, int &);
    void getTypeMap(map<int, Message&> &, node *, int &, string &);
    bool searchByContact(node *,int &, string &);
    bool searchByMsgNum(node *,const int &);
    bool searchByMsgType(node *,const string &, int &);
    void copyTree(msgTree::node *&, msgTree::node *);
    void destroy(node *&);
    static int getHeight(node *);
    static int getBalanceFactor(node *);

};

// inline class helpers
inline void getSearchType(int & opt)
{
    cout << "What would you like to serach by? "
         << "\n\t1.Contact\n\t2.Message Type.\n\t3. Message Number\n";
    cout << "Enter choice: ";

    cin >> opt;

    bool valid = false;
    if(opt == 1 || opt ==2 || opt == 3)
        valid = true;

    while(!valid)
    {

        cout << "Not a valid choice please please enter a valid choice\n";
        cout << "What would you like to search by? "
             << "\n\t1.Contact\n\t2.Message Type.\n\t3. Message Number\n";
        cout << "Enter choice: ";
        cin >> opt;
        if(opt == 1 || opt ==2 || opt == 3)
            valid = true;

        cin.ignore(101,'\n');
    }

}
inline void getInput(string & input)
{
    cin >> input;

    while(input.empty())
    {
        cout << "Error empty inputs are not accepted: " << endl;
        cout << "Please try again: ";
        getline(cin,input);
    }

}
inline void getInt(int & dest)
{
    cin >> dest;
}

#endif //PROGRAM3_MSGTREE_H
