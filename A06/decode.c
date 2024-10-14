/*----------------------------------------------
 * Author: Emma Yu
 * Date: 10/13/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w, h;
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  if (pixels == NULL) {
    printf("Failed to read the PPM file.\n");
    return 1;
    }

  printf("Reading %s with width %d and height %d", argv[1], w, h);
  printf("\n");
  int num_pixels = w * h;
  int total_bits = num_pixels * 3;
  int max_chars = total_bits / 8;
  printf("Max number of characters in the image: %d\n", max_chars);

  unsigned char *pixel_data = (unsigned char *)pixels;
  for (int i = 0; i < total_bits; i+=8) {
    unsigned char c = 0;
    for(int j = 0; j < 8; j++){
      c |= (pixel_data[i + j] & 0x1) << (7 - j);
    }
    if (c == '\0') {
      break;
    }
    printf("%c", c); 
  }

  free(pixel_data);
  return 0;
  return 0;
}

