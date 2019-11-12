
//_/_/_/_/_/_/_/_/_/_/ median.c /_/_/_/_/_/_/_/_/_/_/
#include <stdio.h>
#include "pnm.h"

void sort(int *array, int size) {
  for(int i=0; i<size-1; i++) {
    int minI=i;
    for(int j=i+1;j<size;j++)
      if (array[minI]>array[j]) minI=j;
    int tmp=array[i];
    array[i]=array[minI];
    array[minI]=tmp;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf(
      "Usage: %s src.pnm dst.pnm\n", *argv);
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
  pnmDetails(&pnm, "  ");


  PNM avg;
  if((err = initPNM(&avg, 5, pnm.width, pnm.height, pnm.max))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }

  int array[9];

  for(int y=0; y<pnm.height; y++) {
    for(int x=0; x<pnm.width; x++) {
      int i=0;
      for(int dx=-1; dx<=1; dx++) {
        for(int dy=-1; dy<=1; dy++) {
          array[i++] = getPxPNM(&pnm, x+dx, y+dy);
        }
      }
      sort(array, 9);
      setPxPNM(&avg, x, y, array[4]);
    }
  }

  freePNM(&pnm);


  FILE *wfp = fopen(argv[2], "wb");
  if(!wfp) {
    perror("fopen");
    return -1;
  }
  if ((err = writePNM(&avg, wfp))) {
    fprintf(stderr, "Error: %s\n", err);
    return -1;
  }
  int bytes = ftell(rfp);
  fclose(rfp);

  printf("Wrote: %s < %d Bytes\n", argv[2], bytes);
  pnmDetails(&avg, "  ");

  freePNM(&avg);

  return 0;
}
