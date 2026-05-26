/**
 * ialloc.cpp - Free disk inode allocation
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include <cstring>

#include "filesys.h"

inode* ialloc() {
  if (g_filsys.s_ninode == 0) {
    unsigned int count = 0;
    dinode disk_inode;
    for (unsigned int i = g_filsys.s_rinode;
         i < DINODEBLK * (BLOCKSIZ / DINODESIZ); i++) {
      fseek(g_fd, DINODESTART + i * DINODESIZ, SEEK_SET);
      fread(&disk_inode, sizeof(dinode), 1, g_fd);
      if (disk_inode.di_number == 0) {
        g_filsys.s_inode[count++] = i;
        if (count >= NICINOD) {
          g_filsys.s_rinode = i + 1;
          break;
        }
      }
    }
    if (count == 0) {
      printf("Error: No free inodes available.\n");
      return nullptr;
    }
    g_filsys.s_ninode = count;
    g_filsys.s_pinode = count - 1;
  }

  unsigned int dinode_id = g_filsys.s_inode[g_filsys.s_pinode];
  g_filsys.s_pinode--;
  g_filsys.s_ninode--;
  g_filsys.s_fmod = SUPDATE;

  inode* ino = iget(dinode_id);
  if (!ino) {
    printf("Error: Failed to read inode from disk.\n");
    return nullptr;
  }

  dinode empty_inode;
  memset(&empty_inode, 0, sizeof(empty_inode));
  empty_inode.di_number = 1;

  fseek(g_fd, DINODESTART + dinode_id * DINODESIZ, SEEK_SET);
  fwrite(&empty_inode, sizeof(empty_inode), 1, g_fd);

  /* Sync memory inode: iget() loaded stale (zeroed) data before this write */
  ino->di_number = 1;

  return ino;
}
