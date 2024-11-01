/*----------------------------------------------
 * Author: Emma Yu 
 * Date: 10/03/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error: Could not open file %s\n", filename);
    return NULL;
    }

  char format[4]; 
  fgets(format, sizeof(format), file); 

  char buffer[100];
  fgets(buffer, sizeof(buffer), file);

  fscanf(file, "%d %d", w, h);

  int max_value;
  fscanf(file, "%d", &max_value);

  fgetc(file);
  struct ppm_pixel* pixels = (struct ppm_pixel*)malloc((*w) * (*h) * sizeof(struct ppm_pixel));
  if (pixels == NULL) {
    printf("Error: Memory allocation failed\n");
    fclose(file);
    return NULL;
    }

  fread(pixels, sizeof(struct ppm_pixel), *w * *h, file);
  fclose(file);
  return pixels; 
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
