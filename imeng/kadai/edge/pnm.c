// Author: i15fujimura1s@tokuyama.ac.jp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pnm.h"

static void skipComments(FILE *fp) {
  int c;
  while((c = fgetc(fp)) == '#') {
    while(c != '\n') {
      c = fgetc(fp);
    }
  }
  ungetc(c, fp);
}

static void skip(FILE *fp, const char *delim) {
  int c;
  while(strchr(delim, c = fgetc(fp)));
  ungetc(c, fp);
}

static void skipDelimiters(FILE *fp) {
  int c;
  while(strchr(" \n", c = fgetc(fp)))
    if(c == '\n') skipComments(fp);
  ungetc(c, fp);
}

static int readBytesAsInt(FILE *fp, int unit) {
  int value = 0;
  for(int i = 0; i < unit; i++) {
    value <<= 8;
    value |= fgetc(fp);
  }
  return value;
}

static int readInt(FILE *fp) {
  int value = 0, c;
  while(strchr("0123456789", c = fgetc(fp)))
    value = value * 10 + (c - '0');
  ungetc(c, fp);
  return value;
}

const char *readHeader(PNM *pnm, FILE *fp) {
  skipComments(fp);
  if(fgetc(fp) != 'P') return "bad signature";
  int desc = readInt(fp);
  if(desc < 1 || desc > 6) return "invalid descriptor";
  pnm->descriptor = desc;
  skipDelimiters(fp);
  pnm->width = readInt(fp);
  skipDelimiters(fp);
  pnm->height = readInt(fp);
  if(desc == 1 || desc == 4) {
    pnm->max = 1;
  } else {
    skipDelimiters(fp);
    pnm->max = readInt(fp);
  }
  skip(fp, " ");
  if(fgetc(fp) != '\n') return "bad header line";

  pnm->count = pnm->width * pnm->height;
  if(desc == 3 || desc == 6) pnm->count *= 3;

  return NULL;
}

const char *readPNM(PNM *pnm, FILE *fp) {
  if(!pnm) return "pnm is NULL";

  const char *error;
  if((error = readHeader(pnm, fp)) != NULL) return error;
  unsigned short *data = (unsigned short *) malloc(sizeof(unsigned short) * pnm->count);
  int count = 0;
  switch(pnm->descriptor) {
    case 1:
    case 2:
    case 3:
    {
      while(count < pnm->count && !feof(fp)) {
        skipDelimiters(fp);
        data[count++] = readInt(fp);
      }
      break;
    }
    case 4:
    {
      while(count < pnm->count && !feof(fp)) {
        int b = fgetc(fp);
        for(int i = 0; i < 8; i++) data[count++] = (b & (1 << i)) != 0;
      }
      break;
    }
    case 5:
    case 6:
    {
      int unit = pnm->max < 256 ? 1 : 2;
      int length = unit * pnm->count;
      while(count < pnm->count && !feof(fp)) {
        data[count++] = readBytesAsInt(fp, unit);
      }
      break;
    }
  }
  pnm->count = count;
  pnm->data = data;

  return NULL;
}

const char *writePNMHeader(const PNM *pnm, FILE *fp) {
  if (pnm->descriptor < 1 || pnm->descriptor > 6)
    return "invalid descriptor";
  if (pnm->width < 0)
    return "negative width";
  if (pnm->height < 0)
    return "negative height";
  fprintf(fp, "P%d %d %d", pnm->descriptor, pnm->width, pnm->height);
  if (pnm->descriptor != 1 && pnm->descriptor != 4) {
    if (pnm->max < 0)
      return "negative max";
    fprintf(fp, " %d", pnm->max);
  }
  fprintf(fp, "\n");
  return NULL;
}

const char *writePNM(const PNM *pnm, FILE *fp) {
  const char *err;

  // header
  err = writePNMHeader(pnm, fp);
  if (err) return err;

  // data
  switch (pnm->descriptor) {
    case 1:
    case 2:
    case 3:
    {
      int i=0;
      for(int y=0; y<pnm->height; y++) {
        for(int x=0; x<pnm->width; x++) {
          fprintf(fp, "%d ", pnm->data[i++]);
        }
        fprintf(fp, "\n");
      }
      break;
    }
    case 4:
      for(int i=0; i<pnm->count; i+=8) {
        int c = 0;
        for(int j=0; j<8; j++) {
          if(i+j < pnm->count && pnm->data[i+j] != 0) c |= 1;
          c <<= 1;
        }
        fputc(c, fp);
      }
      break;
    case 5:
    case 6: // max<=255
      if(pnm->max<=255) {
        for(int i=0; i<pnm->count; i++) {
          unsigned char c = (unsigned char) pnm->data[i];
          fputc(c, fp);
        }
      }else {
        for(int i=0; i<pnm->count; i++) {
          unsigned short s = pnm->data[i];
          fputc((unsigned char) (s >> 8), fp);
          fputc((unsigned char) (s & 0xff), fp);
        }
      }
      break;
    default:
      return "invalid descriptor";
  }

  return NULL;
}

const char *copyPNM(const PNM *src, PNM *dst) {
  if(!src) return "src is NULL";
  if(!dst) return "dst is NULL";

  dst->descriptor = src->descriptor;
  dst->width = src->width;
  dst->height = src->height;
  dst->max = src->max;
  dst->count = src->count;

  for(int i=0; i<src->count; i++)
    dst->data[i] = src->data[i];

  return NULL;
}

const char *initPNM(PNM *pnm, int descriptor, int width, int height, int max) {
  if(descriptor<1 || descriptor>6) return "invalid descriptor";
  pnm->descriptor = descriptor;
  if(width<0) return "negative width";
  pnm->width = width;
  if(height<0) return "negative height";
  pnm->height = height;
  if(max<0) return "negative max";
  pnm->max = max;
  pnm->count = width * height;
  pnm->data = (unsigned short *) malloc(sizeof(unsigned short) * pnm->count);
  if(!pnm->data) return "couldn't allocate memory";
  return NULL;
}

const char *freePNM(PNM *pnm) {
  if(pnm->data) {
    free(pnm->data);
    pnm->data = NULL;
  }
  return NULL;
}

void pnmDetails(const PNM *pnm, const char *indent) {
  printf("%sP%d\n", indent, pnm->descriptor);
  printf("%swidth: %d\n  height: %d\n", indent, pnm->width, pnm->height);
  printf("%smax: %d\n", indent, pnm->max);
  printf("%scount: %d\n", indent, pnm->count);
}

int getPxPNM(PNM *pnm, int x, int y) {
  x = x % pnm->width;
  y = y % pnm->height;
  return pnm->data[x + y*pnm->height];
}

void setPxPNM(PNM *pnm, int x, int y, int value) {
  if(value<0) value=0;
  else if(value>pnm->max) value=pnm->max;
  x = x % pnm->width;
  y = y % pnm->height;
  pnm->data[x + y*pnm->height] = value;
}
