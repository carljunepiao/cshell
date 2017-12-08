/*
    Project name: piminal
    Description: An implementation of a kernel interface with basic commands.
    Author: Charlito G. Piao Jr.
    Compiler: GPP Compiler
    Header: files from the GNU C Library

    *Note:
            Some libraries used depends on unix/linux operating
            system which means program won't work in windows like and
            some functions used builtin commands like chdir but modified
            to follow the provided instructions.
*/

#include <sys/wait.h>   //For: chdir(), fork(), exec(), pid_t
#include <stdlib.h>     //For: malloc(), realloc(), free(), exit(), execvp(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>      //For: printf(), fprintf(),stderr, getchar(), perror()
#include <string.h>     //For: strcmp(), strktok()
#include <sys/time.h>   //For: time, localtime
#include <time.h>       //For: time, localtime
#include <dirent.h>     //For: DIR, dr, opendir(), readdir(), closedir()
#include <sys/stat.h>   //For: S_ISREG, mkdir()
#include <unistd.h>     //For: getcwd(), chdir(), read(), write(), close(), fork()
#include <fcntl.h>      //For: O_RDONLY, open, O_CREAT, O_WRONLY
#include <errno.h>

//Ignore warnings
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//Function declarations
int _cd(char **args), _chdir(char **args), _cls(char **args), _cmd(char **args), _copy(char **args), _date(char **args), _del(char **args), _dir(char **args), _mkdir(char **args), _move(char **args), _rename(char **args), _rmdir(char **args), _time(char **args), _type(char **args), _help(char **args), _quit(char **args), _pi(char **args), _about(char **args);

//List of builtin commands
char *commands_str[] = {"cd", "chdir", "cls", "cmd", "copy", "date", "del", "dir", "mkdir", "move", "rename", "rmdir", "time", "type", "help", "quit", "pi", "about"};

int (*commands_func[]) (char**) = {&_cd, &_chdir, &_cls, &_cmd, &_copy, &_date, &_del, &_dir, &_mkdir, &_move, &_rename, &_rmdir, &_time, &_type, &_help, &_quit, &_pi, &_about};

//number of commands
int _num_commands(){
    return sizeof(commands_str) / sizeof(char *);
}

/*
    Command Helper Function
*/

//Checker function if directory or file
int _checktype(const char *path){
    printf("\n");
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

/*
    Implementation of commands 16 commands
*/
//ABOUT - Explain how the terminal works
int _about(char **args){
    printf("\nABOUT THE PIMINAL 1.0\n\n");
    printf("1. Read line of user input\n");
    printf("2. Tokenize read line, using space(' ') as the delimiter\n");
    printf("3. Separate the command from arguments(dir, folder, file)\n");
    printf("4. Use fork() and exec() System Call for starting a new process for the shell\n");
    printf("5. Compare input from created commands\n");
    printf("6. Execute command if it matches\n");
    printf("\n");

    printf("\nCreated by: Charlito Piao for CMSC 125 (2017)\n\n");
    return 1;
}

//CD - Displays the name of or changes the current directory.
int _cd(char **args){
    char cwd[1024];
    int stat;

    if(args[1] == NULL){
         getcwd(cwd, sizeof(cwd));
         printf("current working dir: %s\n", cwd);
    }else{
        stat = chdir(args[1]);

        if(stat != 0){
            perror("pt");
        }else{
            printf("pt: changed directory.\n");
        }
    }
    return 1;
}

//CHDIR - Changes the current directory.
int _chdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "psh: expected location after \"chdir\"\n");
    }else if(chdir(args[1]) == 0){
        printf("pt: changed directory.\n");
    }else{
        printf("pt: \n");
    }

    return 1;
}

//CLS - Clears the screen.
int _cls(char **args){
    if(args[1] == NULL){
        printf("\e[1;1H\e[2J");
    }else{
        printf("pt: requires no argument/s\n");
    }
    return 1;
}

