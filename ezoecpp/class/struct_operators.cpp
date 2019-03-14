#include "all.h"

struct Person {
  std::string name;
  int age;

  void print() {
    std::cout << this->name << "," << this->age << std::endl;
  }
};

struct fractional {
  int num;
  int denom;

  fractional(int num) : num(num), denom(1) {}

  fractional(int num, int denom = 1) : num(num), denom(denom) {}

  void print() {
    std::cout << this->num << "/" << this->denom << std::endl;
  }

  fractional operator *(fractional &r) {
    return fractional { num * r.num, denom * r.denom };
  }

  fractional operator /(fractional &r) {
    return fractional { num * r.denom, denom * r.num };
  }
};

fractional operator +(fractional &l, fractional &r) {
  if (l.denom == r.denom) {
    return fractional { l.num + r.num, l.denom };
  } else {
    return fractional { l.num * r.denom + r.num * l.denom, l.denom * r.denom};
  }
}

fractional operator -(fractional &l, fractional &r) {
  if (l.denom == r.denom) {
    return fractional { l.num - r.num, l.denom };
  } else {
    return fractional { l.num * r.denom - r.num * l.denom, l.denom * r.denom};
  }
}

struct null_array {
  int dummy;

  int & operator [](std::size_t) {
    dummy = 0;
    return dummy;
  }
};

int main() {
  Person me = { "hi", 123};
  me.print();

  Person copy_of_me = me; // copy!
  copy_of_me.age += 5;
  me.print();
  copy_of_me.print();

  // frac
  fractional a(2, 3);
  fractional b(1, 2);

  fractional c = (a + b);
  fractional d = c * c;
  c.print();
  d.print();

  // null-array
  auto nula = null_array();
  std::cout << nula[12] << std::endl;
}

