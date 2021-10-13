#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "constants.h"
#include "parsetools.h"

int main()
{
    // Buffer for reading one line of input
    char line[MAX_LINE_CHARS];
    char* line_words[MAX_LINE_WORDS + 1];

    // Loop until user hits Ctrl-D (end of input)
    // or some other input error occurs
    while(fgets(line, MAX_LINE_CHARS, stdin))
    {
        // Get the number of words user inserted
        int num_words = split_cmd_line(line, line_words);

        // Get the commands from user input and execute
        execute(line_words, num_words);

    } // end of while

    return 0;

} // end of main
