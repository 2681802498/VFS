/**
 * open.cpp - File open
 * Open existing file with FREAD / FWRITE / FAPPEND mode
 * Layer 4 (Member C)
 */
#include <cstdio>
#include "filesys.h"

unsigned short aopen(unsigned int uid, const char *filename, unsigned short openmode)
{
    // TODO: namei find file (return -1 if not found)
    // TODO: iget inode, access check permission
    // TODO: find empty slot in g_sys_ofile (f_count == 0, start from 1)
    // TODO: set f_flag=openmode, f_count=1, f_inode=inode
    // TODO: FAPPEND: f_off = inode->di_size; else f_off = 0
    // TODO: find empty slot in g_user[uid].u_ofile
    // TODO: g_user[uid].u_ofile[j] = sys_no
    // TODO: return user fd (j)
    return 0;
}
