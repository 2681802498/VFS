/**
 * halt.cpp - System shutdown
 * Writeback data, close files, close virtual disk
 * Layer 6-7 (Member D)
 */
#include <cstdio>
#include <cstdlib>
#include "filesys.h"

void halt()
{
    // TODO: chdir("..") writeback current dir
    // TODO: iput(g_cur_path_inode)
    // TODO: for each logged-in user: logout(g_user[i].u_uid)
    // TODO: writeback g_filsys to disk at BLOCKSIZ offset
    // TODO: fclose(g_fd)
    // TODO: printf("Good Bye...\n"), exit(0)
}
