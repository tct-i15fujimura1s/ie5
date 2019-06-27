#include <stdio.h>
#include <stdlib.h>

typedef struct {
  NODE *data;
  size_t capacity;
  size_t length;
} Stack;

Stack *stack_new();
void stack_free(Stack *);
void push(Stack *s, NODE n);
void *pop(Stack *s);
void *peek(Stack *s);

typedef struct {
  enum {BIN, NUM} type;
  union {
    enum {ADD, SUB, MUL, DIV} op;
    int num;
  } data;
} NODE;

int main(int argc, char **argv) {
  if(2 > argc) {
    printf("Usage: %s SUFFIX_FILE\n", argv[0]);
    return 1;
  }
  
  FILE *fp = fopen(argv[1], "r");
  
  Stack *stack = stack_new();
  
  for(;;) {
    
  }
  
  stack_free(stack);
}
