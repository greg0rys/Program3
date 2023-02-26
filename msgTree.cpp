//
// Created by shene on 2/19/2023.
//
#include "msgTree.h"

/*
 * Nested node class methods and constructs.
 */

/**
 * Default constructor
 */
msgTree::node::node():key(0),height(1),sender(nullptr),msg(nullptr),
                      left(nullptr),right(nullptr)
{}


/**
 * Create a node with all data members setup
 * @param key the key for the node
 * @param height the height this node is at in the AVL
 * @param contact the sender of the message
 * @param msg the message and its content
 * @param left pointer to left subtree
 * @param right pointer to right subtree
 *  The left and right pointers are defaulted to nullptr
 *  so that nodes can be created with all data members - l & r trees
 */
msgTree::node::node(const int & key, int height,
                    const Contact & contact, const Message & msg,
                    node * left, node * right)
{
    this->key = key;
    this->height = height;
    this->sender = new Contact(contact);
    this->msg = new Message(msg);
    this->left = left;
    this->right = right;

}


msgTree::node::node(const node & copy): key(0),height(1),
                                        sender(nullptr),msg(nullptr),
                                        left(nullptr),right(nullptr)
{
    *this = copy;
}


msgTree::node& msgTree::node::operator=(const node & copy)
{
    if(this == &copy)
        return *this;

    if(hasData())
        _destruct();

    if(copy.sender)
        sender = new Contact(*copy.sender);
    else
        sender = nullptr;
    if(copy.msg)
        msg = new Message(*copy.msg);
    else
        msg = nullptr;
    key = copy.key;
    height = copy.height;
    left = copy.left;
    right = copy.right;

    return *this;
}


msgTree::node::~node()
{
    _destruct();
}


void msgTree::node::_destruct()
{
    if(sender)
        delete sender;
    if(msg)
        delete msg;
    sender = nullptr;
    msg = nullptr;

}



[[maybe_unused]] void msgTree::node::destroy()
{
    _destruct();
}

void msgTree::node::display()
{
    Contact * ct = sender;
    Message * mssg = msg;

    if(ct)
        cout << *ct << endl;
    if(mssg)
        cout << *mssg << endl;
}




/*
 * End of node class implementation.
 */
/**
 * Default class constructor.
 */
msgTree::msgTree():nodeCount(0),height(0),root(nullptr)
{
}


/**
 * Class copy constructor.
 * @param aCopy the tree we wish to copy.
 */
msgTree::msgTree(const msgTree &aCopy): nodeCount(0),height(0),root(nullptr)
{
    *this = aCopy;
}


/**
 * Overloaded assignment operator to make deep copies of msgTree objects
 * @param copy the msgTree we wish to copy
 * @return a reference to this new tree we just made VIA copy.
 */
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


/**
 * Recursively copy all the nodes in another tree.
 * @param dest the destination tree that will get the node copied into it.
 * @param source the tree that has the node we are copying.
 */
void msgTree::copyTree(msgTree::node *&dest, msgTree::node *source)
{
    if(!source) return;

    dest = new node(*source);
    copyTree(dest->getLeft(), source->getLeft());
    copyTree(dest->getRight(), source->getRight());
}

/**
 * Class Destructor
 */
msgTree::~msgTree()
{
    destroy(root);
}


int msgTree::getHeight(node * curr)
{
    if(!curr)
        return 0;

    return curr->getHeight();
}


int msgTree::getBalanceFactor(node * curr)
{
    if(!curr) return 0;
    return getHeight(curr->getLeft()) - getHeight(curr->getRight());
}



/**
 * Recurse this Binary tree in order to delete all nodes in the tree.
 * @param tRoot the root of the binary tree
 */
void msgTree::destroy(node *& tRoot)
{
    if(!tRoot)
        return;
    destroy(tRoot->getLeft());
    destroy(tRoot->getRight());
    delete tRoot;

    tRoot = nullptr;
}


/**
 * Search the tree based on a given parameter - choices are
 * search by contact name
 * search by message type
 * seach by message number
 * @param matches the total number of matches for a given search
 * @param buffer a ref that will store the users search query so the search
 * results can be output with the query that was asked of the program.
 * @return true if the search finds a given match, false if else.
 * It will also return the number of matches for a given search using the
 * matches reference to an external counter.
 */
bool msgTree::search(int & matches, string &buffer)
{
    string input_buffer;
    int option;
    getSearchType(option);

    if(option == 1)
    {
        cout << "Please enter the contacts name: ";
        getInput(input_buffer);
        buffer = input_buffer;
        return searchByContact(root, matches, input_buffer);
    }

    if(option == 2) {
        cout << "Please enter a message type to search for\n";
        cout << "(EX Facebook or Text): ";
        getInput(input_buffer);
        buffer = input_buffer;
        return searchByMsgType(root,input_buffer, matches);
    }

    cout << "Please enter the message number: ";
    getInt(matches);
    buffer = to_string(matches);
    return searchByMsgNum(root,matches);
}


