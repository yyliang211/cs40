/*
 *                      excpetions.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the description of every Checked Runtime Error 
 *         used in either the Sudoku program and/or the Unblackedges program. 
 *         When called, the program will abort, terminating immediately. The 
 *         exceptions are implemented using Hanson's Except_T.
 */

#include <stdio.h>
#include "except.h"

Except_T Incorrect_Usage_Sudoku = {"Usage: ./sudoku OR ./sudoku filename"};
Except_T Incorrect_Usage_Unblackedges =
    {"Usage: ./unblackedges OR ./unblackedges filename"};
Except_T Cannot_Open_File = {"Cannot open file"};
Except_T Malloc_Fail = {"Failed to allocate memory"};
Except_T Input_Null = {"Input is NULL"};
Except_T Invalid_File = {"File is invalid"};
Except_T Invalid_Number = {"Number must be in between 1 - 9"};
Except_T Array_Not_Init = {"Array is not initialized\n"};
Except_T Invalid_Table_Length = {"Table should have ten key-value pairs"};
Except_T Sudoku_Check_Error = {"Position in table > 9, error in sudoku check"};