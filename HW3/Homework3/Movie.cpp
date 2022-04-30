#include <iostream>
#include <cstddef>
#include <ctime>

#include "Seats.h"
#include "Movie.h"

Movie::Movie (long anMovieID, int aRange) {
    seats = new Seats(aRange);

    id = anMovieID;
    range = aRange;
    avalSeats = seats->getNonRest();
    //cout << "Movie constructed\n";
};

Movie::~Movie() {
    delete seats;
    //cout << "Movie destructed\n";
}

// Deprecated
/*string Movie::toString(const bool forList) {
    if (forList)
        return "Movie at " + Movie::getDate() + " (" + Movie::toString(getAvalSeats()) + " available seats)\n";
    else
        return "Movie at " + getDate() + " has " + toString(getAvalSeats()) + " available seats\n";
}*/

void Movie::testPrint() {
    seats->printSeats();
}

void Movie::printSeats() {
    seats->printNonRest();
}

int Movie::bookSeat(int row, char col){
    int result = seats->setReserved(row, col);
    if (result == 1) // Booked successfully
        avalSeats--;
    return result;
}

int Movie::unbookSeat(int row, char col){
    int result = seats->setFree(row, col);
    if (result == 1) // Unbooked successfully
        avalSeats++;
    return result;
}

long Movie::getID() {return id;}

int Movie::getRange() {return seats->getRange();}

string Movie::getDate() {
    time_t tmptime = id;
    string date = ctime(&tmptime);
    date = date.substr(0, date.length() - 1);
    return date;
}

int Movie::getAvalSeats(){return avalSeats;}
