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
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int _cd(char **args), _chdir(char **args), _cls(char **args), _cmd(char **args), _copy(char **args), _date(char **args), _del(char **args), _dir(char **args), _mkdir(char **args), _move(char **args), _rename(char **args), _rmdir(char **args), _time(char **args), _type(char **args), _help(char **args), _quit(char **args), _pi(char **args);
char *commands_str[] = {"cd", "chdir", "cls", "cmd", "copy", "date", "del", "dir", "mkdir", "move", "rename", "rmdir", "time", "type", "help", "quit", "pi"};
int (*commands_func[]) (char**) = {&_cd, &_chdir, &_cls, &_cmd, &_copy, &_date, &_del, &_dir, &_mkdir, &_move, &_rename, &_rmdir, &_time, &_type, &_help, &_quit, &_pi};

int _num_commands(){
    return sizeof(commands_str) / sizeof(char *);
}

/*
    Command Helper Function
*/

//Checker function if directory or file
int _checktype(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

/*
    Implementation of commands 16 commands
*/

//CD - Displays the name of or changes the current directory.
int _cd(char **args){
    char cwd[1024];
    int stat;

    if(args[1] == NULL){
         getcwd(cwd, sizeof(cwd));
         fprintf(stderr, "Current working dir: %s\n", cwd);
    }else{
        stat = chdir(args[1]);

        if(stat != 0){
            perror("psh");
        }
    }
    return 1;
}

//CHDIR - Changes the current directory.
int _chdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "psh: expected location after \"chdir\"\n");
    }else if(chdir(args[1]) != 0){
        perror("psh");
    }

    return 1;
}

//CLS - Clears the screen.
int _cls(char **args){
    printf("\e[1;1H\e[2J");
    return 1;
}

//TODO:CMD - Starts a new instance of the command interpreter.
int _cmd(char **args){

    if(args[1] == NULL){

    }else{
        perror("psh");
    }

    return 1;
}

//TODO:COPY- Copies one or more files to another location.
int _copy(char **args){
    int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];
    char *src_path, *dst_path;

    if(args[1] == NULL){
        printf("psh: no file selected");
    }else{
        printf("psh: copying");
        src_path = args[1];
        dst_path = args[2];

        //TODO:check if multiple files

        src_fd = open(src_path, O_RDONLY);
        dst_fd = open(dst_path, O_CREAT | O_WRONLY);

        while (1) {
            err = read(src_fd, buffer, 4096);
            if (err == -1) {
                printf("Error reading file.\n");
                exit(1);
            }
            n = err;

            if (n == 0) break;

            err = write(dst_fd, buffer, n);
            if (err == -1) {
                printf("Error writing to file.\n");
                exit(1);
            }
        }

        close(src_fd);
        close(dst_fd);
    }

    return 1;
}

//DATE- Displays or sets the date.
int _date(char **args){
    int tempYear, tempMonth, tempDay;
    // char date;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("Current date: %d-%d-%d\n",tm.tm_year+1900,tm.tm_mon+1, tm.tm_mday);
    printf("Enter the new date: (yy-mm-dd) ");

    //TODO: Ask for year,month, and day
    tempYear = tempMonth = tempDay = 1;

    tm.tm_year = tempYear;
    tm.tm_mon = tempMonth;
    tm.tm_mday = tempDay;
    printf("\n");

    return 1;
}

//DEL- Deletes one or more files.
int _del(char **args){

    if(args[1] == NULL){
        printf("psh: No file selected\n");
    }else{
        //Check if directory or file (needs to be file only)
        if(_checktype(args[1]))
            remove(args[1]);
    }

    return 1;
}

