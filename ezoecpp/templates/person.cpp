#include "all.h"

template <typename T>
T twice(T const &n, T const &x) {
    return n * x;
}

template <typename T, T X>
T dbl(T a) {
    return a * X;
}

struct Person {
    std::string name;
    int age;

    Person operator *(int v) {
        return Person { this->name, this->age * v };
    }

    // const member function!
    // type of 'this' is 'Person const *'
    Person operator *(Person const &x) const {
        auto &ref = *this;
        return Person { ref.name, ref.age * x.age };
    }
};

int main() {
    double a = 1.3;
    double b = 2.4;
    std::cout << twice(a, b) << std::endl;
    std::cout << dbl<int, 3>(114514) << std::endl;

    Person p = Person { "dareka", 15 };
    std::cout << (p * 3).name << "," << (p * 4).age << std::endl;

    Person q = Person { "anot", 10 };
    std::cout << twice(p, q).name << "," << twice(p, q).age << std::endl;
}
