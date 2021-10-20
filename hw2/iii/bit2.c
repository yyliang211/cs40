/*
 *                      bit2.c
 *
 *         Assignment: CS40 HW2 -- iii
 *         Authors: Yingyang Liang & Ale Trujillo
 *         Date: Oct 4, 2021
 *
 *         This file contains the implementation for a two-dimensional array
 *         of bits. Each 2D bit array is represented by a Bit2_T struct that
 *         contains the width, height and a 1D bit array using Hanson's bit 
 *         vector ADT.
 *         We use a index converter function to map 2D indicies in the format
 *         [col][row] to a singular index in the 1D bit vector. 
 *         We utilize the put and get functions from Hanson to store and
 *         retrieve bits since bits cannot be pointed to by an address.
 *         Lastly, we have two mapping functions going to map in row-major *         order and column-major order.
 *
 *         Checks for errors such as if the Bit2 passed in is NULL, bounds
 *         checking and if the bit inserted is a 1 or 0.
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "bit2.h"
#include "bit.h"
#include "except.h"
#include "assert.h"

#define T Bit2_T

/* Struct used to represent a 2D bit vector using singular 1D bit vector*/
struct Bit2_T {
    int width;    /* number of elements per row, at least 1 */
	int height;   /* number of elements per column, at least 1 */
    Bit_T array;  /* 1D array that holds all the elements of the 2D array */
};

/* 
* Takes in width and height as integers, creates and returns Bit2_T
* using those dimensions.
* Raises CRE if width and height are less than 1 or is not able to allocate 
* memory.
*/
T Bit2_new(int arr_width, int arr_height) {
    /* Ensure width and height are positive */
	assert((arr_width > 0) && (arr_height > 0));

	T bit_array;
	NEW (bit_array);
    int length = arr_width * arr_height;

	assert(bit_array != NULL);

	/* Initialize Bit2 with given values and new Bit_T */
	bit_array->array = Bit_new(length);
	bit_array->width = arr_width;
	bit_array->height = arr_height;

	return bit_array;
}

/* 
* Takes in a Bit2_T and returns its width.
* Raises CRE if Bit2_T is NULL.
*/
int Bit2_width(T bit_array) {
    assert(bit_array != NULL);

	return bit_array->width;
}

/* 
* Takes in a Bit2_T and returns its height.
* Raises CRE if Bit2_T is NULL.
*/
int Bit2_height(T bit_array) {
    assert(bit_array != NULL);

	return bit_array->height;
}

/* 
* Takes in a Bit2_T and two integers representing column, row respectively.
* Returns corresponding index in 1D bit vector for the 2D index [column][row].
* Raises CRE if given 2D index is out of bounds.
*/
int index_converter(T bit_array, int col, int row)
{	
	assert(bit_array != NULL);
	
	int width = Bit2_width(bit_array);
	int height = Bit2_height(bit_array);

	/* Assert that index given is within 2D array dimensions */
	assert((col < width) && (col >= 0) && (row < height) && (row >= 0));

	int index = row * width + col;
	return index;
}

/* 
* Takes in a Bit2_T, a 2D index as ints col, row and a bit.
* Converts 2D index [col][row] to 1D index [index].
* Sets bit [index] to [bit] and returns the previous value of bit [index].
* Raises CRE if bit is not 0 or 1, if Bit2_T is NULL or if give index is
* out of bounds.
*/
int Bit2_put(T bit_array, int col, int row, int bit) {
    assert(bit_array != NULL);
    assert(bit == 0 || bit == 1);

    //asserts that index is within 2d array dimension
    int index = index_converter(bit_array, col, row);
    return Bit_put(bit_array->array, index, bit);
}

/* 
* Takes in a Bit2_T, a 2D index as ints col, row.
* Converts 2D index to 1D index.
* Returns bit at index.
* Raises CRE if bit is not 0 or 1, if Bit2_T is NULL or if give index is
* out of bounds.
*/
int Bit2_get(T bit_array, int col, int row) {
    assert(bit_array != NULL);

    /* Asserts that index is within 2d array dimension */
    int index = index_converter(bit_array, col, row);
    return Bit_get(bit_array->array, index);
}

/* 
* Takes in a Bit2_T, apply function and closure argument.
* Traverses 2D array in col-major order and calls apply function on 
* each element.
* Returns nothing.
* Raises CRE if Bit2_T is NULL.
*/
void Bit2_map_col_major(T bit_array,
                        void apply(int col, int row, Bit2_T array, int bit, void *accum),
                        void *cl)
{
    assert(bit_array != NULL);

	int width = bit_array->width;
	int height  = bit_array->height;

	for (int col = 0; col < width; col++) {

		for (int row = 0; row < height; row++) {

			int bit = Bit2_get(bit_array, col, row);
			apply(col, row, bit_array, bit, cl);
		}
	}    
}

/* 
* Takes in a Bit2_T, apply function and closure argument.
* Traverses 2D array in row-major order and calls apply function on 
* each element.
* Returns nothing.
* Raises CRE if Bit2_T is NULL.
*/
void Bit2_map_row_major(T bit_array,
                        void apply(int col, int row, Bit2_T array, int bit, void *accum),
                        void *cl)
{
    assert(bit_array != NULL);

	int width = bit_array->width;
	int height  = bit_array->height;

	for (int row = 0; row < height; row++) {

		for (int col = 0; col < width; col++) {

			int bit = Bit2_get(bit_array, col, row);
			apply(col, row, bit_array, bit, cl);
		}
	}  
}

/* 
* Takes in a pointer to Bit2_T.
* Frees Bit2_T.
* Returns nothing.
* Raises CRE if Bit2_T or pointer to Bit2_T is NULL.
*/
void Bit2_free(T *bit_array)
{
    assert(bit_array != NULL);
    assert(*bit_array != NULL);
    
    /* Dereference pointer to get array and free both 1D array and bit2 struct*/
    Bit2_T arr2 = *bit_array;
    Bit_free(&(arr2->array));
    free(*bit_array);
}