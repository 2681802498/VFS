/**
 * install.cpp - System install / mount
 * Open virtual disk file, load superblock, init memory structures
 * Layer 1-2 (Member A)
 */
#include <cstdlib>
#include <cstring>
#include "filesys.h"

void install()
{
    // TODO: g_fd = fopen("filesystem", "r+b")
    // TODO: fseek + fread superblock from BLOCKSIZ offset into g_filsys
    // TODO: init g_hinode[NHINO] hash headers (i_forw = nullptr)
    // TODO: init g_sys_ofile[SYSOPENFILE] (f_count=0, f_inode=nullptr)
    // TODO: init g_user[USERNUM] (u_uid=0, u_ofile[]=SYSOPENFILE+1)
    // TODO: g_cur_path_inode = iget(1), load root dir into g_dir
}
