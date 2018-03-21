//
// Created by FredericDT on 2018/3/21.
//

#ifndef CPPSTD17_CSV_H
#define CPPSTD17_CSV_H


#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "StringTool.h"

using namespace std;

class CSV {
private:
    bool hasHeader = true;
    string path = "";
    map<string, int> header;

    void init(const string &path, bool hasHeader) {
        this->path = path;
        if (this->hasHeader) {
            ifstream file(this->path);
            string line;
            getline(file, line);
            line = trim(line);
            vector<string> tmpHeader;
            splitString(line, tmpHeader, ",");
            for (int i = 0; i < tmpHeader.size(); ++i) {
                this->header[tmpHeader[i]] = i;
            }
            file.close();
        }
    }

public:
    explicit CSV(const string &path) {
        this->init(path, this->hasHeader);
    }

    CSV(const string &path, bool hasHeader) {
        this->init(path, hasHeader);
    }

    class Row {
    private:
        map<string, int> &header;
        vector<string> value;
    public:
        Row(map<string, int> &header, vector<string> &value) : header(header), value(value) {}

        inline string operator[](int i) {
            return value[i];
        }

        inline string operator[](const string &i) {
            if (this->header.find(i) == this->header.end()) {
                return "";
            }
            return this->value[this->header[i]];
        }
    };

    void iterate(void (*func)(Row row)) {
        ifstream file(this->path);
        string line;
        if (this->hasHeader) {
            getline(file, line);
        }
        vector<string> currentRow;
        while (true) {
            getline(file, line);
            line = trim(line);
            splitString(line, currentRow, ",");
            if (currentRow.size() != this->header.size()) {
                break;
            }
            Row row(this->header, currentRow);
            func(row);
            currentRow.clear();
        }
        file.close();

    }

};

#endif //CPPSTD17_CSV_H
