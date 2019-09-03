#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "header.h"
extern char* g_argv[MAX_ARG_CNT];
extern int g_argc;


void cmd_out_redirect(){
    int symbol_pos;
    for(symbol_pos = 1; symbol_pos < g_argc - 1; symbol_pos++){
        if(strcmp(g_argv[symbol_pos], ">") == 0){
            break;
        }
    }

    g_argv[symbol_pos] = 0;
    pid_t son_pid;
    int son_status;

    int fd = open(g_argv[symbol_pos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("Failed to open file");
        return;
    }
    
    if((son_pid = fork()) == -1){
        perror("Failed to fork child");
        return;
    }

    if(son_pid == 0){
  
        dup2(fd,1);
        execvp(g_argv[0],g_argv);
    
    } else {
        // parent process
        waitpid(son_pid, &son_status, 0);
    }
    
}

void cmd_in_redirect(){
    int symbol_pos;
    for(symbol_pos = 1; symbol_pos < g_argc - 1; symbol_pos++){
        if(strcmp(g_argv[symbol_pos], "<") == 0){
            break;
        }
    }

    g_argv[symbol_pos] = 0;
    pid_t son_pid;
    int son_status;

    int fd = open(g_argv[symbol_pos + 1], O_RDONLY, 0644);

    if(fd == -1){
        perror("Failed to open file");
        return;
    }

    if((son_pid = fork()) == -1){
        perror("Failed to fork child");
        return;
    }

    if(son_pid == 0){
  
        dup2(fd,0);
        execvp(g_argv[0],g_argv);
    
    } else {
        // parent process
        waitpid(son_pid, &son_status, 0);
    }
    
}