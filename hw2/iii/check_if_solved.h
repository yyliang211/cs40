/*
 *                      checked_if_solved.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the declarations of functions that check if a 
 *         sudoku board is correct. It needs uarray2.h for its implementation. 
 *         If it the sudoku puzzle is incorrect it will exit with code 1 
 *         otherwise if it is correct it will return 0.
 */

#ifndef CHECK_IF_SOLVED_INCLUDED
#define CHECK_IF_SOLVED_INCLUDED

/*
 * Takes in a 2D array filled with the values of a sudoku board and checks each 
 * row, column, and submap and calls the validate function on each one. If the 
 * validate function does not exit with code 1 it will return 0.
 */
int check(UArray2_T *array);

/* 
 * Takes in an index (col, row), a 2D array, and an array of frequencies. Then 
 * loops through submaps in the board starting by the given index and calls the 
 * validate function on each one.
 */
void check_3x3(int col, int row, UArray2_T array, void *array_freq);

/*
 * Takes in an index (col, row), a 2D array (sudoku board values), an element 
 * (int 1-9), and an array of frequencies. Validates row/column/submap by 
 * keeping track of how many times it has seen each element with a frequency 
 * array. It will exit with code 1 if it finds any repetitions.
 */
void validate(int col,
              int row,
              UArray2_T uarray2,
              void *elem,
              void *freq_array);

#endif