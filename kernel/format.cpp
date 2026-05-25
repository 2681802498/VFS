/**
 * format.cpp - Virtual disk format
 * Initialize superblock, inode area, root dir, etc dir, password file
 * Layer 1-2 (Member A)
 */
#include <cstdlib>
#include <cstring>
#include "filesys.h"

void format()
{
    // TODO: g_fd = fopen("filesystem", "w+b")
    // TODO: init g_filsys (free block stack, free inode stack)
    // TODO: create root dir "/" (inode=1): . and .. entries
    // TODO: create etc dir (inode=2): . and .. entries
    // TODO: create password file (inode=3)
    // TODO: init free block chain (group linking method)
    // TODO: write superblock back to disk
}
