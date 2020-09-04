#include <algorithm>
#include <iostream>

#include <boost/format.hpp>
#include <gtest/gtest.h>

#include <sort.hpp>

static void print(my::container &v) {
    for (auto &i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

class sort_test : public ::testing::Test {
  public:
    void test(std::function<void(my::container::iterator,
                                 my::container::iterator)> &&func) {
        for (auto &v : datas) {
            print(v);
            func(v.begin(), v.end());
            print(v);
            EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
        }
    }

  protected:
    void SetUp() override {
        datas = {{3, 2, 1, 5, 4}, {0, 0, 0}, {0, 1, 2}, {2, 0, 0}, {1, 2, 1}};
    }
    std::vector<std::vector<int>> datas;
};

TEST_F(sort_test, insert_sort) { test(my::insert_sort::sort); }
TEST_F(sort_test, merge_sort) { test(my::merge_sort::sort); }
TEST_F(sort_test, heap_sort) { test(my::heap_sort::sort); }
TEST_F(sort_test, quick_sort) { test(my::quick_sort::sort); }
