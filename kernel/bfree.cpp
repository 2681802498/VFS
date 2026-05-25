/**
 * bfree.cpp - Free disk block deallocation
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include "filesys.h"

void bfree(unsigned int block_num)
{
    // TODO: if g_filsys.s_nfree == NICFREE (stack full):
    //         write current s_free[] content into block_num
    //         s_nfree = 1, s_free[0] = block_num, s_pfree = 0
    // TODO: else: s_free[s_pfree] = block_num, s_pfree++, s_nfree++
    // TODO: g_filsys.s_fmod = SUPDATE
}
