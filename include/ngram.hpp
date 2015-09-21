/*
 *  File    : ngram.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.08.28.Fri
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef NGRAM_HPP_
#define NGRAM_HPP_

#include <vector>
#include <iostream>

namespace nlp { namespace jang { namespace garnut {

template <typename T_StrType>
class Ngram;

template <typename T_StrType>
std::ostream& operator<<(std::ostream& os, const Ngram<T_StrType>& ngram);

template <typename T_StrType>
class Ngram
{
public:
  Ngram()
    :n_(1)
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

  Ngram(const Ngram<T_StrType>& ngram)
    :n_(ngram.n_)
  {
    for (size_t i=0; i<ngram.getN(); ++i)
    {
      ngram_.push_back(ngram[i]);
    }
  }

  virtual ~Ngram()
  {
    this->ngram_.clear();
  }

public:
  void push_back(const T_StrType& token)
  {
    ngram_.push_back(token);
  }

  void attach(const T_StrType& start, const T_StrType& end)
  {
    for (unsigned int i=0; i<n_-1; ++i)
    {
      ngram_.insert(ngram_.begin(), start);
    }
    for (unsigned int i=0; i<n_-1; ++i)
    {
      ngram_.push_back(end);
    }
  }

  void attach(const T_StrType& start, const T_StrType& end, unsigned int level)
  {
    n_ = level;

    for (unsigned int i=0; i<level-1; ++i)
    {
      ngram_.insert(ngram_.begin(), start);
    }
    for (unsigned int i=0; i<level-1; ++i)
    {
      ngram_.push_back(end);
    }
  }

  const size_t size() const
  {
    return ngram_.size();
  }


public:
  unsigned int getN() const
  {
    return this->n_;
  }
  void setN(const unsigned int n)
  {
    this->n_ = n;
  }

  const std::vector<T_StrType>& getNgram() const
  {
    return this->ngram_;
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

  friend std::ostream& operator<< <>(std::ostream& os, const Ngram<T_StrType>& ngram);

protected:
  std::vector<T_StrType> ngram_;
  unsigned int n_;
};

template <typename T_StrType>
std::ostream& operator<<(std::ostream& os, const Ngram<T_StrType>& ngram)
{
  for (size_t i=0; i<ngram.getN(); ++i)
  {
    os << ngram[i];
    if (i != ngram.getN())
    {
      os << ' ';
    }
  }
  
  return os;
}

template <typename T_StrType>
std::wostream& operator<<(std::wostream& os, const Ngram<T_StrType>& ngram)
{
  for (size_t i=0; i<ngram.getN(); ++i)
  {
    os << ngram[i];
    if (i != ngram.getN())
    {
      os << L' ';
    }
  }
  
  return os;
}

} } } // nlp::jang::garnut

#endif