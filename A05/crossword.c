/*----------------------------------------------
 * Author: Emma Yu 
 * Date: 10/03/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage: %s <word1> <word2>\n", argv[0]);
    exit(0);
  }
  char* word1 = argv[1];
  char* word2 = argv[2];
  bool cross = false;
  int row = -1;
  int col = -1;
  for(int i = 0; i < strlen(word1); i++){
    char ch = word1[i];
    for(int j = 0; j < strlen(word2); j++){
      if (ch == word2[j]){
        cross = true;
        col = j;
        row = i;
        break;
      }
    }
  }
  if(cross == false){
    printf("No common letter!\n");
    exit(0);
    }
  char* matrix = malloc(sizeof(char)*(strlen(word1)*strlen(word2)));
  for(int i = 0; i < strlen(word2); i++){
    for(int j = 0; j < strlen(word1); j++){
      matrix[j* strlen(word2) + i] = '.'; 
    }
    }
  for(int i = 0; i < strlen(word1); i++){
    matrix[i * strlen(word2) + col] = word1[i];
  }
  for(int i = 0; i < strlen(word2); i++){
    matrix[row * strlen(word2) + i] = word2[i];
  }
  for(int i = 0; i < strlen(word1); i++){
    for(int j = 0; j < strlen(word2); j++){
      printf("%c ", matrix[i* strlen(word2) + j]);
    }
    printf("\n");
  }
  free(matrix);
  return 0;
}
