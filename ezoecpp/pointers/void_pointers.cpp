#include "all.h"

void * memcpy(void * dest, void const * src, std::size_t n) {
    auto d = static_cast<std::byte *>(dest);
    auto s = static_cast<std::byte const *>(src);

    auto last = s + n;
    while (s != last) {
        *d = *s;
        ++d;
        ++s;
    }
    return dest;
}


int main() {
    int data {};

    void * void_ptr = & data;
    int * int_ptr = static_cast<int *>(void_ptr);


    int a[] = {1,2,3,4,5};
    int b[] = {6,7,8,9,0};

    memcpy(b, a, 3 * sizeof(int));
    for (auto x : b) {
        std::cout << x << std::endl;
    }
}
