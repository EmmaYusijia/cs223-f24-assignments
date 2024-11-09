#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct thread_data {
  int thread_id;
  int row_offset;
  int col_offset;
  struct ppm_pixel* pixel;
};

void *mandelbrot(void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 250;
  int size = 480; 
  struct ppm_pixel* palette = (struct ppm_pixel*)malloc((maxIterations) * sizeof(struct ppm_pixel));
  int row = data->row_offset;
  int col = data->col_offset;
  srand(time(0));
  for(int i = 0; i < 250; i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }
  for (int i = row; i < row+size/2; i++) {
    for (int j = col; j < col+size/2; j++) {
      float xfrac = (float)i / size;
      float yfrac = (float)j / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;
      while (iter < 250 && x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if (iter < 250){
        data->pixel[j*size+i] = palette[iter];
      }
      else{
        data->pixel[j*size+i].red = 0;
        data->pixel[j*size+i].green = 0;
        data->pixel[j*size+i].blue = 0;
      }
      }
    }
  free (palette);
  return NULL;
}

int main(int argc, char* argv[]) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  char filename[100]; 
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);
  struct ppm_pixel* pixels = (struct ppm_pixel*)malloc((size) * (size) * sizeof(struct ppm_pixel));
  pthread_t* threads = malloc(numProcesses * sizeof(pthread_t));
  struct thread_data* data = (struct thread_data*)malloc(numProcesses * sizeof(struct thread_data));
  int subsize = size/2;
  for (int i = 0; i < numProcesses; i++) {
    data[i].thread_id = i;
    data[i].pixel = pixels;
    data[i].row_offset = (i / 2) * subsize;
    data[i].col_offset = (i % 2) * subsize;
    pthread_create(&threads[i], NULL, mandelbrot, (void*) &data[i]);
    printf("Thread %lu) ", (unsigned long) threads[i]);
    printf("sub-image block: cols (%d, %d) to rows (%d,%d)\n", data[i].col_offset, data[i].col_offset+size/2, data[i].row_offset, data[i].row_offset+size/2);
  }
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    printf("Thread %lu) finished\n", (unsigned long) threads[i]);
  }
  gettimeofday(&tend, NULL);
  float timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size, timer);
  sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));
  write_ppm(filename,pixels,size,size);
  free (threads);
  free (data);
  free(pixels);
  return 0;
}
