/*----------------------------------------------
 * Author: Emma Yu
 * Date: 10/03/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "read_ppm.c"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (pixels == NULL) {
    printf("Failed to read the PPM file.\n");
    return 1;
    }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
      }
    printf("\n");
    }

  free(pixels);
  return 0;
}

