#ifndef __PNM_H
#define __PNM_H

typedef struct {
  int descriptor;
  int width;
  int height;
  int max;
  int count;
  unsigned short *data;
} PNM;

// NULL -> success, otherwise -> error
const char *readPNMHeader(FILE *fp, PNM *pnm);
const char *readPNM(FILE *fp, PNM *pnm);
void freePNM(PNM *pnm);

#endif
