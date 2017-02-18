#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int chk_char(char *c, int len);

int
main(int argc, char *argv[])
{

  char cmd[256];
  char str[256];

  for (;;) {
    printf("Enter Expression:");
    fgets(str, sizeof(str), stdin);

    // check args format
    if (chk_char(str, strlen(str) - 1)) {
      fprintf(stderr, "Error: Expression too complex. %s \n", argv[0]);
      continue;
      // return 1;
    }

    // trim \n
    str[strlen(str) - 1] = '\0';

    // concat python command line
    sprintf(cmd, "python -c \"print(%s)\"", str);

    // debug command
    // printf("%s \n", cmd);

    // system call
    system(cmd);

  }
}

static int
chk_char(char *c, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    switch (c[i]) {
      case ' ':
      case '+':
      case '-':
      case '*':
      case '/':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        // debug code
        // printf("%d: ok  %c\n", i, c[i]);
        break;
      default :
        // debug code
        // printf("%d: ng %c\n", i, c[i]);
        return -1;
    }
  }
  return 0;
}
