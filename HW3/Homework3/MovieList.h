#ifndef MovieListHeader
#define MovieListHeader

#include "Movie.h"

class MovieList {
    public:
        MovieList();

        MovieList ( const MovieList& aList);

        ~MovieList();

        bool isEmpty() const;

        int getLength() const ;

        bool retrieve(int index, Movie*& mov) const;

        bool insert(int index, Movie* mov);

        bool remove(int index);

        // Returns index of movie
        // Returns -1 if does not exist
        int findByID(long movieID) const;

        private:
            struct MovieNode {
                Movie* movie;
                MovieNode* next;
            };

            int size;

            MovieNode *head;

            MovieNode *find(int index) const;
};
#endif // MovieListHeader
