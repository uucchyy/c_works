#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int HASHSIZE = 30;

typedef struct employee {
  char id[20];
  char name[20];
  int age;
} EMPLOYEE;

int hash(char *key) {
    int n, h = 0;
    for (n = 0; key[n] != '\0'; n++) {
        h = (h * 137 + key[n]) % HASHSIZE;
		// debug code
		//printf("h = %d key[n] = %c\n", h, key[n]);
    }
    return h;
}

int main(int argc, char *argv[]) {
	//変数宣言
	int i, h = 0;
	char k[100];
	EMPLOYEE *hashtable;

	//hashtableとなる配列のメモリを動的確保
	hashtable = (EMPLOYEE*)malloc(sizeof(EMPLOYEE) * 30);
	
	//初期化
	memset(k, '\0', strlen(k));

	//hashtableにテストデータを格納する
	h = hash("utsunomiya\0");
	strcpy(hashtable[h].id, "140001");
	strcpy(hashtable[h].name, "utsunomiya");
	hashtable[h].age = 27;

	h = hash("honda\0");
	strcpy(hashtable[h].id, "140002");
	strcpy(hashtable[h].name, "honda");
	hashtable[h].age = 25;
	
	h = hash("fushimi\00");
	strcpy(hashtable[h].id, "140003");
	strcpy(hashtable[h].name, "fushimi");
	hashtable[h].age = 26;
	
	//hashtableの中身を表示する
	for (i = 0; i < 30; i++) {
		if (hashtable[i].id != NULL) {
			printf("%d : %s\n", i, hashtable[i].name);
		} else {
			printf("%d : NULL\n", i);
		}
	}

	//標準入力から入力した従業員名をkeyとしてhashtableから従業員情報（社員番号、年齢）を取り出し表示する
	for(;;) {
		fgets(k, sizeof(k), stdin);
		k[strlen(k) - 1] = '\0';
		printf("key: %s\n", k);
		h = hash(k);
		if (hashtable[h].id != NULL) {
			printf("hash: %d ", h);
			printf("value: id->%s age->%d\n\n", hashtable[h].id, hashtable[h].age);
		} else {
			printf("hash: %d ", h);
			printf("value: NULL \n\n");
		}
	}

	//メモリの解放
	free(hashtable);

	return 0;
}
