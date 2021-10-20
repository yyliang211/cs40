#include <stdlib.h>
#include <stdio.h>
#include <pnmrdr.h>
#include <assert.h>
#include "readaline.h"
#include "table.h"
#include "atom.h"
#include "seq.h"

extern Seq_T read_file(FILE *fp, int *width, int *height);