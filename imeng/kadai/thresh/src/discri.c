
//_/_/_/_/_/_/_/_/_/_/ discri.c /_/_/_/_/_/_/_/_/_/_/
//参考:
//ipr20.cs.ehime-u.ac.jp/column/gazo_syori/chapter4.html
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

  int L = src.max+1;

  // ヒストグラム作成
  int count = 0;
  int hist[L];
  for(int i=0; i<L; i++) hist[i] = 0;
  for(int y=0; y<src.height; y++)
    for(int x=0; x<src.width; x++) {
      hist[getPxPNM(&src, x, y)]++;
      count++;
    }

  double mul = 1.0 / count;
  double hist_norm[L];
  for(int i=0; i<L; i++)
    hist_norm[i] = hist[i] * mul;

  double level_mean = 0;
  for(int i=0; i<L; i++)
    level_mean += i * hist_norm[i];

  double level_var = 0;
  for(int i=0; i<L; i++) {
    double d = i - level_mean + 1;
    level_var += d * d * hist_norm[i];
  }

  printf("level: mean=%f, var=%f\n", level_mean, level_var);

  double w_prev = 0;
  double u_prev = 0;
  double sigB2_max = -1;
  int k_max = -1;
  for(int k=0; k<L; k++) {
    double w = w_prev + hist_norm[k];
    w_prev = w;
    double u = u_prev + (k+1) * hist_norm[k];
    u_prev = u;
    double d = level_mean*w - u;
    double q = w * (1 - w);
    if(q==0) continue;
    double sigB2 = d*d / q;
    if ((k & 15) == 0) printf("sigB2[%d] = %f; w = %f; u = %f\n", k, sigB2, w, u);
    if(sigB2 > sigB2_max) {
      sigB2_max = sigB2;
      k_max = k;
    }
  }
  if(k_max<0) {
    printf("Error: 閾値が見つかりません\n");
    return 1;
  }

  int thresh = k_max; // 閾値
  printf("thresh = %d\n", thresh);

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
