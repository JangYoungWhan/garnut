/*
 *  File    : editdistance.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.10.24.Sat
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef EDIT_DISTANCE_
#define EDIT_DISTANCE_

//#include <numeric> // std::iota
#include <vector>

namespace nlp { namespace jang { namespace garnut {

template <typename T_StrType>
class EditDistance
{
public:
  static unsigned int calculateLevenshteinDistance(const T_StrType& str1, const T_StrType& str2)
  {
    const std::size_t len1 = str1.size(), len2 = str2.size();
    std::vector<unsigned int> col(len2+1), prev_col(len2+1);

    for (unsigned int i=0; i<prev_col.size(); i++)
    {
      prev_col[i] = i;
    }

    for (unsigned int i=0; i<len1; i++)
    {
      col[0] = i + 1;
      for (unsigned int j=0; j<len2; j++)
      {
        col[j+1] = std::min(std::min(prev_col[j+1] + 1, col[j] + 1), prev_col[j] + (str1[i]==str2[j] ? 0 : 1));
      }
      col.swap(prev_col);
    }

    return prev_col[len2];
  }
};

} } } // nlp::jang::garnut

#endif