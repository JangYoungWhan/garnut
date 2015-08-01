/*
 *  File    : encconv.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.07.26.Sun
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef ENC_CONV_HPP_
#define ENC_CONV_HPP_

#include <string>

namespace nlp {
namespace jang {
namespace ganet {

enum CodeRange
{
  BMP_1_BYTES_RANGE = 1,
  BMP_2_BYTES_RANGE,
  BMP_3_BYTES_RANGE,
  SMP_RANGE,
  NONE
};

typedef unsigned int UnicodeChar;

class EncodingConverter
{
public:
  // It returns std::wstring type basically.
  static bool convertFromUtf8ToUnicode(const char* src, wchar_t* dst);

  // It fill second parameter dst with std::wstring type basically.
  static bool convertFromUtf8ToUnicode(const std::string& src, std::wstring& dst);

  // It returns std::string type basically.
  static bool convertFromUnicodeToUtf8(const wchar_t* src, char* dst);

  // It fill second parameter dst with std::string type basically.
  static bool convertFromUnicodeToUtf8(const std::wstring& src, std::string& dst);

private:
  static UnicodeChar getCodeFlag(const std::wstring& src);
  static CodeRange getCodeRange(UnicodeChar flag);

private:
  static bool transformUtf8CharToUnicodeChar(const std::string& src, std::wstring& dst);
  static bool transformUnicodeCharToUtf8Char(const std::wstring& src, std::string& dst);

protected:
  static const UnicodeChar BMP_CODE_RANGE_BEG_1_   = 0x00000000;
  static const UnicodeChar BMP_CODE_RANGE_END_1_   = 0x0000007F;
  static const UnicodeChar BMP_CODE_RANGE_BEG_2_   = 0x00000080;
  static const UnicodeChar BMP_CODE_RANGE_END_2_   = 0x000007FF;
  static const UnicodeChar BMP_CODE_RANGE_BEG_3_   = 0x00000800;
  static const UnicodeChar BMP_CODE_RANGE_END_3_   = 0x0000FFFF;
  static const UnicodeChar SMP_CODE_RANGE_BEG_     = 0x00010000;
  static const UnicodeChar SMP_CODE_RANGE_END_     = 0x0010FFFF;
};


} // namespace ganet
} // namespace jang
} // namespace nlp

#endif