#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"
extern char* g_argv[MAX_ARG_CNT];
extern int g_argc;

void cd(){
    if(chdir(g_argv[1]) != 0){
        perror("Failed to change dir");
    } 
}