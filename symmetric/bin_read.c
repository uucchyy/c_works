#include <stdio.h>

typedef struct {
  char no[7]; /* 社員番号 */
  char name[32]; /* 氏名 */
  int age; /* 年齢 */
} employee;

int
main(int argc, char *argv[])
{

  FILE *fp;
  char *fname = "employe.bin";
  unsigned char buf[100000];
  int i, size;

  fp = fopen(fname, "rb");
  if (fp == NULL) {
    printf("file is not found.");
    return -1;
  }

  size = fread(buf, sizeof(unsigned char), 100000, fp);
  printf("%d size", (int)size);

  for (i = 0; i < size; i++) {
    if (i % 16 == 0) printf("\n");
    printf("%02X", buf[i]);
  }
  
  for (i = 0; i < size; i++) {
    printf("%c", (char)buf[i]);
  }

  fclose(fp);
  return 0;
}
