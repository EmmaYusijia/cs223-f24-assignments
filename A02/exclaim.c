#include <stdio.h>
#include <stdlib.h>

int main() {
  char exclaim[4];
  exclaim[0] = '@';
  exclaim[1] = '!';
  exclaim[2] = '#';
  exclaim[3] = '*';
  char buff[32];
  printf("Enter a word:\n");
  scanf("%31s", buff);
  printf("OMG! ");
  for(int i = 0; buff[i] != '\0'; i++){
    if(((int)(buff[i])>=97)&&((int)(buff[i])<=122)){
      char random_char = exclaim[rand() % 4];
      printf("%c", random_char);
    }else {
      printf("%c", buff[i]);
      }
  }
  printf("\n");
  return 0;
}
