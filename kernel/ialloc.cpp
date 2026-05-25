/**
 * ialloc.cpp - Free disk inode allocation
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include "filesys.h"

inode *ialloc()
{
    // TODO: if g_filsys.s_ninode runs out, scan disk inode area to refill
    // TODO: dinode_id = g_filsys.s_inode[g_filsys.s_pinode]
    // TODO: inode *ino = iget(dinode_id)
    // TODO: zero out dinode area on disk
    // TODO: s_pinode++, s_ninode--, s_fmod = SUPDATE
    // TODO: return ino
    return nullptr;
}
