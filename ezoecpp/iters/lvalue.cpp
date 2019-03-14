#include "all.h"

void f(int &x) {
  x = 3;
}

void println(const std::vector<int> &v) {
  for (auto iter = v.begin() ; iter != v.end() ; ++iter) {
    std::cout << *iter << std::endl;
  }
}

auto swap = [](auto &a, auto &b) {
  auto temp = a;
  a = b;
  b = temp;
};

int main() {
  int a = 2;
  f(a);
  std::cout << "a=" << a << std::endl;

  int c = 0;
  int d = 1;
  swap(c, d);
  std::cout << "c=" << c << " d=" << d << std::endl;

  const std::vector<int> yoyo = {1,2,3,4,5};
  println(yoyo);
}
