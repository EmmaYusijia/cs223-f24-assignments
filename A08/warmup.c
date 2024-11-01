#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  int status;
  printf("%d] A0\n", getpid());
  pid = fork();

  if(pid == 0){
    printf("%d] B1\n", getpid());
  }else{
    printf("%d] B0\n", getpid());
    pid = fork();
    if(pid == 0){
      printf("%d] C1\n", getpid());
    }else{
      printf("%d] C0\n", getpid());
    }
  }
  printf("%d] Bye\n", getpid());
  exit(0);
  return 0;
}