/**
 * Search the tree for messages by a given cotact
 * @param head the root of the tree
 * @param matches the number of matches for a given contact
 * @param cName the name of the contact
 * @return true if the contact was found, false if else
 *
 * It will also return the total number of matches by incrementing the
 * matches ref to an external counter.
 */
bool msgTree::searchByContact(node * head, int &matches, string &cName)
{

    if(!head)
        return false;

  string  senderName = head->getSenderName();
    if(senderName == cName)
    {
        matches++;
        return true;
    }

    // search left if sender is greater than cName
    if(senderName > cName)
        return searchByContact(head->getLeft(), matches, cName);


    return searchByContact(head->getRight(), matches, cName);



}


bool msgTree::searchByMsgType(node * curr,const string & mType, int & matches)
{

    if(!curr) return false;
    Message & currMessage = curr->getMessage();
    string messType;
    currMessage.getMsgType(messType);

     if(messType == mType)
     {
         matches++;
         return true;
     }

     if(messType > mType)
        return searchByMsgType(curr->getLeft(), mType, matches);
     return searchByMsgType(curr->getRight(), mType, matches);


}


bool msgTree::searchByMsgNum(node * curr, const int &mNum)
{

    if(!curr) return false;
    int currMessNum = curr->getMessage().getMNum();
    if(currMessNum == mNum)
    {
        return true;
    }

    if(currMessNum > mNum)
        return searchByMsgNum(curr->getLeft(), mNum);
    return searchByMsgNum(curr->getRight(), mNum);


}


/**
 * Call the recursive insert method to add a new node to the tree.
 * @param ct the contact we will add to the new node
 * @param msg the message that will be added to the new node
 * @return true if the node was added, false if else.
 *  based off the count if the count changes after we call insert that means
 *  the node was added to the tree if the count doesn't change no node was
 *  added.
 */
bool msgTree::insert(const Contact &ct, Message &msg)
{
    int currentCount;

    currentCount = nodeCount;
    root = _insert(root, ct, msg);
    height = getHeight(root);

    return currentCount != nodeCount; // this call to get count if the node
    // was added should be +1 the current count making this return true.
}


/**
 * Recurse the binary tree to add a new node to the proper place in the tree.
 * @param head the tree we wish to add to.
 * @param cont the contact we will add to the node.
 * @param msg the message we will add to the node.
 * @return an updated root pointer.
 */
msgTree::node* msgTree::_insert(msgTree::node *& head,
                                const Contact & cont,
                                const Message & msg)
{

    if(!head)
    {
        nodeCount++;
        return new node(msg.getMNum(), 0, cont, msg);
    }

    if(head->getKey() > msg.getMNum())
        head->getLeft() = _insert(head->getLeft(), cont, msg);
    else
        head->getRight() = _insert(head->getRight(), cont, msg);

    int heightL = getHeight(head->getLeft());
    int heightR = getHeight(head->getRight());
    int newHeight = 1 + (heightL > heightR ? heightL : heightR);
    node *& left = head->getLeft();
    node *& right = head->getRight();
    int currKey = head->getKey();
    int msgKey = msg.getMNum();

    // update the height of newly added nodes ancestor
    head->setHeight(newHeight);

    // ensure tree stays balanced
    // for AVL to be balanced its bf must be 0, 1, -1
    int bf = getBalanceFactor(head);

    // left + right subtree rotations
    if(bf > 1 && (currKey > msgKey))
        return rightRotation(head);
    if(bf < -1 && (currKey < msgKey))
        return leftRotation(head);

    // left subtree right node
    if(bf > 1 && (left->getKey() < msgKey))
    {
        left = leftRotation(left);
        return rightRotation(head);
    }

    if(bf < -1 && (right->getKey() > msgKey))
    {
        right = rightRotation(right);
        return leftRotation(head);
    }

    return head;
}


/**
 * To maintain balance of the AVL at each insert / removal
 * rotation of nodes in the right direction.
 * @param curr - current spot in the tree
 * @return
 */
msgTree::node * msgTree::rightRotation(node *& curr)
{
    int currHeight;
    int rotationHeight;
    node * left = curr->getLeft();
    node * leftRight = left->getRight();

    left->getRight() = left;
    left->getLeft() = leftRight;

    currHeight = max(getHeight(curr->getLeft()),
                     getHeight(curr->getRight())) + 1;
    rotationHeight = max(getHeight(left->getLeft()),
                          getHeight(left->getRight())) + 1;
    curr->setHeight(currHeight);
    left->setHeight(rotationHeight);

    return left;
}


/**
 * To keep the AVL in balance at each insertion / deletion
 * rotation of nodes in the left direction
 * @param curr - the current spot in the tree
 * @return
 */
