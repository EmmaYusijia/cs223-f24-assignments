#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n");
    fprintf(file, "#Created by write_ppm function\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n"); 
    for (int i = 0; i < w * h; i++) {
        fwrite(&pixels[i], sizeof(struct ppm_pixel), 1, file);
    }
    fclose(file);
    printf("Writing file: %s\n", filename);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
}
