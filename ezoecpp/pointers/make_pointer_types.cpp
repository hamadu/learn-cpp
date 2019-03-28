#include "all.h"


template <typename T>
using type = T;

template <typename T>
using add_pointer_t = T *;


int main() {
    // same type
    {
        type<int> a = 2;
        type<std::vector<int>> c = {1, 2, 3, 4, 5};
        std::cout << c[2] << std::endl;
    }

    // pointer type
    {
        type<int> *a = nullptr;
        type<int(int)> *b = nullptr;
        type<int[5]> *c = nullptr;
    }

    // add pointer
    {
        add_pointer_t<int> d = nullptr;
        add_pointer_t<int *> e = nullptr;

        // add_pointer_t<int &> ptr = nullptr;
        std::add_pointer_t<int &> ptr = nullptr;
    }
}
