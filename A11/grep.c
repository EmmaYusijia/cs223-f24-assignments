#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

struct thread_data {
  int tid;
  char *target;
  char **files;
  int start_index;
  int end_index;
};

void *keyword(void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  int counter = 0;
  for(int i = data->start_index; i < data->end_index; i++){
    FILE *file = fopen(data->files[i], "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      char const* pos = strstr(buffer, data->target);
      if (pos){
        printf("%d) %s: %s", data->tid, data->files[i], buffer);
        counter += 1;
      }
    }
    fclose(file);
  }
  return (void *)(intptr_t)counter;
}

int main(int argc, char *argv[]) {
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  if (argc < 4) {
    fprintf(stderr, "Usage: ./grep <NumThreads> <Keyword> <Files>\n");
    return 1;
  }
  int fileNum = argc - 3;
  printf("Searching %d files for keyword: %s\n", fileNum, argv[2]);
  char** files = (char**)malloc(fileNum * sizeof(char*));
  for(int i = 3; i < 3 + fileNum; i++){
    files[i-3] = argv[i];
  }
  int numProcesses = atoi(argv[1]);
  int* sub = (int*)malloc(numProcesses * sizeof(int));
  for(int i = 0; i < numProcesses; i++){
    if(i == 0){
      sub[i] = (fileNum + numProcesses - 1) / numProcesses;
    }else{
      sub[i] = fileNum / numProcesses;
    }
  }
  char *word = argv[2];
  pthread_t* threads = malloc(numProcesses * sizeof(pthread_t));
  struct thread_data* data = (struct thread_data*)malloc(numProcesses * sizeof(struct thread_data));
  for (int i = 0; i < numProcesses; i++) {
    data[i].tid = i;
    data[i].target = word;
    data[i].files = files;
    if(i == 0){
      data[i].start_index = 0;
      data[i].end_index = sub[i] - 1;
    }else{
      data[i].start_index = data[i-1].end_index + 1;
      data[i].end_index = data[i].start_index + sub[i] - 1;
    }
    pthread_create(&threads[i], NULL, keyword, (void*) &data[i]);
    printf("Thread %d searching %d files (%d to %d)\n", i, sub[i], data[i].start_index+3, data[i].end_index+3);
  }
  for (int i = 0; i < numProcesses; i++) {
    void *thread_result;
    pthread_join(threads[i], &thread_result);
    int result = (int)(intptr_t)thread_result;
    printf("Thread %d found %d lines containing keyword: %s\n", i, result, word);
  }
  gettimeofday(&tend, NULL);
  float timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Elapsed time is %f\n", timer);
  free (threads);
  free (data);
  free (files);
  free (sub);
  return 0;
}
