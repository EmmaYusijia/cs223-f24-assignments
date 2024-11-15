#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

pthread_mutex_t mutex;
pthread_barrier_t mybarrier;

struct thread_data {
  int thread_id;
  int row_offset;
  int col_offset;
  struct ppm_pixel* pixel;
  int* membership;
  int* count;
};

void *buddhabrot(void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 250;
  int size = 2480; 
  int subsize = size/2;
  int row = data->row_offset;
  int col = data->col_offset;
  int max = 0;

  for (int i = row; i < row+subsize; i++) {
    for (int j = col; j < col+subsize; j++) {
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
      if (iter < maxIterations){
        data->membership[i*size+j] = 0;
      }else{
        data->membership[i*size+j] = 1;
      }
    }
  }

  for (int i = row; i < row+subsize; i++) {
    for (int j = col; j < col+subsize; j++) {
      if (data->membership[i*size+j] == 1) continue;

      float xfrac = (float)i / size;
      float yfrac = (float)j / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      while (x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;

        int yrow = round(size * (y - ymin)/(ymax - ymin));
        int xcol = round(size * (x - xmin)/(xmax - xmin));
        if (yrow < 0 || yrow >= size) continue; 
        if (xcol < 0 || xcol >= size) continue; 
        pthread_mutex_lock(&mutex);
        data->count[yrow*size + xcol] += 1;
        pthread_mutex_unlock(&mutex);
      }
    }
  }

  pthread_barrier_wait(&mybarrier);
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(data->count[i*size+j] > max){
        max = data->count[i*size+j];
      }
    }
  }
  float gamma = 0.681;
  float factor = 1.0/gamma;
  for (int i = row; i < row+subsize; i++){
   for (int j = col; j < col+subsize; j++){
      float value = 0;
      if (data->count[i*size+j] > 0){
        value = (float)log(data->count[i*size+j]) / log(max);
        value = (float)pow(value, factor);
      }
      data->pixel[i*size+j].red = value * 255;
      data->pixel[i*size+j].green = value * 255;
      data->pixel[i*size+j].blue = value * 255;
   }
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  char filename[100];
  int size = 2480;
  int subsize = size/2;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
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
  printf("Generating buddhabrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  struct ppm_pixel* pixels = (struct ppm_pixel*)malloc((size) * (size) * sizeof(struct ppm_pixel));
  int* memberships = malloc((size*size) * sizeof(int));
  int* counts = malloc((size*size) * sizeof(int));
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      counts[i+j*size] = 0;
    }
  }
  pthread_t* threads = malloc(numProcesses * sizeof(pthread_t));
  struct thread_data* data = (struct thread_data*)malloc(numProcesses * sizeof(struct thread_data));
  pthread_mutex_init(&mutex,NULL);
  pthread_barrier_init(&mybarrier,NULL,numProcesses);
  for (int i = 0; i < numProcesses; i++) {
    data[i].thread_id = i;
    data[i].pixel = pixels;
    data[i].membership = memberships;
    data[i].count = counts;
    data[i].row_offset = (i / 2) * subsize;
    data[i].col_offset = (i % 2) * subsize;
    pthread_create(&threads[i], NULL, buddhabrot, (void*) &data[i]);
    printf("Thread %lu) ", (unsigned long) threads[i]);
    printf("sub-image block: cols (%d, %d) to rows (%d,%d)\n", data[i].col_offset, data[i].col_offset+size/2, data[i].row_offset, data[i].row_offset+size/2);
  }
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    printf("Thread %lu) finished\n", (unsigned long) threads[i]);
  }
  gettimeofday(&tend, NULL);
  float timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n", size, size, timer);
  sprintf(filename, "buddhabrot-%d-%ld.ppm", size, time(0));
  write_ppm(filename,pixels,size,size);
  free (threads);
  free (data);
  free(pixels);
  free (memberships);
  free(counts);
  pthread_mutex_destroy(&mutex);
  pthread_barrier_destroy(&mybarrier);
  return 0;
}
