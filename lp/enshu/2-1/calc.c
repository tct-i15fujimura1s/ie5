#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
input -> {word}
word -> num | op
*/

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) /* debug(__VA_ARGS__) */
#endif

#define TRUE 1
#define FALSE 0

#define BUFSIZE 1023

typedef struct {
  enum {BIN, NUM} type;
  union {
    char op;
    int num;
  } data;
} NODE;

typedef struct {
  NODE *data;
  size_t capacity;
  size_t length;
} Stack;

Stack *stack_new();
void stack_free(Stack *);
void push(Stack *s, NODE n);
NODE pop(Stack *s);
NODE *peek(Stack *s, int offset);

int input(Stack *s, char *buf);

int main(int argc, char **argv) {
  FILE *fp;
  
  if(2 >= argc && strcmp("-h", argv[1]) == 0) {
    fprintf(stderr, "Usage: %s [SUFILE]\n", argv[0]);
    return 0;
  }
  
  if(2 > argc) {
    fp = stdin;
  } else {
    fp = fopen(argv[1], "r");
    if(!fp) {
      perror("fopen");
      exit(1);
    }
  }
  
  Stack *stack = stack_new();
  char buf[BUFSIZE+1];
  
  while(!feof(fp)) {
    
    if(!fgets(buf, sizeof(buf), fp)) break;
    
    int len = strlen(buf);
    if(BUFSIZE == len && buf[BUFSIZE-1] != '\n') {
      fprintf(stderr, "１行が長すぎます\n");
      continue;
    }
    
    int ofs = 0;

    while(ofs < len) {
      // 入力
      int r = input(stack, buf + ofs);
      if(0 > r) break;
      ofs += r;
      // 計算
      if(peek(stack, 1)->type == BIN && peek(stack, 2)->type == NUM && peek(stack, 3)->type == NUM) {
        // ポップ
        char op = pop(stack).data.op;
        int right = pop(stack).data.num;
        int left = pop(stack).data.num;
        int num;
        switch(op) {
          case '+': num = left + right; break;
          case '-': num = left - right; break;
          case '*': num = left * right; break;
          case '/': num = left / right; break;
          default: fprintf(stderr, "error: unknown operator: %c\n", op); exit(-1);
        }
        // プッシュ
        NODE n;
        n.type = NUM;
        n.data.num = num;
        push(stack, n);
      }
    }
    
    if(stack->length != 1) {
      fprintf(stderr, "error: (stack.length = %d) != 1\n", (int) stack->length);
    } else if(peek(stack, 1)->type != NUM) {
      fprintf(stderr, "error: stack.top isn't a number\n");
    } else {
      printf("= %d\n", pop(stack).data.num);
    }
    
#ifdef DEBUG
      printf("stack: ");
      while(stack->length) {
        NODE n = pop(stack);
        if(n.type == NUM) printf("%d ", n.data.num);
        else if(n.type == BIN) printf("%c ", n.data.op);
        else printf("(?) ");
      }
      printf("\n");
#else
      stack->length = 0;
#endif
    
  }
  
  stack_free(stack);
  
  return 0;
}

// < 0 -> error
int readnum(FILE *fp) {
  int c = fgetc(fp);
  if(0 > c || !isdigit(c)) return -1;
  int num = c - '0';
  while(0 <= (c = fgetc(fp)) && isdigit(c)) num = num * 10 + (c - '0');
  return num;
}

// < 0 -> error
int input(Stack *s, char *buf) {
  int offset = 0;
  int c;
  while(' ' == (c = buf[offset++]));
  if(c < 0) return -1;
  
  NODE node;
  switch(c) {
    case '+': case '*': case '/':
      node.type = BIN;
      node.data.op = c;
      break;
    case '-':
      c = buf[offset++];
      if(isdigit(c)) {
        int num = c - '0';
        while(0 <= (c = buf[offset++]) && isdigit(c)) num = num * 10 + (c - '0');
        node.type = NUM;
        node.data.num = -num;
      } else {
        node.type = BIN;
        node.data.op = '-';
      }
      break;
    default:
      if(isdigit(c)) {
        int num = c - '0';
        while(0 <= (c = buf[offset++]) && isdigit(c)) num = num * 10 + (c - '0');
        node.type = NUM;
        node.data.num = num;
      } else return -1;
  }
  push(s, node);
  
  return offset;
}

Stack *stack_new() {
  Stack *s = (Stack *) malloc(sizeof(Stack));
  s->capacity = 16;
  s->length = 0;
  s->data = (NODE *) malloc(sizeof(NODE) * s->capacity);
  return s;
}
void stack_free(Stack *s) {
  free(s->data);
  free(s);
}
void push(Stack *s, NODE n) {
  if(s->length + 1 > s->capacity) {
    s->capacity *= 2;
    s->data = (NODE *) realloc(s->data, sizeof(NODE) * s->capacity);
  }
  s->data[s->length] = n;
  s->length += 1;
  
  debug(n.type == NUM ? "push num %d\n" : "push op %c\n", n.type == NUM ? n.data.num : n.data.op);
}
NODE pop(Stack *s) {
  NODE n = s->data[s->length -= 1];
  debug(n.type == NUM ? "pop num %d\n" : "pop op %c\n", n.type == NUM ? n.data.num : n.data.op);
  return n;
}
NODE *peek(Stack *s, int offset) {
  return &(s->data[s->length - offset]);
}
