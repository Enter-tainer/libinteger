//
// Created by mgt on 9/27/19.
//

#ifndef INTEGER_BASIC_UINT_H
#define INTEGER_BASIC_UINT_H

#include <bitset>
#include <utility>
#include <string>

#include <iostream>

namespace mgt {
  template<size_t l>
  class basic_uint {
  private:
    std::bitset<l> data;

    std::pair<basic_uint<l>, basic_uint<l>> basic_div(const basic_uint<l> &s) { // return <res, mod>
      if (*this < s)
        return std::make_pair(basic_uint<l>(0), basic_uint<l>(s));
      if (s == basic_uint<l>(0))
        throw std::runtime_error("divide by zero");

    }

  public:
    basic_uint() {
      data = 0;
    }

    explicit basic_uint(unsigned long long s) {
      data = std::bitset<l>(s);
    }

    explicit basic_uint(std::bitset<l> s) {
      data = s;
    }

    std::string to_binary_string() {
      return data.to_string();
    }

    virtual std::string to_string() {
      // TODO:
    }

    virtual std::ostream &operator<<(std::ostream &out) {
      return out << this->to_string();
    }

    friend bool operator==(const basic_uint<l> &a, const basic_uint<l> &b) {
      return a.data == b.data;
    }

    friend bool operator<(const basic_uint<l> &a, const basic_uint<l> &b) {
      for (int i = l; i >= 0; --i) {
        if (a.data[i] < b.data[i])
          return true;
        else if (a.data[i] == b.data[i])
          continue;
        else
          return false;
      }
      return false;
    }

    friend bool operator<=(const basic_uint<l> &a, const basic_uint<l> &b) {
      return a < b || a == b;
    }

    friend bool operator>(const basic_uint<l> &a, const basic_uint<l> &b) {
      return !(a <= b);
    }

    friend bool operator>=(const basic_uint<l> &a, const basic_uint<l> &b) {
      return !(a < b);
    }

    friend bool operator!=(const basic_uint<l> &a, const basic_uint<l> &b) {
      return !(a == b);
    }

    friend basic_uint<l> operator&(const basic_uint<l> &a, const basic_uint<l> &b) {
      return basic_uint<l>(a.data & b.data);
    }

    basic_uint<l> operator&=(const basic_uint<l> &a) {
      data &= a.data;
      return *this;
    }

    friend basic_uint<l> operator|(const basic_uint<l> &a, const basic_uint<l> &b) {
      return basic_uint<l>(a.data | b.data);
    }

    basic_uint<l> operator|=(const basic_uint<l> &a) {
      data |= a.data;
      return *this;
    }

    friend basic_uint<l> operator^(const basic_uint<l> &a, const basic_uint<l> &b) {
      return basic_uint<l>(a.data ^ b.data);
    }

    basic_uint<l> operator^=(const basic_uint<l> &a) {
      data ^= a.data;
      return *this;
    }

    friend basic_uint<l> operator<<(const basic_uint<l> &a, size_t v) {
      return basic_uint<l>(a.data << v);
    }

    friend basic_uint<l> operator>>(const basic_uint<l> &a, size_t v) {
      return basic_uint<l>(a.data >> v);
    }

    basic_uint<l> operator<<=(size_t v) {
      data <<= v;
      return (*this);
    }

    basic_uint<l> operator>>=(size_t v) {
      data >>= v;
      return (*this);
    }

    friend basic_uint<l> operator>>=(const basic_uint<l> &a, size_t v) {
      return basic_uint<l>(a.data >> v);
    }

    friend basic_uint<l> operator~(const basic_uint<l> &a) {
      return basic_uint<l>(~a.data);
    }

    friend basic_uint<l> operator+(const basic_uint<l> &a, const basic_uint<l> &b) {
      basic_uint<l> res, inc, tmp;
      res = a ^ b;
      inc = ((a & b) << 1);
      while (inc.data.any()) {
        tmp = res;
        res ^= inc;
        inc = (inc & tmp) << 1;
      }
      return res;
    }

    basic_uint<l> operator+=(const basic_uint<l> &a) {
      this->data = ((*this) + a).data;
      return (*this);
    }

    friend basic_uint<l> operator-(const basic_uint<l> &a, const basic_uint<l> &b) {
      return (a + (~b + basic_uint<l>(1)));
    }

    basic_uint<l> operator-=(const basic_uint<l> &a) {
      this->data = ((*this) - a).data;
      return (*this);
    }

    friend basic_uint<l> operator*(const basic_uint<l> &a, const basic_uint<l> &b) {
      basic_uint<l> res, tmp = b;
      for (size_t i = 0; i < l; ++i, tmp <<= 1) {
        if (a.data[i])
          res += tmp;
      }
      return res;
    }

    basic_uint<l> operator*=(const basic_uint<l> &a) {
      this->data = this->data * a;
      return (*this);
    }
  };

  template<typename l>
  basic_uint<l> from_string(std::string) {
    // TODO:
  }
}


#endif //INTEGER_BASIC_UINT_H
