#include <stdio.h>
#include <stdlib.h>

int main() {
  char phrase[1024];
  printf("Enter a phrase:\n");
  scanf("%[^\n]%*c", phrase);
  printf("Your acronym is ");
  for(int i = 0; phrase[i] != '\0'; i++){
    if(((int)(phrase[i])>=65)&&((int)(phrase[i])<=90)){
      printf("%c", phrase[i]);
    }
  }
  printf("\n");
  return 0;
}
