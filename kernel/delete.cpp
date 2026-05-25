/**
 * delete.cpp - File deletion
 * Decrement di_number; iput handles actual reclamation
 * Layer 4 (Member C)
 */
#include <cstdio>
#include "filesys.h"

void delete_file(const char *filename)
{
    // TODO: di = namei(filename); if not found: print error, return
    // TODO: inode *ino = iget(g_dir.direct[di].d_ino)
    // TODO: ino->di_number--
    // TODO: if di_number == 0: g_dir.direct[di].d_ino = 0 (clear dir entry)
    // TODO: iput(ino) -- iput detects di_number==0 and reclaims
}
