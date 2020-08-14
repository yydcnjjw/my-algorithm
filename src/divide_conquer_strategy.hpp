#pragma once

#include <array>
#include <cassert>
#include <iterator>
#include <limits>
#include <vector>

#include <container.hpp>

namespace my {
template <typename iterator>
inline std::pair<iterator, container::value_type>
__find_max_sum_index(iterator begin, iterator end) {
    auto max = std::numeric_limits<container::value_type>::min();
    auto max_i = begin;
    container::value_type sum{0};
    for (auto it = begin; it != end; ++it) {
        sum += *it;
        if (sum > max) {
            max = sum;
            max_i = it;
        }
    }
    return {max_i, max};
}
struct max_subarray {
    container::iterator begin;
    container::iterator end;
    container::value_type sum;

    bool max(max_subarray &sub) { return this->sum > sub.sum; }
};
// find max sub array
inline max_subarray _find_max_crossing_subarray(container::iterator low,
                                                container::iterator mid,
                                                container::iterator high) {
    auto l = __find_max_sum_index(std::make_reverse_iterator(mid),
                                  std::make_reverse_iterator(low));
    auto r = __find_max_sum_index(mid, high);
    return {l.first.base() - 1, r.first + 1, l.second + r.second};
}

inline max_subarray find_max_subarray(container::iterator low,
                                      container::iterator high) {
    if (std::distance(low, high) == 1) {
        return {low, high, *low};
    } else {
        auto mid = std::next(low, std::distance(low, high) / 2);
        auto l_sub = find_max_subarray(low, mid);
        auto r_sub = find_max_subarray(mid, high);
        auto crossing_sub = _find_max_crossing_subarray(low, mid, high);

        if (l_sub.max(r_sub) && l_sub.max(crossing_sub)) {
            return l_sub;
        } else if (r_sub.max(l_sub) && r_sub.max(crossing_sub)) {
            return r_sub;
        } else {
            return crossing_sub;
        }
    }
}

template <typename T> struct matrix {
  public:
    matrix(size_t rows, size_t cols)
        : rows(rows), cols(cols), _data(rows * cols) {}
    matrix(size_t rows, size_t cols, const T &v)
        : rows(rows), cols(cols), _data(rows * cols, v) {}

    T get_elem(size_t row, size_t col) const {
        return this->_data[row * cols + col];
    }

    void set_elem(size_t row, size_t col, const T &v) {
        this->_data[row * cols + col] = v;
    }

    template <typename Callback, typename = std::enable_if_t<std::is_invocable<
                                     Callback, size_t, size_t>::value>>
    void for_each(Callback &&callback) const {
        for (auto i = 0; i < this->rows; ++i) {
            for (auto j = 0; j < this->cols; ++j) {
                callback(i, j);
            }
        }
    }

    matrix<T> get_sub_matrix(size_t row, size_t col, size_t sub_rows,
                             size_t sub_cols) const {

        matrix<T> sub_m{sub_rows, sub_cols};
        sub_m.for_each([&](auto i, auto j) {
            sub_m.set_elem(i, j, this->get_elem(row + i, col + j));
        });
        return sub_m;
    }

    void set_sub_matrix(const matrix<T> &m, size_t row, size_t col) {
        m.for_each([&](auto i, auto j) {
            this->set_elem(row + i, col + j, m.get_elem(i, j));
        });
    }

    size_t rows;
    size_t cols;

  private:
    std::vector<T> _data;
};

template <typename T>
matrix<T> operator+(const matrix<T> &lhs, const matrix<T> &rhs) {
    assert(lhs.rows == rhs.rows && lhs.cols == rhs.cols);
    auto rows{lhs.rows}, cols{lhs.cols};
    matrix<T> m{rows, cols};
    m.for_each([&](auto i, auto j) {
        m.set_elem(i, j, lhs.get_elem(i, j) + rhs.get_elem(i, j));
    });
    return m;
}

template <typename T>
matrix<T> operator-(const matrix<T> &lhs, const matrix<T> &rhs) {
    assert(lhs.rows == rhs.rows && lhs.cols == rhs.cols);
    auto rows{lhs.rows}, cols{lhs.cols};
    matrix<T> m{rows, cols};
    m.for_each([&](auto i, auto j) {
        m.set_elem(i, j, lhs.get_elem(i, j) - rhs.get_elem(i, j));
    });
    return m;
}

template <typename T>
matrix<T> matrix_mul_slow(matrix<T> &lhs, const matrix<T> &rhs) {
    auto rows = lhs.rows;
    auto cols = lhs.cols;
    matrix<T> m{rows, cols};
    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < cols; ++j) {
            for (auto k = 0; k < cols; ++k) {
                m.set_elem(i, j,
                           m.get_elem(i, j) +
                               lhs.get_elem(i, k) * rhs.get_elem(k, j));
            }
        }
    }
    return m;
}

template <typename T>
matrix<T> operator*(matrix<T> &lhs, const matrix<T> &rhs) {
    assert(lhs.rows == rhs.rows && lhs.cols == rhs.cols);
    auto rows = lhs.rows;
    auto cols = lhs.cols;
    if (rows == 1 && cols == 1) {
        return matrix<T>{rows, cols, lhs.get_elem(0, 0) * rhs.get_elem(0, 0)};
    } else if (rows % 2 == 1 || cols % 2 == 1) {
        return matrix_mul_slow(lhs, rhs);
    } else if (rows % 2 == 0 && cols % 2 == 0 && rows == cols) {
        auto sub_n = rows / 2;
        matrix<T> a11{lhs.get_sub_matrix(0, 0, sub_n, sub_n)},
            a12{lhs.get_sub_matrix(0, sub_n, sub_n, sub_n)},
            a21{lhs.get_sub_matrix(sub_n, 0, sub_n, sub_n)},
            a22{lhs.get_sub_matrix(sub_n, sub_n, sub_n, sub_n)},
            b11{rhs.get_sub_matrix(0, 0, sub_n, sub_n)},
            b12{rhs.get_sub_matrix(0, sub_n, sub_n, sub_n)},
            b21{rhs.get_sub_matrix(sub_n, 0, sub_n, sub_n)},
            b22{rhs.get_sub_matrix(sub_n, sub_n, sub_n, sub_n)};

        matrix<T> s1{b12 - b22}, s2{a11 + a12}, s3{a21 + a22}, s4{b21 - b11},
            s5{a11 + a22}, s6{b11 + b22}, s7{a12 - a22}, s8{b21 + b22},
            s9{a11 - a21}, s10{b11 + b12};

        matrix<T> p1{a11 * s1}, p2{s2 * b22}, p3{s3 * b11}, p4{a22 * s4},
            p5{s5 * s6}, p6{s7 * s8}, p7{s9 * s10};

        matrix<T> c11{p5 + p4 - p2 + p6}, c12{p1 + p2}, c21{p3 + p4},
            c22{p5 + p1 - p3 - p7};
        matrix<T> m{rows, cols};
        m.set_sub_matrix(c11, 0, 0);
        m.set_sub_matrix(c12, 0, sub_n);
        m.set_sub_matrix(c21, sub_n, 0);
        m.set_sub_matrix(c22, sub_n, sub_n);
        return m;
    } else {
        throw;
    }
}

#include <iostream>

template <typename T> inline void print_matrix(const matrix<T> &m) {
    for (auto i = 0; i < m.rows; ++i) {
        for (auto j = 0; j < m.cols; ++j) {
            std::cout << m.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

} // namespace my
