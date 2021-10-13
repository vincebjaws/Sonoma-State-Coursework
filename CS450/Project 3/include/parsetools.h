#ifndef PARSETOOLS_H
#define PARSETOOLS_H

// Parse a command line into a list of words,
//    separated by whitespace.
// Returns the number of words
//

typedef struct args_cmds
{
    char* iden;
    char* iFile;
    char* oFile;
    char** args;
    int flagInput;
    int flagOutput;
    int numCount;
    int append;
    } com_info;

int split_cmd_line(char* line, char** list_to_populate);
void syserror( const char* s);
int is_less(const char* token);
int is_pipe(const char* token);
int is_more(const char* token);
int is_append(const char* token);
int is_command(const char* token);
void execute(char* command_line[], int tokenCount);
void freeMem(com_info* list_of_commands, int size);
#endif
