/*
 *  File    : sentencedealer.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.09.16.Wed
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef SENTENCE_DEALER_HPP_
#define SENTENCE_DEALER_HPP_

#include "tokenizer.hpp"
#include "ngram.hpp"

namespace nlp { namespace jang { namespace garnut {

class SentenceDealer
{
public:
  static void convertSentenceToWordNgram(const std::string& src, std::vector<Ngram<std::string>>& dst,
                                         unsigned int n=2)
  {
    Ngram<std::string> tokenWithTag;
    insertStartEndTags(src, tokenWithTag, n);

    for (size_t i=0; i<tokenWithTag.size()-n+1; ++i)
    {
      Ngram<std::string> ngram(n);

      for (unsigned int j=0; j<n; ++j)
      {
        ngram.push_back(tokenWithTag[i + j]);
      }
      dst.push_back(ngram);
    }

  }

  static void convertSentenceToLetterNgram(const std::string& src, Ngram<std::string::value_type>& dst,
                                           unsigned int n=2)
  {
    for (auto& ch : src)
    {
      dst.push_back(ch);
    }
  }

  static void convertSentenceToLetterNgram(const std::wstring& src, Ngram<std::wstring::value_type>& dst,
                                           unsigned int n=2)
  {
    for (auto& wch : src)
    {
      dst.push_back(wch);
    }
  }

public:
  static void insertStartEndTags(Ngram<std::string>& target,
                                 unsigned int n=2,
                                 const std::string& begin_tag = "<s>",
                                 const std::string& end_tag = "</s>")
  {
    target.attachTags(begin_tag, end_tag, n);
  }

  static void insertStartEndTags(Ngram<std::wstring>& target,
                                 unsigned int n=2,
                                 const std::wstring& begin_tag = L"<s>",
                                 const std::wstring& end_tag = L"</s>")
  {
    target.attachTags(begin_tag, end_tag, n);
  }

  static void insertStartEndTags(const std::string& src, Ngram<std::string>& dst,
                                 unsigned int n=2,
                                 const std::string& begin_tag = "<s>",
                                 const std::string& end_tag = "</s>")
  {
    splitStringToNgram<std::string>(src, dst, " ");

    dst.attachTags(begin_tag, end_tag, n);
  }

  static void insertStartEndTags(const std::wstring& src, Ngram<std::wstring>& dst,
                                 unsigned int n=2,
                                 const std::wstring& begin_tag = L"<s>",
                                 const std::wstring& end_tag = L"</s>")
  {
    splitStringToNgram<std::wstring>(src, dst, L" ");

    dst.attachTags(begin_tag, end_tag, n);
  }
};

} } } // nlp::jang::garnut

#endif
