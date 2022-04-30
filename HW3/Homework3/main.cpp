#include<iostream>
using namespace std;
#include "MovieBookingSystem.h"
int main() {
    MovieBookingSystem mbs;

    mbs.addMovie(13,5);
    mbs.addMovie(213,4);

    mbs.showAllMovies();

    ReservationList RL;
    int a = mbs.makeReservation(13, 1, 'A');
    RL.insert(1, a);
    int b = mbs.makeReservation(213, 1, 'A');
    RL.insert(2, b);

    mbs.cancelMovie(13);
    mbs.cancelMovie(213);

    mbs.showReservation(a);
    mbs.showReservation(b);
    return 0;
}
