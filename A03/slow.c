/*----------------------------------------------
 * Author: Emma Yu
 * Date: 09/19/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int pause = 0;
  char buff[32];
  printf("Pause length: ");
  scanf("%d", &pause);
  printf("Text: ");
  scanf("%s", buff);
  int size = strlen(buff) + strlen(buff) * pause;
  char *arr = malloc(sizeof(char) * (size+1));
  int marker = 0;
  for(int i = 0; i < size; i+=pause+1){
    arr[i] = buff[marker];
    for(int j = i+1; j < i+pause+1; j++){
      arr[j] = '.';
    }
    marker++;
  }
  arr[size] = '\0';
  printf("%s\n",arr);
  free(arr);
  return 0;
}
