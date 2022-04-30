#include <iostream>
#include <cstddef>

#include "ReservationList.h"

using namespace std;

struct ReservationNode {
    int Code;
    ReservationNode* next;
};

ReservationList::ReservationList(): size(0), head(NULL) {};

ReservationList::ReservationList( const ReservationList& aList ): size(aList.size) {
    if (aList.head == NULL)
        head = NULL; // Original list is empty
    else {
        // Copy first node
        head = new ReservationNode;
        head->Code = aList.head->Code;

        // Copy rest of the list
        ReservationNode *newPtr = head; // Dummy pointer for new list
        for ( ReservationNode *origPtr = aList.head->next;
                               origPtr != NULL;
                               origPtr = origPtr->next) {
            newPtr->next = new ReservationNode;
            newPtr = newPtr-> next;
            newPtr->Code = origPtr->Code;
        }
        newPtr->next = NULL;
    }
}

ReservationList::~ReservationList() {
    while (!isEmpty())
        remove(1);
}

bool ReservationList::isEmpty() const {
    return size == 0;
}

int ReservationList::getLength() const {
    return size;
}

bool ReservationList::retrieve(int index, int& resCode) const {
    if (index < 1 || index > getLength())
        return false;

    ReservationNode* cur = find(index);
    resCode = cur->Code;

    return true;
}

bool ReservationList::insert(int index, int resCode) {
    int newLength = getLength() + 1;

    if ((index < 1) || (index > newLength))
        return false;

    ReservationNode *newPtr = new ReservationNode;
    size = newLength;
    newPtr->Code = resCode;

    if (index == 1) {
        newPtr->next = head;
        head = newPtr;
    }
    else {
        ReservationNode *prev = find(index-1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}

bool ReservationList::remove(int index) {
    if (index < 1 || index > getLength())
        return false;

    ReservationNode *cur;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        ReservationNode *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;

    return true;
}

int ReservationList::findByResCode(int resCode) const {
    int i = 1;
    for (ReservationNode* curr = head; curr != NULL; curr = curr->next) {
        if (resCode == curr->Code)
            return i; // Found at index i
        i++;
    }
    return -1; // Unsuccessful

}

// Testing function
void ReservationList::printAll() {
    for (ReservationNode* curr = head; curr != NULL; curr = curr->next) {
        cout << curr->Code << endl;
    }
}

ReservationList::ReservationNode* ReservationList::find(int index) const {
    if (index < 1 || index > getLength())
        return NULL;

    else {
        ReservationNode *cur = head;
        for (int i = 1; i < index; ++i)
            cur = cur->next;
        return cur;
    }
}
