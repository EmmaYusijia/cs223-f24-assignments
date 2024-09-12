/***************************************************
 * mathgame.c
 * Author: Emma Yu 
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int numRounds, correctTimes = 0;
    int num1, num2, userAnswer, correctAnswer;

    printf("Welcome to Math Game!\n");

    printf("How many rounds do you want to play? ");
    scanf("%d", &numRounds);

    for (int i = 0; i < numRounds; i++) {
        num1 = rand() % 9 + 1;
        num2 = rand() % 9 + 1;

        printf("%d + %d = ? ", num1, num2);
        scanf("%d", &userAnswer);

        correctAnswer = num1 + num2;

        if (userAnswer == correctAnswer) {
            printf("Correct!\n");
            correctTimes++;
        } else {
            printf("Incorrect :(\n");
        }
    }

    printf("You answered %d/%d correctly.\n", correctTimes, numRounds);

  return 0;
}
