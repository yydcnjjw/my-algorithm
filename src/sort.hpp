#pragma once

#include <container.hpp>
#include <limits>

namespace my {
inline void insert_sort(container::iterator begin, container::iterator end) {
    for (auto it{begin + 1}; it != end; ++it) {
        auto key = *it;
        auto rit = std::make_reverse_iterator(it);
        auto rend = std::make_reverse_iterator(begin);
        while (rit != rend && *rit > key) {
            *std::prev(rit) = *rit;
            ++rit;
        }
        *std::prev(rit) = key;
    }
}

inline void __merge(container::iterator begin, container::iterator mid,
                    container::iterator end) {
    container lv{begin, mid};
    container rv{mid, end};

    container::const_iterator lv_i{lv.begin()}, rv_i{rv.begin()};
    for (auto it{begin}; it != end; ++it) {
        if (lv_i != lv.end() && rv_i != rv.end()) {
            if (*lv_i <= *rv_i) {
                *it = *lv_i++;
            } else {
                *it = *rv_i++;
            }
            continue;
        }

        if (lv_i == lv.end()) {
            *it = *rv_i++;
        } else if (rv_i == rv.end()) {
            *it = *lv_i++;
        }
    }
}

inline void merge_sort(container::iterator begin, container::iterator end) {
    if (std::distance(begin, end) > 1) {
        auto mid = std::next(begin, std::distance(begin, end) / 2);
        merge_sort(begin, mid);
        merge_sort(mid, end);
        __merge(begin, mid, end);
    }
}

} // namespace my
