/*
 *  File    : encconv.hpp
 *  Author  : YW. Jang
 *  Date    : 2015.07.26.Sun
 *
 *  Copyright 2015, YW. Jang, All rights reserved.
 */

#ifndef ENCODING_CONVERTER_HPP_
#define ENCODING_CONVERTER_HPP_

#include <string>
#include <vector>

namespace nlp { namespace jang { namespace garnut {

enum CodeRange
{
  BMP_1_BYTES_RANGE = 1,
  BMP_2_BYTES_RANGE,
  BMP_3_BYTES_RANGE,
  SMP_RANGE,
  NONE
};

typedef unsigned int UnicodeChar;
typedef unsigned char Utf8char;

class EncodingConverter
{
public:
  // It returns std::wstring type basically.
  static bool convertUtf8ToUnicode(const char* src, wchar_t* dst);

  // It fill second parameter dst with std::wstring type basically.
  static bool convertUtf8ToUnicode(const std::string& src, std::wstring& dst);
  // It supports SMP unicode range.
  static bool convertUtf8ToUnicode(const std::string& src, std::vector<UnicodeChar>& dst);

  // It returns std::string type basically.
  static bool convertUnicodeToUtf8(const wchar_t* src, char* dst);

  // It fill second parameter dst with std::string type basically.
  static bool convertUnicodeToUtf8(const std::wstring& src, std::string& dst);
  // It supports SMP unicode range.
  static bool convertUnicodeToUtf8(const std::vector<UnicodeChar>& src, std::string& dst);

private:
  static UnicodeChar getCodeFlag(size_t pos, const std::wstring& src);
  static UnicodeChar getCodeFlag(size_t pos, const std::vector<UnicodeChar>& src);
  static CodeRange getUnicodeCodeRange(UnicodeChar flag);
  static CodeRange getUtf8CodeRange(unsigned char flag);

private:
  static void transformUtf8CharToUnicodeChar(const char* src, std::wstring& dst, const CodeRange& code_range);
  static void transformUnicodeCharToUtf8Char(const UnicodeChar code, std::string& dst, const CodeRange& code_range);

protected: // unicode range
  static const UnicodeChar BMP_CODE_RANGE_BEG_1_    = 0x00000000;
  static const UnicodeChar BMP_CODE_RANGE_END_1_    = 0x0000007F;
  static const UnicodeChar BMP_CODE_RANGE_BEG_2_    = 0x00000080;
  static const UnicodeChar BMP_CODE_RANGE_END_2_    = 0x000007FF;
  static const UnicodeChar BMP_CODE_RANGE_BEG_3_    = 0x00000800;
  static const UnicodeChar BMP_CODE_RANGE_END_3_    = 0x0000FFFF;
  static const UnicodeChar SMP_CODE_RANGE_BEG_      = 0x00010000;
  static const UnicodeChar SMP_CODE_RANGE_END_      = 0x0010FFFF;

protected: // utf8 range
  static const Utf8char UTF8_1_BYTE_PREFIX_      = 0x00; // 0xxxxxxx
  static const Utf8char UTF8_2_BYTE_PREFIX_      = 0xC0; // 110xxxxx xxxxxxxx
  static const Utf8char UTF8_3_BYTE_PREFIX_      = 0xE0; // 1110xxxx xxxxxxxx xxxxxxxx
  static const Utf8char UTF8_4_BYTE_PREFIX_      = 0xF0; // 11110xxx xxxxxxxx xxxxxxxx xxxxxxxx
  static const Utf8char UTF8_PREFIX_MASK_        = 0x80; // 10xxxxxx
};


} } } // nlp::jang::garnut

#endif