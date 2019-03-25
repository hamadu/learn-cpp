#include "all.h"


/**
 * iterator of Array
 */
template <typename Array>
struct array_iterator {
    Array &a;
    std::size_t i;

    array_iterator(Array &a, std::size_t i) : a(a), i(i) {}

    // ++iter: returns reference
    array_iterator& operator ++() {
        ++i;
        return *this;
    }

    // iter++: returns copy(before operation)
    array_iterator operator ++(int) {
        array_iterator copy = *this;
        ++*this;
        return copy;
    }

    // --iter: returns reference
    array_iterator& operator --() {
        --i;
        return *this;
    }

    // iter--: returns copy(before operation)
    array_iterator operator --(int) {
        array_iterator copy = *this;
        --*this;
        return copy;
    }

    array_iterator& operator +=(std::size_t n) {
        i += n;
        return *this;
    }

    array_iterator operator +(std::size_t n) const {
        array_iterator copy = *this;
        copy += n;
        return copy;
    }

    array_iterator& operator -=(std::size_t n) {
        i -= n;
        return *this;
    }

    array_iterator operator -(std::size_t n) const {
        array_iterator copy = *this;
        copy -= n;
        return copy;
    }

    bool operator ==(array_iterator const &right) const {
        return i == right.i;
    }

    bool operator !=(array_iterator const &right) const {
        return i != right.i;
    }

    bool operator <(array_iterator const &right) const {
        return i < right.i;
    }

    bool operator <=(array_iterator const &right) const {
        return i <= right.i;
    }

    typename Array::reference operator *() {
        return a[i];
    }

    typename Array::reference operator [](std::size_t n) const {
        return *(*this + n);
    }
};

/**
 * const iterator of Array
 */
template <typename Array>
struct array_const_iterator {
    Array const &a;
    std::size_t i;

    array_const_iterator(Array const &a, std::size_t i) : a(a), i(i) {}

    array_const_iterator(typename Array::iterator const &iter) : a(iter.a), i(iter.i) {}

    array_const_iterator& operator ++() {
        ++i;
        return *this;
    }

    array_const_iterator& operator --() {
        --i;
        return *this;
    }

    bool operator ==(array_const_iterator const &right) const {
        return i == right.i;
    }

    bool operator !=(array_const_iterator const &right) const {
        return i != right.i;
    }

    bool operator <(array_const_iterator const &right) const {
        return i < right.i;
    }

    bool operator <=(array_const_iterator const &right) const {
        return i <= right.i;
    }

    array_const_iterator& operator +=(std::size_t n) {
        i += n;
        return *this;
    }

    array_const_iterator operator +(std::size_t n) const {
        array_const_iterator copy = *this;
        copy += n;
        return copy;
    }

    typename Array::const_reference operator *() const {
        return a[i];
    }

    typename Array::const_reference operator [](std::size_t n) const {
        return *(*this + n);
    }
};


template <typename T, std::size_t N>
struct array {
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using size_type = std::size_t;
    using iterator = array_iterator<array>;
    using const_iterator = array_const_iterator<array>;

    value_type storage[N];

    reference operator [](size_type i) {
        // not const
        // storage[i] = -1;
        return storage[i];
    }

    // const member function
    const_reference operator [](size_type i) const {
        // error: assignment of read-only location '((const array<int, 6>*)this)->array<int, 6>::storage[i]'
        // storage[i] = -1;
        return storage[i];
    }

    size_type size() const {
        return N;
    }

    reference front() {
        return storage[0];
    }

    const reference front() const {
        return storage[0];
    }

    reference back() {
        return storage[N-1];
    }

    const reference back() const {
        return storage[N-1];
    }

    void fill(T const &u) {
        std::fill(begin(), end(), u);
    }

    iterator begin() {
        return array_iterator(*this, 0);
    }

    iterator end() {
        return array_iterator(*this, N);
    }

    // type of 'this' is 'array const *'
    const_iterator begin() const {
        return array_const_iterator(*this, 0);
    }

    const_iterator end() const {
        return array_const_iterator(*this, N);
    }
};

template <typename Array>
void print_with_const_index(const Array &c) {
    for (std::size_t i = 0 ; i != c.size() ; ++i) {
        std::cout << i << " = " << c[i] << std::endl;
    }
    for (auto ci : c) {
        std::cout << "const =" << ci << std::endl;
    }
}

template <typename Array>
void print_skip_n(const Array &c, std::size_t step) {
    for (auto iter = c.begin() ; iter < c.end() ; iter += step) {
        std::cout << *iter << std::endl;
    }
}

template <typename Array>
void print_with_index(Array &c) {
    for (std::size_t i = 0 ; i != c.size() ; ++i) {
        std::cout << i << " = " << c[i] << std::endl;
    }
    for (auto ci : c) {
        std::cout << "not const =" << ci << std::endl;
    }
}

int main() {
    array<int, 6> a = {1,2,3,4,5,6};

    print_with_const_index(a);

    std::cout << "front = " << a.front() << std::endl;
    std::cout << "back = " << a.back() << std::endl;

    print_skip_n(a, 2);

    auto iter = a.begin();
    std::cout << "2nd(0-indexed) element = " << iter[2] << std::endl;

    a.fill(11);
    print_with_const_index(a);

    std::cout << std::endl;

    print_with_index(a);

    array<std::string, 7> s = {"a", "bc", "def", "ghij", "klmno", "pqrstu", "vwxyz"};
    print_with_const_index(s);


    for (auto si : s) {
        std::cout << si << std::endl;
    }
}
