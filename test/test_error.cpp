#include <catch2/catch_test_macros.hpp>
#include <cstring>

#include "test_helpers.h"

/* --- vfs_strerror() --- */

TEST_CASE("vfs_strerror() returns correct strings", "[error]") {
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_OK), "Success") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_NOSPC), "No space left on device") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_AUTH), "Authentication failure") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_IO), "Input/output error") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_INVAL), "Invalid argument") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_NFILE), "Too many open files") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_NOENT), "No such file or directory") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_NOPERM), "Permission denied") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_EXIST), "File already exists") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_NOTDIR), "Not a directory") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_ISDIR), "Is a directory") == 0);
    REQUIRE(std::strcmp(vfs_strerror(E_VFS_BUSY), "Device or resource busy") == 0);
    REQUIRE(std::strcmp(vfs_strerror(999), "Unknown error") == 0);
}

/* --- balloc() --- */

TEST_CASE("balloc() sets E_VFS_NOSPC when disk is full", "[error]") {
    reset_globals();
    fs_cleanup();
    format();

    /* Simulate exhausted free block stack */
    g_filsys.s_nfree = 0;
    g_filsys.s_pfree = 0;

    g_vfs_errno = E_VFS_OK;
    uint32_t result = balloc();
    REQUIRE(result == DISKFULL);
    REQUIRE(g_vfs_errno == E_VFS_NOSPC);

    fs_cleanup();
}

/* --- ialloc() --- */

TEST_CASE("ialloc() sets E_VFS_NOSPC when no free inodes", "[error]") {
    reset_globals();
    fs_cleanup();
    format();

    /* Simulate exhausted inode stack and no free inodes on disk */
    g_filsys.s_ninode = 0;
    g_filsys.s_pinode = 0;
    g_filsys.s_rinode = 512; /* beyond all valid inodes */

    g_vfs_errno = E_VFS_OK;
    inode *result = ialloc();
    REQUIRE(result == nullptr);
    REQUIRE(g_vfs_errno == E_VFS_NOSPC);

    fs_cleanup();
}

/* --- ifree() --- */

TEST_CASE("ifree() sets E_VFS_NOSPC when inode stack is full", "[error]") {
    reset_globals();
    g_filsys.s_ninode = NICINOD;
    g_filsys.s_pinode = NICINOD - 1;
    g_filsys.s_rinode = 100;

    g_vfs_errno = E_VFS_OK;
    ifree(200);
    REQUIRE(g_vfs_errno == E_VFS_NOSPC);
}

/* --- login() --- */

static void setup_pwd() {
    reset_globals();
    g_pwd[0].p_uid = 0;
    g_pwd[0].p_gid = 0;
    std::strcpy(g_pwd[0].password, "root");
    g_pwd[1].p_uid = 1;
    g_pwd[1].p_gid = 1;
    std::strcpy(g_pwd[1].password, "pass1");
}

TEST_CASE("login() sets E_VFS_AUTH on bad password", "[error]") {
    setup_pwd();

    g_vfs_errno = E_VFS_OK;
    int32_t result = login(0, "wrong");
    REQUIRE(result == 0);
    REQUIRE(g_vfs_errno == E_VFS_AUTH);
}

TEST_CASE("login() sets E_VFS_AUTH on unknown uid", "[error]") {
    setup_pwd();

    g_vfs_errno = E_VFS_OK;
    int32_t result = login(99, "pass1");
    REQUIRE(result == 0);
    REQUIRE(g_vfs_errno == E_VFS_AUTH);
}

TEST_CASE("login() sets E_VFS_NFILE when user table is full", "[error]") {
    setup_pwd();

    /* Fill all user slots */
    for (int i = 0; i < USERNUM; i++) {
        g_user[i].u_uid = 100 + i;
    }

    g_vfs_errno = E_VFS_OK;
    int32_t result = login(0, "root");
    REQUIRE(result == 0);
    REQUIRE(g_vfs_errno == E_VFS_NFILE);
}

/* --- logout() --- */

TEST_CASE("logout() sets E_VFS_AUTH on unknown uid", "[error]") {
    setup_pwd();

    g_vfs_errno = E_VFS_OK;
    int32_t result = logout(99);
    REQUIRE(result == 0);
    REQUIRE(g_vfs_errno == E_VFS_AUTH);
}
