#include<iostream>
#include<cmath>
using namespace std;
int main()
{
 int num;
 int range;
 char *p;
 p = new char[100];
 int a[100];
 int b = 0;
 for (int i = 0; i <= 100; i++)
 {
  if (i <= '0 '&&i <= '100')//'100'写法语法错误，参照阅读关键字"char类型"
  {
   num = i + 1;//num 变量内容未初始化
   range = int(p[i] - 0);//p[i] - 0 等价于p[i]
  }

  if (p[i] == 'X')
  {
   a[b] = i + 1;
   b++;
  }
 }
 int c[100];
 int d = 0;
 for (int i = 0; i <= 100; i++)
 {
  c[i] = fabs(a[i] - num);//不安全的类型强转
 }

 for (int i = 0; i <= 100; i++)
 {
  if (c[i] <= range)
  {
   d = d + 1;
  }
 }
 cout << d;
 return 0;
}

/*
 * 此方法用于取代fabs
 */
int intAbs(int input) {
 return input >= 0 ? input : -input;
}
