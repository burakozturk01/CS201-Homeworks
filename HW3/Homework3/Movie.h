#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <iostream>

#include "seats.h"

using namespace std;

class Movie {
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;

    Movie( long anMovieID, int aRange);

    ~Movie();

    std::string toString(const bool forList);

    void testPrint();

    // Same with testPrint but hides restricted seats
    void printSeats();

    // Turns the value of a seat from aval to occ,
    // if it is aval to begin with.
    int bookSeat(int row, char col);

    int unbookSeat(int row, char col);

    long getID();
    int getRange();
    string getDate();

    int getAvalSeats();
    Seats* seats;

private:

    long id;
    int range;
    int avalSeats;
};
#endif
