#include <stdio.h>
#include "pnm.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: %s src.pnm dst.pnm", *argv);
    return 0;
  }

  PNM pnm;
  const char *err;

  FILE *rfp = fopen(argv[1], "rb");
  if(!rfp) {
    perror("fopen");
    return -1;
  }
  if((err = readPNM(&pnm, rfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int rbytes = ftell(rfp);
  fclose(rfp);

  printf("Loaded: %s > %d Bytes\n", argv[1], rbytes);
  printf("  P%d\n", pnm.descriptor);
  printf("  width: %d\n  height: %d\n", pnm.width, pnm.height);
  printf("  max: %d\n", pnm.max);
  printf("  count: %d\n", pnm.count);

  FILE *wfp = fopen(argv[2], "wb");
  if(!wfp) {
    perror("fopen");
    return -1;
  }
  if ((err = writePNM(&pnm, wfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int bytes = ftell(rfp);
  fclose(rfp);

  freePNM(&pnm);

  printf("Wrote: %s < %d Bytes\n", argv[2], bytes);

  return 0;
}
