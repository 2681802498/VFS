/**
 * ifree.cpp - Free disk inode deallocation
 * Layer 2 (Member A)
 */
#include "filesys.h"

void ifree(unsigned int dinodeid)
{
    // TODO: g_filsys.s_ninode++
    // TODO: if s_pinode != NICINOD: s_inode[s_pinode] = dinodeid, s_pinode++
    // TODO: else if dinodeid < s_rinode: update s_rinode
    // TODO: g_filsys.s_fmod = SUPDATE
}
