/*
文法
term -> factor {("+" | "-") factor}
factor -> primary {("*" | "-") primary}
primary -> num | "(" term ")"
num -> natural | negative
natural -> digit {digit}
negative -> "-" natural
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 1023

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
NODE *_negative();
NODE *_natural();

void print_suffix(NODE *tree);

int token;
int offset;
FILE *rfp, *wfp;
char buf[BUFSIZE+1];

int main(int argc, char **argv) {
  if(3 > argc) {
    printf("Usage: %s INFILE SUFILE\n", argv[0]);
    exit(1);
  }
  
  // ファイルオープン
  
  rfp = fopen(argv[1], "r");
  if(NULL == rfp) {
    perror("fopen");
    exit(1);
  }
  
  wfp = fopen(argv[2], "w");
  if(NULL == wfp) {
    perror("fopen");
    exit(1);
  }
  
  // 入力
  while(!feof(rfp)) {
    if(!fgets(buf, sizeof(buf), rfp)) break;
    if(buf[sizeof(buf) - 2] != '\n') {
      fprintf(stderr, "1行の文字数が多すぎます\n");
      continue;
    }
    offset = 0;

    // 文法解析
    lookahead();
    NODE *n = _term();

    // 出力
    print_suffix(n);
    fprintf(wfp, "\n");
  }
  
  return 0;
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
  lookahead();
  return n;
}

NODE *_num() {
  NODE *n = _negative();
  if(n) return n;
  return _natural();
}

NODE *_negative() {
  if('-' != token) return NULL;
  lookahead();
  NODE *n = _natural();
  if(n) n->param.num *= -1;
  return n;
}

NODE *_natural() {
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
    default: fprintf(wfp, "?"); return;
  }
num:
  fprintf(wfp, "%d", node->param.num);
  goto fin;
bin:
  print_suffix((NODE *) node->param.bin.left);
  fprintf(wfp, " ");
  print_suffix((NODE *) node->param.bin.right);
  fprintf(wfp, " %s", op);
  goto fin;
fin:
  free(node);
}

void lookahead() {
  token = offset < BUFSIZE ? buf[offset++] : -1;
}
