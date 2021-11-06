#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <except.h>
#include "readaline.h"

/* readaline
 * purpose: return the size of the line and store the line into datapp 
 * arguments: FILE *inpufd is a file pointer to be read
 *            char **datapp is double pointer to store the line going to be read
 * return: size_t is the size of the line
*/
size_t readaline(FILE *inputfd, char **datapp)
{
    // if FILE * is null then return error statement using assert.
    assert(inputfd);  
    
    int size  = 100;
    int index = 0; 
    char c    = fgetc(inputfd);

    // create space in memory to store char * 
    *datapp   = malloc(size);

    // if the file has no more lines to read 
    // then set *datapp = NULL and return 0
    if(c == EOF) {
        free(*datapp);
        *datapp = NULL;
        return 0;
    }

    // if the number of characters is LESS than size = 1000, then store the 
    // character into the collection in the stack.
    // if the number of characters is GREATER OR EQUAL to size = 1000, then 
    // reallocate twice the size and update size. Then store the character into
    // the collection in the stack.
    while(c != EOF) {
        if(c != '\n') {
            if (index < size - 2) {
            *(*datapp + index) = c;
            index++;
            c = fgetc(inputfd);
            }
            else {
            size *= 2;
            *datapp = realloc(*datapp, size);
            }
        }
        else {
            *(*datapp + index) = '\n';
            break;
        }
    }
    // return number of elements casted to size_t
    return (size_t) index + 1;
}