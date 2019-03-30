#include "all.h"

template <typename T>
class dynamic_array {
private:
    T * first;
    T * last;
public:
    dynamic_array(std::size_t size = 0) : first(new T[size]), last(first+size) {}

    ~dynamic_array() { delete[] first; }

    // copy constructor
    dynamic_array(const dynamic_array & r) : first(new T[r.size()]), last(first+r.size()) {
        std::cout << "copy(construct)!" << std::endl;
        std::copy(r.begin(), r.end(), begin());
    }

    // move constructor
    dynamic_array(dynamic_array && r) : first(r.first), last(r.last) {
        std::cout << "move(construct)!" << std::endl;
        r.first = nullptr;
        r.last = nullptr;
    }

    // copy assignment
    dynamic_array & operator = (const dynamic_array & r) {
        std::cout << "copy(assign)!" << std::endl;
        if (this != &r && size() != r.size())
        {
            delete[] first;
            first = new T[r.size()];
            last = first + r.size();
            std::copy(r.begin(), r.end(), begin());
        }
        return *this;
    }

    // move assignment
    dynamic_array & operator = (dynamic_array && r) {
        std::cout << "move(assign)!" << std::endl;
        delete[] first;

        first = r.first;
        last = r.last;

        r.first = nullptr;
        r.last = nullptr;

        return *this;
    }

    T & operator [] (std::size_t i) const noexcept {
        return first[i];
    }

    std::size_t size() const noexcept {
        return last - first;
    }

    T * begin() const noexcept {
        return first;
    }

    T * end() const noexcept {
        return last;
    }
};

int main() {
    dynamic_array<int> a(6);
    dynamic_array<int> b(3);

    a[0] = 12;
    a[1] = -34;

    b = a; // copy assignment!
    b[2] = 5;

    dynamic_array<int> c = b; // copy construct!
    c[1] = -111;

    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "===" << std::endl;
    for (auto x : b) {
        std::cout << x << std::endl;
    }
    std::cout << "===" << std::endl;
    for (auto x : c) {
        std::cout << x << std::endl;
    }
    std::cout << "===" << std::endl;
    dynamic_array<int> ma = std::move(a); // move construct!
    ma[0] = 999;
    for (auto x : ma) {
        std::cout << x << std::endl;
    }
    std::cout << "===" << std::endl;

    dynamic_array<int> mma(100);
    mma = std::move(ma); // move assignment!
    mma[0]++;
    for (auto x : mma) {
        std::cout << x << std::endl;
    }
    std::cout << "===" << std::endl;
}
