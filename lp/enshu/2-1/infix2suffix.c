/*
文法
term -> factor {("+" | "-") factor}
factor -> primary {("*" | "-") primary}
primary -> num | "(" term ")"
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NIL, ADD, SUB, MUL, DIV, NUM
} NODE_TYPE;

typdef struct {
  NODE_TYPE type;
  union {
    struct {
      NODE *left;
      NODE *right;
    } bin;
    int num;
  } param;
} Node;

void lookahead();

NODE *_term();
NODE *_factor();
NODE *_primary();

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
  _term();
}

NODE *_term() {
  NODE *n = _factor();
  for(;;) {
    switch(token) {
      case 
    }
  }
}
