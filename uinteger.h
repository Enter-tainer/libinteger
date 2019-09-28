//
// Created by mgt on 9/27/19.
//

#ifndef INTEGER_UINTEGER_H
#define INTEGER_UINTEGER_H

#include <bitset>
#include <utility>
#include <string>

#include <iostream>

namespace mgt {
  template<size_t l>
  class u {
  private:
    std::bitset<l> data;

    std::pair<u<l>, u<l>> basic_div(const u<l> &s) { // return <res, mod>
      if (*this < s)
        return std::make_pair(u<l>(0), u<l>(s));
      if (s == u<l>(0))
        throw std::runtime_error("divide by zero");
      int high_pos_self, high_pos_s;
      for (high_pos_self = l; high_pos_self >= 0 && data[high_pos_self] == 0; --high_pos_self);
      for (high_pos_s = l; high_pos_s >= 0 && s.data[high_pos_s] == 0; --high_pos_s);
      if (high_pos_s == -1)
        high_pos_s = 0;
      if (high_pos_self == -1)
        high_pos_self = 0;
      int pos = high_pos_self - high_pos_s;
      u<l> res, mod, tmp = s << pos;
      for (; pos >= 0; --pos) {

      }

    }

  public:
    u() {
      data = 0;
    }

    explicit u(unsigned long long s) {
      data = std::bitset<l>(s);
    }

    explicit u(std::bitset<l> s) {
      data = s;
    }

    std::string to_bitset_string() {
      return data.to_string();
    }

    friend bool operator==(const u<l> &a, const u<l> &b) {
      return a.data == b.data;
    }

    friend bool operator<(const u<l> &a, const u<l> &b) {
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

    friend bool operator<=(const u<l> &a, const u<l> &b) {
      return a < b || a == b;
    }

    friend bool operator>(const u<l> &a, const u<l> &b) {
      return !(a <= b);
    }

    friend bool operator>=(const u<l> &a, const u<l> &b) {
      return !(a < b);
    }

    friend bool operator!=(const u<l> &a, const u<l> &b) {
      return !(a == b);
    }

    friend u<l> operator&(const u<l> &a, const u<l> &b) {
      return u<l>(a.data & b.data);
    }

    u<l> operator&=(const u<l> &a) {
      data &= a.data;
      return *this;
    }

    friend u<l> operator|(const u<l> &a, const u<l> &b) {
      return u<l>(a.data | b.data);
    }

    u<l> operator|=(const u<l> &a) {
      data |= a.data;
      return *this;
    }

    friend u<l> operator^(const u<l> &a, const u<l> &b) {
      return u<l>(a.data ^ b.data);
    }

    u<l> operator^=(const u<l> &a) {
      data ^= a.data;
      return *this;
    }

    friend u<l> operator<<(const u<l> &a, size_t v) {
      return u<l>(a.data << v);
    }

    friend u<l> operator>>(const u<l> &a, size_t v) {
      return u<l>(a.data >> v);
    }

    u<l> operator<<=(size_t v) {
      data <<= v;
      return (*this);
    }

    u<l> operator>>=(size_t v) {
      data >>= v;
      return (*this);
    }

    friend u<l> operator>>=(const u<l> &a, size_t v) {
      return u<l>(a.data >> v);
    }

    friend u<l> operator~(const u<l> &a) {
      return u<l>(~a.data);
    }

    friend u<l> operator+(const u<l> &a, const u<l> &b) {
      u<l> res, inc, tmp;
      res = a ^ b;
      inc = ((a & b) << 1);
      while (inc.data.any()) {
        tmp = res;
        res ^= inc;
        inc = (inc & tmp) << 1;
      }
      return res;
    }

    u<l> operator+=(const u<l> &a) {
      this->data = ((*this) + a).data;
      return (*this);
    }

    friend u<l> operator-(const u<l> &a, const u<l> &b) {
      return (a + (~b + u<l>(1)));
    }

    u<l> operator-=(const u<l> &a) {
      this->data = ((*this) - a).data;
      return (*this);
    }

    friend u<l> operator*(const u<l> &a, const u<l> &b) {
      u<l> res, tmp = b;
      for (size_t i = 0; i < l; ++i, tmp <<= 1) {
        if (a.data[i])
          res += tmp;
      }
      return res;
    }

    u<l> operator*=(const u<l> &a) {
      this->data = this->data * a;
      return (*this);
    }
  };

}


#endif //INTEGER_UINTEGER_H
