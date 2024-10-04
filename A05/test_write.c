/*----------------------------------------------
 * Author: Emma Yu
 * Date: 10/03/2024
 * Description
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include "read_ppm.c"
#include "write_ppm.c"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  write_ppm("test.ppm", pixels, w, h);
  free(pixels);

  pixels = read_ppm("test.ppm", &w, &h);

  printf("Testing file test.ppm: %d %d\n", w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel* pixel = &pixels[i * w + j];
      printf("(%d, %d, %d) ", pixel->red, pixel->green, pixel->blue);
      }
      printf("\n");
      }

  free(pixels); 
  return 0;
}
