/**
 * rdwt.cpp - File read / write operations
 * vfs_read():  read data from file
 * vfs_write(): write data to file
 * Layer 4 (Member C)
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "filesys.h"

unsigned int vfs_read(unsigned int fd, char *buf, unsigned int size)
{
    // TODO: get sys_ofile index via g_user[g_user_id].u_ofile[fd]
    // TODO: inode *ino = g_sys_ofile[sys_no].f_inode
    // TODO: check g_sys_ofile[sys_no].f_flag & FREAD
    // TODO: off = g_sys_ofile[sys_no].f_off
    // TODO: if off + size > ino->di_size: size = ino->di_size - off
    // TODO: loop over blocks with fread()
    // TODO: g_sys_ofile[sys_no].f_off += size
    return 0;
}

unsigned int vfs_write(unsigned int fd, const char *buf, unsigned int size)
{
    // TODO: get sys_ofile index via g_user[g_user_id].u_ofile[fd]
    // TODO: inode *ino = g_sys_ofile[sys_no].f_inode
    // TODO: check g_sys_ofile[sys_no].f_flag & FWRITE
    // TODO: off = g_sys_ofile[sys_no].f_off
    // TODO: loop over blocks with fwrite(), call balloc() for new blocks
    // TODO: update ino->di_size = max(off+size, ino->di_size)
    // TODO: g_sys_ofile[sys_no].f_off += size
    return 0;
}
