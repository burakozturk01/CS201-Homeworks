#ifndef MBS_HEADER
#define MBS_HEADER

#include <iostream>
#include <ctime>
#include "Movie.h"

using namespace std;

class MovieBookingSystem {
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;

    const static int maxmov = 100;
    const static int maxreserv = 500;

     MovieBookingSystem();
    ~MovieBookingSystem();

    void addMovie          ( const long movieID, const int audienceRadius );
    void cancelMovie       ( const long movieID);
    void showAllMovies     ();
    void showMovie         ( const long movieID);
    int  makeReservation   ( const long movieID, const int row, const char col);
    void cancelReservation (const int resCode);
    void cancelReservations( const int numRes, const int* resCode);
    void showReservation   ( const int resCode);
    int findMovie          (const long movieID);
    bool resCodeExists     (const int resCode);
    void testPrintReservs  ();
    int testGetRCount      ();

private:
    Movie* movies;
    int movieCount;

    long** reserv;
    int reservCount;

    int freeResCode;
};
#endif // MBS_HEADER
