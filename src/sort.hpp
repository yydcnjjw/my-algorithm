#pragma once

#include <limits>
#include <vector>

namespace my {
inline void insert_sort(std::vector<int> &v) {
    for (int j = 1; j < v.size(); ++j) {
        auto key = v[j];
        int i = j - 1;
        while (i >= 0 && v[i] > key) {
            v[i + 1] = v[i];
            i = i - 1;
        }
        v[i + 1] = key;
    }
}

inline void __merge(std::vector<int> &v, int p, int q, int r) {
    std::vector<int> lv{v.begin() + p, v.begin() + q};
    std::vector<int> rv{v.begin() + q, v.begin() + r};

    std::vector<int>::const_iterator lv_i{lv.begin()}, rv_i{rv.begin()};
    int k{p};
    for (; k < r; ++k) {
        if (lv_i != lv.end() && rv_i != rv.end()) {
            if (*lv_i <= *rv_i) {
                v[k] = *lv_i++;
            } else {
                v[k] = *rv_i++;
            }
            continue;
        }

        if (lv_i == lv.end()) {
            v[k] = *rv_i++;
        } else if (rv_i == rv.end()) {
            v[k] = *lv_i++;
        }
    }
}

inline void _merge_sort(std::vector<int> &v, int p, int r) {
    if (r - p > 1) {
        auto q = p + (r - p) / 2;
        _merge_sort(v, p, q);
        _merge_sort(v, q, r);
        __merge(v, p, q, r);
    }
}

inline void merge_sort(std::vector<int> &v) { _merge_sort(v, 0, v.size()); }

} // namespace my
