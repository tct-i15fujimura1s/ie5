/*
文法
term -> factor {("+" | "-") factor}
factor -> primary {("*" | "-") primary}
primary -> num | "(" term ")"
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
  NIL, ADD, SUB, MUL, DIV, NUM
} NODE_TYPE;

typedef struct {
  NODE_TYPE type;
  union {
    struct {
      void *left;
      void *right;
    } bin;
    int num;
  } param;
} NODE;

void lookahead();

NODE *_term();
NODE *_factor();
NODE *_primary();
NODE *_num();

void print_suffix(NODE *tree);

int token;

FILE *fp;

int main(int argc, char **argv) {
  if(2 > argc) {
    printf("Usage: %s INFIX_FILE\n", argv[0]);
    exit(1);
  }
  
  fp = fopen(argv[1], "r");
  if(NULL == fp) {
    perror("fopen");
    exit(1);
  }
  
  // 文法解析
  lookahead();
  NODE *n = _term();
  
  // 出力
  print_suffix(n);
}

NODE *_term() {
  NODE *n = _factor();
  if(!n) return NULL;
  for(;;) {
    NODE_TYPE nt;
    switch(token) {
      case '+': nt = ADD; break;
      case '-': nt = SUB; break;
      default: return n;
    }
    lookahead();
    NODE *n2 = _factor();
    if(!n2) return NULL;
    NODE *nn = (NODE *) malloc(sizeof(NODE));
    nn->type = nt;
    nn->param.bin.left = n;
    nn->param.bin.right = n2;
    n = nn;
  }
}

NODE *_factor() {
  NODE *n = _primary();
  if(!n) return NULL;
  for(;;) {
    NODE_TYPE nt;
    switch(token) {
      case '*': nt = MUL; break;
      case '/': nt = DIV; break;
      default: return n;
    }
    lookahead();
    NODE *n2 = _primary();
    if(!n2) return NULL;
    NODE *nn = (NODE *) malloc(sizeof(NODE));
    nn->type = nt;
    nn->param.bin.left = n;
    nn->param.bin.right = n2;
    n = nn;
  }
}

NODE *_primary() {
  NODE *n = _num();
  if(n) return n;
  if('(' != token) return NULL;
  lookahead();
  n = _term();
  if(!n || ')' != token) return NULL;
  return n;
}

NODE *_num() {
  int num = 0;
  if(!isdigit(token)) return NULL;
  for(;;) {
    num = (num * 10) + (token - '0');
    lookahead();
    if(!isdigit(token)) {
      NODE *n = (NODE *) malloc(sizeof(NODE));
      n->type = NUM;
      n->param.num = num;
      return n;
    }
  }
}

void print_suffix(NODE *node) {
  char *op;
  switch(node->type) {
    case ADD: op = "+"; goto bin;
    case SUB: op = "-"; goto bin;
    case MUL: op = "*"; goto bin;
    case DIV: op = "/"; goto bin;
    case NUM: goto num;
    default: printf("(error)"); return;
  }
num:
  printf("%d", node->param.num);
  goto fin;
bin:
  print_suffix((NODE *) node->param.bin.left);
  printf(" ");
  print_suffix((NODE *) node->param.bin.right);
  printf(" %s", op);
  goto fin;
fin:
  free(node);
}
