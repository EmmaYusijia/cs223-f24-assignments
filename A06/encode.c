/*----------------------------------------------
 * Author: Emma Yu 
 * Date: 10/13/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

void embed_message(struct ppm_pixel *pixels, int num_pixels, const char *message) {
    for (int i = 0; i < num_pixels && message[i] != '\0'; i++) {
        pixels[i].red = (pixels[i].red & ~1) | (message[i] & 1); 
        pixels[i].green = (pixels[i].green & ~1) | ((message[i] >> 1) & 1); 
        pixels[i].blue = (pixels[i].blue & ~1) | ((message[i] >> 2) & 1); 
    }
    if (strlen(message) < num_pixels) {
        pixels[strlen(message)].red = (pixels[strlen(message)].red & ~1);
        pixels[strlen(message)].green = (pixels[strlen(message)].green & ~1);
        pixels[strlen(message)].blue = (pixels[strlen(message)].blue & ~1);
    }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w, h;
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  if (pixels == NULL) {
    printf("Failed to read the PPM file.\n");
    return 1;
    }
  printf("Reading tiny_encoded.ppm with width %d and height %d", w, h);
  printf("\n");
  int num_pixels = w * h;
  int total_bits = num_pixels * 3;
  int max_chars = total_bits / 8;
  printf("Max number of characters in the image: %d\n", max_chars);
  printf("Enter a phrase:\n");
  char message[48];
  fgets(message, sizeof(message), stdin);
  embed_message(pixels, num_pixels, message);
  write_ppm(argv[1], pixels, w, h);
  free(pixels);
  return 0;
}
