#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int HASHSIZE = 30;

typedef struct employee {
  char* id;
  char* name;
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
	for (i = 0; i < 30; i++) {
		hashtable[i] = NULL;
	}

	//hashtableにテストデータを格納する
	EMPLOYEE* e1 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	e1->id = (char*)malloc(16);
	e1->name = (char*)malloc(16);
	strcpy(e1->id, "140001");
	strcpy(e1->name, "utsunomiya");
	e1->age = 27;
	
	EMPLOYEE* e2 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	e2->id = (char*)malloc(16);
	e2->name = (char*)malloc(16);
	strcpy(e2->id, "140002");
	strcpy(e2->name, "honda");
	e2->age = 25;

	EMPLOYEE* e3 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	e3->id = (char*)malloc(16);
	e3->name = (char*)malloc(16);
	strcpy(e3->id, "140003");
	strcpy(e3->name, "fushimi");
	e3->age = 26;

	h = hash(e1->name);
	hashtable[h] = e1;
	h = hash(e2->name);
	hashtable[h] = e2;
	h = hash(e3->name);
	hashtable[h] = e3;

	//hashtableの中身を表示する
	for (i = 0; i < 30; i++) {
		if (hashtable[i] != NULL) {
			printf("%d : %s\n", i, hashtable[i]->name);
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
		if (hashtable[h] != NULL) {
			printf("hash: %d ", h);
			printf("value: id->%s age->%d\n\n", hashtable[h]->id, hashtable[h]->age);
		} else {
			printf("hash: %d ", h);
			printf("value: NULL \n\n");
		}
	}

	return 0;
}
