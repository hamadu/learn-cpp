#include "all.h"

auto output_all = [](auto first, auto last, auto output_iter) {
  for (auto iter = first ; iter != last ; ++iter, ++output_iter) {
    *output_iter = *iter;
  }
};

void itr(std::vector<int> *s) {
  for (auto iter = std::begin(*s), last = std::end(*s) ; iter != last ; ++iter) {
    *iter += 3;
    std::cout << "x:" << *iter << std::endl;
  }
}

int main() {
  std::vector<int> s = {1,2,3,4,5,6};
  std::vector<int> cp(6);


  output_all(s.begin(), s.end(), std::ostream_iterator<int>(std::cout));
  output_all(s.begin(), s.end(), cp.begin());

  s.push_back(12);

  output_all(cp.begin(), cp.end(), std::ostream_iterator<int>(std::cout));

  itr(&s);

  auto x = s.at(2);
  std::cout << x << std::endl;

  std::vector<std::vector<int>> w = {{1},{2,3},{4,5,6},{7,8,9,10}};
  for (auto iter = std::begin(w), last = std::end(w) ; iter != last ; ++iter) {
    for (auto i = std::begin(*iter), l = std::end(*iter) ; i != l ; ++i) {
      std::cout << *i << " ";
    }
    std::cout << std::endl;
  }

}
