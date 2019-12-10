
//_/_/_/_/_/_/_/_/_/_/ mode.c /_/_/_/_/_/_/_/_/_/_/
#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    printf(
      "Usage: %s src.src dst.pnm\n", *argv);
    return 1;
  }

  char * const srcFile = argv[1];
  char * const dstFile = argv[2];

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

  // ヒストグラム作成
  int values[src.max+1];
  for(int y=0; y<src.height; y++) {
    for(int x=0; x<src.width; x++) {
      values[getPxPNM(&src, x, y)]++;
    }
  }

  // 積分
  int radius = 25;
  int intvals[src.max+1];
  for(int i=0; i<=src.max; i++) {
    int val = 0;
    for(int k = 0; k < 13; k++) {
      int j = i + k - radius / 2;
      if(j<0) j = 0;
      else if(j>src.max) j = src.max;
      val += values[j];
    }
    intvals[i] = val;
  }

  // 左の山を探す
  int li=0;
  for(int i=1; i<=src.max; i++) {
    int sub = intvals[li]-intvals[i];
    if(sub<0) li = i;
    else if(sub>0) break;
  }

  // 右の山を探す
  int ri=0;
  for(int i=src.max; i>=0; i--) {
    int sub = intvals[ri]-intvals[i];
    if(sub<0) ri = i;
    else if(sub>0) break;
  }

  // // 谷を探す
  // int vi=li;
  // for(int i=li+1; i<=ri; i++) {
  //   int sub = intvals[vi]-intvals[i];
  //   if(sub>0) vi=i;
  //   else if(sub>0) break;
  // }

  int vi = (li + ri) / 2;
  printf("left=%d, right=%d, valley=%d\n", li, ri, vi);

  int thresh = vi;

  // 二値化
  for(int y=0; y<src.height; y++) {
    for(int x=0; x<src.width; x++) {
      int val = 0;
      if(getPxPNM(&src, x, y)>=thresh) val = dst.max;
      setPxPNM(&dst, x, y, val);
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
