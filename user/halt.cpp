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
    //writeback current dir
    chdir("..");
    iput(g_cur_path_inode);
    for(int i = 0 ; i < USERNUM ;i++){
        logout(g_user[i].u_uid);
    }
    // writeback g_filsys (superblock) to disk at BLOCKSIZ offset
    if (g_fd) {
        if (fseek(g_fd, BLOCKSIZ, SEEK_SET) == 0) {
            if (fwrite(&g_filsys, sizeof(g_filsys), 1, g_fd) != 1) {
                g_vfs_errno = E_VFS_IO;
                printf("Error: %s\n", vfs_strerror(E_VFS_IO));
            } else {
                fflush(g_fd);
            }
        } else {
            g_vfs_errno = E_VFS_IO;
            printf("Error: %s\n", vfs_strerror(E_VFS_IO));
        }

        fclose(g_fd);
        g_fd = nullptr;
    }

    printf("Good Bye...\n");
    exit(0);
}
