#include <iostream>
#include <cstddef>

#include "Movie.h"
#include "MovieList.h"

using namespace std;

struct MovieNode {
    Movie* movie; // I stored Movies as pointers to prevent copyings
    MovieNode* next;
};

MovieList::MovieList(): size(0), head(NULL) {/*cout << "MovieList constructed\n";*/};

MovieList::MovieList( const MovieList& aList ): size(aList.size) {
    if (aList.head == NULL)
        head = NULL; // Original list is empty
    else {
        // Copy first node
        head = new MovieNode;
        head->movie = aList.head->movie;

        // Copy rest of the list
        MovieNode *newPtr = head; // Dummy pointer for new list
        for ( MovieNode *origPtr = aList.head->next;
                               origPtr != NULL;
                               origPtr = origPtr->next) {
            newPtr->next = new MovieNode;
            newPtr = newPtr-> next;
            newPtr->movie = origPtr->movie;
        }
        newPtr->next = NULL;
    }
}

MovieList::~MovieList() {
    while (!isEmpty())
        remove(1);
    //cout << "MovieList destructed\n";
}

bool MovieList::isEmpty() const {
    return size == 0;
}

int MovieList::getLength() const {
    return size;
}

bool MovieList::retrieve(int index, Movie*& mov) const {
    if (index < 1 || index > getLength())
        return false;

    MovieNode* cur = find(index);
    mov = cur->movie;

    return true;
}

bool MovieList::insert(int index, Movie* mov) {
    int newLength = getLength() + 1;

    if ((index < 1) || (index > newLength))
        return false;

    MovieNode *newPtr = new MovieNode;
    size = newLength;
    newPtr->movie = mov;

    if (index == 1) {
        newPtr->next = head;
        head = newPtr;
    }
    else {
        MovieNode *prev = find(index-1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}

bool MovieList::remove(int index) {
    if (index < 1 || index > getLength())
        return false;
    MovieNode *cur;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        MovieNode *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur->movie;
    delete cur;
    cur = NULL;

    return true;
}

int MovieList::findByID(long movieID) const {
    int i = 1;
    for (MovieNode* curr = head; curr != NULL; curr = curr->next) {
        if (movieID == curr->movie->getID())
            return i; // Found at index i
        i++;
    }
    return -1; // Unsuccessful
}

MovieList::MovieNode* MovieList::find(int index) const {
    if (index < 1 || index > getLength())
        return NULL;

    else {
        MovieNode *cur = head;
        for (int i = 1; i < index; ++i) {
            cur = cur->next;
        }
        return cur;
    }
}
