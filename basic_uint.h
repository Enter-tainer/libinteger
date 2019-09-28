//
// Created by mgt on 9/27/19.
//

#ifndef INTEGER_BASIC_UINT_H
#define INTEGER_BASIC_UINT_H

#include <bitset>
#include <utility>
#include <string>
#include <algorithm>

#include <iostream>
namespace mgt {
  template<size_t l = 1024>
  class basic_uint {
  private:
    std::bitset<l> data;

    std::pair<basic_uint<l>, basic_uint<l>> basic_div(const basic_uint<l> &s) const { // return <res, mod>
      if (*this < s)
        return std::make_pair(basic_uint<l>(0), basic_uint<l>(*this));
      if (s == basic_uint<l>(0))
        throw std::runtime_error("divide by zero");
      basic_uint<l> lb(0), rb = (*this) + basic_uint<l>(1), m;
      while (lb + basic_uint<l>(1) < rb) {
        m = (lb + rb) >> 1;
        if (m * s <= *this)
          lb = m;
        else
          rb = m;
      }

      if (rb * s <= *this)
        return std::make_pair(rb, *this - rb * s);
      else
        return std::make_pair(lb, *this - lb * s);
    }

    std::bitset<l> basic_from_string(std::string str) {
      std::bitset<l> tmp;
      size_t end = str.length() - 1;
      for (size_t i = 0; i <= l - 1; ++i) {
        if ((str[end] - '0') % 2 != 0) {
          str[end] -= 1;
          dev_by_2(str);
          tmp[i] = 1;
        } else {
          dev_by_2(str);
          tmp[i] = 0;
        }
      }
      return tmp;
    }

    void dev_by_2(std::string &str) {
      size_t end = str.length() - 1;
      int current_num = 0;
      int buff = 0;
      for (size_t i = 0; i <= end; ++i) {
        current_num = str[i] - '0';
        current_num += 10 * buff;
        if (current_num % 2 == 1)
          buff = 1;
        else
          buff = 0;
        str[i] = current_num / 2 + '0';
      }
    }
  public:
    basic_uint() {
      data = 0;
    }

    basic_uint(const basic_uint<l> &s) { data = s.data; }

    explicit basic_uint(unsigned long long s) {
      data = std::bitset<l>(s);
    }

    explicit basic_uint(std::bitset<l> s) {
      data = s;
    }

    std::string to_binary_string() {
      return data.to_string();
    }

    unsigned long long to_ull() {
      return data.to_ullong();
    }

    [[nodiscard]] virtual std::string to_string() const {
      std::string res;
      std::bitset<8> tmp;
      basic_uint<l> cpy = *this;
      while (cpy.data.any()) {
        auto s = cpy.basic_div(basic_uint<l>(10));
        for (size_t i = 0; i < 8; ++i)
          tmp[i] = s.second.data[i];
        res += static_cast<char>('0' + tmp.to_ulong());
        cpy.data = s.first.data;
      }
      std::reverse(res.begin(), res.end());
      return res;
    }

    virtual void from_string(const std::string &str) {
      this->data = basic_from_string(str);
    }

    friend std::ostream &operator<<(std::ostream &out, const basic_uint<l> &d) {
      return out << d.to_string();
    }

    friend std::istream &operator>>(std::istream &in, basic_uint<l> &d) {
      std::string res;
      in >> res;
      d.from_string(res);
      return in;
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
      this->data = ((*this) * a).data;
      return (*this);
    }

    friend basic_uint<l> operator/(const basic_uint<l> &a, const basic_uint<l> &b) {
      return a.basic_div(b).first;
    }

    basic_uint<l> operator/=(const basic_uint<l> &a) {
      this->data = ((*this) / a).data;
    }

    friend basic_uint<l> operator%(const basic_uint<l> &a, const basic_uint<l> &b) {
      return a.basic_div(b).second;
    }

    basic_uint<l> operator%=(const basic_uint<l> &a) {
      this->data = ((*this) % a).data;
    }
  };
}


#endif //INTEGER_BASIC_UINT_H
