#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct {
  void* data;
  void* parent; /*親要素へのポインタ*/
  void* children; /*子要素のポインタ*/
  int depth; /*階層*/
  void* sibling; /*兄弟要素へのポインタ*/
} NODE;

typedef struct {
  char* tagname; /* 要素名 */
} ELEM;

NODE* createNode(ELEM* data, int d) {
    NODE* n = malloc(sizeof(NODE));
    n->data = data;
    n->parent = NULL;
    n->children = NULL;
    n->sibling = NULL;
    n->depth = d;
    return n;
}

ELEM* createElem(char* name) {
    ELEM* e = malloc(sizeof(ELEM));
    e->tagname = (char*)malloc(sizeof(name));
    strcpy(e->tagname, name);
    return e;
}

void appendChildNode(NODE* parent, NODE* child) {
    child->parent = parent;
    parent->children = child;
}

void appendSiblingNode(NODE* prev, NODE* next) {
    prev->sibling = next;
}

static NODE* parse_html(const char* path, NODE* nodelist[]);
static void printTagName(NODE *n);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    // 初期化
    int i;
    int j;
    NODE* doc = NULL;
    ELEM* tmp;

    // メモリ開放時に使用するポインタリスト
    NODE* nodelist[1000];

    // ファイル読み込み
    for (i = 1; i < argc; i++) {
      doc = parse_html(argv[i], nodelist);
    }

    // タグ一覧出力
    printTagName(doc);

    for(j = 0;j < 1000; j++) {
        if (nodelist[j] == NULL) {
            break;
        }
        tmp = nodelist[j]->data;
        printf("debug code free: %s\n", tmp->tagname);
        free(tmp->tagname);
        free(nodelist[j]->data);
        free(nodelist[j]);
    }
    return 0;
}

#define BUFFER_SIZE 2048

static NODE* parse_html(const char *path, NODE* nodelist[])
{
  // 変数宣言
  int fd;
  int n;
  int i, tag_i;
  int fTagNameStart;
  int depth;
  int prevDepth;
  int nodeCnt;
  char tagname[10];
  unsigned char buf[BUFFER_SIZE];
  NODE* root;
  NODE* parent;
  NODE* current;

  // 変数初期化
  fTagNameStart = 0;
  depth = 0;
  prevDepth = 0;
  nodeCnt = 0;
  memset(tagname, '\0', 10);
  root = NULL;
  parent = NULL;
  current = NULL;

  fd = open(path, O_RDONLY);
  if (fd <0) die(path);
  for (;;) {
    n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    for (i = 0; i < 200; i++) {
        if (buf[i] == '<') {
            if (buf[i + 1] == '/') {
                //HTMLタグの終了処理
                depth--;
                continue;
            } else {
                //HTMLタグの開始処理
                fTagNameStart = 1;
                tag_i = 0;
                memset(tagname, '\0', strlen(tagname));
                depth++;
                continue;
            }
        }

        if (fTagNameStart == 1) {
            if (buf[i] == ' ' || buf[i] == '>') {
                if (current != NULL) {
                    parent = current;
                }
                current = createNode(createElem(tagname), depth);
                nodelist[nodeCnt++] = current;
                if (root == NULL) {
                    root = current;
                } else {
                    appendChildNode(parent, current);
                }
                fTagNameStart = 0;
            } else {
                tagname[tag_i++] = buf[i];
            }
        }
    }
    //if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fd) < 0) die(path);

  return root;
}

static void printTagName(NODE *n) {
    ELEM* elem;
    if (n == NULL) {
        return;
    }
    for(;;) {
        elem = n->data;
        printf("tagname: %s depth: %d\n", elem->tagname, n->depth);
        if (n->children != NULL) {
            n = n->children;
        } else {
            break;
        }
    }
}

static void
die(const char *s)
{
  perror(s);
  exit(1);
}

