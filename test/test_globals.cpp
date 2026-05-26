#include "filesys.h"

hinode g_hinode[NHINO];
dir    g_dir;
file   g_sys_ofile[SYSOPENFILE];
filsys g_filsys;
pwd    g_pwd[PWDNUM];
user_t g_user[USERNUM];
FILE  *g_fd              = nullptr;
inode *g_cur_path_inode  = nullptr;
int32_t g_user_id        = -1;
