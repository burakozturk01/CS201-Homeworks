#include <iostream>
#include <ctime>

#include "MovieBookingSystem.h"

//#include "MovieBookingSystem.h"

using namespace std;

int main()
{
    MovieBookingSystem mbs;

    mbs.showAllMovies();
    cout << endl;

    mbs.addMovie(1263748, 5);
    cout << endl;
    mbs.addMovie(8765398765, 1);
    cout << endl;
    mbs.addMovie(1263748, 4);
    cout << endl;

    mbs.showAllMovies();
    cout << endl;

    int resC1 = mbs.makeReservation(8765398765,1,'A');
    cout << resC1 << endl;
    int resC2 = mbs.makeReservation(1263748,7,'G');
    cout << resC2 << endl;

    mbs.showReservation(resC1);
    mbs.showReservation(resC2);
    mbs.showReservation(7);

    cout << endl;

    int* res = new int[2];
    res[0] = resC1;
    res[1] = resC2;

    mbs.cancelReservations(2, res);
    cout << endl;

    mbs.showReservation(resC1);
    mbs.showReservation(resC2);
    mbs.testPrintReservs();

    cout << endl;

    mbs.showMovie(8765398765);
    mbs.showMovie(1263748);
    mbs.showMovie(123123623);


    return 0;
}
