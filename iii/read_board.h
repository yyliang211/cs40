/*
 *                      read_board.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         File with function to read in a sudoku board from a given file 
 *         stream and populate a 2D array with its values. Will raise CREs if 
 *         given an invalid file, or invalid sudoky board. Uses uarray2.h.
 */

#ifndef READ_BOARD_INCLUDED
#define READ_BOARD_INCLUDED

/*
 * Takes in a file stream and a 2D array pointer. Populates the 2D array with 
 * the values on the board. Will raise CREs if given an invalid file or invalid 
 * sudoku board.
 */
void read_board(FILE *fp, UArray2_T *array);

#endif