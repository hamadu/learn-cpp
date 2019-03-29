#include "all.h"

int main() {
    {
        std::allocator<std::string> a;
        std::string * p = a.allocate(1);
        std::string *s = new(p) std::string("hellohellow");
        std::cout << *s << std::endl;
        s->~basic_string();
        a.deallocate(p, 1);
    }

    {
        int N = 10;

        std::allocator<std::string> a;
        using traits = std::allocator_traits<decltype(a)>;
        std::string *p = traits::allocate(a, 2);
        traits::construct(a, p, "hello!");
        traits::construct(a, p+1, "hello!!");

        std::cout << *p << std::endl;
        std::cout << *(p+1) << std::endl;

        traits::destroy(a, p);
        traits::destroy(a, p+1);
        traits::deallocate(a, p, 2);
    }
}
