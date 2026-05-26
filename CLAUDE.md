# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

```bash
# Configure (generates build/compile_commands.json for clangd)
cmake --preset ninja-debug

# Build
cmake --build build

# Run
./build/Debug/vfs.exe
```

## Architecture

7-layer simulated UNIX file system running on a single host file (`filesystem`) as the virtual disk.

| Layer | Responsibility | Files |
|-------|---------------|-------|
| 7: Shell | Command parsing, REPL | `user/shell.cpp`, `user/main.cpp` |
| 6: User mgmt | login/logout, pwd table, user table | `user/log.cpp`, `user/halt.cpp` |
| 5: Directory ops | mkdir, chdir, dir, namei, iname | `kernel/dir.cpp`, `kernel/name.cpp` |
| 4: File ops | creat, open, close, delete, read, write, access | `kernel/access.cpp`, `kernel/creat.cpp`, `kernel/open.cpp`, `kernel/close.cpp`, `kernel/delete.cpp`, `kernel/rdwt.cpp` |
| 3: Inode cache | iget/iput, hash chain (128 buckets) | `kernel/igetput.cpp` |
| 2: Block mgmt | balloc/bfree (group linking, 50/group), ialloc/ifree | `kernel/balloc.cpp`, `kernel/bfree.cpp`, `kernel/ialloc.cpp`, `kernel/ifree.cpp` |
| 1: Virtual disk | format, install, block-level I/O on host file | `kernel/format.cpp`, `kernel/install.cpp` |

All globals declared in `include/filesys.h`, defined in `user/main.cpp`.

### Disk layout (512B blocks)

| Region | Offset | Size | Content |
|--------|--------|------|---------|
| Boot block | 0 | 1 block | Unused |
| Superblock | 512B | 1 block | `filsys` struct |
| Inode area | 1024B | 32 blocks (16KB) | 512 `dinode` at 32B each |
| Data area | 17408B | 512 blocks (256KB) | File/directory data, password file |

### Key data structures

- **dinode** (32B): `di_number` (links), `di_mode` (type+perms), `di_uid/gid`, `di_size`, `di_addr[10]` (direct blocks, max 5KB file)
- **inode** (memory): dinode fields + `i_forw/i_back` (hash chain), `i_flag`, `i_ino`, `i_count`
- **direct** (16B): `d_name[14]` + `d_ino` — 128 entries per directory block
- **file**: `f_flag`, `f_count`, `f_inode`, `f_off` — stored in `g_sys_ofile[40]`
- **user_t**: `u_uid/gid`, `u_ofile[20]` (indices into `g_sys_ofile`)
- **filsys**: superblock — `s_free[50]` (free block stack), `s_inode[50]` (free inode stack)

### Implementation status

**Done** (Layer 1, 2, 6, 7): format, install, balloc, bfree, ialloc, ifree, login, logout, halt, shell loop, global definitions.

**Stubs** (Layer 3, 4, 5): iget/iput, namei/iname, _dir, mkdir, chdir, access, creat, open, close, delete, read, write. These contain TODO comments describing the algorithm; bodies return sentinel values.

### Known bugs from original sample code (DESIGN.md §10)

1. `namei()` return 0 ambiguous (found at index 0 vs. not found)
2. `login()` strcmp logic — need `== 0` for match
3. `aopen()` condition: `!= NULL` should be `== NULL`
4. `creat()` access() third param should be `mode`, not `inode`
5. `iput()` self-reference (`i_back == pinode`) hash chain repair
6. `chdir()` directory entry compaction on writeback
7. `balloc()` missing fseek before reading next group
8. `bfree()` fwrite at correct disk offset when stack is full
9. `read()`/`write()` cross-block boundary conditions
10. `halt()` `close()` missing `user_id` parameter

### Key interfaces (from DESIGN.md §8)

- A→B/C/D: `balloc()`, `bfree()`, `ialloc()`, `ifree()`, `format()`, `install()`
- B→C/D: `iget()`, `iput()`, `namei()`, `iname()`, `mkdir()`, `chdir()`, `_dir()`
- C→D: `access()`, `creat()`, `aopen()`, `close()`, `delete_file()`, `vfs_read()`, `vfs_write()`
- D→all: `login()`, `logout()`, `halt()`
