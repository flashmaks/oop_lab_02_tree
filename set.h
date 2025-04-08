#ifndef set_H
#define set_H
#include "tree.h"
#include <iostream>

template <typename T>
class set {
public:
    set() = default;

    set(const set<T>& s) : tree(s.tree) {}

    set(set <T>&& s) : tree(std::move(s.tree)) {}

    explicit set(std::initializer_list<T> lst) : tree(lst) {}

    ~set() = default;

    set<T>& operator =(const set<T>& lst) {
        tree = lst.tree;
        return *this;
    };

    void print() {
        tree.print();
    }

    int get_length() const {
        return tree.get_length();
    }

    bool contains(const T& elem) {
        return tree.contains(elem);
    }

    void add(const T& elem) {
        tree.add(elem);
    }

    void remove(const T& elem) {
        tree.remove(elem);
    }

    T* to_array() {
        return tree.to_array();
    }

    set<T>& unionWith(const set<T>& s) {
        BTree<T> tmp = tree.unionWith(s.tree);
        tree = tmp;
        return *this;
    }

    set<T>& intersectionWith(const set<T>& s) {
        BTree<T> tmp = tree.intersectionWith(s.tree);
        tree = tmp;
        return *this;
    }

    set<T>& subtractWith(const set<T>& s) {
        BTree<T> tmp = tree.subtractWith(s.tree);
        tree = tmp;
        return *this;
    }

    set<T>& operator +=(const set<T>& s) {
        return unionWith(s);
    }

    set<T>& operator *=(const set<T>& s) {
        return intersectionWith(s);
    }

    set<T>& operator /=(const set<T>& s) {
        return subtractWith(s);
    }

    auto iterator_begin() {
        return tree.iterator_begin();
    }

    auto iterator_begin() const {
        return tree.iterator_begin();
    }

    auto iterator_end() {
        return tree.iterator_end();
    }

    auto iterator_end() const {
        return tree.iterator_end();
    }

    void clear() {
        tree.clear();
    }

private:
    BTree<T> tree;
};

template<typename T>
std::ostream& operator <<(std::ostream& os, const set<T>& lst) {
    for(auto it = lst.iterator_begin(); it != lst.iterator_end(); ++it)
        os << it.value() << " ";
    return os;
}

template<typename T>
set<T> operator +(const set<T>& s1, const set<T>& s2) {
    set<T> tmpSet(s1);
    tmpSet += s2;
    return tmpSet;
}

template<typename T>
set<T> operator *(const set<T>& s1, const set<T>& s2) {
    set<T> tmpSet(s1);
    tmpSet *= s2;
    return tmpSet;
};

template<typename T>
set<T> operator /(const set<T>& s1, const set<T>& s2) {
    set<T> tmpSet(s1);
    tmpSet /= s2;
    return tmpSet;
}

#endif // set_H
