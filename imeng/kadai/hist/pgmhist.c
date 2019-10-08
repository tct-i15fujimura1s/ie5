#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnm.h"

/*
$ cc -o pgmhist pgmhist.c pnm.c
$ ./pgmhist cup.pgm > data.txt
*/

int main(int argc, char **argv) {
  if(argc < 2) {
    fprintf(stderr,
      "PGM Histgram Tool\n"
      "Usage: %s image.pgm > data.txt\n"
    , *argv);
    return 1;
  }

  FILE *fp = fopen(argv[1], "rb");
  if(!fp) {
    perror("fopen");
    return -1;
  }

  fprintf(stderr, "fopen\n");

  PNM pnm;
  const char *error;
  if((error = readPNM(fp, &pnm)) != NULL) {
    fprintf(stderr, "PNM Error: %s\n", error);
    return -1;
  }

  fprintf(stderr, "readPNM\n");
  fprintf(stderr,
    "\twidth = %d\n"
    "\theight = %d\n"
    "\tmax = %d\n"
    "\tcount = %d\n"
    "\tdata = %p\n"
  , pnm.width, pnm.height, pnm.max, pnm.count, pnm.data);

  int *hist = (int *) calloc(pnm.max + 1, sizeof(int));
  for(int i = 0; i < pnm.count; i++) hist[pnm.data[i]]++;
  fprintf(stderr, "hist\n");

  for(int i = 0; i <= pnm.max; i++) printf("%d\n", hist[i]);
  fprintf(stderr, "complete\n");

  return 0;
}
