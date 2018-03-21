//
// Created by FredericDT on 2018/3/21.
//

#include <iostream>
#include "csv.h"

using namespace std;

void func(CSV::Row r) {
    cout << r[2] << "," << r[7] << "," << r[8] << "," << r[9] << "," << r[11] << "," << r[12] << endl;
}

int main() {
    CSV csv("/Users/Frederic_DT/Documents/jwxt_all_class/j.csv", true);
    csv.iterate(&func);
}
