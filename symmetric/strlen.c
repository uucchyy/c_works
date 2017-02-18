#include <stdio.h>

static int strlen(char *str);

int
main(int argc, char *argv[])
{
  int i, c, len;
  char str[256];

  i = 0;
  c = 0;
  len = 0;

  while((c = getchar()) != EOF)
  {
    if (c == '\n') {
      len = strlen(str);
      printf("string: %s, length: %d\n", str, len);
      
      i = 0;
      len = 0;
      memset(str, '\0', sizeof(str));
    } else {
      str[i++] = c;
    }
  }
  return 0;
}

int
strlen(char *str)
{
  int i;
  int len;
  len = 0;
  
  for(i = 0;; i++) {
    if (str[i] == '\0') {
      return len;
    } else {
      len++;
    }
  }
}
