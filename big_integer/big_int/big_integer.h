#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <functional>
#include "vector/vector.h"

struct big_integer
{
    using value_type = uint32_t;
    using tr_value_type = uint64_t;

    big_integer();
    big_integer(const big_integer& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(const big_integer& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    void multiply(const value_type& rhs);
    big_integer& operator/=(big_integer const& rhs);
    void quotient(const value_type& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool abs_greater(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);
    void out() const;

private:
    static constexpr int BITS { std::numeric_limits<value_type>::digits }; // Assuming it's 32
    static constexpr tr_value_type BASE { static_cast<tr_value_type>(1) << BITS };
    enum
    {
        SMALL,
        BIG
    } state;
    union
    {
        value_type number;
        vector<value_type> big_number;
    };
    bool sign { };  // Storing sign as value_type in array is memory overhead, whereas storing
                    // the number in two's complement form adding unwanted complexity to the code

    const value_type& size() const { return big_number.size(); };
    value_type& operator[](size_t n) { return big_number[n]; };
    const value_type& operator[](size_t n) const { return big_number[n]; };
    void detach();
    void swap(big_integer& tmp);
    void assign_vector(vector<value_type>& tmp);
    void quick_copy(const big_integer& other);
    bool get_sign() { return big_number[big_number.size() - 1] >> (BITS - 1); };
    bool convert_to_signed();
    void convert_to_2s(bool sign);
    void simple_conversion();
    void reverse_bytes();
    void ensure_big_object();
    void perform_bitwise_operation(std::function<void(value_type&, value_type&)>, const big_integer&);
    void trim();
    big_integer from_value_type(value_type t) const;
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H
