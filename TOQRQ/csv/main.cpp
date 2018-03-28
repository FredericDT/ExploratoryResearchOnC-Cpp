//
// Created by FredericDT on 2018/3/21.
//

#include <algorithm>
#include <iostream>

#include "csv.h"
#include "StringTool.h"
#include "ws.h"

#include <map>

using namespace std;

int week = 1;

string day = "1";

map<string, int> tmp;

const int ROOM_LEN = 81;

const string classRooms[] = {
        "D-N04",
        "D-S04",
        "D-S05",
        "D-S06",
        "D-S08",
        "D-S10",
        "N103",
        "N104",
        "N105",
        "N108",
        "N110",
        "N111",
        "N113",
        "N116",
        "N118",
        "N119",
        "N201",
        "N206",
        "N207",
        "N208",
        "N209",
        "N214",
        "N215",
        "N216",
        "N301",
        "N302",
        "N307",
        "N308",
        "N309",
        "N315",
        "N318",
        "N319",
        "N327",
        "N403",
        "N404",
        "N420",
        "N424",
        "N506",
        "N512",
        "N524",
        "S103",
        "S104",
        "S106",
        "S107",
        "S109",
        "S112",
        "S113",
        "S114",
        "S118",
        "S119",
        "S202",
        "S205",
        "S207",
        "S208",
        "S210",
        "S211",
        "S215",
        "S216",
        "S301",
        "S302",
        "S307",
        "S308",
        "S323",
        "S327",
        "S403",
        "S404",
        "S418",
        "S419",
        "S422",
        "S503",
        "S504",
        "S505",
        "S506",
        "S509",
        "S512",
        "S514",
        "S518",
        "S519",
        "S522",
        "S523",
        "报告厅",
};

map<int, vector<string>> emptyRoomsByTime = {
        {1, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {2, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {3, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {4, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {5, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {6, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {7, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {8, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {9, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {10, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {11, vector<string>(classRooms, classRooms + ROOM_LEN)},
        {12, vector<string>(classRooms, classRooms + ROOM_LEN)}
                                          };


void func(CSV::Row &r) {

    // 排除非教学实验综合楼
    if (r[11] != "教学实验综合楼") {
        return;
    }
    // 排除非本周同一天
    if (day != r[8]) {
        return;
    }
    vector<string> weeks;
    splitString(r[7], weeks, "、");
    for (const string &weekStr : weeks) {
        string concated;
        bool isOddEvenDifferent = false;
        bool isOdd = true;
        wstring wweekStr = s2ws(weekStr);
        for (wchar_t i : wweekStr) {
            if ((i >= L'0' && i <= L'9') || i == L'-') {
                concated += i;
            } else if (i == L'单') {
                isOddEvenDifferent = true;
            } else if (i == L'双') {
                isOddEvenDifferent = true;
                isOdd = false;
            }
        }
        vector<string> weekPeriod;
        splitString(concated, weekPeriod, "-");
        bool isOnThatWeek = false;
        if (weekPeriod.size() < 2) {
            int weekInt = stoi(weekPeriod[0]);
            isOnThatWeek = (weekInt == week);
        } else {
            int weekStart = stoi(weekPeriod[0]);
            int weekEnd = stoi(weekPeriod[1]);
            if (week >= weekStart && week <= weekEnd) {
                isOnThatWeek = true;
                if (isOddEvenDifferent) {
                    if (isOdd ^ (week % 2)) {
                        isOnThatWeek = false;
                    }
                }
            }
        }
        if (! isOnThatWeek) {
            return;
        }
        vector<string> classTime;
        splitString(r[9], classTime, "~");
        int end = stoi(classTime[1]);
        for (int timeI = stoi(classTime[0]); timeI <= end; ++timeI) {
            vector<string> &currentFreeRooms = emptyRoomsByTime[timeI];
            currentFreeRooms.erase(std::remove(currentFreeRooms.begin(), currentFreeRooms.end(), r[12]), currentFreeRooms.end());
        }
    }


    //周次 星期 节次 楼 教室
    //cout << r[7] << "," << r[8] << "," << r[9] << "," << r[11] << "," << r[12] << endl;


}

int main() {

    cout << "input week day: ";

    cin >> week >> day;

    CSV csv("/Users/Frederic_DT/Documents/jwxt_all_class/j.csv", true);
    csv.iterate(&func);

    for (const auto &i : emptyRoomsByTime) {
        cout << i.first << endl;
        for (const auto &j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }


}

