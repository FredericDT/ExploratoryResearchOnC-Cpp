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
  if (i <= '0 '&&i <= '100')
  {
   num = i + 1;
   range = int(p[i] - 0);
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
  c[i] = fabs(a[i] - num);
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
