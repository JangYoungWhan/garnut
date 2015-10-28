/*
 *  File    : editdistance.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.10.24.Sat
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef EDIT_DISTANCE_
#define EDIT_DISTANCE_

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

  static unsigned int calculateDamerauLevenshteinDistance(const T_StrType& str1, const T_StrType& str2, unsigned int num_of_alphabet)
  {
    // "infinite" distance is just the max possible distance
    const unsigned int INF = str1.length() + str2.length();

    // make and initialize the character array indices
    unsigned int* DA = (unsigned int*) calloc (sizeof(unsigned int), num_of_alphabet);

    // make the distance matrix H[-1..a.length][-1..b.length]
    unsigned int** H = (unsigned**) calloc (sizeof(unsigned*), str1.length()+1);
    H[0] = (unsigned*) calloc (sizeof(unsigned), str1.length()+1 * str2.length()+1);
    for(unsigned int i=1; i<str1.length()+1; ++i)
    {
      H[i] = H[i-1] + str2.length()+1;
    }

    // initialize the left and top edges of H
    H[0][0] = INF;
    for (unsigned int i=0; i<str1.length(); ++i)
    {
      H[i][0] = INF;
      H[i][1] = i;
    }
    for (unsigned int j=0; j<str2.length(); ++j)
    {
      H[0][j] = INF;
      H[1][j] = j;
    }

    // fill in the distance matrix H
    // look at each character in a
    for (unsigned int i=1; i<str1.length(); ++i)
    {
      unsigned int DB = 0;
      // look at each character in b
      for (unsigned int j=1; j<str2.length(); ++j)
      {
        unsigned int i1 = DA[str2[j-1]];
        unsigned int j1 = DB;
        unsigned int cost;
        if (str1[i-1] == str2[j-1])
        {
          cost = 0;
          DB   = j;
        }
        else
          cost = 1;
        H[i][j] = std::min(H[i-1][j-1] + cost,                        // substitution
                           H[i   ][j-1] + 1,                          // insertion
                           H[i-1 ][j  ] + 1,                          // deletion
                           H[i1-1][j1-1] + (i-i1-1) + 1 + (j-j1-1));
      }
      DA[str1[i-1]] = i;
    }
    return H[str1.length()][str2.length()];
  }
};

} } } // nlp::jang::garnut

#endif