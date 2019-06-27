#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) /* debug(__VA_ARGS__) */
#endif

#define TRUE 1
#define FALSE 0

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

int input(Stack *s, FILE *fp);

int main(int argc, char **argv) {
  if(2 > argc) {
    printf("Usage: %s SUFFIX_FILE\n", argv[0]);
    return 1;
  }
  
  FILE *fp = fopen(argv[1], "r");
  
  Stack *stack = stack_new();
  
  for(;;) {
    if(!input(stack, fp)) break;
    
    if(peek(stack, 1)->type == BIN && peek(stack, 2)->type == NUM && peek(stack, 3)->type == NUM) {
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
      
      NODE n;
      n.type = NUM;
      n.data.num = num;
      push(stack, n);
    }
  }
  
  if(peek(stack, 1)->type == NUM) {
    printf("= %d\n", pop(stack).data.num);
  }
  
  stack_free(stack);
  
  return 0;
}

int input(Stack *s, FILE *fp) {
  int c;
  while(' ' == (c = fgetc(fp)));
  if(c < 0) return FALSE;
  
  NODE node;
  switch(c) {
    case '+': case '-': case '*': case '/':
      node.type = BIN;
      node.data.op = c;
      break;
    default:
      if(!isdigit(c)) return FALSE;
      node.type = NUM;
      int num = 0;
      while(isdigit(c = fgetc(fp))) num = (num * 10) + (c - '0');
      node.data.num = num;
  }
  push(s, node);
  
  return TRUE;
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
