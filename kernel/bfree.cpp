/**
 * bfree.cpp - Free disk block deallocation
 * Layer 2 (Member A)
 */
#include <cstdlib>
#include <cstring>

#include "filesys.h"

void bfree(unsigned int block_num) {
  if (g_filsys.s_nfree == NICFREE) {
    char block[BLOCKSIZ];
    memset(block, 0, BLOCKSIZ);
    unsigned int* block_ptr = (unsigned int*)block;
    block_ptr[0] = g_filsys.s_nfree;
    memcpy(block + sizeof(unsigned int), g_filsys.s_free,
           NICFREE * sizeof(unsigned int));
    fseek(g_fd, DATASTART + block_num * BLOCKSIZ, SEEK_SET);
    fwrite(block, BLOCKSIZ, 1, g_fd);

    g_filsys.s_free[0] = block_num;
    g_filsys.s_nfree = 1;
    g_filsys.s_pfree = 0;
  } else {
    g_filsys.s_pfree++;
    g_filsys.s_nfree++;
    g_filsys.s_free[g_filsys.s_pfree] = block_num;
  }

  g_filsys.s_fmod = SUPDATE;
}
