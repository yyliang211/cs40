/*
 *                      excpetions.h
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the declaration of every Checked Runtime Error 
 *         used in either the Sudoku program and/or the Unblackedges program. 
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdio.h>
#include "except.h"

Except_T Array_Not_Init;
Except_T Incorrect_Usage_Sudoku;
Except_T Incorrect_Usage_Unblackedges;
Except_T Cannot_Open_File;
Except_T Malloc_Fail;
Except_T Input_Null;
Except_T Invalid_File;
Except_T Invalid_Number;
Except_T Invalid_Table_Length;
Except_T Sudoku_Check_Error;

#endif