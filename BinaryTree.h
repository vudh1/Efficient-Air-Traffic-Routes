#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

#include <iomanip>
#include <iostream>
#include <string>

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;
    int count;

public:
    BinaryTree() : rootPtr(nullptr), count(0) {}
    BinaryTree(const BinaryTree& tree);
    virtual ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& sourceTree);

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    void clear()
    {
        destroyTree(rootPtr);
        rootPtr = nullptr;
        count = 0;
    }

    void preOrder(void visit(ItemType&)) const
    {
        _preorder(visit, rootPtr);
    }

    void inOrder(void visit(ItemType&)) const
    {
        _inorder(visit, rootPtr);
    }

    void postOrder(void visit(ItemType&)) const
    {
        _postorder(visit, rootPtr);
    }

    void BreadthFirstTraversal(void visit(ItemType&)) const
    {
        _breadthFirstTraversal(visit, rootPtr);
    }

    // Kept for compatibility with the original project.
    void findItem(void visit(ItemType&), std::string target)
    {
        _findItem(visit, rootPtr, target);
    }

    void indentedList(void visit(ItemType&)) const
    {
        _indentedList(visit, rootPtr, 0);
    }

    BinaryNode<ItemType>* minValueNode(BinaryNode<ItemType>* node);

    virtual bool insert(const ItemType& newData) = 0;
    virtual bool remove(const ItemType& data) = 0;
    virtual bool getEntry(const ItemType& entry,
                          ItemType& returnedItem) const = 0;

private:
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    BinaryNode<ItemType>* copyTree(
        const BinaryNode<ItemType>* nodePtr);

    void _preorder(void visit(ItemType&),
                   BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType&),
                  BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType&),
                    BinaryNode<ItemType>* nodePtr) const;

    void _breadthFirstTraversal(
        void visit(ItemType&),
        BinaryNode<ItemType>* nodePtr) const;

    void _findItem(void visit(ItemType&),
                   BinaryNode<ItemType>* nodePtr,
                   const std::string& target);

    void _indentedList(void visit(ItemType&),
                       BinaryNode<ItemType>* nodePtr,
                       int indent) const;
};

template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree& tree)
    : rootPtr(copyTree(tree.rootPtr)), count(tree.count)
{
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(
    const BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr == nullptr)
        return nullptr;

    BinaryNode<ItemType>* copy =
        new BinaryNode<ItemType>(nodePtr->getItem());

    copy->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
    copy->setRightPtr(copyTree(nodePtr->getRightPtr()));
    return copy;
}

template<class ItemType>
BinaryTree<ItemType>::~BinaryTree()
{
    destroyTree(rootPtr);
}

template<class ItemType>
BinaryTree<ItemType>& BinaryTree<ItemType>::operator=(
    const BinaryTree<ItemType>& sourceTree)
{
    if (this == &sourceTree)
        return *this;

    clear();
    rootPtr = copyTree(sourceTree.rootPtr);
    count = sourceTree.count;
    return *this;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr == nullptr)
        return;

    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());
    delete nodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr == nullptr)
        return;

    ItemType item = nodePtr->getItem();
    visit(item);
    _preorder(visit, nodePtr->getLeftPtr());
    _preorder(visit, nodePtr->getRightPtr());
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr == nullptr)
        return;

    _inorder(visit, nodePtr->getLeftPtr());
    ItemType item = nodePtr->getItem();
    visit(item);
    _inorder(visit, nodePtr->getRightPtr());
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr == nullptr)
        return;

    _postorder(visit, nodePtr->getLeftPtr());
    _postorder(visit, nodePtr->getRightPtr());
    ItemType item = nodePtr->getItem();
    visit(item);
}

template<class ItemType>
void BinaryTree<ItemType>::_breadthFirstTraversal(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr == nullptr)
        return;

    Queue<BinaryNode<ItemType>*> queue;
    queue.enqueue(nodePtr);

    while (!queue.isEmpty())
    {
        BinaryNode<ItemType>* current = nullptr;
        queue.dequeue(current);

        ItemType item = current->getItem();
        visit(item);

        if (current->getLeftPtr() != nullptr)
            queue.enqueue(current->getLeftPtr());

        if (current->getRightPtr() != nullptr)
            queue.enqueue(current->getRightPtr());
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_findItem(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr,
    const std::string& target)
{
    if (nodePtr == nullptr)
        return;

    // The original project used this compatibility hook with
    // customerData's name comparison operator.
    ItemType item = nodePtr->getItem();
    _findItem(visit, nodePtr->getLeftPtr(), target);
    _findItem(visit, nodePtr->getRightPtr(), target);

    if (item.getName() == target)
        visit(item);
}

template<class ItemType>
void BinaryTree<ItemType>::_indentedList(
    void visit(ItemType&),
    BinaryNode<ItemType>* nodePtr,
    int indent) const
{
    if (nodePtr == nullptr)
        return;

    if (nodePtr->getRightPtr() != nullptr)
        _indentedList(visit, nodePtr->getRightPtr(), indent + 5);

    std::cout << std::setw(indent) << ' ';
    ItemType item = nodePtr->getItem();
    std::cout << ((indent + 5) / 5) << ". ";
    visit(item);
    std::cout << '
';

    if (nodePtr->getLeftPtr() != nullptr)
        _indentedList(visit, nodePtr->getLeftPtr(), indent + 5);
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::minValueNode(
    BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* current = nodePtr;
    while (current != nullptr && current->getLeftPtr() != nullptr)
        current = current->getLeftPtr();
    return current;
}

#endif