//CMD - Create new instance of the command interpreter
int _cmd(char **args){

    if(args[1] == NULL){
        printf("\e[1;1H\e[2J");
        printf("\n--------------------------------------------------------------------------------");
        printf("--\t\t\t~ WELCOME TO PITERMINAL 1.0\t\t\t     --\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("\nType 'help' to show all the list of commands.\n\n");

    }else{
        perror("pt");
    }

    return 1;
}

//COPY- Copies one or more files to another location.
int _copy(char **args){
    FILE *fptr_input, *fptr_output;
    char c;

    if(args[1] == NULL){
        printf("pt: no file selected\n");
    }else if (args[2] == NULL) {
        printf("pt: no argument destination\n");
    }else{
        //get the path of source and destination
        fptr_input = fopen(args[1], "r");
        chdir(args[2]);
        fptr_output = fopen(args[1], "w+");

        while(1){
            c = fgetc(fptr_input);
            if(feof(fptr_input)){
                break;
            }
            fprintf(fptr_output, "%c", c);
        }
        fclose(fptr_input);
        fclose(fptr_output);

        chdir("..");
        printf("pt: file coppied successfully.\n");
    }

    return 1;
}

//DATE- Displays or sets the date.
int _date(char **args){
    const char* dataStr = args[1];

    if(args[1] == NULL){
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("Current date: %d-%d-%d (MMDDYY)\n",tm.tm_mon+1, tm.tm_mday,tm.tm_year+1900);

    }else if(args[1] != NULL){
        char buf[3] = {0};

        strncpy(buf, dataStr + 0, 2);
        unsigned short month = atoi(buf);

        strncpy(buf, dataStr + 2, 2);
        unsigned short day = atoi(buf);

        strncpy(buf, dataStr + 4, 2);
        unsigned short year = atoi(buf);

        time_t mytime = time(0);
        struct tm* tm_ptr = localtime(&mytime);

        if (tm_ptr)
        {
            tm_ptr->tm_mon  = month - 1;
            tm_ptr->tm_mday = day;
            tm_ptr->tm_year = year + (2000 - 1900);

            const struct timeval tv = {mktime(tm_ptr), 0};
            settimeofday(&tv, 0);
        }
    }else{
        printf("pt: requires no argument/s.\n");
    }

    return 1;
}

//DEL- Deletes one or more files.
int _del(char **args){

    if(args[1] == NULL){
        printf("pt: no argument/s found.\n");
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

    if(args[1] == NULL){
        while((de = readdir(dr)) != NULL){
            printf("  %s\n", de->d_name);
        }
        closedir(dr);
    }else if(args[1] != NULL){
        dr = opendir(args[1]);
        while((de = readdir(dr)) != NULL){
            printf("%s\n", de->d_name);
        }
    }else{
        printf("pt: select one directory only\n");
    }

    return 1;
}

//MKDIR- Creates a directorx`y.
int _mkdir(char **args){
    struct stat st = {0};

    if(args[1] == NULL){
        printf("pt: no argument/s found.\n");
    }else{
        if(stat(args[1],&st) == -1){
            mkdir(args[1], 0700);
        }
    }
    return 1;
}

//TODO:MOVE- Moves one or more files from one directory to another directory.
int _move(char **args){
    FILE *fptr_input, *fptr_output;
    char c;
    int i;

    if(args[1] == NULL){
        printf("pt: no file selected\n");
    }else if (args[2] == NULL) {
        printf("pt: no argument destination\n");
    }else{
        fptr_input = fopen(args[1], "r");
        chdir(args[2]);
        fptr_output = fopen(args[1], "w+");

        while(1){
            c = fgetc(fptr_input);
            if(feof(fptr_input)){
                break;
            }
            fprintf(fptr_output, "%c", c);
        }
        fclose(fptr_input);
        fclose(fptr_output);

        chdir("..");
        remove(args[1]);
        printf("pt: file moved successfully.\n");
    }

    for(i = 1; args[i]!= NULL; i++){

    }

    return 1;
}

//RENAME- Renames a file or files.
int _rename(char **args){

    if(args[1] == NULL || args[2] == NULL){
        printf("pt: no argument/s found.\n");
    }else{
        if(rename(args[1], args[2]) == 0){
            printf("pt: successfully renamed file\n");
        }else{
            printf("pt: error occured.\n");
        }
    }

    return 1;
}

//RMDIR- Removes a directory.
int _rmdir(char **args){

    if(args[1] == NULL){
        printf("pt: no argument/s found.\n");
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
            printf("pt: file doesn't exist.\n");
        }

        c = fgetc(fptr);
        while(c != EOF){
            printf("%c",c);
            c = fgetc(fptr);
        }
        fclose(fptr);
    }else{
        printf("pt: no argument/s found.\n");
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

    if(args[1] == NULL){
        printf("\nList of commands: \n");

        for(i = 0, j = 1; i < _num_commands(); i++,j++){
            printf("%d. %s\n",j,commands_str[i]);
        }
    }else{
        printf("pt: requires no argument/s.\n");
    }

    return 1;
}

//pi ao- show pi calculation
int _pi(char **args){

    if(args[1] == NULL){
        //Dik T. Winter Implementation of computation of first 800 digits of pi
        int a=10000,b,c=2800,d,e,f[2801],g;

        for(;b-c;)f[b++]=a/5;
        for(;d=0,g=c*2; c-=14,printf("%.4d",e+d/a),e=d%a)
        for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);

        printf("\n");
    }else{
        printf("pt: requires no argument/s");
    }

    return 1;
}


/*
    Main Helper Functions
*/

//Launch piminal
int _launch(char **args){
    int status;
    pid_t pid = fork();

    if(pid == 0){
        // if(execvp(args[0], args) == -1){
        //     perror("pt");
        //     exit(1);
        // }
    }else if(pid < 0){
        perror("pt");
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

    //Find the command
    for(i = 0; i < _num_commands(); i++){
        if(strcmp(args[0], commands_str[i]) == 0){
            return (*commands_func[i])(args);
        }
    }

    // printf("%d\n", (*commands_func[i])(args));

    return _launch(args);
}

//Read Line input
#define LSH_RL_BUFSIZE 1024

char *_readline(void){
    char *line = NULL;
    size_t buffersize = 0;
    getline(&line, &buffersize, stdin);
    return line;
}

//Split Line input
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **_splitline(char *line){
    int buffersize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = (char**)malloc(buffersize * sizeof(char*));
    char *token, **tokens_backup;

    if(!tokens){
        fprintf(stderr, "pt: Allocation Error!\n");
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
                fprintf(stderr, "pt: allocation error!\n");
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
    printf("--\t\t\t~ WELCOME TO PITERMINAL 1.0\t\t\t     --\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("\nType 'help' to show all the list of commands.\n\n");
    char *line;
    char **args;
    int status = 1;

    do{
        printf("\n> ");
        line = _readline();
        args = _splitline(line);
        status = _execute(args);

        free(line);
        free(args);
    }while(status); //loop until user doesn't use command: quit

    return 0;
}
