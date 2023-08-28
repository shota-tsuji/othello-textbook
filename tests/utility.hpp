#include "include/board.hpp"

class TestBoard {
public:
    static std::vector<int> beginning() {
        std::vector<int> v(hw2, Vacant);
        v[D4] = White;
        v[E4] = Black;
        v[D5] = Black;
        v[E5] = White;

        return v;
    }
    static std::vector<int> d3() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
        v[E4] = Black;
        v[D5] = Black;
        v[E5] = White;

        return v;
    }
    static std::vector<int> d3c5() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
        v[E4] = Black;
        v[C5] = White;
        v[D5] = White;
        v[E5] = White;

        return v;
    }

    static std::vector<int> d3c5e6() {
        std::vector<int> v(hw2, Vacant);
        v[D3] = Black;
        v[D4] = Black;
        v[E4] = Black;
        v[C5] = White;
        v[D5] = White;
        v[E5] = Black;
        v[E6] = Black;

        return v;
    }

    static std::vector<int> all_black() {
        std::vector<int> v(hw2, Black);
        return v;
    }
};

