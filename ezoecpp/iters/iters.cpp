#include "../all.h"

int main() {
  // for_each
  auto for_each = [](auto first, auto last, auto f) {
    for (auto iter = first ; iter != last ; ++iter) {
      f(*iter);
    }
  };

  std::vector<int> v = {1,2,3,4,5};
  auto print_value = [](auto v) {
    std::cout << v << std::endl;
  };
  for_each(v.begin(), v.end(), print_value);

  for_each(v.begin(), v.end(), [](auto v) {
    std::cout << v*2 << std::endl;
  });

  // all_of, any_of
  auto all_of = [](auto first, auto last, auto pred) {
    for (auto iter = first ; iter != last ; ++iter) {
      if (pred(*iter) == false) {
        return false;
      }
    }
    return true;
  };

  auto any_of = [](auto first, auto last, auto pred) {
    for (auto iter = first ; iter != last ; ++iter) {
      if (pred(*iter) == true) {
        return true;
      }
    }
    return false;
  };

  if (all_of(v.begin(), v.end(), [](auto v) { return v % 2 == 0; })) {
    std::cout << "all even" << std::endl;
  } else {
    std::cout << "not all even" << std::endl;
  }
  if (any_of(v.begin(), v.end(), [](auto v) { return v % 2 == 0; } )) {
    std::cout << "some is even" << std::endl;
  } else {
    std::cout << "nothing is even" << std::endl;
  }

  // find-if,find
  {
    auto find_if = [](auto first, auto last, auto pred) {
      for (auto iter = first ; iter != last ; ++iter) {
        if (pred(*iter)) {
          return iter;
        }
      }
      return last;
    };
    auto find = [=](auto first, auto last, auto v) {
      return find_if(first, last, [&](auto elem) { return v == elem; });
    };

    if (find(v.begin(), v.end(), 114) != v.end()) {
      std::cout << "found" << std::endl;
    } else {
      std::cout << "not found" << std::endl;
    }
    std::vector<std::vector<int>> vofv = {{1,2},{2,3,4,5,6},{3,4,5},{4,5,6},{5,6},{6,7,8,9}};
    std::vector<int> vec = {2,3,4,5,6};
    if (find(vofv.begin(), vofv.end(), vec) != vofv.end()) {
      std::cout << "found" << std::endl;
    } else {
      std::cout << "not found" << std::endl;
    }
  }

  // count,count_if
  {
    auto count_if = [](auto first, auto last, auto pred) {
      int count = 0;
      for (auto iter = first ; iter != last ; ++iter) {
        if (pred(*iter)) {
          ++count;
        }
      }
      return count;
    };
    auto count = [=](auto first, auto last, auto v) {
      return count_if(first, last, [&](auto elem) { return elem == v; });
    };
    std::cout << "count 1:" << count(v.begin(), v.end(), 1) << std::endl;
  }

  // equal
  {
    auto equal = [](auto first1, auto last1, auto first2, auto last2, auto pred) {
      auto size1 = std::distance(first1, last1);
      auto size2 = std::distance(first2, last2);
      if (size1 != size2) {
        return false;
      }

      for (auto i = first1, j = first2 ; i != last1 ; ++i, ++j) {
        if (pred(*i, *j) == false) {
          return false;
        }
      }
      return true;
    };

    std::vector<int> a = {1,2,3,4};
    std::vector<int> b = {11,12,13,14};
    if (equal(a.begin(), a.end(), b.begin(), b.end(), [](auto a, auto b) { return a % 10 == b % 10; })) {
      std::cout << "same mod 10" << std::endl;
    } else {
      std::cout << "same mod 10" << std::endl;
    }
  }

  // transform
  {
    auto transform = [](auto first, auto last, auto result, auto op) {
      for (auto iter = first ; iter != last ; ++iter, ++result) {
        *result = op(*iter);
      }
    };

    std::vector<int> a = {1,2,3,4,5,6};
    std::vector<int> b(12);

    transform(a.begin(), a.end(), b.begin(), [](auto v) { return v * 2; });

    for (auto i = b.begin() ; i != b.end(); ++i) {
      std::cout << *i << std::endl;
    }
  }

  // replace
  {
    auto replace = [](auto first, auto last, auto pred, auto new_value) {
      for (auto iter = first ; iter != last ; ++iter) {
        if (pred(*iter)) {
          *iter = new_value;
        }
      }
    };

    std::vector<int> a = {1,2,3,4,5,6};
    replace(a.begin(), a.end(), [](auto v) { return v % 2 == 0; }, -1);
    for (auto i = a.begin() ; i != a.end() ; ++i) {
      std::cout << *i << std::endl;
    }
  }

  // for
  for (auto &x : v) {
    x += 1;
    std::cout << x << std::endl;
  }
}
