#include "all.h"

struct Object {
    // int Object::*
    int member;

    // int * Object::*
    int * ptr;

    // void (Object::*)()
    void func() {
        std::cout << member << std::endl;
    }

    // int (Object::*)(int)
    int id(int n) {
        return n;
    }
};

int main() {
    int Object::* int_ptr = &Object::member;
    void (Object::* func_ptr)() = &Object::func;
    int (Object::* id_ptr)(int) = &Object::id;

    Object object;
    object.*int_ptr = 123;
    (object.*func_ptr)();

    std::cout << (object.*id_ptr)(10) << std::endl;
}
