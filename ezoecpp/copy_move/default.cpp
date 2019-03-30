#include "all.h"

struct Point {
    int x;
    int y;
    int z;
};

int main() {
    // default copy: copy each member
    {
        Point a {1,2,3};
        Point b = a; // copy constructor
        Point c;
        c = a; // copy assignment

        b.x = 12;
        c.y = -1;
        std::cout << b.x << "," << b.y << "," << b.z << std::endl;
        std::cout << c.x << "," << c.y << "," << c.z << std::endl;
        std::cout << a.x << "," << a.y << "," << a.z << std::endl;
    }

    // default move: move each member
    {
        Point a {1,2,3};
        Point b;
        b = std::move(a);
        // equivalent to below:
        // Point b;
        // b.x = std::move(a.x); <- actualy, moving 'int' is just a copy.
        // b.y = std::move(a.y);
        // b.z = std::move(a.z);
        std::cout << b.x << "," << b.y << "," << b.z << std::endl;
    }

    // vector move
    {
        std::vector<int> v;
        std::vector<int> w = {1, 2, 3, 4, 5};

        v = std::move(w);
        for (auto i : v) {
            std::cout << i << std::endl;
        }

        w.resize(7); // we can use 'w' again now
        w[0] = -1;
        w[1] = -2;
        for (auto i : w) {
            std::cout << i << std::endl;
        }
    }
}
