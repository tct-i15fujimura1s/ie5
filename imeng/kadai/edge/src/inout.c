
//_/_/_/_/_/_/_/_/_/_/ inout.c /_/_/_/_/_/_/_/_/_/_/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "pnm.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: %s [options] src.pnm dst.pnm", *argv);
    printf(
      "Options:\n"
      "  -p N       output as PN format\n"
      "  -s N       scale N times\n"
      "  -m N       set max=N\n"
    );
    return 0;
  }

  int desc = -1;
  int scale = 1;
  int max = -1;

  int opt;
  while((opt = getopt(argc, argv, "p:s:m:")) != -1) {
    switch(opt) {
      case 'p':
        desc = atoi(optarg);
        break;
      case 's':
        scale = atoi(optarg);
        break;
      case 'm':
        max = atoi(optarg);
        break;
      default:
        return -1;
    }
  }

  if(scale < 1) {
    fprintf(stderr, "Error: scale must be larger than 0\n");
    return -1;
  }

  PNM pnm;
  const char *err;

  char *fileIn = argv[optind], *fileOut = argv[optind+1];

  FILE *rfp = fopen(fileIn, "rb");
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

  printf("Loaded: %s > %d Bytes\n", fileIn, rbytes);
  pnmDetails(&pnm, "  ");


  if(desc<0) desc = pnm.descriptor;
  if(max<0) max = pnm.max;

  PNM outpnm;

  if((err = initPNM(&outpnm, desc, pnm.width * scale, pnm.height * scale, max))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }

  for(int x=0; x<pnm.width; x++) for(int y=0; y<pnm.height; y++) {
    int s = getPxPNM(&pnm, x, y) * max / pnm.max;
    for(int dx=0; dx<scale; dx++) for(int dy=0; dy<scale; dy++) {
      setPxPNM(&outpnm, x*scale+dx, y*scale+dy, s);
    }
  }

  freePNM(&pnm);

  FILE *wfp = fopen(fileOut, "wb");
  if(!wfp) {
    perror("fopen");
    return -1;
  }
  if ((err = writePNM(&outpnm, wfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int bytes = ftell(rfp);
  fclose(rfp);

  printf("Wrote: %s < %d Bytes\n", fileOut, bytes);
  pnmDetails(&outpnm, "  ");

  freePNM(&outpnm);

  return 0;
}
