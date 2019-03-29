#include "all.h"


template <typename T>
void dynamic_allocate() {
    void * ptr = ::operator new(sizeof(T));
    T * t_ptr = static_cast<T *>(ptr);
    *t_ptr = T{};
    ::operator delete(ptr);
}

struct Simple {
    int i;
    double d;
};

struct Logger {
    std::string name;

    Logger() : name("default") {}

    Logger(std::string name) : name(name) {
        std::cout << name << " is constructed" << std::endl;
    }

    ~Logger() {
        std::cout << name << " is destructed" << std::endl;
    }
};

int main() {
    {
        void *ptr = ::operator new(sizeof(int));
        int *int_ptr = static_cast<int *>(ptr);

        *int_ptr = 123;
        std::cout << int_ptr << std::endl;
        std::cout << *int_ptr << std::endl;

        ::operator delete(ptr);
    }

    {
        dynamic_allocate<Simple>(); // ok
        // dynamic_allocate<Logger>(); // segmentation fault
        // dynamic_allocate<std::vector<int>>(); // error for object 0xc000000000000000: pointer being freed was not allocated
    }

    {
        Logger a("hoge");
        {
            Logger b("fuga");
        }

        void * ptr = ::operator new(sizeof(Logger));
        Logger *logger_ptr = new(ptr) Logger { "piyo" };

        logger_ptr->~Logger();
        ::operator delete(ptr);
    }
}
