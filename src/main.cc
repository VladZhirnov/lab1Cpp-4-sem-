#include <iostream>
#include <functions/header.h>

void main() {
    Tree a;
    a.insert(5);
    a.insert(9);
    a.insert(2);
    a.insert(4);
    a.print();
    a.erase(4);
    a.print();
    Tree b;
    b = a;
}