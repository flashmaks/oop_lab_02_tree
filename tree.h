#ifndef BTree_H
#define BTree_H
#include "node.h"
#include "stack.h"
#include <iostream>

template <typename T>
class BTree {
public:
    BTree() : root(nullptr) {size = 0;}

    BTree(const BTree<T>& s) : size(s.size) {
        root = copyBTree(s.root);
    }

    BTree(BTree<T>&& s) : root(s.root) {
        s.root = nullptr;
    };

    explicit BTree(std::initializer_list<T> list) : root(nullptr), size(list.size()) {
        for(auto it = list.begin(); it != list.end(); ++it)
            insert(root, *it);
    };

    ~BTree() { destroyNode(root); }

private:
    NodeTree<T>* root;
    int size;

    static void destroyNode(NodeTree<T>* node) {
        if(node) {
            destroyNode(node->left);
            destroyNode(node->right);
            delete node;
        }
    }

    bool contains(NodeTree<T>* node, T data) const {
        if(!node)
            return false;
        else if(data == node->data)
            return true;
        else if(data < node->data)
            return contains(node->left, data);
        else
            return contains(node->right, data);
    }

    void insert(NodeTree<T>*& node, T data) {
        if(!node) {
            node = new NodeTree<T>(data);
        }
        else {
            if(data == node->data)
                return;
            else if(data < node->data)
                insert(node->left, data);
            else
                insert(node->right, data);
        }
    }

    void print(NodeTree<T>* node) const {
        if(node) {
            print(node->left);
            std::cout << node->data << " ";
            print(node->right);
        }
    }

    void inOrderTraversal(NodeTree<T>* node, T* array, int& i) {
        if(node) {
            inOrderTraversal(node->left, array, i);
            array[i++] = node->data;
            inOrderTraversal(node->right, array, i);
        }
    }

    NodeTree<T>* findMin(NodeTree<T>* node) const {
        while(node->left) node = node->left;
        return node;
    }

    NodeTree<T>* findMax(NodeTree<T>* node) const {
        while(node->right) node = node->right;
        return node;
    }

    NodeTree<T>* remove(NodeTree<T>* node, T data) {
        if(!node)
            return node;
        else if(data < node->data)
            node->left = remove(node->left, data);
        else if (data > node->data)
            node->right = remove(node->right, data);
        else {
            if(!node->left) {
                NodeTree<T> *temp = node;
                node = node->right;
                delete temp;
            }
            else if(!node->right) {
                NodeTree<T> *temp = node;
                node = node->left;
                delete temp;
            }
            else {
                NodeTree<T> *temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

    NodeTree<T>* copyBTree(NodeTree<T>* node) {
        if(!node) return nullptr;

        NodeTree<T>* newNode = new NodeTree<T>(node->data);
        newNode->left = copyBTree(node->left);
        newNode->right = copyBTree(node->right);

        return newNode;
    }

public:

    BTree<T>& operator =(const BTree<T>& s) {
        if(this != &s) {
            destroyNode(root);
            root = copyBTree(s.root);
            size = s.size;
        }
        return *this;
    }

    int get_length() const {
        return size;
    }

    bool contains(T data) const {
        return contains(root, data);
    }

    void add(T data) {
        insert(root, data);
        size++;
    }

    void print() const {
        print(root);
        std::cout << std::endl; // Доп. метод в задании  нет.
    }

    void remove(T data) {
        root = remove(root, data);
        size--;
    }

public:
    template <typename U>
    class Iterator {
    public:
        Iterator(BTree<U>& container_obj) {
            addToStack(container_obj.root);
        }

        Iterator(const BTree<U>& container_obj) {
            addToStack(container_obj.root);
        }

        Iterator() = default;

        Iterator<U>& next() {
            if(!stack.isEmpty()) {
                NodeTree<U>* nextNode = stack.top();
                stack.pop();
                if(nextNode->right)
                    addToStack(nextNode->right);
            }
            return *this;
        };

        const U& value() const {
            return stack.top()->data;
        };

        Iterator<U>& operator++() {
            return next();
        };

        U& operator*() {
            return stack.top()->data;
        };

        const U& operator*() const {
            return stack.top()->data;
        };

        bool operator ==(const Iterator<U>& b) const {
            bool mark;

            if(stack.isEmpty() && b.stack.isEmpty())
                mark = true;
            else if(stack.isEmpty() || b.stack.isEmpty())
                mark = false;
            else {
                mark = stack.top() == b.stack.top();
            }
            return mark;
        };

        bool operator !=(const Iterator<U>& b) const {
            return !(*this == b);
        };

    private:

        void addToStack(NodeTree<T>* node) {
            while(node) {
                stack.push(node);
                node = node->left;
            }
        }

        bool hasNext() {
            return stack.getSize() > 0;
        }

        stack<NodeTree<U>*> stack;
    };

public:

    Iterator<T> iterator_begin() {
        return Iterator<T>(*this);
    }

    Iterator<T> iterator_begin() const {
        return Iterator<T>(*this);
    }

    Iterator<T> iterator_end() {
        return Iterator<T>();
    }

    Iterator<T> iterator_end() const {
        return Iterator<T>();
    }

    /*    T* to_array() { // Две версии, эта через рекурсию
        if(!root) return nullptr;

        T* array = new T[size];
        int index = 0;
        inOrderTraversal(root, array, index);

        return array;
    }
*/

    T* to_array() { // Две версии, эта через итератор
        if(!root) return nullptr;

        T* array = new T[size];
        int i = 0;
        for(auto it = iterator_begin(); it != iterator_end(); ++it) {
            array[i++] = it.value();
        }
        return array;
    }

    BTree<T> unionWith(const BTree<T>& s) const {
        BTree<T> unionBTree(*this);

        for(auto it = s.iterator_begin(); it != iterator_end(); ++it) {
            unionBTree.add(it.value());
        }

        return unionBTree;
    }

    BTree<T> intersectionWith(const BTree<T>& s) const {
        BTree<T> intersectionBTree;

        for(auto it = iterator_begin(); it != iterator_end(); ++it) {
            if(s.contains(it.value()))
                intersectionBTree.add(it.value());
        }

        return intersectionBTree;
    }

    BTree<T> subtractWith(const BTree<T>& s) const {
        BTree<T> subtractBTree(*this);

        for(auto it = s.iterator_begin(); it != iterator_end(); ++it) {
            subtractBTree.remove(it.value());
        }

        return subtractBTree;
    }

    void clear() {
        destroyNode(root);
        root = nullptr;
        size = 0;
    }

};

template<typename T>
std::ostream& operator <<(std::ostream& os, const BTree<T>& lst) {
    for(auto it = lst.iterator_begin(); it != lst.iterator_end(); ++it)
        os << it.value << " ";
    return os;
}

template<typename T>
BTree<T> operator +(const BTree<T>& s1, const BTree<T>& s2) {
    return s1.unionWith(s2);
}

template<typename T>
BTree<T> operator *(const BTree<T>& s1, const BTree<T>& s2) {
    return s1.intersectionWith(s2);
}

template<typename T>
BTree<T> operator /(const BTree<T>& s1, const BTree<T>& s2) {
    return s1.subtractWith(s2);
}

#endif // BTree_H
