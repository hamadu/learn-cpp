#include "all.h"

int f(int x) {
    std::cout << x << std::endl;
    return x*2;
}

using f_pointer = int (*) (int);

f_pointer g(f_pointer p) {
    p(0);
    return p;
}

int main() {
    f_pointer ptr = &f;
    (*ptr)(123);

    int (*ptr2)(int) = &f;

    (*ptr2)(456);

    g(&f);

    /*
        int (*      <- return value of g := pointer of f
          (*g_ptr)  <- variable name
            (
                int (*)(int) <- argument of g := pointer of f
            )
        )(int)
    */
    auto g_ptr = &g;
    (*g_ptr)(&f);
}
