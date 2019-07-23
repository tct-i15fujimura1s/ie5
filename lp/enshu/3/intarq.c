#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum RES_TYPE {
  FAIL = 0,
  UNI,
  BIN
}

typedef struct {
  enum RES_TYPE type;
  union {
    int i;
    struct {
      void *name;
      void *value;
    } uni;
    struct {
      void *name;
      void *left;
      void *right;
    } bin;
    Stack *stack;
  } data;
} RES;

#define IF_FAIL(r) if(FAIL == r.type)

#define CUR (__ctx->index < 0 ? '\0' : __ctx->buffer[__ctx->index])
#define STR(s) (is_str(__ctx, (s)))
#define SAVE ctx_push(__ctx)
#define LOAD (__ctx->index = ctx_pop(__ctx))
#define POP ctx_pop(__ctx)
#define BEGIN { SAVE;
#define END POP;}
#define RET POP; return (RES)
#define BIN(x, y, z) {BIN, {.bin = {x, y, z}}}
#define RET_BIN(x, y, z) RET BIN(x, y, z)
#define UNI(x, y) {UNI, {.uni = {x, y}}}
#define RET_UNI(x, y) RET UNI(x, y)
#define OR(r) IF_FAIL(r) r =
#define EXIT { LOAD; return RES_FAIL; }
#define GET(r, name) RES r = C(name); IF_FAIL(r) EXIT
#define LA lookahead(__ctx)

#define S(name) RES _##name(CTX *__ctx)
#define C(name) _##name(__ctx)


const RES RES_FAIL = {FAIL, 0};

S(stat) BEGIN
  RES r = C(assign);
  OR(r) C(input);
  OR(r) C(print);
  OR(r) C(end);
  RET r;
END;

S(assign) BEGIN
  GET(r, name);
  if('=' != CUR) EXIT;
  GET(s, expr);
  RET_BIN("=", make_ptr(rp), make_ptr(sp));
END;

S(input) BEGIN
  if(!STR("input")) EXIT;
  GET(r, name);
  RET_UNI("input", make_ptr(r));
END;

S(print) BEGIN
  if(!STR("print")) EXIT;
  GET(r, expr);
  RET_UNI("print", make_ptr(r));
END;

S(end) BEGIN
  if(!STR("end")) EXIT;
  RET_UNI("end", NULL);
END;

S(expr) BEGIN
  GET(r, term);
  for(;;) {
    if('+' != CUR && '-' != CUR) break;
    char *name = ('+' == CUR) ? "+" : "-";
    LA;
    GET(s, term);
    r = (RES) BIN(name, make_ptr(r), make_ptr(s));
  }
  return r;
END;
