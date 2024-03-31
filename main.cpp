#include <iostream>

#include "PriorityQueue.hpp"

int main() {
    PriorityQueue<int> integers(10);
    integers.insert(10,1);
    integers.insert(10,2);
    integers.insert(10,3);
    integers.insert(10,4);
    integers.insert(10,5);
    integers.insert(10,6);
    integers.insert(10,7);
    integers.insert(10,8);
    integers.insert(10,9);
    integers.insert(10,10);

    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();

    integers.pop();
    integers.print();
    return 0;
}
