#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song{
  char title[32];
  char artist[32];
  int duration;
  float danceability;
};

void print(struct song playlist[], int size){
   for (int i = 0; i < size; i++) {
    int min = playlist[i].duration/60;
    int sec = playlist[i].duration%60;
        printf("%d) %-20s by %-20s duration: %d:%d danceability: %.2f\n", 
               i, playlist[i].title, playlist[i].artist, min, sec, playlist[i].danceability);
    }
}

int main() {
  struct song playlist[3];

    strcpy(playlist[0].title, "Shout");
    strcpy(playlist[0].artist, "Tears for Fears");
    playlist[0].duration = 251;
    playlist[0].danceability = 0.50;

    strcpy(playlist[1].title, "As it Was");
    strcpy(playlist[1].artist, "Harry Styles");
    playlist[1].duration = 167;
    playlist[1].danceability = 0.70;

    strcpy(playlist[2].title, "Wish You Were Here");
    strcpy(playlist[2].artist, "Pink Floyd");
    playlist[2].duration = 334;
    playlist[2].danceability = 0.30;

int songID;
char attr[20];
printf("Welcome to Steven Struct's Song List.\n");
print(playlist, 3);
printf("Enter a song id to edit [0,1,2]:\n");
scanf("%d",&songID);
if((songID < 0)|(songID > 2)){
  printf("Invalid choice!\n");
}else{
  printf("Which attribute do you wish to edit? [artist, title, duration, danceability]:\n");
  scanf("%s",attr);
  char artistUser[32];
  char titleUser[32];
  int minUser;
  int secUser;
  int minFinal;
  float danceabilityUser;
  if(strcmp(attr,"artist")==0){
    printf("Enter a artist:");
    scanf(" %[^\n]%*c",artistUser);
    strcpy(playlist[songID].artist,artistUser);
  }else if(strcmp(attr, "title")==0){
    printf("Enter a title:");
    scanf(" %[^\n]%*c",titleUser);
    strcpy(playlist[songID].title,titleUser);
  }else if(strcmp(attr, "duration")==0){
    printf("Enter a duration (minutes):\n");
    scanf("%d",&minUser);
    printf("Enter a duration (seconds):\n");
    scanf("%d",&secUser);
    minFinal = minUser*60+secUser;
    playlist[songID].duration = minFinal;
  }else{
    printf("Enter danceability:");
    scanf("%f",&danceabilityUser);
    playlist[songID].danceability = danceabilityUser;
  }
  print(playlist, 3);
}
  return 0;
}
