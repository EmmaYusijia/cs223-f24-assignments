/*----------------------------------------------
 * Author: Emma Yu
 * Date: 09/26/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
  char title[128];
  char artist[128];
  int duration;
  float danceability;
  float energy;
  float tempo;
  float valence;
  struct node* next;
};

struct node* insert(char title[], char artist[], int duration, 
float danceability, float energy, float tempo, float valence) {
  struct node* n = malloc(sizeof(struct node));
  if (n == NULL) {
    printf("ERROR: Out of space!\n");
    exit(1);
  }
  strcpy(n->title, title);
  strcpy(n->artist, artist);
  n->duration = duration;
  n->danceability = danceability;
  n->energy = energy;
  n->tempo = tempo;
  n->valence = valence;
  n->next = NULL;
  return n;
}

int size(struct node* head){
  int size = 0;
  for(struct node* n = head; n != NULL; n = n->next){
    size ++;
  }
  return(size);
}

void printList(struct node* node) {
  int index = 0;
  for (struct node* n = node; n != NULL; n = n->next) {
    int msConvert = floor(n->duration/1000);
    int min = msConvert/60;
    int sec = msConvert%60;
    printf("%d) %-20s by %-20s duration: %d:%d danceability: %.3f" 
    " energy: %.3f tempo: %.3f valence: %.3f\n",  
    index, n->title, n->artist, min, sec, n->danceability, n->energy,
    n->tempo, n->valence);
    index++;
  }
  printf("Dataset contains %d songs\n", index);
  printf("\n");
}

struct node* printMost(struct node* node) {  
  struct node* most = node;
  for (struct node* n = node->next; n != NULL; n = n->next) {
    if(n->danceability > most->danceability){
      most = n;
    }
  }
  int msConvert = floor(most->duration/1000);
  int min = msConvert/60;
  int sec = msConvert%60;
  printf("%-20s by %-20s duration: %d:%d danceability: %.3f" 
  " energy: %.3f tempo: %.3f valence: %.3f\n",
  most->title, most->artist, min, sec, most->danceability, most->energy,
  most->tempo, most->valence);
  printf("\n");
  return(most);
}

struct node* removeMost(struct node* head, struct node* most){
  struct node* prev;
  struct node* newHead;
  for (struct node* n = head; n != NULL; n = n->next) {
    if(n==most){
      if(n==head){
        newHead = n->next;
        free(n);
        n = NULL;
        return(newHead);
      }else{
        prev->next = n->next;
        free(n);
        n = NULL;
        return(head);
      }
      break;
    }
    prev = n;
  }
  return(head);
}

void clear(struct node* head){
  for(struct node* n = head; n != NULL; n = n->next){
    free(n);
    n = NULL;
  }
}

int main() {
  FILE *infile; FILE *outfile;
  infile = fopen("songlist.csv", "r");
  if(infile == NULL){
  printf("Error: unable to open file %s\n","songlist.csv");
  exit(1);
  }
  
  char line[128];
  fgets(line, 128, infile);

  fgets(line, 128, infile);
  char* token1 = strtok(line, ",");
  char* token2 = strtok(NULL, ",");
  char* token3 = strtok(NULL, ",");
  char* token4 = strtok(NULL, ",");
  char* token5 = strtok(NULL, ",");
  char* token6 = strtok(NULL, ",");
  char* token7 = strtok(NULL, ",");
  if (!token1 || !token2 || !token3 || !token4 || !token5 || !token6 || !token7) {
    fprintf(stderr, "Error: Malformed line, expected 7 tokens but got less.\n");
    return 0;  
    }
  struct node* head = insert(token1, token2, atoi(token3), atof(token4), atof(token5), atof(token6), atof(token7));

  fgets(line, 128, infile);
  token1 = strtok(line, ",");
  token2 = strtok(NULL, ",");
  token3 = strtok(NULL, ",");
  token4 = strtok(NULL, ",");
  token5 = strtok(NULL, ",");
  token6 = strtok(NULL, ",");
  token7 = strtok(NULL, ",");
  if (!token1 || !token2 || !token3 || !token4 || !token5 || !token6 || !token7) {
    fprintf(stderr, "Error: Malformed line, expected 7 tokens but got less.\n");
    return 0;  
    }
  struct node* n2 = insert(token1, token2, atoi(token3), atof(token4), atof(token5), atof(token6), atof(token7));
  head -> next = n2;

  fgets(line, 128, infile);
  token1 = strtok(line, ",");
  token2 = strtok(NULL, ",");
  token3 = strtok(NULL, ",");
  token4 = strtok(NULL, ",");
  token5 = strtok(NULL, ",");
  token6 = strtok(NULL, ",");
  token7 = strtok(NULL, ",");
  if (!token1 || !token2 || !token3 || !token4 || !token5 || !token6 || !token7) {
    fprintf(stderr, "Error: Malformed line, expected 7 tokens but got less.\n");
    return 0; 
    }
  struct node* n3 = insert(token1, token2, atoi(token3), atof(token4), atof(token5), atof(token6), atof(token7));
  n2->next = n3;

  fgets(line, 128, infile);
  token1 = strtok(line, ",");
  token2 = strtok(NULL, ",");
  token3 = strtok(NULL, ",");
  token4 = strtok(NULL, ",");
  token5 = strtok(NULL, ",");
  token6 = strtok(NULL, ",");
  token7 = strtok(NULL, ",");
  if (!token1 || !token2 || !token3 || !token4 || !token5 || !token6 || !token7) {
    fprintf(stderr, "Error: Malformed line, expected 7 tokens but got less.\n");
    return 0;  
    }
  struct node* n4 = insert(token1, token2, atoi(token3), atof(token4), atof(token5), atof(token6), atof(token7));
  n3->next = n4;

  fgets(line, 128, infile);
  token1 = strtok(line, ",");
  token2 = strtok(NULL, ",");
  token3 = strtok(NULL, ",");
  token4 = strtok(NULL, ",");
  token5 = strtok(NULL, ",");
  token6 = strtok(NULL, ",");
  token7 = strtok(NULL, ",");
  if (!token1 || !token2 || !token3 || !token4 || !token5 || !token6 || !token7) {
    fprintf(stderr, "Error: Malformed line, expected 7 tokens but got less.\n");
    return 0;  
    }
  struct node* n5 = insert(token1, token2, atoi(token3), atof(token4), atof(token5), atof(token6), atof(token7));
  n4->next = n5;

  printList(head);
  printf("\n");
  char danceable;
  struct node* most;
  while(1){
    printf("Press 'd' to show the most danceable song (any other key to quit): ");
    scanf(" %c", &danceable);
    if(danceable=='d'){
      if(size(head)!=0){
      printf("Most danceable\n");
      most = printMost(head);
      head = removeMost(head, most);
      printList(head);
      }else{
        printf("Dataset contains 0 songs\n");
        }
        }
        else{
          break;
        }
        }
  if(size(head)!=0){
    clear(head);
  }

  fclose(infile);
  return 0;
}

