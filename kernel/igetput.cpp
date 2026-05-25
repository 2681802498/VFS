/**
 * igetput.cpp - Memory inode get / put
 * iget(): hash lookup + disk load
 * iput(): refcount --, writeback + free when zero
 * Layer 3 (Member B)
 */
#include <cstdlib>
#include "filesys.h"

inode *iget(unsigned int dinodeid)
{
    // TODO: hash = dinodeid % NHINO
    // TODO: walk g_hinode[hash].i_forw linked list for cached inode
    // TODO: hit: i_count++, return inode
    // TODO: miss: malloc new inode
    // TODO: fseek(g_fd, DINODESTART + dinodeid * DINODESIZ, SEEK_SET)
    // TODO: fread dinode fields into inode
    // TODO: set i_ino, i_count=1, i_flag=0, insert at hash chain head
    // TODO: return inode
    return nullptr;
}

void iput(inode *pinode)
{
    // TODO: if i_count > 1: i_count--, return
    // TODO: if di_number != 0: writeback inode to disk
    //         fseek + fwrite at DINODESTART + i_ino * DINODESIZ
    // TODO: if di_number == 0: bfree all data blocks, ifree disk inode
    // TODO: remove from hash chain, free(pinode)
}
