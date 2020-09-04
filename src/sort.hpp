#pragma once

#include <container.hpp>
#include <limits>

namespace my {
namespace insert_sort {
inline void sort(container::iterator begin, container::iterator end) {
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
} // namespace insert_sort

namespace merge_sort {
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

inline void sort(container::iterator begin, container::iterator end) {
    if (std::distance(begin, end) > 1) {
        auto mid = std::next(begin, std::distance(begin, end) / 2);
        sort(begin, mid);
        sort(mid, end);
        __merge(begin, mid, end);
    }
}

} // namespace merge_sort

namespace heap_sort {
inline int left(int i) { return (i << 1) + 1; }

inline int right(int i) { return (i << 1) + 2; }

inline int parent(int i) { return ((i + 1) >> 1) - 1; }

inline void max_heapify(container::iterator begin, container::iterator end,
                        container::difference_type i) {
    auto size = std::distance(begin, end);
    auto l = left(i);
    auto r = right(i);

    int largest;
    if (l<size &&*(begin + l)> * (begin + i)) {
        largest = l;
    } else {
        largest = i;
    }

    if (r<size &&*(begin + r)> * (begin + largest)) {
        largest = r;
    }
    if (largest != i) {
        std::swap(*(begin + i), *(begin + largest));
        max_heapify(begin, end, largest);
    }
}

inline void build_max_heap(container::iterator begin, container::iterator end) {
    auto size = std::distance(begin, end);
    for (auto i = size / 2 - 1; i >= 0; --i) {
        max_heapify(begin, end, i);
    }
}

inline void sort(container::iterator begin, container::iterator end) {
    build_max_heap(begin, end);
    for (auto i = std::prev(end); i != begin; --i) {
        std::swap(*begin, *i);
        max_heapify(begin, i, 0);
    }
}

} // namespace heap_sort

namespace quick_sort {
inline container::iterator partition(container::iterator begin,
                                     container::iterator end) {
    auto pivot = end - 1;
    auto i = begin - 1;
    for (auto it = begin; it != pivot; ++it) {
        if (*it <= *pivot) {
            ++i;
            std::swap(*i, *it);
        }
    }
    std::swap(*(i + 1), *pivot);
    return i + 1;
}

inline void sort(container::iterator begin, container::iterator end) {
    if (std::distance(begin, end) > 1) {
        auto q = partition(begin, end);
        sort(begin, q);
        sort(q, end);
    }
}
} // namespace quick_sort

} // namespace my
