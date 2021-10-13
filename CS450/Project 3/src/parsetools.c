#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "constants.h"
#include "parsetools.h"

// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//
int split_cmd_line(char* line, char** list_to_populate) {
    char* saveptr;  // for strtok_r; see http://linux.die.net/man/3/strtok_r
    char* delimiters = " \t\n"; // whitespace
    int i = 0;

    list_to_populate[0] = strtok_r(line, delimiters, &saveptr);

    while(list_to_populate[i] != NULL && i < MAX_LINE_WORDS - 1)  {
        list_to_populate[++i] = strtok_r(NULL, delimiters, &saveptr);
    };

    return i;
}

void syserror(const char* s) {
    extern int errno;
    fprintf( stderr, "%s\n", s );
    fprintf( stderr, " (%s)\n", strerror(errno) );
    exit( 1 );

}

int is_less(const char* token){
    if(strcmp(token, "<") == 0)
        return 1;
    return 0;
}
int is_append(const char* token){
    if(strcmp(token, ">>") == 0)
        return 1;
    return 0;
}
int is_more(const char* token){
    if(strcmp(token, ">") == 0)
        return 1;
    return 0;
}
int is_pipe(const char* token){
    if(strcmp(token, "|") == 0)
        return 1;
    return 0;
}
int is_command(const char* token){
    if(is_less(token) == 1)
        return 0;
    if(is_more(token) == 1)
        return 0;
    if(is_pipe(token) == 1)
        return 0;
    return 1;
}

void execute(char* command_line[], int tokenCount)
{

    int file_check, io_check, count_commands, pipes, first_command, arguments, append;
    append = file_check = io_check = count_commands = pipes = 0;
    first_command = arguments = 1;

    for (int i = 0; i < tokenCount; i++) {
        if (is_pipe(command_line[i]) == 1) {
            pipes++;
        }
    }

    com_info* list_of_commands = malloc((pipes + 1) * sizeof(com_info));
    list_of_commands[count_commands].args = malloc(tokenCount * sizeof(char*));

    for (int i = 0; i < tokenCount; i++)
    {
        if (first_command == 0) {
            if (is_command(command_line[i]) == 1) {
                if (file_check == 1) {
                    if (io_check == 0)
                        strcpy((list_of_commands[count_commands].oFile = malloc(strlen(command_line[i]) + 1)), command_line[i]);
                    else
                        strcpy((list_of_commands[count_commands].iFile = malloc(strlen(command_line[i]) + 1)), command_line[i]);
                }
                else {
                    strcpy((list_of_commands[count_commands].args[arguments++] = malloc(strlen(command_line[i]) + 1)), command_line[i]);
                    list_of_commands[count_commands].numCount++;
                }
            }
            else if (is_less(command_line[i]) == 1) {
                file_check = io_check = list_of_commands[count_commands].flagInput = 1;
            }
            else if (is_more(command_line[i]) == 1) {
                file_check = list_of_commands[count_commands].flagOutput = 1;
                io_check = 0;
            }
            else if (is_append(command_line[i]) == 1) {
                file_check = list_of_commands[count_commands].append = 1;
                io_check = 0;
            }
            else if (is_pipe(command_line[i]) == 1) {
                list_of_commands[++count_commands].args = malloc(tokenCount * sizeof(char*));
                first_command = 1;
            }
        }
        else {
            if(is_command(command_line[i])){
                strcpy((list_of_commands[count_commands].iden = malloc(strlen(command_line[i]) + 1)), command_line[i]);
                strcpy((list_of_commands[count_commands].args[0] = malloc(strlen(command_line[i]) + 1)), command_line[i]);
                list_of_commands[count_commands].numCount = arguments = 1;
                list_of_commands[count_commands].flagInput = list_of_commands[count_commands].flagOutput = file_check = first_command = 0;
            }
            else if(is_pipe(command_line[i])){
                list_of_commands[++count_commands].args = malloc(sizeof(char*));
                first_command = 1;
            }

        }

    }

    int pfd[pipes * 2];
    for (int i = 0; i < pipes; i++){
        if (pipe(pfd + i * 2) < 0)
            syserror( "Error creating pipes" );
    }

    for (int i = 0; i < pipes+1; i++) {
        list_of_commands[i].args[list_of_commands[i].numCount] = NULL;
        int num_words = list_of_commands[i].numCount;
        for (int j = 0; j < num_words; j++) {
            if (list_of_commands[i].args[j][0] == '\"' || list_of_commands[i].args[j][0] == '\''){
                list_of_commands[i].args[j]++;
                list_of_commands[i].args[j][(strlen(list_of_commands[i].args[j]-1)) - 2] = 0;
            }
        }

        int pid = fork();
        if(pid == -1){
            syserror( "Error creating fork" );
        }
        else if(pid == 0){
            if (list_of_commands[i].flagOutput) {
                int fd;
                if ((fd = open(list_of_commands[i].oFile, O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
                    syserror("Error opening output file");
                if (dup2(fd, STDOUT_FILENO) < 0)
                    syserror("Error connecting STDOUT to file descriptor");
            }

            if (list_of_commands[i].append) {
                int fd;
                if ((fd = open(list_of_commands[i].oFile, O_WRONLY | O_APPEND, 0777)) < 0)
                    syserror("Error opening output file");
                if (dup2(fd, STDOUT_FILENO) < 0)
                    syserror("Error connecting STDOUT to file descriptor");
            }

            if (list_of_commands[i].flagInput) {
                int fd;
                if ((fd = open(list_of_commands[i].iFile, O_RDONLY)) < 0)
                    syserror("Error opening input file");
                if (dup2(fd, STDIN_FILENO) < 0)
                    syserror("Error connecting STDIN to file descriptor");
            }
            if (i != 0)
                if (dup2(pfd[(i-1)*2], STDIN_FILENO) < 0)
                    syserror( "Error connecting STDIN to pipe read pipe" );
            if (i != pipes)
                if (dup2(pfd[(i*2)+1], STDOUT_FILENO) < 0)
                    syserror( "Error connecting STDOUT to write pipe" );
            for (int i = 0; i < (pipes) * 2; i ++)
                if (close(pfd[i]) < 0)
                    syserror( "Error closing pipes" );

            execvp(list_of_commands[i].iden, list_of_commands[i].args);

            syserror( "Error could not execvp" );

        }

    } // end of for loop

    for (int i = 0; i < (pipes) * 2; i ++)
        if (close(pfd[i]) < 0)
            syserror( "Error closing remainder pipes" );

    while ( wait(NULL) != -1)
        ;

    //freeMem(cmds, (NumCmds));// * sizeof(command));
}

/*void freeMem(com_info* list_of_commands, int size){

    for (int i = 0; i < size; i++) {
        if(list_of_commands[i].args) free(list_of_commands[i].args);
        if(list_of_commands[i].iden) free(list_of_commands[i].iden;);
        if(list_of_commands[i].inFile) free(list_of_commands[i].inFile);
        if(list_of_commands[i].outFile) free(list_of_commands[i].inFile);
    }

    if (cmds) free(cmds);
    }*/

