/**
 * balloc.cpp - Free disk block allocation
 * Group linking method (50 blocks per group)
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include "filesys.h"

unsigned int balloc()
{
    // TODO: if g_filsys.s_nfree == 0: return DISKFULL
    // TODO: free_block = g_filsys.s_free[g_filsys.s_pfree]
    // TODO: if s_pfree == NICFREE-1 (last block in stack):
    //         read next group info from free_block into s_free[]
    //         reset s_pfree and s_nfree from read count
    // TODO: else: s_pfree++, s_nfree--
    // TODO: g_filsys.s_fmod = SUPDATE
    // TODO: return free_block
    return DISKFULL;
}
