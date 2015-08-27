/*
 *  File    : distribution_array.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.08.28.Fri
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef DISTRIBUTION_ARRAY_HPP_
#define DISTRIBUTION_ARRAY_HPP_

#include <map>
#include <string>
#include <iostream>

namespace nlp { namespace jang { namespace garnut {

template <typename T_val>
class DistributionArray {
private:
  typedef std::string StringType;

public:
  DistributionArray()
    : size_of_script_dist_(0) {
    script_distribution_ = nullptr;
  }

  DistributionArray(const StringType& math_script, int size)
    : math_script_(math_script), size_of_script_dist_(size) {
    script_distribution_ = (T_val*) calloc(size, sizeof(T_val));
  }

  DistributionArray(const DistributionArray& dist_arr) {
    this->math_script_ = dist_arr.math_script_;
    this->size_of_script_dist_ = dist_arr.size_of_script_dist_;

    if (dist_arr.script_distribution_ == nullptr) { // NULL check.
      this->script_distribution_ = nullptr;
    } else {
      this->script_distribution_ = (T_val*) calloc(dist_arr.size_of_script_dist_, sizeof(T_val));

      for (auto i = 0; i < dist_arr.size_of_script_dist_; ++i) {
        this->script_distribution_[i] = dist_arr.script_distribution_[i];
      }
    }
  }

  ~DistributionArray() { // This class is a data class, so do not inherit it. (Non-virtual)
    delete script_distribution_;
  }

public:
  bool IncreaseValue(int id, const T_val& value) {
    // For example, where id=2 and value=8,
    //         [0] [1] [2] [3] ...
    // Before : 0   0   0   0  ...
    // Doing  : 0   0  0+8  0  ...
    // After  : 0   0   8   0  ...
    if (id < size_of_script_dist_ && script_distribution_ != nullptr) {
      script_distribution_[id] += value;
      return true;
    } else {
      fprintf(stderr, "Cannot set id(%d) and value(%d).", id, value);
      return false;
    }
  }

public:
  DistributionArray& operator+=(const DistributionArray& rhs) {
    for (auto i = 0; i < size_of_script_dist_; ++i) {
      this->script_distribution_[i] += rhs.script_distribution_[i];
    }

    return *this;
  }

  friend DistributionArray operator+(DistributionArray lhs, const DistributionArray& rhs) {
    lhs += rhs;

    return lhs;
  }

  DistributionArray& operator-(const DistributionArray& rhs) {
    for (auto i = 0; i < size_of_script_dist_; ++i) {
      this->script_distribution_[i] -= rhs.script_distribution_[i];
    }

    return *this;
  }

  friend DistributionArray operator-=(DistributionArray lhs, const DistributionArray& rhs) {
    lhs -= rhs;

    return lhs;
  }

  DistributionArray& operator=(const DistributionArray& rhs) {
    if (this == &rhs) { // Check for self-assignment
      return *this;
    }
    this->math_script_ = rhs.math_script_;
    this->size_of_script_dist_ = rhs.size_of_script_dist_;
    delete this->script_distribution_;

    if (rhs.script_distribution_ != nullptr) {
      this->script_distribution_ = (T_val*) calloc(size, sizeof(T_val));
    } else {
      this->script_distribution_ = nullptr;
    }

    return *this;
  }

  T_val& operator[](int i) {
    return this->script_distribution_[i];
  }

  bool operator==(const DistributionArray& rhs) const {
    for (auto i = 0; i < size_of_script_dist_; ++i) {
      if (this->script_distribution_[i] != rhs.script_distribution_[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const DistributionArray& rhs) const {
    return !(*this == rhs);
  }

  friend std::ostream& operator<<(std::ostream& ofs, DistributionArray& dist_arr) {
    ofs << "[ ";
    for (auto i = 0; i < dist_arr.size_of_script_dist_; ++i) {
      ofs << (dist_arr.script_distribution_)[i] << " ";
    }
    ofs << "]";
    return ofs;
  }

private:
  StringType math_script_;
  unsigned int size_of_script_dist_;
  T_val* script_distribution_;
};

} } } // nlp::jang::garnut

#endif