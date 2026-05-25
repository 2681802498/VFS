/**
 * name.cpp - Directory entry lookup
 * namei(): search dir entry by name
 * iname(): find empty dir entry slot
 * Layer 5 (Member B)
 */
#include <cstring>
#include <cstdio>
#include "filesys.h"

unsigned int namei(const char *name)
{
    // TODO: iterate g_dir.direct[0..g_dir.size-1]
    // TODO: strcmp(d_name, name) == 0 && d_ino != DIEMPTY
    // TODO: found: return index i, else return (unsigned int)-1
    return 0;
}

unsigned short iname(const char *name)
{
    // TODO: iterate g_dir.direct[0..DIRNUM-1]
    // TODO: find slot where d_ino == DIEMPTY
    // TODO: strcpy(d_name, name), return index
    // TODO: if full: print "directory full", return 0
    return 0;
}
