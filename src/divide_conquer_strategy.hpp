#include <cassert>
#include <iterator>
#include <limits>
#include <vector>

namespace my {
using container = std::vector<int>;

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
} // namespace my
