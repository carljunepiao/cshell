/*
    Project name: piminal
    Description: An implementation of a kernel interface with basic commands.
    Author: Charlito G. Piao Jr.
    Compiler: GPP Compiler
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int _cd(char **args);
int _chdir(char **args);
int _cls(char **args);
int _cmd(char **args);
int _copy(char **args);
int _date(char **args);
int _del(char **args);
int _dir(char **args);
int _mkdir(char **args);
int _move(char **args);
int _rename(char **args);
int _rmdir(char **args);
int _time(char **args);
int _type(char **args);
int _help(char **args);
int _quit(char **args);


char *commands_str[] = {
    "cd",
    "chdir",
    "cls",
    "cmd",
    "copy",
    "date",
    "del",
    "dir",
    "mkdir",
    "move",
    "rename",
    "rmdir",
    "time",
    "type",
    "help",
    "quit"
};

int (*commands_func[]) (char**) = {
    &_cd,
    &_chdir,
    &_cls,
    &_cmd,
    &_copy,
    &_date,
    &_del,
    &_dir,
    &_mkdir,
    &_move,
    &_rename,
    &_rmdir,
    &_time,
    &_type,
    &_help,
    &_quit
};

int _num_commands(){
    return sizeof(commands_str) / sizeof(char *);
}

/*
    Implementation of commands 16 commands
*/

//CD - Displays the name of or changes the current directory.
int _cd(char **args){
    char cwd[1024];
    if(args[1] == NULL){
         //show current directory
         getcwd(cwd, sizeof(cwd));
         fprintf(stderr, "Current working dir: %s\n", cwd);
    }else{
        chdir(args[1]);
        if(chdir(args[1]) != 0){
            perror("psh:");
        }
    }
    return 1;
}

//CHDIR - Changes the current directory.
int _chdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "psh: expected argument to \"chdir\"\n");
    }else if(chdir(args[1]) != 0){
        perror("psh:");
    }

    return 1;
}

//CLS - Clears the screen.
int _cls(char **args){
    printf("\e[1;1H\e[2J");
    return 1;
}

//CMD - Starts a new instance of the command interpreter.
int _cmd(char **args){

    return 1;
}

//COPY- Copies one or more files to another location.
int _copy(char **args){

    return 1;
}

//DATE- Displays or sets the date.
int _date(char **args){

    return 1;
}

//DEL- Deletes one or more files.
int _del(char **args){

    return 1;
}

//DIR- Displays a list of files and subdirectories in a directory.
int _dir(char **args){

    return 1;
}

//MKDIR- Creates a directory.
int _mkdir(char **args){

    return 1;
}

//MOVE- Moves one or more files from one directory to another directory.
int _move(char **args){

    return 1;
}

//RENAME- Renames a file or files.
int _rename(char **args){

    return 1;
}

//RMDIR- Removes a directory.
int _rmdir(char **args){

    return 1;
}

//TIME- Displays or sets the system time.
int _time(char **args){

    return 1;
}

//TYPE- Displays the contents of a text file.
int _type(char **args){

    return 1;
}

//EXIT- close the piterminal
int _quit(char **args){

    return 0;
}

int _help(char **args){

    return 1;
}

int main(int argc, char **argv)
{
    printf("\n\n\t\t\t~ WELCOME TO PITERMINAL\n\n");
    // printf("\n\n\t\t\tGenerate PI in the terminal\n\n\n");

    char *line;
    char **args;
    int status = 1;

    do{
        printf("~ ");

        // free(line);
        // free(args);
        status = 0;
    }while(status);

    // return EXIT_SUCCESS;
    return 0;
}
