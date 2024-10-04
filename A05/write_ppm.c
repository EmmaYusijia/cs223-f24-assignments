/*----------------------------------------------
 * Author: Emma Yu
 * Date: 10/03/2024
 * Description
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE* file = fopen(filename, "wb");
    fprintf(file, "P6\n");
    fprintf(file, "#Created by write_ppm function\n");
    fprintf(file, "%d %d\n", w, h);
    fprintf(file, "255\n"); 
    fwrite(pixels, sizeof(struct ppm_pixel), w * h, file);
    fclose(file);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
