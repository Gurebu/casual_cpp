//
// Created by Gurebu on 19.07.2016.
//

#ifndef CASUAL_CPP_RANGE_H
#define CASUAL_CPP_RANGE_H

// TODO iterator_traits

namespace grb {

    template<typename _Value, typename _Diff = int>
    class numerical_range {
    public:
        using value_type = _Value;
        using diff_type = _Diff;

        class const_iterator {
        private:
            using self = const_iterator;
            using pointer = const_iterator *;
            using reference = const_iterator &;

            bool _negative() const { return _nr._negative(); }

        public:
            explicit const_iterator(const numerical_range<_Value, _Diff> &nr, _Value val) : _nr(nr), _val(val) {}
//        const_iterator(reference other): _ir(other._ir), _val(other._val) {}

            _Value operator*() const { return _val; }

            bool operator==(self other) const { return _val == other._val; }

            bool operator!=(self other) const { return !(*this == other); }

            reference operator++() {
                _val += _nr._step;
                return *this;
            }

            self operator++(int) {
                self _tmp = *this;
                ++(*this);
                return _tmp;
            }

            reference operator--() {
                _val -= _nr._step;
                return *this;
            }

            self operator--(int) {
                self _tmp = *this;
                --(*this);
                return _tmp;
            }

            reference operator+=(_Diff diff) {
                _val += _nr._step * diff;
                return *this;
            }

            reference operator-=(_Diff diff) {
                _val -= _nr._step * diff;
                return *this;
            }

            self operator+(_Diff diff) const { return self(_nr, _val + _nr._step * diff); }

            self operator-(_Diff diff) const { return self(_nr, _val - _nr._step * diff); }

            bool operator<(reference other) const { return _negative() xor (_val < other._val); }

            bool operator<=(reference &other) const { return _negative() xor (_val <= other._val); }

            bool operator>=(reference &other) const { return !(*this < other); }

            bool operator>(reference &other) const { return !(*this >= other); }

        private:
            const numerical_range<_Value, _Diff> &_nr;
            _Value _val;
        };

//    class const_reverse_iterator {
//    private:
//        using self = const_reverse_iterator;
//        using pointer = const_reverse_iterator*;
//        using reference = const_reverse_iterator&;
//
//        bool _negative() const { return _ir._negative(); }
//    public:
//        explicit const_reverse_iterator(const irange<_Value, _Diff> &ir, _Value val): _ir(ir), _val(val) {}
////        const_reverse_iterator(reference other): _ir(other._ir), _val(other._val) {}
//
//        _Value operator*() const { return _val; }
//
//        bool operator==(reference other) const { return _val == other._val; }
//        bool operator!=(reference other) const { return !(*this == other); }
//
//        reference operator++() { _val -= _ir._step; return *this; }
//        reference operator--() { _val += _ir._step; return *this; }
//        reference operator+=(_Diff diff) { _val -= _ir._step * diff; return *this; }
//        reference operator-=(_Diff diff) { _val += _ir._step * diff; return *this; }
//        self operator+(_Diff diff) const { return self(_ir, _val - _ir._step * diff); }
//        self operator-(_Diff diff) const { return self(_ir, _val + _ir._step * diff); }
//
//        bool operator<(reference other) const { return _negative() xor (_val >= other._val); }
//        bool operator<=(reference &other) const { return _negative() xor (_val > other._val); }
//        bool operator>=(reference &other) const { return !(*this < other); }
//        bool operator>(reference &other) const { return !(*this >= other); }
//    private:
//        const irange<_Value, _Diff> &_ir;
//        _Value _val;
//    };

        explicit numerical_range(_Value end) : numerical_range(0, end) {}

        explicit numerical_range(_Value start, _Value end) : numerical_range(start, 1, end) {}

        explicit numerical_range(_Value start, _Value step, _Value end) : _start(start), _end(end), _step(step) {}

        const_iterator begin() const { return const_iterator(*this, _start); }

        const_iterator end() const { return const_iterator(*this, _end_val()); }

        const_iterator cbegin() const { return begin(); }

        const_iterator cend() const { return end(); }
//    const_reverse_iterator rbegin() const { return const_reverse_iterator(*this, *(end() - 1)); }
//    const_reverse_iterator rend() const { return const_reverse_iterator(*this, *(begin() - 1)); }
    private:
        bool _negative() const { return _start > _end; }

        _Value _end_val() const {
            if (!_negative()) {
                return _end - ((_end - _start) % _step);
            } else {
                return _end + ((_start - _end) % _step);
            }
        }

        _Value _start, _end, _step;
    };

    using irange = numerical_range<int>;
    using lrange = numerical_range<long long, long long>;
//    using frange = numerical_range<double, double>;

}

#endif //CASUAL_CPP_RANGE_H