msgTree::node* msgTree::leftRotation(node *& curr)
{
    int currHeight;
    int rotationHeight;

    node * right = curr->getRight();
    node * rightLeft = right->getLeft();

    right->getLeft() = curr;
    curr->getRight() = rightLeft;

    currHeight = max(getHeight(curr->getLeft()),
                     getHeight(curr->getRight())) + 1;
    rotationHeight = max(getHeight(right->getLeft()),
                         getHeight(right->getRight())) + 1;
    curr->setHeight(currHeight);
    right->setHeight(rotationHeight);

    return right;

}

map<int, Contact&> msgTree::getMessageByContact(string & cName)
{
    map<int, Contact&> contacts_map;
    int counter = 0;
    if(!searchByContact(root, counter, cName))
        return contacts_map; // check against empty map on return
    else
    {
        getContactsMap(contacts_map, root, cName, counter);
    }

    return contacts_map;
}


void msgTree::getContactsMap(map<int, Contact&> &mp, node * curr,
                             string &cName, int &counter)
{
    if(!curr) return;
    if(curr->getSenderName() == cName)
        mp.insert(pair<int,Contact&>(counter++,curr->getSender()));

    if(curr->getSenderName() > cName)
        getContactsMap(mp, curr->getLeft(), cName, counter);
    else
        getContactsMap(mp, curr->getRight(), cName, counter);
}


map<int,Message&> msgTree::getMessagesByType(string & msgType)
{
    map<int, Message&> mp;
    int counter = 0;
    if(!searchByMsgType(root, msgType, counter))
    {
        return mp;
    }
    else
    {
        getTypeMap(mp, root, counter, msgType);
    }

    return mp;
}


void msgTree::getTypeMap(map<int, Message &> & mp, msgTree::node * curr, int
& counter,string & mType)
{
    if(!curr) return;
    string temp;
    curr->getMessage().getMsgType(temp);
    if(temp == mType)
        mp.insert(pair<int,Message&>(counter++, curr->getMessage()));
    if(temp > mType)
        getTypeMap(mp, curr->getLeft(), counter, mType);
    else
        getTypeMap(mp,curr->getLeft(), counter, mType);
}

/**
 * the smallest node in a BST is always the leftmost leaf node
 * @param curr
 * @return
 */
msgTree::node* msgTree::getSmallest(node *& curr)
{
    node * temp = curr;

    while(temp->getLeft())
        temp = temp->getLeft();
    return temp;
}

msgTree::node* msgTree::removeNode(node *& curr, const int & key)
{
    if(!curr) return curr;
    int currKey = curr->getKey();

    if(currKey > key)
        curr->getLeft() = removeNode(curr->getLeft(), key);
    else if(currKey < key)
        curr->getRight() = removeNode(curr->getRight(), key);
    else
    {
        node *& left = curr->getLeft();
        node *& right = curr->getRight();
        node * temp = nullptr;

        if(!left || !right)
        {
            temp = left ? left : right;

            if(!temp)
            {
                temp = curr;
                curr = nullptr;
            }
            else *curr = *temp;

            delete temp;
        }
        else
        {
            temp = getSmallest(right);
            curr->setKey(temp->getKey());
            right = removeNode(right, temp->getKey());
        }
    }

    if(!curr) return curr;
    node *& left = curr->getLeft();
    node *& right = curr->getRight();
    int currHeight = 1 + max(getHeight(left),
                             getHeight(right));
    int bf;
    curr->setHeight(currHeight);
    bf = getBalanceFactor(curr);

    // handle rotations needed after delete
    if(bf > 1 && getBalanceFactor(left) >= 0)
        return rightRotation(curr);
    if(bf > 1 && getBalanceFactor(left) < 0)
    {
        left = leftRotation(left);
        return rightRotation(curr);
    }

    if(bf < - 1 && getBalanceFactor(right) <= 0)
        return leftRotation(curr);
    if(bf < -1 && getBalanceFactor(right) > 0)
    {
        right = rightRotation(right);
        return leftRotation(curr);
    }

    return curr;
}

bool msgTree::removeMsgNum(mssg & dest, int & msgNum)
{
    cout << "remove" << endl;
    return true;
}

bool msgTree::removeByContact(Contact & dest, int &)
{
    cout << "Remove" << endl;
    return true;
}

bool msgTree::removeByType(int & matches)
{
    cout << "Remove" << endl;
    return true;
}


void msgTree::printOrdered()
{
    if(!root)
        return;
    inorderDisplay(root);
    cout << endl;
}


void msgTree::inorderDisplay(msgTree::node * head)
{
    if(!head) return;
    inorderDisplay(head->getLeft());
    inorderDisplay(head->getRight());
    cout << head->getSender().getName() << endl;

}






#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#pragma clang diagnostic pop





