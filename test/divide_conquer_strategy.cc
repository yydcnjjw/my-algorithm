#include <iostream>

#include <boost/format.hpp>
#include <gtest/gtest.h>

#include <divide_conquer_strategy.hpp>

TEST(divide_conquer_strategy, find_max_subarray) {
    {
        std::vector<int> v{-1, 1, 2, 3, 4, -5};
        auto max_subarray = my::find_max_subarray(v.begin(), v.end());
        EXPECT_EQ(v[1], *max_subarray.begin);
        EXPECT_EQ(v[5], *max_subarray.end);
        EXPECT_EQ(10, max_subarray.sum);
    }
    {
        std::vector<int> v{13, -3, -25, 20, -3,  -16, -23, 18,
                           20, -7, 12,  -5, -22, 15,  -4,  7};
        auto max_subarray = my::find_max_subarray(v.begin(), v.end());
        EXPECT_EQ(v[7], *max_subarray.begin);
        EXPECT_EQ(v[11], *max_subarray.end);
        EXPECT_EQ(43, max_subarray.sum);
    }
}

TEST(divide_conquer_strategy, square_matrix_mul) {
    my::matrix<int> m1{4, 4, 2};
    int v{1};
    m1.for_each([&](auto i, auto j) { m1.set_elem(i, j, v++); });

    my::print_matrix(m1);

    {
        auto m = my::matrix_mul_slow(m1, m1);
        my::print_matrix(m);
    }

    my::print_matrix(m1);    
    {
        auto m = m1 * m1;
        my::print_matrix(m);
    }
}
