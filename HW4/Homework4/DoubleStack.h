#ifndef DoubleStackH
#define DoubleStackH

typedef double DItemType;

class DoubleStack {
public:
    DoubleStack();
    DoubleStack(const DoubleStack& aDoubleStack);
    ~DoubleStack();

    bool isEmpty() const;
    bool push(DItemType newItem);
    bool pop();
    bool pop(DItemType& topItem);
    bool getTop(DItemType& topItem);

private:
    struct DoubleStackNode {
        DItemType item;
        DoubleStackNode* next;
    };

    DoubleStackNode* topPtr;
};

#endif // DoubleStackH
