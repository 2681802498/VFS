/**
 * dir.cpp - Directory operations
 * _dir(): list current directory
 * mkdir(): create subdirectory
 * chdir(): change current directory
 * Layer 5 (Member B)
 */
#include <cstring>
#include <cstdio>
#include "filesys.h"

void _dir()
{
    // TODO: iterate g_dir.direct[0..g_dir.size-1]
    // TODO: for each valid entry: print d_name + permission string(rwx)
    // TODO: if file: print size + block chain (iget -> check DIFILE)
    // TODO: if dir: print <dir>
    // TODO: iput each inode
}

void mkdir(const char *dirname)
{
    // TODO: namei check for duplicate name
    // TODO: iname get empty slot
    // TODO: ialloc() new inode, balloc() new data block
    // TODO: write "." (self) and ".." (parent) entries to data block
    // TODO: set inode: di_mode = DIDIR | g_user[g_user_id].u_default_mode
    // TODO: set di_uid/gid, di_size = 2*(DIRSIZ+2), di_addr[0] = block
    // TODO: g_dir.size++, iput(inode)
}

void chdir(const char *dirname)
{
    // TODO: namei + iget target directory inode
    // TODO: access check permission
    // TODO: writeback current g_dir to g_cur_path_inode (compact entries)
    // TODO: iput(g_cur_path_inode), g_cur_path_inode = target inode
    // TODO: load new dir content from disk into g_dir
}
