#include <iostream>
#include <ctime>

#include "MovieBookingSystem.h"
#include "Movie.h"

using namespace std;

char alph1[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

     MovieBookingSystem::MovieBookingSystem() {
        movies = new Movie[maxmov];
        movieCount = 0;

        reserv = new long*[maxreserv];
        reservCount = 0;

        freeResCode = 0;

        for (int i = 0; i < maxreserv; i++) {
            reserv[i] = new long[4];
        }
     }
    MovieBookingSystem::~MovieBookingSystem() {
        delete[] movies;
        delete[] reserv;
    }

    void MovieBookingSystem::addMovie          ( const long movieID, const int audienceRadius ) {
        if (audienceRadius < 0 || audienceRadius > 7) {
            cout << "Audience radius is invalid, please enter a number in range [0, 7]\n";
        }
        else if (movieID < 0) {cout << "Invalid movie ID entered\n";}
        else if ( findMovie(movieID) == -1 ) {
            movies[movieCount].setMovie(movieID, audienceRadius);
            cout << "Movie at " << movies[movieCount].getDate() << " has been added\n";
            movieCount++;
        }
        else {
            Movie dummy(movieID, 0);
            cout << "Movie at " << dummy.getDate() << " already exists\n";
        }
    }

   void MovieBookingSystem::cancelMovie       ( const long movieID) {
        if (movieID < 1) {
            cout << "Invalid movie ID entered\n";
            return;
        }
        else if (!(movies[findMovie(movieID)].isEnabled())) {
            Movie dummy(movieID, 0);
            cout << "Movie at " << dummy.getDate() << " does not exist\n";
        }

        for (int i = 0; i < maxmov; i++) {
            if (movies[i].getID() == movieID) {
                movies[i].setCancelled(false);

                int resCount = 0;
                for (int i = 0; i < reservCount; i++) {
                    if (reserv[i][0] == movieID) {
                        resCount++;
                    }

                }
                int resArr[resCount];
                for (int i = 0; i < reservCount; i++) {
                    if (reserv[i][0] == movieID) {
                        resArr[i] = reserv[i][3];
                    }
                }
                cout << "Movie at " << movies[i].getDate() << " has been canceled\n";
                cancelReservations(resCount, resArr);
            }
        }
        Movie dummy(movieID, 0);
        cout << "Movie at " << dummy.getDate() << " does not exist\n";
    }
    void MovieBookingSystem::showAllMovies     () {
        cout << "Movies on show:\n";
        for (int i = 0; i < movieCount; i++) {
            if (movies[i].isEnabled()) {
                cout << movies[i].toString(true);
            }
        }
    }
    void MovieBookingSystem::showMovie         ( const long movieID) {
        if (movieID < 1) {
            cout << "Movie ID can't be smaller than 1\n";
            return;
        }

        int index = findMovie(movieID);

        if (index == -1 || !(movies[findMovie(movieID)].isEnabled())) {
            Movie dummy(movieID, 0);
            cout << "Movie at " << dummy.getDate() << " does not exist\n";
        }
        else {
            cout << movies[index].toString(false);
            movies[index].printSeats();
        }
    }
    int MovieBookingSystem::makeReservation   ( const long movieID, const int row, const char col) {
        int mcol;
        for (int i = 1; i <= numOfColumn; i++) {
            if (alph1[i-1] == col) {
                mcol = i;
                break;
            }
        }

        int index = findMovie(movieID);
        if (movieID == -1 || !(movies[findMovie(movieID)].isEnabled())) {
            Movie dummy(movieID, 0);
            cout << "Movie at " << dummy.getDate() << " does not exist\n";
        }

        int out = movies[index].bookSeat(row, mcol);
        // Return values:
        // 0: successful | 1: occupied
        // 2: restricted | 3: unvalid input

        switch(out) {
            case 1:
                cout << "Seat " << col << row << " is not available in Movie at " << movies[index].getDate() << endl;
                break;
            case 2:
                cout << "Seat " << col << row << " is restricted due to COVID-19 precautions in Movie at " << movies[index].getDate() << endl;
                break;
            case 3:
                cout << "Invalid values entered for column and/or row\n";
                break;
            case 0:
                cout << "Reservation done for " << col << row << " in Movie at " << movies[index].getDate() << endl;
                break;
            default:
                cout << "Something must have gone very wrong\nThis output shouldn't be possible\n";
                break;
        }

        if (out == 0) {
            reserv[reservCount][0] = movieID;
            reserv[reservCount][1] = row;
            reserv[reservCount][2] = mcol;
            reserv[reservCount][3] = freeResCode;
            reservCount++;
            return freeResCode++;
        }
    }

    void MovieBookingSystem::cancelReservation(const int resCode) {
        for (int i = 0; i < reservCount; i++) {
            if (reserv[i][3] == resCode) {
                cout << "Reservation on Code " << resCode << " is canceled: Seat " << alph1[reserv[resCode][2] - 1] << reserv[resCode][1] << " in Movie at " << movies[findMovie(reserv[i][0])].getDate() << endl;
                int j = i;
                while (j < reservCount) {
                    if (j == reservCount - 1) {
                        reserv[j][0] = 0;
                        reserv[j][1] = 0;
                        reserv[j][2] = 0;
                        reserv[j][3] = 0;
                        break;
                    }
                    reserv[j][0] = reserv[j+1][0];
                    reserv[j][1] = reserv[j+1][1];
                    reserv[j][2] = reserv[j+1][2];
                    reserv[j][3] = reserv[j+1][3];
                    j++;
                }
                reservCount--; return;
            }
        }
    }

    void MovieBookingSystem::cancelReservations( const int numRes, const int* resCode) {
        if (reservCount == 0) {
            cout << "Some reservation codes do not exist. Cancellation is failed\n";
            return;
        }
        for (int i = 0; i < numRes; i++) {
            if (!(resCodeExists(resCode[i]))) {
                cout << "Some reservation codes do not exist. Cancellation is failed\n";
                return;
            }
        }
        for (int i = 0; i < numRes; i++) {
            cancelReservation(resCode[i]);
        }
    }

    void MovieBookingSystem::showReservation   ( const int resCode) {
        if (resCode < 0) {
            cout << "Invalid reservation code entered\n";
        }
        else {
            for (int i = 0; i < reservCount; i++) {
                if (reserv[i][3] == resCode) {
                    cout << "Reservation with Code " << resCode << ": Seat " << alph1[reserv[resCode][2] - 1] << reserv[resCode][1] << " in Movie at " << movies[findMovie(reserv[i][0])].getDate() << endl;
                    return;
                }
            }
            cout << "No reservation with Code " << resCode << endl;
        }

    }

    int MovieBookingSystem::findMovie(const long movieID) {
        for (int i = 0; i < movieCount; i++) {
            if (movies[i].getID() == movieID) {
                return i;
            }
        }
        return -1;
    }

    bool MovieBookingSystem::resCodeExists(const int resCode) {
        for (int i = 0; i < reservCount; i++) {
            if (reserv[i][3] == resCode) {
                return true;
            }
        }
        return false;
    }

    void MovieBookingSystem::testPrintReservs() {
        for (int i = 0; i < reservCount; i++) {
            for (int j = 0; j < 3; j++) {
                cout << reserv[i][j] << " ";
            }
            cout << endl;
        }
    }

    int MovieBookingSystem::testGetRCount() { return reservCount; }
