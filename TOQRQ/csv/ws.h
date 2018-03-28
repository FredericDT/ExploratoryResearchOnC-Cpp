//
// Created by 田维翰 on 2018/3/28.
//

#ifndef CPPSTD17_WS_H
#define CPPSTD17_WS_H

#include <codecvt>
#include <string>
#include <iostream>

using namespace std;

std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

#endif //CPPSTD17_WS_H
