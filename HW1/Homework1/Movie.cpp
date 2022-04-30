#include <iostream>
#include <ctime>
#include <string>

#include "Movie.h"

using namespace std;

char alph[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    // Empty movie objects
    Movie::Movie () {
        notCancel = false;
        return;
    }

    Movie::Movie( const long movieID, const int audienceRadius) {
        ID = movieID;
        radius = audienceRadius;
        notCancel = true;

        // Marking available and restricted seats
        for (int i = 0; i < numOfRow; i++) {
            for (int j = 0; j < numOfColumn; j++) {
                if ( (i % (radius + 1) == 0) && (j % (radius + 1) == 0) ) {
                    seats[j][i] = aval;
                } else {
                    seats[j][i] = restr;
                }
            }
        }
    }

    Movie::~Movie() {
        delete seats;
    }

    void Movie::setMovie( const long movieID, const int audienceRadius) {
        ID = movieID;
        radius = audienceRadius;
        notCancel = true;

        // Marking available and restricted seats
        for (int i = 0; i < numOfRow; i++) {
            for (int j = 0; j < numOfColumn; j++) {
                if ( (i % (radius + 1) == 0) && (j % (radius + 1) == 0) ) {
                    seats[j][i] = aval;
                } else {
                    seats[j][i] = restr;
                }
            }
        }
    }

    string Movie::toString(const bool forList) {
        if (forList) {
            return "Movie at " + getDate() + " (" + to_string(getAvalSeats()) + " available seats)\n";
        }
        else {
            return "Movie at " + getDate() + " has " + to_string(getAvalSeats()) + " available seats\n";
        }
    }

    void Movie::testPrint() {
        // Printing letters of table
        cout << "   ";
        for (int a = 0; a < numOfColumn; a++) {
            cout << " " << alph[a] << " ";
        }
        cout << "\n";

        // printing rows with numbers on left side
        for (int i = 0; i < numOfRow; i++) {
            cout << i+1;
            for (int j = 0; j < numOfColumn; j++) {
                if (seats[j][i] == occ) {
                    cout << " " << "X" << " ";
                }
                else if (seats[j][i] == aval) {
                    cout << " " << "O" << " ";
                }
                else {
                    cout << " " << "-" << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // Same with testPrint but hides restricted seats
    void Movie::printSeats() {
        cout << "  ";
        for (int a = 0; a < numOfColumn; a++) {
            if (a % (radius + 1) == 0) {
                cout << " " << alph[a] << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < numOfRow; i++) {
            if (i % (radius + 1) == 0) {
                if (i < 10) { cout << " " << i+1; }
                else { cout << i+1; }
                for (int j = 0; j < numOfColumn; j++) {
                    if (seats[j][i] == occ) {
                        cout << " " << "X" << " ";
                    }
                    else if (seats[j][i] == aval) {
                        cout << " " << "O" << " ";
                    }
                }
                cout << endl;
            }
        }
    }

    // Turns the value of a seat from aval to occ,
    // if it is aval to begin with.
    int Movie::bookSeat(const int row, const char col) {
        // Return values:
        // 0: successful | 1: occupied
        // 2: restricted | 3: unvalid input

        if (row < 1 || col < 1 || row > numOfRow || col > numOfColumn)
            { return 3; }
        else if (seats[col-1][row-1] == aval) {
            seats[col-1][row-1] = occ;
            return 0;
        }
        else { return seats[col-1][row-1]; }
    }

    long Movie::getID() { return ID; }
    int Movie::getRadius() { return radius; }

    int Movie::getAvalSeats() {
        int counter = 0;

        for (int i = 0; i < numOfRow; i++) {
            for (int j = 0; j < numOfColumn; j++) {
                counter += seats[j][i] == aval;
            }
        }
        return counter;
    }

    string Movie::getDate() {
        time_t tmptime = ID;
        string date = ctime(&tmptime);
        date = date.substr(0, date.length() - 1);
        return date;
    }

    bool Movie::isEnabled() { return notCancel; }
    bool Movie::setCancelled(const bool cancel) { notCancel = cancel; }
