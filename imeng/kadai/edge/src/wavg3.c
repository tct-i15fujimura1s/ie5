
//_/_/_/_/_/_/_/_/_/_/ wavg3.c /_/_/_/_/_/_/_/_/_/_/
#include <stdio.h>
#include "pnm.h"

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

  for(int y=0; y<pnm.height; y++) {
    for(int x=0; x<pnm.width; x++) {
      int sum=0;
      sum += 27*getPxPNM(&pnm, x  , y  );

      sum += 22*getPxPNM(&pnm, x  , y+1);
      sum += 22*getPxPNM(&pnm, x+1, y  );
      sum += 22*getPxPNM(&pnm, x  , y-1);
      sum += 22*getPxPNM(&pnm, x-1, y  );

      sum += 17*getPxPNM(&pnm, x+1, y+1);
      sum += 17*getPxPNM(&pnm, x+1, y-1);
      sum += 17*getPxPNM(&pnm, x-1, y+1);
      sum += 17*getPxPNM(&pnm, x-1, y-1);

      sum +=  7*getPxPNM(&pnm, x  , y+2);
      sum +=  7*getPxPNM(&pnm, x+2, y  );
      sum +=  7*getPxPNM(&pnm, x  , y-2);
      sum +=  7*getPxPNM(&pnm, x-2, y  );

      sum +=-13*getPxPNM(&pnm, x+2, y+2);
      sum +=-13*getPxPNM(&pnm, x+2, y-2);
      sum +=-13*getPxPNM(&pnm, x-2, y+2);
      sum +=-13*getPxPNM(&pnm, x-2, y-2);

      sum +=  2*getPxPNM(&pnm, x+1, y+2);
      sum +=  2*getPxPNM(&pnm, x+2, y+1);
      sum +=  2*getPxPNM(&pnm, x+1, y-2);
      sum +=  2*getPxPNM(&pnm, x-2, y+1);

      sum +=  2*getPxPNM(&pnm, x+2, y+1);
      sum +=  2*getPxPNM(&pnm, x+1, y+2);
      sum +=  2*getPxPNM(&pnm, x+2, y-1);
      sum +=  2*getPxPNM(&pnm, x-1, y+2);
      setPxPNM(&avg, x, y, sum/175);
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
