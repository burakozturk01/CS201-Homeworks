#include <iostream>
#include <cstddef>

#include "MovieBookingSystem.h"

using namespace std;

MovieBookingSystem::MovieBookingSystem() {
    //cout << "MovieBookingSystem constructed\n";
}
MovieBookingSystem::~MovieBookingSystem() {
    //cout << "MovieBookingSystem destructed\n";
}

void MovieBookingSystem::addMovie(const long movieID, const int audienceRadius){
    if (audienceRadius < 0 || audienceRadius > 7) {
        cout << "Your audience radius is out of bounds. [0,7]\n";
        return;
    }

    Movie* mov = new Movie(movieID, audienceRadius);
    if (checkMovieID(movieID)) {
        //cout << "No ID conflict\n"; //Debug
        movies.insert(movies.getLength() + 1, mov);
        cout << "Movie at " << mov->getDate() << " has been added\n";
        return;
    }
    cout << "Movie at " << mov->getDate() << " already exists\n";
    delete mov;
}
void MovieBookingSystem::cancelMovie(const long movieID){
    Movie* mov = new Movie(movieID, 1);
    if (checkMovieID(movieID)) {
        cout << "Movie at " << mov->getDate() << " does not exists\n";
        delete mov;
        return;
    }

    int resCode;
    int resID;
    int i = 1;

    while (i <= reservationCodes.getLength()) {
        reservationCodes.retrieve(i, resCode);
        resID = resCode / 10000;


        if (resID == movieID) {
            reservationCodes.remove(reservationCodes.findByResCode(resCode));
            continue;
        }
        i++;
    }

    int index = movies.findByID(movieID);
    movies.remove(index);

    cout << "Movie at " << mov->getDate() << " has been canceled\n";
    delete mov;
}

void MovieBookingSystem::showMovie(const long movieID) const {
    Movie* mov = new Movie(movieID, 1);
    if (checkMovieID(movieID)) {
        cout << "Movie at " << mov->getDate() << " does not exists\n";
        delete mov;
        return;
    }
    movies.retrieve(movies.findByID(movieID), mov);
    cout << "Movie at " << mov->getDate() << " has " << mov->getAvalSeats() << " available seats\n";
    mov->printSeats();
}
void MovieBookingSystem::showAllMovies() const {
    if (movies.isEmpty()) {
        cout << "No movie on show\n";
        return;
    }

    cout << "Movies on show:\n";
    Movie* mov;
    for (int i = 1; i <= movies.getLength(); i++) {
        movies.retrieve(i, mov);
        cout << "Movie at " << mov->getDate() << " (" << mov->getAvalSeats() << " available seats)\n";
    }
}

bool MovieBookingSystem::checkMovieID(const long movieID) const {
    if (movies.isEmpty())
        return true;

    Movie* testMovie;
    for (int i = 1; i <= movies.getLength(); i++) {
        movies.retrieve(i, testMovie);

        if (movieID == testMovie->getID())
            return false;
    }
    return true;
}
// Note: Only way I can think for generating unique resCode for every reservation
// and being able to find out movieID, row and col from resCode other than
// storing movieID in ReservationList is including all three in resCode.
// Therefore my resCode implementation doesn't work with too big movieIDs.
int MovieBookingSystem::makeReservation(const long movieID, const int row, const char col) {
    // -1: Movie doesn't exist, Seat restricted, Seat occupied
    // resCode: Successful
    Movie* mov;
    bool movieExists = movies.retrieve(movies.findByID(movieID), mov);

    if (!movieExists) {
        mov = new Movie(movieID, 1);
        cout << "Movie at " << mov->getDate() << " does not exists\n";
        delete mov;
        return -1;
    }

    int result = mov->bookSeat(row, col); // Returns 1: Successful, 0: Sold already, -1: Restricted

    int resCode; // resCode = [movieID][column number as ASCII][row number] put together
    if (result == 1) {
        resCode = movieID;

        resCode *= 100;
        resCode += col;


        resCode *= 100;
        resCode += row;

        reservationCodes.insert(reservationCodes.getLength()+1, resCode);
    }

    switch (result) {
        case(1):
            cout << "Reservation done for " << col << row << " in Movie at " << mov->getDate() << endl;
            return resCode;
        case(0):
            cout << "Seat " << col << row << " is already sold in Movie at " << mov->getDate() << endl;
            return -1;
        case(-1):
            cout << "Seat " << col << row << " is restricted in Movie at " << mov->getDate() << endl;
            return -1;
    }
}

void MovieBookingSystem::cancelReservation(const int resCode) {
    reservationCodes.remove(reservationCodes.findByResCode(resCode));

    int row = resCode % 100;
    char col = (resCode / 100) % 100;
    long movID = resCode / 10000;

    Movie* mov;
    movies.retrieve(movies.findByID(movID), mov);

    mov->unbookSeat(row, col);

    cout << "Reservation on Code " << resCode << " canceled: Seat " << col << row << " in ";
    cout << mov->getDate() << endl;
}

void MovieBookingSystem::cancelReservations(ReservationList resCodes) {
    if (resCodes.isEmpty()) {
        cout << "Some reservation codes do not exist. Cancelation is failed\n";
        return;
    }

    int otherResCode;
    for (int i = 1; i <= resCodes.getLength(); i++) {
        resCodes.retrieve(i, otherResCode);

        int oInd = reservationCodes.findByResCode(otherResCode);

        if (oInd == -1) {
            cout << "Some reservation codes do not exist. Cancelation is failed\n";
            return;
        }
    }

    for (int i = 1; i <= resCodes.getLength(); i++) {
        resCodes.retrieve(i, otherResCode);
        cancelReservation(otherResCode);
    }

}
void MovieBookingSystem::showReservation(const int resCode) const {
    int index = reservationCodes.findByResCode(resCode);

    if (index == -1) {
        cout << "No reservation with Code " << resCode << endl;
        return;
    }

    int row = resCode % 100;
    char col = (resCode / 100) % 100;
    long movID = resCode / 10000;

    Movie* mov;
    movies.retrieve(movies.findByID(movID), mov);

    cout << "Reservation with Code " << resCode << ": Seat " << col << row << " in Movie at " << mov->getDate() << endl;
}
