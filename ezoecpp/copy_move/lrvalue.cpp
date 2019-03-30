#include "all.h"

void f(const int &) {
    std::cout << "lvalue" << std::endl;
}

void f(int &&) {
    std::cout << "rvalue" << std::endl;
}

int main() {
    // lvalue
    int lvalue {};
    f(lvalue);

    // lvalue reference
    int &l_ref = lvalue;
    f(l_ref);

    // cast lvalue to rvalue reference
    int &&r_ref = static_cast<int &&>(lvalue);
    int &&r = std::move(lvalue);

    // both is lvalue: rvalue reference is lvalue
    f(r_ref);
    f(r);

    // std::move(...) is xvalue, which is rvalue
    f(static_cast<int &&>(lvalue));
    f(std::move(lvalue));

    // prvalue is rvalue
    f(1+1);
}
