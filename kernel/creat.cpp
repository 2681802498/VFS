/**
 * creat.cpp - File creation
 * Create new file or truncate existing one
 * Layer 4 (Member C)
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "filesys.h"

int creat(unsigned int uid, const char *filename, unsigned short mode)
{
    // TODO: namei check if file exists
    // TODO: exists: iget inode, access check, bfree all data blocks
    //         di_size = 0, update sys_ofile f_off for open instances
    // TODO: not exists: iname empty slot + ialloc new inode
    //         set di_mode, di_uid, di_gid, di_size = 0
    //         g_dir.direct[slot].d_ino = inode->i_ino
    //         g_dir.size++
    // TODO: find empty slot in g_sys_ofile (f_count == 0)
    // TODO: find empty slot in g_user[uid].u_ofile (== SYSOPENFILE+1)
    // TODO: link and return user fd
    return -1;
}
