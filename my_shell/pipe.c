#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"
extern char* g_argv[MAX_ARG_CNT];
extern int g_argc;


void cmd_pipe(){
    int pipe_symbol_pos;
    for(pipe_symbol_pos = 1; pipe_symbol_pos < g_argc - 1; pipe_symbol_pos++){
        if(strcmp(g_argv[pipe_symbol_pos], "|") == 0){
            break;
        }
    }

    g_argv[pipe_symbol_pos] = 0;
    pid_t son_pid;
    int son_status;
    int pipe_fd[2];
    if((son_pid = fork()) == -1){
        perror("Failed to fork child[son]");
        return;
    }

    if(son_pid == 0){
        // son process
        // open pipe in son process
        if(pipe(pipe_fd) == -1){
            perror("Open pipe error");
            exit(-1);
        }

        pid_t grandson_pid;

        if((grandson_pid = fork()) == -1){
            perror("Failed to fork child[grandson]");
            exit(-1);
        }
        if(grandson_pid == 0){
            // grandson
            close(pipe_fd[0]);    
            dup2(pipe_fd[1],1);
            execvp(g_argv[0],g_argv);
        } else {
            // son
            close(pipe_fd[1]);   
            dup2(pipe_fd[0],0);   
            execvp(g_argv[pipe_symbol_pos+1], &(g_argv[pipe_symbol_pos + 1]));
        }
    } else {
        // parent process
        waitpid(son_pid, &son_status, 0);
    }
    
}