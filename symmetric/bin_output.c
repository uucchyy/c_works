#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char no[7]; /* 社員番号 */
  char name[32]; /* 氏名 */
  int age; /* 年齢 */
} employee;

int
main(int argc, char *argv[])
{
  FILE *fp;
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

printf("sizeof employee:%d\n", sizeof(employee));
printf("sizeof data: %d\n", sizeof(data));

  if((fp = fopen("employe.bin","wb")) != NULL){
    fwrite(data, sizeof(employee), 4, fp);
    fclose(fp);
  }

  return 0;
}
