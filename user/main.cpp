/**
 * main.cpp - VFS entry point
 * Startup: format? -> install -> login -> shell -> halt
 * Layer 7 (Member D)
 */
#include "filesys.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

// ====== Global Variables ====== //
hinode g_hinode[NHINO];
dir    g_dir;
file   g_sys_ofile[SYSOPENFILE];
filsys g_filsys;
pwd    g_pwd[PWDNUM];
user_t g_user[USERNUM];
FILE  *g_fd              = nullptr;
inode *g_cur_path_inode   = nullptr;
int    g_user_id          = -1;

void shell_loop();

int main()
{
    std::cout << "======================================\n";
    std::cout << "  Virtual File System (VFS) v1.0\n";
    std::cout << "  Simulated UNIX-like File System\n";
    std::cout << "======================================\n\n";

    // Step 1: Check if format is needed
    std::cout << "Do you want to format the virtual disk? (y/n): ";
    char ch;
    std::cin >> ch;
    std::cin.ignore();

    if (ch == 'y' || ch == 'Y') {
        std::cout << "WARNING: Format will erase all data!\n";
        std::cout << "Are you sure? (y/n): ";
        std::cin >> ch;
        std::cin.ignore();
        if (ch == 'y' || ch == 'Y') {
            format();
            std::cout << "Format completed.\n";
        }
    }

    // Step 2: Load file system
    install();
    std::cout << "File system loaded.\n\n";

    // Step 3: User login
    std::cout << "Please login:\n";
    std::cout << "  Username (uid): ";
    unsigned short uid;
    std::cin >> uid;
    std::cin.ignore();
    std::cout << "  Password: ";
    std::string passwd;
    std::getline(std::cin, passwd);

    if (login(uid, passwd.c_str())) {
        std::cout << "Login successful!\n\n";
    } else {
        std::cout << "Login failed. Exiting.\n";
        halt();
        return 1;
    }

    // Step 4: Enter command loop
    std::cout << "Type 'help' for available commands.\n";
    shell_loop();

    return 0;
}
