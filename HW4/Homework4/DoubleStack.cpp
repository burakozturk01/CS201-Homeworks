#include <cstddef>

#include  "DoubleStack.h"

DoubleStack::DoubleStack() {
    topPtr = NULL;
}

DoubleStack::DoubleStack(const DoubleStack& aDoubleStack) {
    if (aDoubleStack.isEmpty())
        topPtr = NULL;

    else {
        // First node
        topPtr = new DoubleStackNode;
        topPtr->item = aDoubleStack.topPtr->item;

        // Rest of the nodes
        DoubleStackNode* newPtr = topPtr;
        for (DoubleStackNode* origPtr = aDoubleStack.topPtr->next;
                        origPtr != NULL;
                        origPtr = origPtr->next) {
            newPtr->next = new DoubleStackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

DoubleStack::~DoubleStack() {
    while (!isEmpty())
        pop();
}

bool DoubleStack::isEmpty() const {
    return topPtr == NULL;
}

bool DoubleStack::push(DItemType newItem) {
    // New node
    DoubleStackNode* newPtr = new DoubleStackNode;

    // Put data in
    newPtr->item = newItem;

    // Put the node on top of the DoubleStack
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool DoubleStack::pop() {
    if (isEmpty())
        return false;

    else {
        DoubleStackNode* tmp = topPtr;
        topPtr = topPtr->next;

        tmp->next = NULL;
        delete tmp;
        return true;
    }
}

bool DoubleStack::pop(DItemType& topItem) {
    if (isEmpty())
        return false;

    else {
        topItem = topPtr->item;
        DoubleStackNode* tmp = topPtr;
        topPtr = topPtr->next;

        tmp->next = NULL;
        delete tmp;
        return true;
    }
}

bool DoubleStack::getTop(DItemType& topItem) {
    if (isEmpty())
        return false;

    else {
        topItem = topPtr->item;
        return true;
    }
}
