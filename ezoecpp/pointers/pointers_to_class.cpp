#include "all.h"

struct C {
    int data;
    void func() {
        std::cout << data << std::endl;
    }

    void set(int n) {
        this->data = n; // this := C *

        auto & ref = *this;
        ref.data = n;
    }

    void con() const {
        C const * ptr = this;
    }
};

int main() {
    C object{};
    C * pointer = &object;

    pointer->data = 10;
    pointer->func();

    C & ref = *pointer;
    ref.data = 20;
    ref.func();
}
