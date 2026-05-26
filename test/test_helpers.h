#pragma once

#include <cstdio>
#include <cstring>

#include "filesys.h"

inline void reset_globals() {
    std::memset(g_hinode, 0, sizeof(g_hinode));
    std::memset(&g_dir, 0, sizeof(g_dir));
    std::memset(g_sys_ofile, 0, sizeof(g_sys_ofile));
    std::memset(&g_filsys, 0, sizeof(g_filsys));
    std::memset(g_pwd, 0, sizeof(g_pwd));
    std::memset(g_user, 0, sizeof(g_user));
    g_fd = nullptr;
    g_cur_path_inode = nullptr;
    g_user_id = -1;
}

inline void fs_cleanup() {
    if (g_fd) {
        std::fclose(g_fd);
        g_fd = nullptr;
    }
    std::remove("filesystem");
}
