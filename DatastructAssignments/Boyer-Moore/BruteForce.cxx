/**
 * @assignment
 *
 * 任选一篇txt格式的英文文档；
 * 用户输入任意一个英文单词，可以在该英文文档中检索这个英文单词，如果找到，则给出该英文单词出现的次数和所有位置，如果没有找到返回检索失败；
 * 用户输入可以用命令行方式，所选的英文文档路径也用命令行输入；
 * 采用BM算法进行检索（Boyer-Moore算法是一种基于后缀匹配的模式串匹配算法，后缀匹配就是模式串从右到左开始比较，但模式串的移动还是从左到右的。）
 * 需要提交设计报告和源代码，要求和《实验一》一样
 * 补充：输入的单词中包括通配字符；
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

//#define DEBUG

/**
 * @author FredericDT <frederic.dt.twh@gmail.com> DA8F097136E9AD8A
 * @date 11/29/2018
 *
 */
namespace fdt {
    /**
     * @function bool equals(char s, char p)
     *
     * @return bool
     * @param s char
     *   char from the source string
     * @param p char
     *   char from the pattern string
     *
     * plain equals function
     * return true when the two char are equal
     *
     */
    bool equals(char s, char p) {
        return s == p;
    }

    /**
     * @function bool equalsWithGeneric(char s, char p)
     *
     * @return bool
     * @param s char
     *   char from the source string
     * @param p char
     *   char from the pattern string
     *
     * equals function with generic character '*'
     * return true if p is '*' or p equals s
     *
     */
    bool equalsWithGeneric(char s, char p) {
        return s == p || p == '?';
    }

    /**
     * @class BruteForce
     *
     * BruteForce compare function
     * intended for assertion tests
     *
     */
    class BruteForce {
    public:
        /**
         * @static
         * @function static long indexOf(std::string const &source, std::string const &pattern, long startIndex, bool (*eqf)(char s, char p))
         *
         * @return long
         * @param source std::string const &
         *   reference of the source string
         * @param pattern std::string const &
         *   reference of the pattern string
         * @param eqf bool (*)(char s, char p)
         *   equals function
         * @param startIndex long
         *   start index of matching
         *
         * a function implementing brute force string compare
         * return the first appearance index of the pattern string in source string
         *
         */
        static long
        indexOf(std::string const &source, std::string const &pattern, long startIndex = 0,
                bool (*eqf)(char s, char p) = &equals) {
            for (long i = startIndex; i < source.length(); ++i) {
                long ii = i;
                long j = 0;
                while (j < pattern.length() && eqf(source[ii], pattern[j])) {
                    ++j;
                    ++ii;
                }
                if (j >= pattern.length()) {
                    return i;
                }
            }
            return -1;
        }

        /**
         * @static
         * @function static std::vector<long> getAllIndexsOf(std::string const &source, std::string const &pattern, bool (*eqf)(char s, char p))
         *
         * @return std::vector<long>
         * @param source std::string const &
         *   reference of the source string
         * @param pattern std::string const &
         *   reference of the pattern string
         * @param eqf bool (*)(char s, char p)
         *   equals function
         *
         * return all occurence index of the pattern string in the source string
         * by a std::vector<long>
         *
         */
        static std::vector<long>
        getAllIndexsOf(std::string const &source, std::string const &pattern, bool (*eqf)(char s, char p) = &equals) {
            long i = -pattern.length();
            i = BruteForce::indexOf(source, pattern, i + pattern.length(), eqf);
            std::vector<long> v{};
            while (i >= 0) {
                v.push_back(i);
                i = indexOf(source, pattern, i + pattern.length(), eqf);
            }
            return v;
        }
    };

    /**
     * @function std::string read_file_to_string(std::string const &path)
     *
     * @return std::string
     * @param path std::string const &
     *   reference of path of the target file
     *
     * read the file located at (path), the return its content as std::string
     *
     */
    std::string read_file_to_string(std::string const &path) {
        std::ifstream inFile;
        inFile.open(path);
        std::stringstream stringStream;
        stringStream << inFile.rdbuf();
        std::string s = stringStream.str();
        inFile.close();
        return s;
    }
}

int main(int argc, char **argv) {
#ifndef DEBUG
    if (argc < 3) {
        std::cout << "Usage: BruteForce <filepath> <pattern> [withGeneric<0|1>]" << std::endl;
        exit(1);
    }
    bool (*eqf)(char s, char p) = &fdt::equals;
    if (argc >= 4) {
        if (*argv[3] == '1') {
            eqf = &fdt::equalsWithGeneric;
        }
    }
    std::string s(fdt::read_file_to_string(argv[1]));
    std::string p(argv[2]);
#else
    std::string s(fdt::read_file_to_string("text"));//"HERE_IS_A_SIMPLE_EXAMPLE");
    std::string p("was");//"EXAMPLE");
    bool (*eqf)(char s, char p) = &fdt::equals;
#endif
    //fdt::BoyerMoorePattern bmp(p, eqf);
    std::vector<long> v = /*bmp.getAllIndexOf(s, 0);*/fdt::BruteForce::getAllIndexsOf(s, p, eqf);
    for (auto &i : v) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl << "count of all existence: " << v.size() << std::endl;:
    return 0;
}