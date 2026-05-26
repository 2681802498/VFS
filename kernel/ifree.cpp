/**
 * ifree.cpp - Free disk inode deallocation
 * Layer 2 (Member A)
 */
#include "filesys.h"

void ifree(unsigned int dinodeid) {
  if(g_filsys.s_ninode < NICINOD) {
    g_filsys.s_ninode++;
    g_filsys.s_pinode++;
    g_filsys.s_inode[g_filsys.s_pinode] = dinodeid;
  }
  if(dinodeid < g_filsys.s_rinode) {
    g_filsys.s_rinode = dinodeid;
  }

  g_filsys.s_fmod = SUPDATE;
}
