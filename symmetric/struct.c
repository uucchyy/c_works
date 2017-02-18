#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char no[7]; /* 社員番号 */
  char name[256]; /* 氏名 */
  int age; /* 年齢 */
} employee;

int employee_sort( const void * a , const void * b ) {
  employee e1 = *(employee*)a;
  employee e2 = *(employee*)b;
  return strcmp(e1.name, e2.name);
  //return strcmp(e2.name, e1.name);
  }

int
main(int argc, char *argv[])
{
  // 社員構造体配列の初期化
  employee data[4];

  strcpy(data[0].no, "150001");
  strcpy(data[0].name, "takahashi");
  data[0].age = 27;

  strcpy(data[1].no, "150002");
  strcpy(data[1].name, "fushimi");
  data[1].age = 127;

  strcpy(data[2].no, "150003");
  strcpy(data[2].name, "honda kiyonori");
  data[2].age = 227;

  strcpy(data[3].no, "150004");
  strcpy(data[3].name, "kobayan");
  data[3].age = 327;

  printf("%s: name:%s age:%d\n", data[0].no, data[0].name, data[0].age);
  printf("%s: name:%s age:%d\n", data[1].no, data[1].name, data[1].age);
  printf("%s: name:%s age:%d\n", data[2].no, data[2].name, data[2].age);
  printf("%s: name:%s age:%d\n\n", data[3].no, data[3].name, data[3].age);

  qsort(( void *)data, 4, sizeof(data[0]), employee_sort);

  printf("%s: name:%s age:%d\n", data[0].no, data[0].name, data[0].age);
  printf("%s: name:%s age:%d\n", data[1].no, data[1].name, data[1].age);
  printf("%s: name:%s age:%d\n", data[2].no, data[2].name, data[2].age);
  printf("%s: name:%s age:%d\n", data[3].no, data[3].name, data[3].age);

  return 0;
}
