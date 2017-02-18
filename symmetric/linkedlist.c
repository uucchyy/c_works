#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct listData {
  void* data;
  void* next;
  void* prev;
} LIST_DATA;

typedef struct employee {
    char* id;
    char* name;
} EMPLOYEE;

LIST_DATA* createList(void* data) {
    LIST_DATA* tmp = malloc(sizeof(LIST_DATA));
    tmp->data = data;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

void addList(LIST_DATA* prev, LIST_DATA* target) {
    LIST_DATA* tmp = prev->next;
    prev->next = target;
    target->next = tmp;
    target->prev = prev;
    if (tmp != NULL) {
      tmp->prev = target;
    }
}

void deleteList(LIST_DATA* target) {
   LIST_DATA* next = target->next;
   LIST_DATA* prev = target->prev;
   next->prev = prev;
   prev->next = next;
   free(target);
}

int main(int argc, char* args [], char* env []) {
 
    LIST_DATA* head = createList(NULL);
    LIST_DATA* tail = createList(NULL);
    addList(head, tail);
 
    EMPLOYEE* e1 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
    e1->id = (char*)malloc(16);
    e1->name = (char*)malloc(16);
    strcpy(e1->id, "111111");
    strcpy(e1->name, "utsunomiya");

    EMPLOYEE* e2 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
    e2->id = (char*)malloc(16);
    e2->name = (char*)malloc(16);
    strcpy(e2->id, "222222");
    strcpy(e2->name, "fushimi");

    EMPLOYEE* e3 = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
    e3->id = (char*)malloc(16);
    e3->name = (char*)malloc(16);
    strcpy(e3->id, "333333");
    strcpy(e3->name, "honda");

    LIST_DATA* new = createList(e1);
    LIST_DATA* new2 = createList(e2);
    LIST_DATA* new3 = createList(e3);

    addList(head, new);
    addList(new, new2);
    addList(new2, new3);

    deleteList(new2);

    LIST_DATA* tmp;
    tmp = head->next;

    int i;
    EMPLOYEE* eData;
    for (i = 0; i < 100; i++) {
      if (tmp->data == NULL) {
        break;
      }
      eData = tmp->data;
      printf("id:%d %s\n", i, eData->id);
      printf("name:%d %s\n", i, eData->name);
      tmp = tmp->next;
    }

    return 0;

}
