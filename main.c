/*
    Project name: piminal
    Description: An implementation of a kernel interface with basic commands.
    Author: Charlito G. Piao Jr.
    Compiler: GPP Compiler
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// main entry point
int main(int argc, char **argv)
{
    printf("\n\n\t\t\t~ Welcome to piterminal");

    printf("\n\n\t\tGenerate PI in the terminal based on the \n");

    int c;

    c = getchar();

    while (c != EOF) {
        /* code */
        putchar(c);
        c = getchar();
    }

    return 0;
}
