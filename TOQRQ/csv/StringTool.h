//
// Created by FredericDT on 2018/3/21.
//

#ifndef CPPSTD17_STRINGTOOL_H
#define CPPSTD17_STRINGTOOL_H

#include <iostream>
#include <vector>

using namespace std;

/*
 *
 * csdn
 * https://www.cnblogs.com/zhiranok/archive/2011/12/08/stl_string_trim_split_replace.html
 *
 */
string trim(const string &str) {
    string::size_type pos = min(str.find_first_not_of('\r'), str.find_first_not_of(' '));//for mac
    if (pos == string::npos) {
        return str;
    }
    string::size_type pos2 = max(str.find_last_not_of('\r'), str.find_last_not_of(' '));
    if (pos2 != string::npos) {
        return str.substr(pos, pos2 - pos + 1);
    }
    return str.substr(pos);
}

/*
 *
 * csdn @egmkang
 * https://www.cnblogs.com/dfcao/p/cpp-FAQ-split.html#2889651
 *
 */
void splitString(const std::string &s, std::vector<std::string> &v, const std::string &c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

#endif //CPPSTD17_STRINGTOOL_H
