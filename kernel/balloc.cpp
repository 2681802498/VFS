/**
 * balloc.cpp - Free disk block allocation
 * Group linking method (50 blocks per group)
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include <cstring>

#include "filesys.h"

unsigned int balloc() {
  if (g_filsys.s_nfree == 0) {
    printf("Error: No free disk blocks available.\n");
    return DISKFULL;
  }

  unsigned int free_block = g_filsys.s_free[g_filsys.s_pfree];

  if (g_filsys.s_nfree == 1) {
    char block[BLOCKSIZ];
    memset(block, 0, BLOCKSIZ);

    fseek(g_fd, DATASTART + free_block * BLOCKSIZ, SEEK_SET);
    fread(block, BLOCKSIZ, 1, g_fd);
    unsigned int next_nfree = ((unsigned int*)block)[0];
    if (next_nfree > 0 && next_nfree <= NICFREE) {
      memcpy(g_filsys.s_free, block + sizeof(unsigned int),
             next_nfree * sizeof(unsigned int));
      g_filsys.s_nfree = next_nfree;
      g_filsys.s_pfree = next_nfree - 1;
    } else {
      g_filsys.s_nfree = 0;
      g_filsys.s_pfree = 0;
    }
  } else {
    g_filsys.s_pfree--;
    g_filsys.s_nfree--;
  }

  g_filsys.s_fmod = SUPDATE;

  return free_block;
}
