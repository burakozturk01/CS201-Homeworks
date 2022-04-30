#include "ReservationList.h"
#include "MovieList.h"

class MovieBookingSystem {
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;

    MovieBookingSystem();
    ~MovieBookingSystem();

    void addMovie(const long movieID, const int audienceRadius);
    void cancelMovie(const long movieID);

    void showMovie(const long movieID) const;
    void showAllMovies() const;

    bool checkMovieID(const long movieID) const;

    int makeReservation(const long movieID, const int row, const char col);
    void cancelReservations(ReservationList resCodes);
    void cancelReservation(const int resCode);
    void showReservation(const int resCode) const;

private:
    ReservationList reservationCodes;
    MovieList movies;
};