//DIR- Displays a list of files and subdirectories in a directory.
int _dir(char **args){
    struct dirent *de;
    DIR *dr = opendir(".");

    while((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
    }
    closedir(dr);

    return 1;
}

//MKDIR- Creates a directory.
int _mkdir(char **args){
    struct stat st = {0};

    if(stat(args[1],&st) == -1){
        mkdir(args[1], 0700);
    }
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

    if(args[1] == NULL){
        printf("psh: Directory not found\n");
    }else{
        //Check if directory or file (needs to be directory only)
        if(_checktype(args[1]))
            printf("psh: choose directory");
        else
            remove(args[1]);
    }

    return 1;
}

//TIME- Displays or sets the system time.
int _time(char **args){
    int tempHour, tempMin, tempSec;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d:%d:%d\n",tm.tm_hour,tm.tm_min, tm.tm_sec);
    printf("Enter the new date: (yy-mm-dd) ");

    //TODO: Ask for hour,minute, and second
    tempHour = tempMin = tempSec = 1;

    tm.tm_hour = tempHour;
    tm.tm_min = tempMin;
    tm.tm_sec = tempSec;
    printf("\n");

    return 1;
}

//TYPE- Displays the contents of a text file.
int _type(char **args){
    FILE *fptr;
    char c;

    if(args[1] != NULL){
        fptr = fopen(args[1], "r");

        if(fptr == NULL){
            printf("File doesn't exist.\n");
        }

        c = fgetc(fptr);
        while(c != EOF){
            printf("%c",c);
            c = fgetc(fptr);
        }
        fclose(fptr);
    }else{
        printf("psh: no file selected\n");
    }

    return 1;
}

//EXIT- close the piterminal
int _quit(char **args){
    return 0;
}

//HELP- Show the list of commands
int _help(char **args){
    int i, j;
    printf("\nList of commands: \n");

    for(i = 0, j = 1; i < _num_commands(); i++,j++){
        printf("%d. %s\n",j,commands_str[i]);
    }

    return 1;
}

//pi ao- show pi calculation
int _pi(char **args){

    //Dik T. Winter Implementation of computation of first 800 digits of pi
    int a=10000,b,c=2800,d,e,f[2801],g;

    for(;b-c;)f[b++]=a/5;
    for(;d=0,g=c*2; c-=14,printf("%.4d",e+d/a),e=d%a)
    for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);

    printf("\n");
    return 1;
}


/*
    Main Helper Functions
*/

//Launch
int _launch(char **args){
    int status;
    pid_t pid = fork();

    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("psh");
        exit(1);
    }
    }else if(pid < 0){
        perror("psh");
    }else{
        do{
            waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

//Execute Commands
int _execute(char **args){
    int i;

    if(args[0] == NULL){
        return 1;
    }

    for(i = 0; i < _num_commands(); i++){
        if(strcmp(args[0], commands_str[i]) == 0){
            return (*commands_func[i])(args);
        }
    }

    return _launch(args);
}

//Read Line input
#define LSH_RL_BUFSIZE 1024

char *_readline(void){
    int buffersize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = (char*)malloc(sizeof(char) * buffersize);
    int c;

    if(!buffer){
        fprintf(stderr, "psh: Allocation error\n");
        exit(1);
    }

    while((c = getchar())!= EOF){
        if(c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        if(position >= buffersize){
            buffersize += LSH_RL_BUFSIZE;
            buffer = (char*)realloc(buffer, buffersize);

            if(!buffer){
                fprintf(stderr, "psh: Allocation Error!\n");
                exit(1);
            }
        }
    }
    exit(0);
}

//Split Line input
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **_splitline(char *line){
    int buffersize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = (char**)malloc(buffersize * sizeof(char*));
    char *token, **tokens_backup;

    if(!tokens){
        fprintf(stderr, "psh: Allocation Error!\n");
        exit(1);
    }

    token = strtok(line, LSH_TOK_DELIM);

    while(token!=NULL){
        tokens[position] = token;
        position++;

        if(position >= buffersize){
            buffersize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char**) realloc(tokens, buffersize * sizeof(char*));

            if(!tokens){
                free(tokens_backup);
                fprintf(stderr, "psh: Allocation Error!\n");
                exit(1);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


/*
    Main Function
*/

int main(int argc, char **argv){
    printf("\n--------------------------------------------------------------------------------");
    printf("---\t\t\t~ WELCOME TO PITERMINAL \t\t\t     ---\n");
    printf("--------------------------------------------------------------------------------\n");

    char *line;
    char **args;
    int status = 1;

    do{
        printf("\n~ ");
        line = _readline();
        args = _splitline(line);
        status = _execute(args);

        free(line);
        free(args);
    }while(status);

    return 0;
}
