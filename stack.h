#ifndef STACK_H
#define STACK_H
#include "node.h"

template <typename T>
class stack {
public:
    stack() : topNode(nullptr), size(0) {}

    ~stack() {
        while(!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return (!topNode);
    }

    void push(T data) {
        NodeStack<T>* ptr = new NodeStack(data);
        ptr->next = topNode;
        topNode = ptr;
        size++;
    }

    bool pop() {
        if(isEmpty()) {
            return 0;
        }
        NodeStack<T>* ptr = topNode;
        topNode = topNode->next;
        delete ptr;
        size--;
        return 1;
    }

    T& top () {
        if(isEmpty())
            throw "Stack is empty.";
        return topNode->data;
    }

    const T& top() const {
        if(isEmpty())
            throw "Stack is empty.";
        return topNode->data;
    }

    int getSize() {
        return size;
    }

private:
    NodeStack<T>* topNode;
    int size;
};


#endif // STACK_H
