/*----------------------------------------------
 * Author: Emma Yu
 * Date: 09/19/2024
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct song{
  char title[128];
  char artist[128];
  int duration;
  float danceability;
  float energy;
  float tempo;
  float valence;
};

void print(struct song playlist[], int size){
   for (int i = 0; i < size; i++) {
    int msConvert = floor(playlist[i].duration/1000);
    int min = msConvert/60;
    int sec = msConvert%60;
        printf("%d) %-20s by %-20s duration: %d:%d danceability: %.3f" 
        " energy: %.3f tempo: %.3f valence: %.3f\n",  
        i, playlist[i].title, playlist[i].artist, min, sec, 
        playlist[i].danceability, playlist[i].energy,
        playlist[i].tempo, playlist[i].valence);
    }
}

int main() {
  printf("Welcome to Dynamic Donna's Danceability Directory.\n");
  printf("\n");
  FILE *infile; FILE *outfile;
  infile = fopen("songlist.csv", "r");
  if(infile == NULL){
  printf("Error: unable to open file %s\n","songlist.csv");
  exit(1);
  }
  
  char line[128];
  fgets(line, 128, infile);
  char *token = strtok(line, ",");
  int size = atoi(token);
  fgets(line, 128, infile);

  struct song *playlist = malloc(sizeof(struct song)*size);
  for(int i = 0; i < size; i++){
    fgets(line, 128, infile);
    strcpy(playlist[i].title, strtok(line, ","));
    strcpy(playlist[i].artist, strtok(NULL, ","));
    playlist[i].duration = (atoi)(strtok(NULL, ","));
    playlist[i].danceability = (atof)(strtok(NULL, ","));
    playlist[i].energy = (atof)(strtok(NULL, ","));
    playlist[i].tempo = (atof)(strtok(NULL, ","));
    playlist[i].valence = (atof)(strtok(NULL, ","));
    }
    print(playlist, size);
    fclose(infile);
    free(playlist);
    return 0;
    }
