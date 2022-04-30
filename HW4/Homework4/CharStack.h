#ifndef CharStackH
#define CharStackH

typedef char ItemType;

class CharStack {
public:
    CharStack();
    CharStack(const CharStack& aCharStack);
    ~CharStack();

    bool isEmpty() const;
    bool push(ItemType newItem);
    bool pop();
    bool pop(ItemType& topItem);
    bool getTop(ItemType& topItem);

private:
    struct CharStackNode {
        ItemType item;
        CharStackNode* next;
    };

    CharStackNode* topPtr;
};

#endif // CharStackH
