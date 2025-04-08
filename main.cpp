#include <iostream>
#include "set.h"
int main() {
    set<int> d;
    set<int> k{1, 2, 7};
    d.add(1);
    d.add(2);
    d.add(3);;
    set<int> temp = d + k;
    std::cout << temp;
    return 0;
}
