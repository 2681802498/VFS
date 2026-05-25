/**
 * access.cpp - File access permission check
 * owner / group / other  x  r / w / x
 * Layer 4 (Member C)
 */
#include "filesys.h"

unsigned int access(unsigned int uid, inode *inode, unsigned short mode)
{
    // TODO: switch (mode)
    // TODO: case READ_MODE: check ODIREAD / GDIREAD / UDIREAD
    // TODO: case WRITE_MODE: check ODIWRITE / GDIWRITE / UDIWRITE
    // TODO: case EXECUTE_MODE: check ODIEXECUTE / GDIEXECUTE / UDIEXECUTE
    // TODO: group check: g_user[uid].u_gid == inode->di_gid
    // TODO: owner check: g_user[uid].u_uid == inode->di_uid
    // TODO: return 1 if allowed, 0 otherwise
    return 0;
}
