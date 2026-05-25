/**
 * close.cpp - File close
 * Release user + system open file table entries, iput inode
 * Layer 4 (Member C)
 */
#include "filesys.h"

void close(unsigned int uid, unsigned short cfd)
{
    // TODO: sys_no = g_user[uid].u_ofile[cfd]
    // TODO: inode *ino = g_sys_ofile[sys_no].f_inode
    // TODO: iput(ino)
    // TODO: g_sys_ofile[sys_no].f_count--
    // TODO: g_user[uid].u_ofile[cfd] = SYSOPENFILE + 1
}
