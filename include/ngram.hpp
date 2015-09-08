/*
 *  File    : ngram.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.08.28.Fri
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef NGRAM_HPP_
#define NGRAM_HPP_

#include "ngram.hpp"

#include <vector>

namespace nlp { namespace jang { namespace garnut {

template <typename T_StrType>
class Ngram
{
public:
  Ngram()
  {

  }

  Ngram(unsigned int n)
    :n_(n)
  {
    ngram_.reserve(n);
  }

  Ngram(const std::vector<T_StrType>& ngram)
  {
    this->ngram_ = ngram;
  }

  virtual ~Ngram()
  {

  }

public:
  void push_back(const T_StrType& token)
  {
    ngram_.push_back(token);
  }

public:
  unsigned int getN() const
  {
    return this->n_;
  }

public: // operator overloading
  // Non-const variants
  T_StrType& operator[](std::size_t idx)
  {
    return ngram_[idx];
  }

  // Const variants
  const T_StrType& operator[](std::size_t idx) const
  {
    return ngram_[idx];
  }

  bool operator==(const Ngram& rhs) const
  {
    return this->ngram_ == rhs.ngram_;
  }

  bool operator!=(const Ngram& rhs)
  {
    return !(this->ngram_ == rhs);
  }

  bool operator>(const Ngram& rhs)
  {
    return this->ngram_ > rhs.ngram_;
  }

  bool operator>=(const Ngram& rhs)
  {
    return  this->ngram_ >= rhs.ngram_;
  }
  
  bool operator<(const Ngram& rhs)
  {
    return  this->ngram_ < rhs.ngram_;
  }
  
  bool operator<=(const Ngram& rhs)
  {
    return  this->ngram_ <= rhs.ngram_;
  }

protected:
  std::vector<T_StrType> ngram_;
  unsigned int n_;
};

} } } // nlp::jang::garnut

#endif