/*
 *                      sudoku.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains a program that takes in the name of a file to be 
 *         read in, if none is given it will read it in from stdin, reads and 
 *         populates a 2D array with the all the pixels' densities, forming a 
 *         sudoku puzzle. It will then check if the given sudoku puzzle has 
 *         been correctly solved. It will return 0 if the sudoku puzzle is 
 *         correct, otherwise it will return 1. Program will raise CREs if the 
 *         given file name is not valid or it cannot open the file.
 */

#include <stdio.h>
#include <stdlib.h>

#include "except.h"
#include "uarray2.h"
#include "exceptions.h"
#include "check_if_solved.h"
#include "read_board.h"

int main (int argc, char *argv[])
{
    FILE *infile;

    /* Check that only a max of one file is given */    
    if (argc > 2) {    
        RAISE(Incorrect_Usage_Sudoku);    
    } else if (argc == 2) {    
        /* Attempt to open given file */
        infile = fopen(argv[1], "r");

        if (infile == NULL) {        
            RAISE(Invalid_File);
        }
    } else {
        /* If no file was provided read in from stdin */
        extern FILE *stdin;
        infile = stdin;
    }

    /* Create empty 9x9 sudoky board */
    UArray2_T array = UArray2_new(9, 9, sizeof(int));
    
    /* Populate board with values read in from file */
    read_board(infile, &array);
    
    /* Close input file */
    fclose(infile);    
    infile = NULL;

    /* Check if board is solved and return result */
    int result = check(&array);

    /* Free data and structures used*/
    UArray2_free(&array);

    return result;
}