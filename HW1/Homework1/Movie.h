#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <ctime>

using namespace std;

class Movie {
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;

    // All possible states of a seat
    const static int  aval = 0;
    const static int   occ = 1;
    const static int restr = 2;

    Movie ();

    Movie( const long movieID, const int audienceRadius);

    ~Movie();

    void setMovie( const long movieID, const int audienceRadius);

    string toString(const bool forList);

    void testPrint();

    // Same with testPrint but hides restricted seats
    void printSeats();

    // Turns the value of a seat from aval to occ,
    // if it is aval to begin with.
    int bookSeat(const int row, const char col);

    long getID();
    int getRadius();

    int getAvalSeats();

    string getDate();

    bool isEnabled();
    bool setCancelled(const bool cancel);


private:
    long ID;
    int radius;
    bool notCancel;

    int seats[numOfColumn][numOfRow];
};
#endif // MOVIE_H
