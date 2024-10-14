/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    char output_filename[256];
    char *dot = strrchr(filename, '.');
    if (dot) {
        // Copy the part of the filename before the dot
        strncpy(output_filename, filename, dot - filename);
        output_filename[dot - filename] = '\0'; // Null-terminate the string
        strcat(output_filename, "-encoded.ppm"); // Append "-encoded.ppm"
    }
    FILE* file = fopen(output_filename, "wb");
    fprintf(file, "P6\n");
    fprintf(file, "#Created by write_ppm function\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n"); 
    for (int i = 0; i < w * h; i++) {
        fwrite(&pixels[i], sizeof(struct ppm_pixel), 1, file);
    }
    fclose(file);
    printf("Writing file %s\n", output_filename);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
