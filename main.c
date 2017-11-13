/*
    Project name: piminal
    Description: An implementation of a kernel interface with basic commands.
    Author: Charlito G. Piao Jr.
    Compiler: GPP Compiler
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//read a line in the piminal
#define LSH_RL_BUFSIZE 1024
char *_read(void){

}

char *_split(){

}

char *_execute(){

}

int _input(){
    char *line;
    char **args;
    bool status = true;

    while (status) {
        printf("~ ");
        line = _read();
        args = _split(line);
        status = _execute(args);
    }

    return 0;
}

// main entry point
int main(int argc, char **argv)
{

    printf("Generate PI in the terminal based on the \n");
    _input();
    return 0;
}
