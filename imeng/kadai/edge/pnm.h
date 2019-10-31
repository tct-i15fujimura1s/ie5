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
const char *initPNM(PNM *pnm, int descriptor, int width, int height, int max);
const char *readPNMHeader(PNM *pnm, FILE *fp);
const char *readPNM(PNM *pnm, FILE *fp);
const char *writePNMHeader(const PNM *pnm, FILE *fp);
const char *writePNM(const PNM *pnm, FILE *fp);
const char *copyPNM(const PNM *src, PNM *dst);
const char *freePNM(PNM *pnm);

void pnmDetails(const PNM *pnm, const char *indent);

int getPxPNM(PNM *pnm, int x, int y);
void setPxPNM(PNM *pnm, int x, int y, int value);

#endif
