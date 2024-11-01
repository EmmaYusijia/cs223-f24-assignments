#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
    printf(ANSI_COLOR_RED "***" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE " Welcome to Emma's Shell" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA " ^_^ " ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "***\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "/Users" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "/emmayu" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "/Documents" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "/GitHub" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "/cs223-f24-assignments" ANSI_COLOR_RESET);
    while(1){
        char * line = readline("-~-~-~>>> ");
        if (line && *line) {
            add_history(line);
        }
        char *command = strtok(line, " ");
        char *argv[100];
        int index = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            argv[index] = token;
            token = strtok(NULL, " "); 
            index ++;
        }
        argv[index] = NULL;
        if(strcmp(command, "exit") != 0){
            printf(ANSI_COLOR_BLUE "/Users" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "/emmayu" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_CYAN "/Documents" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_GREEN "/GitHub" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "/cs223-f24-assignments" ANSI_COLOR_RESET);
            pid_t pid;
            int status;
            pid = fork();
            if(pid == 0){
                if(execvp(command, argv) < 0){
                    printf("%s: Command not found.\n", argv[0]);
                    exit(0);
                }
            }else{
                waitpid(pid, &status, 0);
            }
            }else{
                exit(0);
            }
    }
    return 0;
}