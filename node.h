#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    Node(T data = T()) : data(data) {}

    T data;
};

template <typename T>
class NodeTree : public Node<T> {
public:
    NodeTree(T data = 0) : Node<T>(data), left(nullptr), right(nullptr) {}
    NodeTree<T>* left;
    NodeTree<T>* right;
};

template <typename T>
class NodeStack : public Node<T> {
public:
    NodeStack(T data = 0) : Node<T>(data), next(nullptr) {}
    NodeStack<T>* next;
};

#endif // NODE_H
