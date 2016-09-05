//
// Created by Gurebu on 19.07.2016.
//

#ifndef PRIMER_ENUMERATION_H
#define PRIMER_ENUMERATION_H

template <typename Container, typename Value = unsigned>
class enumeration {
public:
    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    explicit enumeration(Container &cont): _cont(cont) {}

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;
private:
    Container &_cont;
};

#endif //PRIMER_ENUMERATION_H
