

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"
#include "uarray2.h"
#include "uarray.h"
#include "except.h"
#include "assert.h"

#define T UArray2_T

struct UArray2_T {
    int width;    /* number of elements per row, at least 1 */
	int height;   /* number of elements per column, at least 1 */
    int size;     /* number of bytes in one element */
    UArray_T array;  /* 1D array that holds all the elements of the 2D array */
};

T UArray2_new(int arr_width, int arr_height, int arr_size)
{
	/* Ensure width, height and size are positive */
	assert((arr_size > 0) && (arr_width > 0) && (arr_height > 0));

	int length = arr_width * arr_height;
	T uarray2;
	NEW(uarray2);

	assert(uarray2 != NULL);

	/* Initialize UArray2 with given values and new UArray */
	uarray2->array = UArray_new(length, arr_size);
	uarray2->width = arr_width;
	uarray2->height = arr_height;
	uarray2->size = arr_size;

	return uarray2;
}

int UArray2_width(T uarray2)
{
	assert(uarray2 != NULL);
	return uarray2->width;
}

int UArray2_height(T uarray2)
{
	assert(uarray2 != NULL);
	return uarray2->height;
}

int UArray2_size(T uarray2)
{
	assert(uarray2 != NULL);
	return uarray2->size;
}

int index_converter(T uarray2, int col, int row)
{
	assert(uarray2 != NULL);
	
	int width = UArray2_width(uarray2);
	int height = UArray2_height(uarray2);

	/* Assert that index given is within 2D array dimensions */
	assert((col < width) && (col >= 0) && (row < height) && (row >= 0));

	int index = row * width + col;
	return index;
}

void *UArray2_at(T uarray2, int col, int row)
{
	assert(uarray2 != NULL);
	int index = index_converter(uarray2, col, row);
	return UArray_at(uarray2->array, index);
}

/* Row indices vary more rapidly than column indices. (Vertical) */
void UArray2_map_col_major(T uarray2,
                           void apply(int col,int row, T uarray2, void *elem, void *accum),
                           void *cl)
{
	assert(uarray2 != NULL);

	int width = uarray2->width;
	int height  = uarray2->height;

	for (int col = 0; col < width; col++) {

		for (int row = 0; row < height; row++) {
			void *elem = UArray2_at(uarray2, col, row);
			apply(col, row, uarray2, elem, cl);
		}
	}
}

/* Column indices vary more rapidly than row indices. (Horizontal) */
void UArray2_map_row_major(T uarray2,
                           void apply(int col, int row, T uarray2, void *elem, void *accum),
                           void *cl)
	{
		assert(uarray2 != NULL);

		int width = uarray2->width;
		int height  = uarray2->height;

		for (int row = 0; row < height; row++) {

			for (int col = 0; col < width; col++) {
				void *elem = UArray2_at(uarray2, col, row);
				apply(col, row, uarray2, elem, cl);
			}
		}
	}


void UArray2_free(T *uarray2)
{
    assert(uarray2 != NULL);
    assert(*uarray2 != NULL);
	
	/* Dereference pointer to get array and free both 1D array and uarray2 struct*/
	T arr2 = *uarray2;
	UArray_free(&(arr2->array));
	FREE(*uarray2);
}