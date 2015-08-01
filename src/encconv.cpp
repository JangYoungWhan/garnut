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
namespace ganet {

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

  UnicodeChar flag = getCodeFlag(src);

  CodeRange code_range = getCodeRange(flag);

  switch (code_range)
  {
  case nlp::jang::ganet::BMP_1_BYTES_RANGE:
    convert_result = true;
    break;
  case nlp::jang::ganet::BMP_2_BYTES_RANGE:
    convert_result = true;
    break;
  case nlp::jang::ganet::BMP_3_BYTES_RANGE:
    convert_result = true;
    break;
  case nlp::jang::ganet::SMP_RANGE:
    convert_result = true;
    break;
  case nlp::jang::ganet::NONE:
    convert_result = false;
    break;
  default:
    convert_result = false;
    break;
  }

  return convert_result;
}

inline
UnicodeChar EncodingConverter::getCodeFlag(const std::wstring& src)
{
  unsigned int code_flag = 0x00000000;

  // It have to be BMP code range, otherwise It has a critical problem.
  if (src.length() == 1)
  {
    code_flag = static_cast<unsigned int>(src[0]);
  }
  else if (src.length() > 1)
  {
    code_flag |= (static_cast<unsigned int>(src[0]) << 16) & 0xFFFF0000;
    code_flag |= static_cast<unsigned int>(src[1]);
  }

  return code_flag;
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
    return CodeRange::BMP_1_BYTES_RANGE;
  }

  // 000800-00FFFF
  else if ((BMP_CODE_RANGE_BEG_3_ <= flag) && (flag <= BMP_CODE_RANGE_END_3_))
  {
    return CodeRange::BMP_1_BYTES_RANGE;
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

} // namespace ganet
} // namespace jang
} // namespace nlp