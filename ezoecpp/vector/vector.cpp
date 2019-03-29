#include "all.h"

template <typename T, typename Allocator = std::allocator<T>>
class vector {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const pointer;
    using reference = value_type &;
    using const_reference = const value_type &;
    using allocator_type = Allocator;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using traits = std::allocator_traits<allocator_type>;
private:
    pointer first = nullptr;
    pointer last = nullptr;
    pointer reserved_last = nullptr;
    allocator_type alloc;

    pointer allocate(size_type n) {
        return traits::allocate(alloc, n);
    }

    void deallocate() {
        traits::deallocate(alloc, first, capacity());
    }

    void construct(pointer ptr) {
        traits::construct(alloc, ptr);
    }

    void construct(pointer ptr, const_reference value) {
        traits::construct(alloc, ptr, value);
    }

    void construct(pointer ptr, value_type && value) {
        traits::construct(alloc, ptr, std::move(value));
    }

    void destroy(pointer ptr) {
        traits::destroy(alloc, ptr);
    }

    void destroy_until(reverse_iterator rend) {
        for (auto iter = rbegin() ; iter != rend ; ++iter, --last) {
            destroy(&*iter);
        }
    }

    void clear() noexcept {
        destroy_until(rend());
    }

public:
    vector(const allocator_type & alloc) : alloc(alloc) {}

    vector() : vector(allocator_type()) {}

    vector(size_type n) : vector(allocator_type()) {
        resize(n);
    }

    vector(size_type n, const allocator_type & alloc) : vector(alloc) {
        resize(n);
    }

    vector(size_type n, const_reference value) : vector(allocator_type()) {
        resize(n, value);
    }

    vector(size_type n, const_reference value, const allocator_type & alloc) : vector(alloc) {
        resize(n, value);
    }

    ~vector() {
        clear();

        deallocate();
    }

    // vector(const vector &x);
    // vector & operator =(const vector &x);

    // void push_back(const T & x);
    // T & operator [](std::size_t i) noexcept;

    void push_back(const_reference value) {
        if (size() + 1 > capacity()) {
            reserve(size() + 1);
        }
        construct(last, value);
        ++last;
    }

    void reserve(size_type sz) {
        if (sz <= capacity()) {
            return;
        }

        auto ptr = allocate(sz);
        auto old_first = first;
        auto old_last = last;
        auto old_capacity = capacity();

        first = ptr;
        last = first;
        reserved_last = first + sz;
        for (auto old_iter = old_first ; old_iter != old_last ; ++old_iter, ++last) {
            construct(last, std::move(*old_iter));
        }

        for (auto riter = reverse_iterator(old_last), rend = reverse_iterator(old_first) ; riter != rend ; ++riter) {
            destroy(&*riter);
        }
    }

    void resize(size_type sz) {
        if (sz < size()) {
            auto diff = size() - sz;
            destroy_until(rbegin() + diff);
            last = first + sz;
        } else if (sz > size()) {
            reserve(sz);
            for (; last != reserved_last ; ++last) {
                construct(last);
            }
        }
    }

    void resize(size_type sz, const_reference value) {
        if (sz < size()) {
            auto diff = size() - sz;
            destroy_until(rbegin() + diff);
            last = first + sz;
        } else if (sz > size()) {
            reserve(sz);
            for (; last != reserved_last ; ++last) {
                construct(last, value);
            }
        }
    }


    iterator begin() noexcept {
        return first;
    }

    iterator end() noexcept {
        return last;
    }

    const_iterator begin() const noexcept {
        return first;
    }

    const_iterator end() const noexcept {
        return last;
    }

    const_iterator cbegin() const noexcept {
        return first;
    }

    const_iterator cend() const noexcept {
        return last;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator { last }; // explicit typecast using constructor
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator { first };
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator { last };
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator { first };
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator { last };
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator { first };
    }

    size_type size() const noexcept {
        return end() - begin();
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    size_type capacity() const noexcept {
        return reserved_last - first;
    }

    reference operator [](size_type i) {
        return first[i];
    }

    const_reference operator [](size_type i) const {
        return first[i];
    }

    reference at(size_type i) {
        if (i >= size()) {
            throw std::out_of_range("index is out of range.");
        }
        return first[i];
    }

    const_reference at(size_type i) const {
        if (i >= size()) {
            throw std::out_of_range("index is out of range.");
        }
        return first[i];
    }

    reference front() {
        return first;
    }

    const_reference front() const {
        return first;
    }

    reference back() {
        return last - 1;
    }

    const_reference back() const {
        return last - 1;
    }

    pointer data() noexcept {
        return first;
    }

    const_pointer data() const noexcept {
        return first;
    }
};

int main() {
    vector<int> v(10, 1);
    v[2]= 99;
    v.resize(5);

    v.push_back(-1);
    v.push_back(9);

    for (auto x : v) {
        std::cout << x << std::endl;
    }

    for (int i = 0 ; i < v.size() ; i++) {
        std::cout << i << "=" << v[i] << std::endl;
    }

    {
        vector<int> v(100000, 1);
        for (int i = 0 ; i < 100000 ; i++) {
            v.push_back(i);
        }
    }
    return 0;
}
