/*
 *  File    : encconv.cpp
 *  Author  : YW. Jang
 *  Date    : 2015.07.26.Sun
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#include "encconv.hpp"

namespace nlp {
namespace jang {
namespace garnut {

bool EncodingConverter::convertFromUtf8ToUnicode(const char* src, wchar_t* dst)
{
  return false;
}

bool EncodingConverter::convertFromUtf8ToUnicode(const std::string& src, std::wstring& dst)
{
  return false;
}

bool EncodingConverter::convertFromUnicodeToUtf8(const wchar_t* src, char* dst)
{
  return false;
}

bool EncodingConverter::convertFromUnicodeToUtf8(const std::wstring& src, std::string& dst)
{
  bool convert_result = false;

  for (size_t idx=0; idx<src.length(); ++idx)
  {
    std::wstring uni_ch;

    // converted current character.
    std::string utf8_ch;

    UnicodeChar flag = getCodeFlag(idx, src);

    CodeRange code_range = getCodeRange(flag);

    uni_ch.reserve(2);
    switch (code_range)
    {
    case nlp::jang::garnut::BMP_1_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_1_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::BMP_2_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_2_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::BMP_3_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_3_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::SMP_RANGE:
      uni_ch.push_back(src[idx]);
      uni_ch.push_back(src[++idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, SMP_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::NONE:
      convert_result = false;
      break;
    default:
      convert_result = false;
      break;
    }

    for (auto ch = utf8_ch.begin(); ch!=utf8_ch.end(); ++ch)
    {
      dst.push_back(*ch);
    }
  }

  return convert_result;
}

bool EncodingConverter::convertFromUnicodeToUtf8(const std::vector<UnicodeChar>& src, std::string& dst)
{
  bool convert_result = false;

  for (size_t idx=0; idx<src.size(); ++idx)
  {
    std::wstring uni_ch;

    // converted current character.
    std::string utf8_ch;

    UnicodeChar flag = getCodeFlag(idx, src);

    CodeRange code_range = getCodeRange(flag);

    uni_ch.reserve(2);
    switch (code_range)
    {
    case nlp::jang::garnut::BMP_1_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_1_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::BMP_2_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_2_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::BMP_3_BYTES_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, BMP_3_BYTES_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::SMP_RANGE:
      uni_ch.push_back(src[idx]);
      transformUnicodeCharToUtf8Char(flag, utf8_ch, SMP_RANGE);
      convert_result = true;
      break;
    case nlp::jang::garnut::NONE:
      convert_result = false;
      break;
    default:
      convert_result = false;
      break;
    }

    for (auto ch = utf8_ch.begin(); ch!=utf8_ch.end(); ++ch)
    {
      dst.push_back(*ch);
    }
  }

  return convert_result;
}

inline
UnicodeChar EncodingConverter::getCodeFlag(size_t pos, const std::wstring& src)
{
  unsigned int code_flag = 0x00000000;

  // Always It have to be BMP code range, otherwise It has a critical problem.
  if (true)
  {
    code_flag = static_cast<UnicodeChar>(src[pos]);
  }
  // If it is possible, we have to check high and low surrogates.
  // TO DO : YW. Jang
  else
  {
    code_flag |= (static_cast<unsigned int>(src[0]) << 16) & 0xFFFF0000;
    code_flag |= static_cast<unsigned int>(src[1]);
  }

  return code_flag;
}

inline
UnicodeChar EncodingConverter::getCodeFlag(size_t pos, const std::vector<UnicodeChar>& src)
{
  return src[pos];
}

inline
CodeRange EncodingConverter::getCodeRange(UnicodeChar flag)
{
  // 000000-00007F
  if ((BMP_CODE_RANGE_BEG_1_ <= flag) && (flag <= BMP_CODE_RANGE_END_1_))
  {
    return CodeRange::BMP_1_BYTES_RANGE;
  }

  // 000080-0007FF
  else if ((BMP_CODE_RANGE_BEG_2_ <= flag) && (flag <= BMP_CODE_RANGE_END_2_))
  {
    return CodeRange::BMP_2_BYTES_RANGE;
  }

  // 000800-00FFFF
  else if ((BMP_CODE_RANGE_BEG_3_ <= flag) && (flag <= BMP_CODE_RANGE_END_3_))
  {
    return CodeRange::BMP_3_BYTES_RANGE;
  }

  // 010000-10FFFF
  else if ((SMP_CODE_RANGE_BEG_ <= flag) && (flag <= SMP_CODE_RANGE_END_))
  {
    return CodeRange::SMP_RANGE;
  }

  // otherwise
  else
  {
    return CodeRange::NONE;
  }
}

inline
void EncodingConverter::transformUtf8CharToUnicodeChar(const std::string& src, std::wstring& dst)
{

}

inline
void EncodingConverter::transformUnicodeCharToUtf8Char(const UnicodeChar code, std::string& dst, const CodeRange& code_range)
{
  char utf_code;
  char high_surrogated, low_surrogated;

  switch (code_range)
  {
    case nlp::jang::garnut::BMP_1_BYTES_RANGE:
      utf_code = static_cast<char>(code);
      dst.push_back(utf_code); // 0xxx xxxx
      break;
    case nlp::jang::garnut::BMP_2_BYTES_RANGE:
      utf_code = (0xC0) | (code >> 6);
      dst.push_back(utf_code); // 110x xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
      break;
    case nlp::jang::garnut::BMP_3_BYTES_RANGE:
      utf_code = (0xE0) | (code >> 12);
      dst.push_back(utf_code); // 1110 xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code >> 6) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
      break;
    case nlp::jang::garnut::SMP_RANGE:
      utf_code = (0xF0) | (code >> 18);
      dst.push_back(utf_code); // 1111 0xxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code >> 12) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code >> 6) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
#if 0 // below this rule is utf16 to utf8
      high_surrogated = ((code >> 22) & 0x0F) + 1;
      utf_code = (0xF0) | (high_surrogated >> 2);
      dst.push_back(utf_code); // 1111 0zzz
      utf_code = (UTF8_PREFIX_MASK_) | ((high_surrogated << 4) & 0x3F) | ((code >> 18) & 0x0F);
      dst.push_back(utf_code); // 10zz xxxx

      low_surrogated = ((code >> 6) & 0x0C);
      utf_code = (UTF8_PREFIX_MASK_) | ((code >> 10) & 0x30) | low_surrogated | ((code >> 6) & 0x03);
      dst.push_back(utf_code); // 10xx xxxx
      utf_code = (UTF8_PREFIX_MASK_) | ((code) & 0x3F);
      dst.push_back(utf_code); // 10xx xxxx
#endif
      break;
    case nlp::jang::garnut::NONE:
      break;
    default:
      break;
  }
}

} // namespace garnut
} // namespace jang
} // namespace nlp