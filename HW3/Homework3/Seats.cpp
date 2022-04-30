#include <iostream>
#include <cstddef>

#include "Seats.h"

using namespace std;

struct Seat {
    int row;
    char col;

    int state; // aval: 0 res: 1 rest: 2

    Seat* next;
};

Seats::Seats(int aRange) {
    size = 1;
    nonRest = 1;

    head = new Seat;
    head->row = 1;
    head->col = 'A';
    head->state = 0;

    range = aRange;

    Seat* curr = head;
    for (int rows = 1; rows <= numOfRow; rows++) {
        for (char cols = 'A'; cols <= 'Z'; cols++) {
            if (cols == 'A' && rows == 1)
                continue;
            size++;

            Seat* t = new Seat;

            t->row = rows;
            t->col = cols;

            if (((rows-1)*numOfRow + cols - 65) % (range + 1) == 0 && (rows-1) % (range+1) == 0) {
                t->state = 0;
                nonRest++;
            }
            else
                t->state = 2;

            curr->next = t;
            curr = curr->next;
        }
    }
    curr->next = NULL;
    //cout << "Seats constructed\n";
};

/*Seats::Seats( const Seats& aList ): size(aList.size) {
    if (aList.head == NULL)
        head = NULL; // Original list is empty
    else {
        // Copy first node
        head = new Seat;
        head->row = aList.head->row;
        head->col = aList.head->col;
        head->state = aList.head->state;

        // Copy rest of the list
        Seat *newPtr = head; // Dummy pointer for new list
        for ( Seat *origPtr = aList.head->next;
                               origPtr != NULL;
                               origPtr = origPtr->next) {
            newPtr->next = new Seat;
            newPtr = newPtr-> next;
            newPtr->row = origPtr->row;
            newPtr->col = origPtr->col;
            newPtr->state = origPtr->state;
        }
        newPtr->next = NULL;
    }
}*/

Seats::~Seats() {
    while (!isEmpty())
        remove(1);
    //cout << "Seats destructed\n";
}

// Prints all seats
void Seats::printSeats() {
    cout << "   ";
    for (char col = 'A'; col <= 'Z'; col++) {
        cout << " " << col << " ";
    }
    cout << "\n";

    int line = 2;
    for (Seat* curr = head; curr != NULL; curr = curr->next) {
        if (curr->state == 0)
            cout << " " << "O" << " ";
        else if (curr->state == 1)
            cout << " " << "X" << " ";
        else if (curr->state == 2)
            cout << " " << "-" << " ";
        if (curr->col == 'Z')
            cout << endl << line++;
    }
}

// Doesn't print restricted seats
void Seats::printNonRest() {
    cout << "  ";
    for (int row = 'A'; row <= 'Z'; row++) {
        if ((int(row-65) % (range + 1)) == 0) {
            cout << " " << char(row) << " ";
        }
    }
    cout << endl;
    for (Seat* curr = head; curr != NULL; curr = curr->next) {
        if (((curr->col - 65) % (range + 1) == 0) && ((curr->row - 1) % (range + 1) == 0)) {
            if(curr->col == 'A') {
                if ((curr->row) < 10) {cout << " ";}
                cout << curr->row;
            }
            if (curr->state == 1) {
                cout << " " << "X" << " ";
            }
            else if (curr->state == 0) {
                cout << " " << "O" << " ";
            }
        }
        if (curr->col == 'Z' && ((curr->row - 1) % (range + 1) == 0))
            cout << endl;
    }
}

// Sets a seat reserved if it is available
int Seats::setReserved(int rows, char cols) {
    // Returns 1: Successful, 0: Sold already, -1: Restricted
    for (Seat* curr = head; curr != NULL; curr = curr->next) {
        if (curr->row == rows && curr->col == cols) {
            if (curr->state == 0) {
                curr->state = 1;
                return 1;
            }
            else if (curr->state == 1)
                return 0;
            else
                return -1;
        }
    }
    return -2; // Shouldn't happen
}

// Sets a seat available if it is reserved
int Seats::setFree(int rows, char cols) {
    // Returns 1: Successful, 0: Was free already, -1: Restricted
    for (Seat* curr = head; curr != NULL; curr = curr->next) {
        if (curr->row == rows && curr->col == cols) {
            if (curr->state == 1) {
                curr->state = 0;
                return 1;
            }
            else if (curr->state == 0)
                return 0;
            else
                return -1;
        }
    }
    return -2; // Shouldn't happen
}

bool Seats::isEmpty() const {
    return size == 0;
}

int Seats::getLength() const {
    return size;
}

int Seats::getRange() const {
    return range;
}

int Seats::getNonRest() const {
    return nonRest;
}

bool Seats::retrieve(int index, int& row, char& col, int& state) const {
    if (index < 1 || index > getLength())
        return false;

    Seat* cur = find(index);
    row = cur->row;
    col = cur->col;
    state = cur->state;

    return true;
}

bool Seats::remove(int index) {
    if (index < 1 || index > getLength())
        return false;

    Seat *cur;

    --size;
    if (index == 1) {
        cur = head;
        head = head->next;
    }
    else {
        Seat *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;

    return true;
}

Seats::Seat* Seats::find(int index) const {
    if (index < 1 || index > getLength())
        return NULL;

    else {
        Seat *cur = head;
        for (int i = 1; i < index; ++i)
            cur = cur->next;
        return cur;
    }
}

