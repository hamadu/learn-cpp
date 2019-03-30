#include "all.h"

template <typename T>
class unique_ptr {
    T * ptr = nullptr;
public:
    unique_ptr(){}

    explicit unique_ptr(T * ptr) : ptr(ptr) {}

    ~unique_ptr() { delete ptr; }

    // forbid copy
    unique_ptr(const unique_ptr &) = delete;
    unique_ptr & operator = (const unique_ptr &) = delete;


    // move constructor
    unique_ptr(unique_ptr && r) : ptr(r.ptr) {
        r.ptr = nullptr;
    }

    // move assignment
    unique_ptr & operator = (unique_ptr && r) {
        delete ptr;
        ptr = r.ptr;
        r.ptr = nullptr;
    }

    T & operator * () noexcept {
        return *ptr;
    }

    T * operator -> () noexcept {
        return ptr;
    }

    T * get() noexcept {
        return ptr;
    }
};

template <typename T>
struct shared_ptr {
    T * ptr = nullptr;
    std::size_t * count = nullptr;


    void release() {
        if (count == nullptr) {
            return;
        }

        --*count;
        if (*count == 0) {
            delete ptr;
            ptr = nullptr;
            delete count;
            count = nullptr;
        }
    }
public:
    shared_ptr() {}

    explicit shared_ptr(T * ptr) : ptr(ptr), count(new std::size_t(1)) {
    }

    ~shared_ptr() {
        release();
    }

    shared_ptr(const shared_ptr & r) : ptr(r.ptr), count(r.count) {
        ++*count;
    }

    shared_ptr & operator = (const shared_ptr & r) {
        if (this == &r) {
            return *this;
        }

        release();
        ptr = r.ptr;
        count = r.count;
        ++*count;
    }

    shared_ptr(shared_ptr && r) : ptr(r.ptr), count(r.count) {
        r.ptr = nullptr;
        r.count = nullptr;
    }

    shared_ptr & operator = (shared_ptr && r) {
        release();
        ptr = r.ptr;
        count = r.count;
        r.ptr = nullptr;
        r.count = nullptr;
    }

    T & operator * () noexcept {
        return *ptr;
    }

    T * operator -> () noexcept {
        return ptr;
    }

    T * get() noexcept {
        return ptr;
    }
};

int main() {
    shared_ptr<int> a;

}
