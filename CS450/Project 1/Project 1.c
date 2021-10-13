#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>

/* These are the only two global variables allowed in your program */
static int verbose = 0;
static int use_fork = 0;

//Struct for the Sudoku board
struct SudokuBoardArgs{
    int array[9][9];
    int row;
    int column;
    int grid;
    int isValid;
};

// This is a simple function to parse the --fork argument.
// It also supports --verbose, -v
void parse_args(int argc, char *argv[])
{
    int c;
    while (1)
    {
        static struct option long_options[] =
                {
                        {"verbose", no_argument,       0, 'v'},
                        {"fork",    no_argument,       0, 'f'},
                        {0, 0, 0, 0}
                };
        int option_index = 0;
        c = getopt_long (argc, argv, "vf", long_options, &option_index);
        if (c == -1) break;

        switch (c)
        {
            case 'f':
                use_fork = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                exit(1);
        }
    }
}



void* check_column(void * arg);
void* check_row(void * arg);
void* check_grid(void * arg);
int arrbin_conv(int num[]);

int main(int argc, char *argv[])
{
    parse_args(argc, argv);
    int input = 0;
    int valid = 0;
    struct SudokuBoardArgs board[27];
    for (int i = 0; i < 27; i++) {
        board[i].grid = 0;
        board[i].column = 0;
        board[i].row = 0;
        board[i].isValid = 0;
    }
    if (verbose && use_fork) {
        printf("We are forking child processes as workers.\n");
    } else if (verbose) {
        printf("We are using worker threads.\n");
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            scanf("%d", &input);
            for(int a= 0; a < 27; a++) {
                board[a].array[i][j] = input;
            }
        }
    }


    if(use_fork){
        int bin_num[5] = {0, 0, 0, 0, 0};
        int i;


        // assigns binary array to each process
        for(i = 0; i < 5; i = i + 1){
            bin_num[i] = fork();
            if(bin_num[i] != 0) bin_num[i] = 1;
        }

        // changes binary array into decimal
        int num = arrbin_conv(bin_num);

        // terminates extra forked processes
        if(num > 26) exit(0);

        for(i = 0; i < 9; i++){
            if(num == i) check_row(&board[i]); // Checks Rows
            if(num == i+9) check_column(&board[i]); // Checks Columns
            if(num == i+18) check_grid(&board[i]); // Checks Subgrids

            board[i+1].row = i+1;
            board[i+1].column = i+1;
            board[i+1].grid = i+1;
        }

        // checks if there are any errors within the structs
        int valid = 0;
        for(i = 0; i < 27; i++){
            if(board[i].isValid == 1) valid += 1;
        }

        // Parent process is tasked with outputting final statement
        if(valid != 0){
            if(num == 0)
                printf("This input is not a valid sudoku\n");
        }
        else{
            if(num == 0)
                printf("This input is a valid sudoku\n");
        }
    }

    else{
        pthread_t tids[27];

        for(int i = 0; i < 9; i++) {
            pthread_create(&tids[i], NULL, check_row, &board[i]);
            pthread_create(&tids[i + 9], NULL, check_column, &board[i]);
            pthread_create(&tids[i + 18], NULL, check_grid, &board[i]);
            board[i+1].row = i+1;
            board[i+1].column = i+1;
            board[i+1].grid = i+1;
        }

        for(int i = 0; i < 9; i++) {
            pthread_join(tids[i], NULL);
            pthread_join(tids[i+9], NULL);
            pthread_join(tids[i+18], NULL);
        }

        for(int i = 0; i < 27; i++){
            if(board[i].isValid == 1) valid = 1;
        }

        if(valid == 1) printf("The input is not a valid sudoku");
        else printf("The input is a valid sudoku");
        return 0;
    }
}

