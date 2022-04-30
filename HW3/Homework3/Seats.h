#ifndef HEADERFILE_H2
#define HEADERFILE_H2

class Seats {
    public:
        Seats(int aRange);

        //Seats ( const Seats& aList);

        ~Seats();

        void printSeats();

        void printNonRest();

        int setReserved(int rows, char cols);

        int setFree(int rows, char cols);

        bool isEmpty() const;

        int getLength() const;

        int getRange() const;

        int getNonRest() const;

        bool retrieve(int index, int& row, char& col, int& state) const;

        bool remove(int index);

    private:
        const static int numOfRow = 30;
        const static int numOfColumn = 26;

        struct Seat {
            int row;
            char col;

            int state;

            Seat* next;
        };

        int size;
        int range;

        int nonRest;

        Seat *head;

        Seat *find(int index) const;
};
#endif
