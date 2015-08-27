/*
 *  File    : progressbar.hpp
 *  Author  : YW. Jang
 *  Date    : 2014.10.09.Thu
 *
 *  Copyright 2014, YW. Jang, All rights reserved.
 */

#ifndef PROGRESS_BAR_HPP_
#define PROGRESS_BAR_HPP_

#include <iostream>
#include <iomanip>

namespace nlp { namespace jang { namespace garnut {

template <typename T_int>
class ProgressBar
{
public:
	ProgressBar();
	virtual ~ProgressBar();
	static void dispalyPrgressBar(T_int x, T_int n, int w = 50);
};

template <typename T_int>
ProgressBar<T_int>::ProgressBar()
{

}

template <typename T_int>
ProgressBar<T_int>::~ProgressBar()
{

}

template <typename T_int>
inline
void ProgressBar<T_int>::dispalyPrgressBar(T_int x, T_int n, int w)
{
  x += 1;
  if ((x != n) && (x % (n/100+1) != 0)) return;

  float ratio =  x / static_cast<float>(n);
  T_int c =  static_cast<int>(ratio*w);

  std::wcout << std::setw(3) << static_cast<T_int>(ratio*100) << "% [";
  for (T_int p=0; p<w; p++)
  {
    if (p < c)
      std::wcout << "=";
    else if(p == c)
      std::wcout << ">";
    else
      std::wcout << " ";
  }
  std::wcout << "]\r" << std::flush;
}

} } } // nlp::jang::garnut

#endif