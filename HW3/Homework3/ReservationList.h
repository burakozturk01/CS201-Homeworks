#ifndef ResHeader
#define ResHeader

class ReservationList {
    public:
        ReservationList();

        ReservationList ( const ReservationList& aList);

        ~ReservationList();

        bool isEmpty() const;

        int getLength() const ;

        bool retrieve(int index, int& resCode) const;

        bool insert(int index, int resCode);

        bool remove(int index);

        int findByResCode(int resCode) const;

        void printAll();

        private:
            struct ReservationNode {
                int Code;
                ReservationNode* next;
            };

            int size;

            ReservationNode *head;

            ReservationNode *find(int index) const;
};
#endif // ResHeader
