#include <cstddef>

#include  "CharStack.h"

CharStack::CharStack() {
    topPtr = NULL;
}

CharStack::CharStack(const CharStack& aCharStack) {
    if (aCharStack.isEmpty())
        topPtr = NULL;

    else {
        // First node
        topPtr = new CharStackNode;
        topPtr->item = aCharStack.topPtr->item;

        // Rest of the nodes
        CharStackNode* newPtr = topPtr;
        for (CharStackNode* origPtr = aCharStack.topPtr->next;
                        origPtr != NULL;
                        origPtr = origPtr->next) {
            newPtr->next = new CharStackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

CharStack::~CharStack() {
    while (!isEmpty())
        pop();
}

bool CharStack::isEmpty() const {
    return topPtr == NULL;
}

bool CharStack::push(ItemType newItem) {
    // New node
    CharStackNode* newPtr = new CharStackNode;

    // Put data in
    newPtr->item = newItem;

    // Put the node on top of the CharStack
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool CharStack::pop() {
    if (isEmpty())
        return false;

    else {
        CharStackNode* tmp = topPtr;
        topPtr = topPtr->next;

        tmp->next = NULL;
        delete tmp;
        return true;
    }
}

bool CharStack::pop(ItemType& topItem) {
    if (isEmpty())
        return false;

    else {
        topItem = topPtr->item;
        CharStackNode* tmp = topPtr;
        topPtr = topPtr->next;

        tmp->next = NULL;
        delete tmp;
        return true;
    }
}

bool CharStack::getTop(ItemType& topItem) {
    if (isEmpty())
        return false;

    else {
        topItem = topPtr->item;
        return true;
    }
}