void* check_row(void * arg){
    struct SudokuBoardArgs *r_board = (struct SudokuBoardArgs *)arg;
    int r_num = r_board->row;
    int valid_nums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 9; i++) {

        if (r_board->array[r_num][i] < 1){
            r_num = r_num + 1;
            printf("Row %d doesn't have the required values\n", r_num);
            r_board->isValid = 1;
            return NULL;
        }
        if (r_board->array[r_num][i] > 9){
            r_num = r_num + 1;
            printf("Row %d doesn't have the required values\n", r_num);
            r_board->isValid = 1;
            return NULL;
        }
        valid_nums[(r_board->array[r_num][i]) - 1] = (valid_nums[(r_board->array[r_num][i]) - 1]) + 1;
        if(valid_nums[(r_board->array[r_num][i]) - 1] > 1){
            r_num = r_num + 1;
            printf("Row %d doesn't have the required values\n", r_num);
            r_board->isValid = 1;
            return NULL;
        }
    }

    return NULL;
}

void* check_column(void * arg){
    struct SudokuBoardArgs *c_board = (struct SudokuBoardArgs *)arg;
    int c_num = c_board->column;
    int valid_nums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 9; i++) {
        //printf("%d\n", board->array[r_num][i]);
        if (c_board->array[i][c_num] < 1){
            c_num = c_num + 1;
            printf("Column %d doesn't have the required values\n", c_num);
            c_board->isValid = 1;
            return NULL;
        }
        if (c_board->array[i][c_num] > 9){
            c_num = c_num + 1;
            printf("Column %d doesn't have the required values\n", c_num);
            c_board->isValid = 1;
            return NULL;
        }
        valid_nums[(c_board->array[i][c_num])- 1] = (valid_nums[(c_board->array[i][c_num])- 1]) + 1;
        if(valid_nums[(c_board->array[i][c_num])- 1] > 1){
            c_num = c_num + 1;
            printf("Column %d doesn't have the required values\n", c_num);
            c_board->isValid = 1;
            return NULL;
        }
    }

    return NULL;
}

void* check_grid(void * arg) {
    struct SudokuBoardArgs *g_board = (struct SudokuBoardArgs *) arg;
    int g_num = g_board->grid;
    int valid_nums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int a = 0;
    int b = 0;
    if (g_num == 0) {
        a = 0;
        b = 0;
    }
    if (g_num == 3) { //1
        a = 3;
        b = 0;
    }
    if (g_num == 6) { //2
        a = 6;
        b = 0;
    }
    if (g_num == 1) {//3
        a = 0;
        b = 3;

    }
    if (g_num == 4) {
        a = 3;
        b = 3;
    }
    if (g_num == 7) { //5
        a = 6;
        b = 3;
    }
    if (g_num == 2) {
        a = 0;
        b = 6;
    }
    if (g_num == 5) {
        a = 3;
        b = 6;
    }
    if (g_num == 8) {
        a = 6;
        b = 6;
    }
    for (int i = a; i < (a + 3); i++) {
        for (int j = b; j < (b + 3); j++) {
            //printf("%d\n", board->array[i][j]);
            if (g_board->array[i][j] < 1) {
                //i = i + 1;
                //j = j + 1;
                printf("Grid %d doesn't have the required values\n", g_board->grid + 1);
                g_board->isValid = 1;
                return NULL;
            }
            if (g_board->array[i][j] > 9) {
                //i = i + 1;
                //j = j + 1;
                printf("Grid %d doesn't have the required values\n", g_board->grid + 1);
                g_board->isValid = 1;
                return NULL;
            }
            valid_nums[(g_board->array[i][j]) - 1] = (valid_nums[(g_board->array[i][j]) - 1]) + 1;
            if (valid_nums[(g_board->array[i][j]) - 1] > 1) {
                //i = i + 1;
                //j = j + 1;
                printf("Grid %d doesn't have the required values\n", g_board->grid + 1);
                g_board->isValid = 1;
                return NULL;
            }
        }
    }
    return NULL;
}

// converts binary from num[] to decimal
int arrbin_conv(int num[]){
    int i;
    int out = 0, pow = 1;
    for(i = 0; i < 5; i++){
        out += num[4-i]*pow;
        pow *= 2;
    }
    return out;
}