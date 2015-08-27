/*
 *  File    : ngramvector.hpp
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

template <typename T_key>
class Ngram
{
public:
  Ngram()
  {

  }

  Ngram(const std::vector<T_key>& ngram)
  {
    this->ngram_ = ngram;
  }

  virtual ~Ngram()
  {

  }

public:

protected:
  std::vector<T_key> ngram_;
};

} } } // nlp::jang::garnut

#endif