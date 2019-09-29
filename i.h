//
// Created by mgt on 9/28/19.
//

#ifndef INTEGER_I_H
#define INTEGER_I_H

#include "basic_uint.h"

namespace mgt {
  template<size_t l = 1024>
  class i : public basic_uint<l> {
  public:
    i() {
      this->data = 0;
    }

    i(const i<l> &s) { this->data = s.data; }

    i(const basic_uint<l> &num) : basic_uint<l>(num) {}

    explicit i(long long s) {
      if (s >= 0)
        this->data = std::bitset<l>(s);
      else {
        this->data = std::bitset<l>(-s);
        (*this) = (~*this) + basic_uint<l>(1);
      }
    }

    explicit i(const std::string str) {
      this->from_string(str);
    }

    explicit i(std::bitset<l> s) {
      this->data = s;
    }

    void from_string(const std::string &str) {
      if (str[0] != '-')
        this->data = this->basic_from_string(str);
      else {
        std::string tmp;
        for (size_t i = 1; i < str.length(); ++i)
          tmp.push_back(str[i]);
        this->data = this->basic_from_string(str);
        (*this) = ~(*this);
        (*this) = (*this) + i < l > (1);
      }
    }

    [[nodiscard]] virtual std::string to_string() const {
      if (this->data[l - 1])
        return "-" + this->basic_to_string((~(*this)) + basic_uint<l>(1));
      else
        return this->basic_to_string(*this);
    }
		
		i<l> &operator=(const long long s) {
      *this = i<l>(s);
      return *this;
    }

    i<l> &operator=(const std::string str) {
      *this = i<l>(str);
      return *this;
    }

    friend i<l> operator+(const i<l> &a, const i<l> &b) {
      return i<l>((basic_uint<l>) a + (basic_uint<l>) b);
    }

    friend i<l> operator-(const i<l> &a, const i<l> &b) {
      return i<l>((basic_uint<l>) a - (basic_uint<l>) b);
    }

    friend i<l> operator*(const i<l> &a, const i<l> &b) {
      return i<l>((basic_uint<l>) a * (basic_uint<l>) b);
    }

    friend i<l> operator/(const i<l> &a, const i<l> &b) {
      return i<l>((basic_uint<l>) a / (basic_uint<l>) b);
    }

    friend std::ostream &operator<<(std::ostream &out, const i<l> &d) {
      return out << d.to_string();
    }

    friend bool operator<(const i<l> &a, const i<l> &b) {
      return is_neg(a - b);
    }

    friend bool operator<=(const i<l> &a, const i<l> &b) {
      return a < b || a == b;
    }

    friend bool operator>(const i<l> &a, const i<l> &b) {
      return !(a <= b);
    }

    friend bool operator>=(const i<l> &a, const i<l> &b) {
      return !(a < b);
    }

    friend bool operator!=(const i<l> &a, const i<l> &b) {
      return !(a == b);
    }

    friend std::istream &operator>>(std::istream &in, i<l> &d) {
      std::string res;
      in >> res;
      d.from_string(res);
      return in;
    }

    friend bool is_neg(const i<l> &num) {
      return num.data[l - 1];
    }
  };


}
#endif //INTEGER_I_H
