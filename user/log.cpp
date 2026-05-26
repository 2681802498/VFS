/**
 * log.cpp - User login / logout
 * Layer 6 (Member D)
 */
#include <cstdio>
#include <cstring>
#include "filesys.h"

int login(unsigned short uid, const char *passwd)
{
    for (int i = 0; i < PWDNUM; i++) {
        // Match both uid and password.
        if (g_pwd[i].p_uid == uid && strcmp(passwd, g_pwd[i].password) == 0) {
            for (int j = 0; j < USERNUM; j++) {
                // Find an empty slot in g_user.
                if (g_user[j].u_uid == 0) {
                    g_user[j].u_uid = uid;
                    g_user[j].u_gid = g_pwd[i].p_gid;
                    g_user[j].u_default_mode = DEFAULTMODE;
                    // Init user's open file table.
                    for (int k = 0; k < NOFILE; k++) {
                        g_user[j].u_ofile[k] = SYSOPENFILE + 1;
                    }
                    g_user_id = j;
                    return 1;
                }
            }
            g_vfs_errno = E_VFS_NFILE;
            return 0;
        }
    }
    g_vfs_errno = E_VFS_AUTH;
    return 0;
}

int logout(unsigned short uid)
{
    // Find uid slot in g_user[].
    for (int i = 0; i < USERNUM; i++) {
        if (uid == g_user[i].u_uid) {
            // Close any open files.
            for (int j = 0; j < NOFILE; j++) {
                if (g_user[i].u_ofile[j] != SYSOPENFILE + 1) {
                    close(i, static_cast<unsigned short>(j));
                }
                g_user[i].u_ofile[j] = SYSOPENFILE + 1;
            }

            g_user[i].u_uid = 0;
            g_user[i].u_gid = 0;
            g_user[i].u_default_mode = 0;
            if (g_user_id == i) {
                g_user_id = -1;
            }
            return 1;
        }
    }
    g_vfs_errno = E_VFS_AUTH;
    return 0;
}
