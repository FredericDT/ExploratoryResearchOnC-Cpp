# 设计报告

    author FredericDT

    author 田维翰 2017211417

## 设计思路

    算法已指定，根据算法思路，实现 Boyer-Moore 字符串匹配算法

    有两种匹配规则

    1. BadCharacter -> 当前匹配失败，移动 pattern 对齐上一出现字符到当前失配位置
    2. GoodSuffix -> 当前匹配失败，从末尾到当前，之前出现过的最大相同字串对齐

    根据以上思路编写

## 代码说明
### BruteForce.cxx
    用于测试
### main.cpp  
详见代码中注释

`bool equals(char s, char p)` 平凡相等

`bool equalsWithGeneric(char s, char p)` 问号通配符相等

`class BoyerMoorePattern {...}` pattern 预处理容器

`void initBadCharacterMaps()`  badCharacter 规则初始化函数

`long getBadPatternIndex(long index, char target)`  获取上一次 badCharacter 在 pattern 中的出现 index

`void parseGoodSuffix()` 初始化 goodSuffix 规则缓存

`long indexOf(std::string const &source, long startIndex = 0)` 搜索第一次从 startIndex 出现的 pattern 的 index

`std::vector<long> getAllIndexOf(std::string const &source, long startIndex = 0)` 搜索所有从 startIndex 开始出现过的 pattern index

`std::string read_file_to_string(std::string const &path)` 文件读取 helper

## Runtime Capture
![Runtime Capture](Capture.PNG)

