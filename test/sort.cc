#include <algorithm>
#include <iostream>

#include <boost/format.hpp>
#include <gtest/gtest.h>

#include <sort.hpp>

class sort_test : public ::testing::Test {
  public:
    void test(std::function<void(std::vector<int> &)> &&func) {
        for (auto &v : datas) {
            func(v);
            EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
        }
    }

  protected:
    void SetUp() override {
        datas = {{3, 2, 1, 5, 4}, {0, 0, 0}, {0, 1, 2}, {2, 0, 0}, {1, 2, 1}};
    }
    std::vector<std::vector<int>> datas;
};

TEST_F(sort_test, insert_sort) { test(my::insert_sort); }
TEST_F(sort_test, merge_sort) { test(my::merge_sort); }
