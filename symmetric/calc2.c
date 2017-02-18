#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int chk_char(char *c, int len);
static int parseExpression(char *c, int len, int data[]);
static int sum(int data[]);

int
main(int argc, char *argv[])
{

  char str[256];
  int nData[100] = {};

  for (;;) {
    printf("Enter Expression:");
    fgets(str, sizeof(str), stdin);

    // check args format
    if (chk_char(str, strlen(str))) {
      fprintf(stderr, "Error: Expression too complex. %s \n", argv[0]);
      continue;
    }

    // parse Expression
    parseExpression(str, strlen(str),nData);

    printf("ans: %d\n", sum(nData));

    memset(str, '\0', strlen(str));
    memset(nData, '\0', sizeof(nData));
  }
}

static int
parseExpression(char *c, int len, int data[])
{
  char buf[256];
  int i,j,dCnt,op;
  j = 0;
  dCnt = 0;
  op = 0;

  for (i = 0; i < len; i++) {
    if (isdigit((unsigned char)c[i])) {
      buf[j++] = c[i];
    } else {
      buf[j] = '\0';
      switch (op) {
        case 0:
          data[dCnt] = atoi(buf);
          dCnt++;
          break;
        case 1:
          data[dCnt] = -atoi(buf);
          dCnt++;
          break;
        case 2:
          data[dCnt - 1] *= atoi(buf);
          break;
        case 3:
          data[dCnt - 1] /= atoi(buf);
          break;
        default:
          break;
      }
      switch (c[i]) {
        case '+':
          op = 0;
          break;
        case '-':
          op = 1;
          break;
        case '*':
          op = 2;
          break;
        case '/':
          op = 3;
          break;
        default :
          break;
      }
      j = 0;
      memset(buf, '\0', strlen(buf));
    }
  }
  return 0;
}

static int
sum(int data[])
{
  int i,sum;
  sum = 0;
  for (i = 0; i < 100; i++) {
    sum += data[i];
  }
  return sum;
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
      case '\n':
        break;
      default :
        return -1;
    }
  }
  return 0;
}
