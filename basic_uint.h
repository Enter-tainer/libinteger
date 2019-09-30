//
// Created by mgt on 9/27/19.
//

#ifndef INTEGER_BASIC_UINT_H
#define INTEGER_BASIC_UINT_H

#include <bitset>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace mgt {
  template<size_t l>
  size_t get_high_1_index(const std::bitset<l> &bits) { // assume that bits != 0
    size_t res;
    for (res = l - 1; res >= 0; --res)
      if (bits[res])
        return res;
  }

  template<size_t l = 1024>
  class basic_uint {
  protected:
    std::bitset<l> data;

    std::pair<basic_uint<l>, basic_uint<l>> basic_div(const basic_uint<l> &s) const { // return <res, mod>
      if (*this < s)
        return std::make_pair(basic_uint<l>(0), basic_uint<l>(*this));
      if (s == basic_uint<l>(0))
        throw std::runtime_error("divide by zero");
      int diff = get_high_1_index(this->data) - get_high_1_index(s.data);
      basic_uint<l> tmp = s << diff, res, cpy(*this);
      for (; diff >= 0; --diff, tmp >>= 1) {
        if (tmp <= cpy) {
          res.data[diff] = 1;
          cpy -= tmp;
        }
      }
      return std::make_pair(res, cpy);
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

    template<size_t s>
    uint8_t get_bcd_from_index(const std::bitset<s> &num, size_t idx) const { // idx, idx + 1, .. idx + 3
      uint8_t res = 0, tmp = 1;
      res += num[idx] ? tmp : 0;
      tmp <<= 1u;
      res += num[idx + 1] ? tmp : 0;
      tmp <<= 1u;
      res += num[idx + 2] ? tmp : 0;
      tmp <<= 1u;
      res += num[idx + 3] ? tmp : 0;
      return res;
    }

    template<size_t s>
    void add_3_to_index(std::bitset<s> &num, size_t idx) const {
      size_t inc = 0, tmp;
      std::bitset<4> three(3);
      for (size_t i = 0; i < 4; ++i) {
        tmp = num[i + idx];
        num[i + idx] = tmp ^ inc ^ three[i];
        inc = (tmp + inc + three[i]) >= 2 ? 1 : 0;
      }
    }

    template<size_t s>
    uint8_t read_bcd_from_index(const std::bitset<s> &num, size_t idx) const {
      uint8_t res = 0, tmp = 1;
      for (size_t i = idx; i < idx + 4; ++i) {
        if (num[i])
          res += tmp;
        tmp <<= 1u;
      }
      return res;
    }

    std::string basic_to_string(const basic_uint<l> &num) const { // Double_dabble
      std::bitset<3 * l> opt;
      for (size_t i = 0; i < l; ++i)
        opt[i] = num.data[i];
      for (size_t k = 0; k < l; ++k) {
        for (size_t i = l; i < k + l; i += 4) {
          if (get_bcd_from_index(opt, i) >= 5) {
            add_3_to_index(opt, i);
          }
        }
        opt <<= 1;
      }
      std::string res, tmp_str;
      for (size_t i = l; i < 3 * l; i += 4) {
        char c = '0' + read_bcd_from_index(opt, i);
        if (c == '0')
          tmp_str += '0';
        else {
          res += tmp_str + c;
          tmp_str = "";
        }
      }
      std::reverse(res.begin(), res.end());
      if (res.empty())
        res = "0";
      return res;
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
/*  
    char to_hex(int number) {
      if (number <= 9)
        return ('0' + number);
      else
        return 'a' + number - 10;
    }    
    
    void hex_plus(std::string &result, const std::string &a, const std::string &b) {
      
    }
*/
  public:
    std::string to_binary_string() {
      return data.to_string();
    }

    unsigned long long to_ull() {
      return data.to_ullong();
    }

    [[nodiscard]] virtual std::string to_string() const {
      return basic_to_string(*this);
    }

    virtual void from_string(const std::string &str) {
      this->data = basic_from_string(str);
    }

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

    explicit basic_uint(std::string str) {
      this->from_string(str);
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
      for (int i = l - 1; i >= 0; --i) {
        if (a.data[i] < b.data[i])
          return true;
        if (a.data[i] > b.data[i])
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
      basic_uint<l> res;
      uint8_t inc = 0;
      for (size_t i = 0; i < l; ++i) {
        res.data[i] = a.data[i] ^ b.data[i] ^ inc;
        inc = (a.data[i] + b.data[i] + inc) >= 2 ? 1 : 0;
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
      /*
      basic_uint<l> res, tmp = b;
      for (size_t i = 0; i < l; ++i, tmp <<= 1) {
        if (a.data[i])
          res += tmp;
      }
      return res;
      */
      // int times = l / 4;
      basic_uint<l> res(0);
      int current_numa , current_numb , buff = 0;
      int temp_res;
      std::string stra , strb;
      size_t i;
      for (i = 0; i < l - 5; i += 4) {
        current_numa = current_numb = 0;
        for (size_t j = i; j < i + 4; ++j) {
          if (a.data[j])
            current_numa += std::pow(2, j - i);
          if (b.data[j])
            current_numb += std::pow(2, j - i);
        }
        stra.push_back(current_numa);
        strb.push_back(current_numb);
      }
      i -= 4;
      current_numa = current_numb = 0;
      for (size_t j = i; j < l; ++j)
      {
        if (a.data[j])
          current_numa += std::pow(2, j - i);
        if (b.data[j])
          current_numb += std::pow(2, j - i);
      }
      stra.push_back(current_numa);
      strb.push_back(current_numb);
      int length = stra.length();

      std::string strres(2 * length, 0);
      for (size_t k = 0; k < length; ++k) {
        for (size_t m = 0; m < length; ++m) {
          strres[k + m] += stra[k] * strb[m];
          strres[k + m + 1] += strres[k + m] / 16;
          strres[k + m] %= 16;
        }
      }

      for (size_t k = 0; k < 2 * length; ++k) {
        for (size_t m = 4 * k; m < 4 * k + 4; ++m) {
          res.data[m] = strres[k] % 2;
          strres[k] /= 2;
        }
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
