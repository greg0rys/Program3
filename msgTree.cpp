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
}