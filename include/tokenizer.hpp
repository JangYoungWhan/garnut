/*
 *  File    : tokenizer.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.07.26.Sun
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_

#include <vector>
#include <ngram.hpp>

namespace nlp { namespace jang { namespace garnut {

template <typename T_str>
void splitStringToNgram(const T_str& src, std::vector<T_str>& dst, const T_str& delimiter, bool keepEmpty=false)
{
	size_t prev = 0;
	size_t next = 0;

	while ((next = src.find_first_of(delimiter, prev)) != std::string::npos)
	{
		if (keepEmpty || (next - prev != 0))
		{
			dst.push_back(src.substr(prev, next - prev));
		}
		prev = next + 1;
	}

	if (prev < src.size())
		dst.push_back(src.substr(prev));
}

template <typename T_str>
void splitStringToNgram(const T_str& src, Ngram<T_str>& dst, const T_str& delimiter, bool keepEmpty=false)
{
	size_t prev = 0;
	size_t next = 0;

	while ((next = src.find_first_of(delimiter, prev)) != std::string::npos)
	{
		if (keepEmpty || (next - prev != 0))
		{
			dst.push_back(src.substr(prev, next - prev));
		}
		prev = next + 1;
	}

	if (prev < src.size())
		dst.push_back(src.substr(prev));
}

} } } // nlp::jang::garnut

#endif