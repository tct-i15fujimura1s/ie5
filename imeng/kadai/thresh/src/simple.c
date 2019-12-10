
//_/_/_/_/_/_/_/_/_/_/ simple.c /_/_/_/_/_/_/_/_/_/_/
#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"

int main(int argc, char** argv) {
  if (argc < 4) {
    printf(
      "Usage: %s <threshold> src.pnm dst.pnm\n", *argv);
    return 1;
  }

  const int thresh = atoi(argv[1]);
  char * const srcFile = argv[2];
  char * const dstFile = argv[3];

  PNM src;
  const char *err;

  FILE *rfp = fopen(srcFile, "rb");
  if(!rfp) {
    perror("fopen");
    return -1;
  }
  if((err = readPNM(&src, rfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int rbytes = ftell(rfp);
  fclose(rfp);

  printf("Loaded: %s > %d Bytes\n", srcFile, rbytes);
  pnmDetails(&src, "  ");


  PNM dst;
  if((err = initPNM(&dst, 5, src.width, src.height, src.max))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }

  for(int y=0; y<src.height; y++) {
    for(int x=0; x<src.width; x++) {
      int bin = 0;
      if (getPxPNM(&src, x, y) >= thresh) bin = dst.max;
      setPxPNM(&dst, x, y, bin);
    }
  }

  freePNM(&src);


  FILE *wfp = fopen(dstFile, "wb");
  if(!wfp) {
    perror("fopen");
    return -1;
  }
  if ((err = writePNM(&dst, wfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int bytes = ftell(rfp);
  fclose(rfp);

  printf("Wrote: %s < %d Bytes\n", dstFile, bytes);
  pnmDetails(&dst, "  ");

  freePNM(&dst);

  return 0;
}
