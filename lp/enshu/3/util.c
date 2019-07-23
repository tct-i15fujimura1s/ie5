#include "util.h"

typedef struct {
  void *stack;
  size_t unit;
  size_t size;
  size_t length;
} Stack;

Stack *Stack_new(size_t unit) {
  Stack *stack = (Stack *) malloc(sizeof(Stack));
  stack->stack = malloc(unit * 16);
  stack->unit = unit;
  stack->size = 16;
  stack->length = 0;
  return stack;
}

void Stack_free(Stack *stack) {
  free(stack->stack);
  free(stack);
}

void Stack_push(Stack *stack, void *element) {
  if(stack->length == stack->size) {
    stack->size *= 2;
    stack->stack = realloc(unit * stack->size);
  }
  memcpy(stack + stack->unit * stack->length, element, stack->unit);
  stack->length += 1;
}

void *Stack_pop(Stack *stack) {
  if(stack->length <= 0) {
    return NULL;
  }
  stack->length -= 1;
  return stack->stack + stack->unit * stack->length;
}

typedef struct {
  FILE *input;
  char *buffer;
  size_t bufsize;
  size_t length;
  int index;
  Stack *stack;
} CTX;

void ctx_init(CTX *ctx, FILE *input) {
  ctx->input = input;
  ctx->buffer = (char *) malloc(16);
  ctx->bufsize = 16;
  ctx->length = 1;
  ctx->index = 0;
  ctx->stack = Stack_new(sizeof(int));
}

void ctx_push(CTX *ctx) {
  Stack_push(ctx->stack, ctx->index);
}

int ctx_pop(CTX *ctx) {
  return *(int *) Stack_pop(ctx->stack);
}

void lookahead(CTX *ctx) {
  ctx->index += 1;
  if(ctx->index < ctx->length) return;
  if(ctx->length >= ctx->bufsize) {
    ctx->bufsize *= 2;
    ctx->buffer = (char *) realloc(ctx->buffer, ctx->bufsize);
  }
  int c = fgetc(ctx->input);
  if(c < 0) {
    ctx->index = -1;
    return;
  }
  ctx->buffer[ctx->length] = c;
  ctx->length += 1;
}

RES *make_ptr(RES *rq) {
  RES *rp = (RES *) malloc(sizeof(RES));
  memcpy(rp, rq, sizeof(RES));
  return rp;
}

int is_str(CTX *ctx, char *s) {
  PUSH;
  for(;;) {
    if(NULL == *s) return 1;
    if(CUR != *s) break;
  }
}
