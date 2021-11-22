#include <stdint.h>
#include <stdio.h>
#include "seq.h"

uint32_t next_id(Seq_T avail, uint32_t *avail_after);
void reuse_id(Seq_T avail, uint32_t *avail_after, uint32_t id);

int main()
{

}

uint32_t next_id(Seq_T avail, uint32_t *avail_after)
{
    uint32_t id = 0;
    if (Seq_length(avail) == 0){
        id = *avail_after;
        (*avail_after)++;
    } else {
        id = (uint32_t)Seq_remlo(avail);
    }
}

void reuse_id(Seq_T avail, uint32_t *avail_after, uint32_t id)
{
    /* if it's right under avail_after, change avail_after to be id
     * if it's greater than avail_after, do nothing b/c it's already in the set
     * of available ids
     * if it's less, add it to sequence */
    if (id == *avail_after - 1) {
        (*avail_after)--;
    } else if (id < *avail_after) {
        Seq_addhi(avail, &id);
    }
}
