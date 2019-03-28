#include "all.h"

int * invalidptr() {
    int v = 2;
    return &v;
}

int & invalidref() {
    int v = 2;
    return v;
}

int main() {
    // ref
    {
        int obj = 1;
        auto &ref = obj;
        std::cout << ref << std::endl;

        // int &ref; // error: reference requires initialize
    }



    // ptr
    {
        int obj = 1;
        auto *ptr = &obj;
        std::cout << ptr << std::endl;
        std::cout << *ptr << std::endl;

        int *emptyptr = nullptr;
        std::cout << emptyptr << std::endl;
    }

    // int *x = invalidptr();
    // std::cout << x << std::endl;

    // int x = invalidref(); // segmentation fault

    // ref to ptr
    {
        int obj = 1;
        int *x = &obj;
        int *&ptrref = x;
        std::cout << ptrref << std::endl;  // address
        std::cout << *ptrref << std::endl; // value
    }

    // const int pointer
    {
        int x{};
        const int *ptr = &x; // generate const int pointer form non-const int
        const int &ref = x; // generate const int reference form non-const int

        // *ptr = 12; // error: cannot change value
        // ref = 1; // error: cannot change value

        const int y{};
        ptr = &y;
    }

    // int const pointer
    {
        int x{};
        int * const ptr = &x;

        // can change value
        *ptr = 1;

        // error: cannot change pointer
        // ptr = nullptr;
    }

    // const int const pointer
    {
        int x{};
        int const * const ptr = &x;

        // cannot change value nor pointer
        // *ptr = 1;
        // ptr = nullptr;
    }

    // pointer of pointer
    {
        int x = 123;
        int *p = &x;
        int **pp = &p;

        int value1 = **pp;
        int y = 456;
        **pp = y;

        std::cout << value1 << std::endl;
        std::cout << **pp << std::endl;


        int z = 789;
        *pp = &z;
        std::cout << **pp << std::endl;
    }
}
