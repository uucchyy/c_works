#include <stdio.h>

int main(int argc, char *argv[])
{
  int c;
  int ans;
  int left;
  int right;

  int flg = 0;
  while((c = getchar()) != EOF)
  {
    if (c == 10) {
      ans = left + right;
      printf("%d", ans);
    } else if (c == 43) {
      flg = 1;
      printf("%c", c);
    } else if (c == 61) {
      printf("%c", c);
    } else {
      if (flg == 1) {
        right = c - 48;
      } else {
        left = c - 48;
      }
      printf("%d", c - 48);
    }
  }
  return 0;
}
