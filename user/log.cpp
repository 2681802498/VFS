/**
 * log.cpp - User login / logout
 * Layer 6 (Member D)
 */
#include <cstdio>
#include <cstring>
#include "filesys.h"

int login(unsigned short uid, const char *passwd)
{
    // TODO: iterate g_pwd[0..PWDNUM-1] to find uid
    // TODO: strcmp(passwd, g_pwd[i].password) == 0 means match
    // TODO: find empty slot in g_user[] (u_uid == 0)
    // TODO: g_user[j].u_uid = uid, g_user[j].u_gid = g_pwd[i].p_gid
    // TODO: g_user[j].u_default_mode = DEFAULTMODE
    // TODO: init u_ofile[k] = SYSOPENFILE + 1 for all 20 slots
    // TODO: g_user_id = j, return 1
    return 0;
}

int logout(unsigned short uid)
{
    // TODO: find uid slot in g_user[]
    // TODO: iterate u_ofile[]: close any open file
    //         if g_user[i].u_ofile[j] != SYSOPENFILE+1: close(i, j)
    // TODO: zero out g_user[i]: u_uid = 0
    // TODO: return 1 on success, 0 on failure
    return 0;
}
