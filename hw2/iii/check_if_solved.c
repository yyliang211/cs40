/*
 *                      checked_if_solved.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the functions that check if a sudoku board is 
 *         correct. It uses a 2D array by using uarray2.h to store the values 
 *         in the board. If it finds a number repeated in a row, column, or 
 *         submap it will exit with code 1 otherwise it will return 0.
 */

#include <stdio.h>
#include <stdlib.h>

#include "except.h"
#include "uarray2.h"
#include "exceptions.h"

/* 
 * Takes in an index (col, row), a 2D array, an element (an int from 1-9), and 
 * a pointer to an array of frequencies of 10 elements. It uses the array of 
 * frequencies to keep track of the times it has seen an element, while the 0 
 * position in the array is used to track how many elements we have seen in 
 * total. It goes through the elements and if it encounters an element twice it 
 * exits the program with 1.
 */
void validate(int col,
              int row,
              UArray2_T uarray2,
              void *elem,
              void *array_freq_ptr)
{
    (void) col;
    (void) row;
    (void) uarray2;

    int *array = (int *)array_freq_ptr;

    int index = *(int *)elem;

    /* If value in array is 1 or more it means we've seen it before, exit(1) */
    if (*(array + index) >= 1) {
        UArray2_free(&uarray2);
        exit(1);
    } else {
        /* If we haven't seen the element add one to that index in the array */
        (*(array + index)) = *(array + index)+1;
    }

    /* Continue updating how many elements we've seen in total (position) */
    *array = *array + 1;
    int position = *array;


    /* If position is 9, we've gotten to the end of the row/col, clear table */
    if (position == 9) {
        for (int i = 0; i < 10; i++) {
            (*(array + i)) = 0;
        }
    }

    /* Exception if position ever exceeds 9 which it should not do */
    if (position > 9) {
        RAISE(Sudoku_Check_Error);
    }
}   

/*
 * Takes in an index (col, row), a 2D array, and an array of frequencies. It 
 * loops through submaps in the board starting by the given index and validates 
 * that the submap is correct.
 */
void check_3x3(int col, int row, UArray2_T array, void *array_freq) {
    for (int sub_col = col; sub_col < col + 3; sub_col++) {

        for (int sub_row = row; sub_row < row + 3; sub_row++) {

            void *elem = UArray2_at(array, sub_col, sub_row);
            validate(sub_col, sub_row, array, elem, array_freq);
        }
    }
}

/* 
 * Takes in a 2D array populated with the values of a sudoku board. Goes 
 * through the rows, colums, and and submaps individually and validates each 
 * one of them. If it is incorrect it will exit with code 1, otherwise it will 
 * return 0.
 */
int check(UArray2_T *array)
{
    if ((array == NULL) || (*array == NULL)) {
        RAISE(Input_Null);
    }

    int array_freq[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /* Validate both rows and columns are correct. */
    UArray2_map_col_major(*array, validate, &array_freq);
    UArray2_map_row_major(*array, validate, &array_freq);

    int col = 0;
    int row = 0;
    
    /* Loop through 3x3 submaps and validates each one */
    for (int i = 1; i < 10; i++) {
        if (col == 9){
            row = row + 3;
            col = 0;
        }

        check_3x3(col, row, *array, &array_freq);
        col = col + 3;
    }

    /* If had not exited yet, it is correct, return 0 */
    return 0;
}


