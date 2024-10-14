/*----------------------------------------------
 * Author: Emma Yu
 * Date: 10/13/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      unsigned long mask = 0x1ul << (63 - (row * 8 + col));
            
      if (img & mask) {
        printf("@ ");
        } else {
          printf("  ");
          }
    }
    printf("\n");
    }
  return 0;
}
