#include <iostream>
#include <string>

using namespace std;
/*
 * 思路：
 * 用一个固定长度的int数组存储thief能否被抓到的信息 int thief[100]
 * 按位处理之后，计算thief中可被抓到标记的总数
 *
 * 此算法复杂度 (O)n * k 其中n为字符串长度，k为能力者数量
 */
int main() {
    string input = "";//用于存储第一行输入数据
    //例如 AAAAXXXX24X
    getline(std::cin, input);//读取一行并存入input
    int thief[100] = {0};//用于存储"被抓到"这个信息
    for (int i = 0; i < input.length(); ++i) {//按位处理整个input
        if (input[i] >= '0' && input[i] <= '9') {//当前位内容为 0-9 时
            int pre = i - 1;//当前位的前一位的数组下标
            int after = i + 1;//当前位的后一位的数组下标
            int strength = input[i] - '0';//当前位代表的能力者能力值
            /*
             * 同时移动 pre 和 after 
             * 分析当前能力者能抓捕的犯人
             * 发现此犯人能抓捕时，标记thief对应下标的值为 1
             */
            while (strength--) {
                if (pre >= 0) {//越界控制
                    if (input[pre] == 'X') {
                        thief[pre] = 1;
                    }
                }
                if (after < input.length()) {//越界控制
                    if (input[after] == 'X') {
                        thief[after] = 1;
                    }
                }
                --pre;
                ++after;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < input.length(); ++i) {//计算thief数组每个元素的总和
        sum += thief[i];
    }
    std::cout << sum << std::endl;
    return 0;
}
