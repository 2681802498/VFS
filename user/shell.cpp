/**
 * shell.cpp - Command interpreter
 * Parse user input and dispatch commands
 * Layer 7 (Member D)
 */
#include "filesys.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

static std::vector<std::string> parse_cmd(const std::string &line)
{
    std::vector<std::string> args;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) args.push_back(token);
    return args;
}

static void show_help()
{
    std::cout << "Available commands:\n";
    std::cout << "  login <uid> <password>   - User login\n";
    std::cout << "  logout                   - User logout\n";
    std::cout << "  dir / ls                 - List directory\n";
    std::cout << "  mkdir <dirname>          - Create directory\n";
    std::cout << "  cd <dirname>             - Change directory\n";
    std::cout << "  creat <filename> <mode>  - Create file\n";
    std::cout << "  open <filename> <mode>   - Open file\n";
    std::cout << "  read <fd> <size>         - Read file\n";
    std::cout << "  write <fd> <size>        - Write file\n";
    std::cout << "  close <fd>               - Close file\n";
    std::cout << "  delete <filename>        - Delete file\n";
    std::cout << "  format                   - Format disk\n";
    std::cout << "  halt / exit / quit       - Exit system\n";
}

void shell_loop()
{
    std::string line;

    while (true) {
        std::cout << "$ ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        auto args = parse_cmd(line);
        if (args.empty()) continue;

        const std::string &cmd = args[0];

        if (cmd == "help") {
            show_help();
        } else if (cmd == "login" && args.size() >= 3) {
            login(std::stoul(args[1]),args[2].c_str());
        } else if (cmd == "logout") {
            logout(g_user[g_user_id].u_uid);
        } else if (cmd == "dir" || cmd == "ls") {
            _dir();
        } else if (cmd == "mkdir" && args.size() >= 2) {
            mkdir(args[1].c_str());
        } else if (cmd == "cd" && args.size() >= 2) {
            chdir(args[1].c_str());
        } else if (cmd == "creat" && args.size() >= 3) {
            creat(g_user_id, args[1].c_str(), std::stoul(args[2]));
        } else if (cmd == "open" && args.size() >= 3) {
            aopen(g_user_id, args[1].c_str(), std::stoul(args[2]));
        } else if (cmd == "read" && args.size() >= 3) {
            char buf[BUFSIZ];
            vfs_read(std::stoul(args[1]), buf, std::stoul(args[2]));
            for(int i = 0; i < strlen(buf);i++){
                std::cout << buf[i];
            }
        } else if (cmd == "write" && args.size() >= 3) {
            vfs_write(std::stoul(args[1]), "test data", std::stoul(args[2]));
        } else if (cmd == "close" && args.size() >= 2) {
            close(g_user_id, std::stoul(args[1]));
        } else if (cmd == "delete" && args.size() >= 2) {
            delete_file(args[1].c_str());
        } else if (cmd == "format") {
            format();
        } else if (cmd == "halt" || cmd == "exit" || cmd == "quit") {
            halt();
            break;
        } else {
            std::cout << "Unknown command: " << cmd
                      << "\nType 'help' for available commands.\n";
        }
    }
}
