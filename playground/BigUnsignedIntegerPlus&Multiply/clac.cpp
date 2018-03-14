//MIT License
//
//Copyright (c) 2018 FredericDT
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "clac.h"

std::string stringPlus(std::string a, std::string b) {
    int c = 0;
    long long ai = a.size() - 1;
    long long bi = b.size() - 1;
    std::string r = std::string("\0");
    while (ai >= 0 || bi >= 0) {
        int pr = (ai >= 0 ? (a[ai] - '0') : 0) + (bi >= 0 ? (b[bi] - '0') : 0) + c;
        c = pr / 10;
        r.insert(0, to_string(pr % 10));
        --ai;
        --bi;
    }
    return r;
}

std::string multiply(std::string a, std::string b) {
    std::string res = "0";
    long long bi = b.size();
    std::string suffix;
    while (bi--) {
        std::string cr;
        long long ai = a.size();
        int c = 0;
        while (ai--) {
            int pr = (b[bi] - '0') * (a[ai] - '0') + c;
            c = pr / 10;
            cr.insert(0, to_string(pr % 10));
        }
        if (c) {
            cr.insert(0, to_string(c));
        }
        res = stringPlus(res, cr + suffix);
        suffix += "0";
    }
    return res;
}