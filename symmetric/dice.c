#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int sort(int *dice_number, int *result);

int
main(int argc, char *argv[])
{
  int i, num;
  int result[2][6] = {{1,2,3,4,5,6},{0}};

  i = 0;
  srand((unsigned int)time(NULL));
  num = 0;

  for (i = 0; i < 10000; i++) {
    num = rand() % 6;
    result[1][num] = result[1][num] + 1;
  }

  printf("Random number generation result.\n");
  for (i = 0; i < 6; i++) {
    printf("dice_number %d: %d\n", result[0][i], result[1][i]);
  }

  sort(result[0], result[1]);

  printf("\nSort result.\n");
  for (i = 0; i < 6; i++) {
    printf("dice_number %d: %d\n", result[0][i], result[1][i]);
  }
  return 0;
}

int sort(int *dice_number, int *result) {

  int i = 0;
  int flg = 0;
  int tmp = 0;

  for (;;) {
    for (i = 0; i < 5; i++) { 
      if (result[i] < result[i + 1]) {
        tmp = result[i];
        result[i] = result[i + 1];
        result[i + 1] = tmp;
        tmp = dice_number[i];
        dice_number[i] = dice_number[i + 1];
        dice_number[i + 1] = tmp;
        flg = 1;
      }
    }
    if (flg == 0) {
      return 0;
    } else { 
      flg = 0;
    }
  }


}
