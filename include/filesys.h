#ifndef FILESYS_H
#define FILESYS_H

#include <cstdint>
#include <cstdio>

/* ====== Disk Layout & System Constants ====== */
#define BLOCKSIZ     512   /* block size in bytes */
#define SYSOPENFILE  40    /* max system open files */
#define DIRNUM       128   /* max directory entries per dir */
#define DIRSIZ       14    /* directory entry name size */
#define PWDSIZ       12    /* password string size */
#define PWDNUM       32    /* max password entries */
#define NOFILE       20    /* max open files per user */
#define NADDR        10    /* direct index blocks per inode */
#define NHINO        128   /* hash chain count (power of 2) */
#define USERNUM      10    /* max concurrent users */
#define DINODESIZ    32    /* disk inode size in bytes */
#define DINODEBLK    32    /* inode area block count */
#define FILEBLK      512   /* data area block count */
#define NICFREE      50    /* superblock free block stack size */
#define NICINOD      50    /* superblock free inode stack size */

#define DINODESTART  (2 * BLOCKSIZ)
#define DATASTART    ((2 + DINODEBLK) * BLOCKSIZ)

/* ====== Inode Type & Permission Flags ====== */
#define DIEMPTY    0x0000  /* empty inode */
#define DIFILE     0x1000  /* regular file */
#define DIDIR      0x2000  /* directory */

#define UDIREAD    0x0001
#define UDIWRITE   0x0002
#define UDIEXECUTE 0x0004
#define GDIREAD    0x0010
#define GDIWRITE   0x0020
#define GDIEXECUTE 0x0040
#define ODIREAD    0x0100
#define ODIWRITE   0x0200
#define ODIEXECUTE 0x0400
#define DEFAULTMODE 0x0777

/* ====== File & Superblock Flags ====== */
#define READ_MODE    1
#define WRITE_MODE   2
#define EXECUTE_MODE 3

#define IUPDATE 0x0002  /* inode modified */
#define SUPDATE 0x0001  /* superblock modified */

#define FREAD   0x0001
#define FWRITE  0x0002
#define FAPPEND 0x0004

#define DISKFULL 65535  /* disk full sentinel */

/* ====== Disk Inode (32 bytes) ====== */
struct dinode {
    uint16_t di_number;       /* link count */
    uint16_t di_mode;         /* type + permissions */
    uint16_t di_uid;          /* owner uid */
    uint16_t di_gid;          /* owner gid */
    uint32_t di_size;         /* file size in bytes */
    uint16_t di_addr[NADDR];  /* direct block pointers */
};

/* ====== Forward Declarations ====== */
struct inode;

/* ====== Directory Entry (16 bytes) ====== */
struct direct {
    char     d_name[DIRSIZ];  /* file name */
    uint32_t d_ino;           /* inode number */
};

/* ====== Superblock ====== */
struct filsys {
    uint16_t s_isize;            /* inode area block count */
    uint32_t s_fsize;            /* data area block count */
    uint32_t s_nfree;            /* free block count in stack */
    uint16_t s_pfree;            /* free block stack pointer */
    uint32_t s_free[NICFREE];    /* free block stack */
    uint32_t s_ninode;           /* free inode count in stack */
    uint16_t s_pinode;           /* free inode stack pointer */
    uint32_t s_inode[NICINOD];   /* free inode stack */
    uint32_t s_rinode;           /* remembered inode */
    char     s_fmod;             /* modified flag */
};

/* ====== Password Entry ====== */
struct pwd {
    uint16_t p_uid;
    uint16_t p_gid;
    char     password[PWDSIZ];
};

/* ====== Current Directory ====== */
struct dir {
    struct direct direct[DIRNUM];
    int32_t size;
};

/* ====== Inode Hash Table Header ====== */
struct hinode {
    inode *i_forw;
};

/* ====== System Open File Table Entry ====== */
struct file {
    char     f_flag;
    uint32_t f_count;
    inode   *f_inode;
    uint32_t f_off;
};

/* ====== User Structure ====== */
struct user_t {
    uint16_t u_default_mode;
    uint16_t u_uid;
    uint16_t u_gid;
    uint16_t u_ofile[NOFILE];
};

/* ====== Memory Inode (full definition) ====== */
struct inode {
    inode    *i_forw;
    inode    *i_back;
    char      i_flag;
    uint32_t  i_ino;
    uint32_t  i_count;
    uint16_t  di_number;
    uint16_t  di_mode;
    uint16_t  di_uid;
    uint16_t  di_gid;
    uint16_t  di_size;
    uint32_t  di_addr[NADDR];
};

/* ====== Global Variables ====== */
extern hinode g_hinode[NHINO];
extern dir    g_dir;
extern file   g_sys_ofile[SYSOPENFILE];
extern filsys g_filsys;
extern pwd    g_pwd[PWDNUM];
extern user_t g_user[USERNUM];
extern FILE  *g_fd;
extern inode *g_cur_path_inode;
extern int32_t g_user_id;

/* ====== Function Declarations ====== */

/* Layer 1-2: Virtual disk + Block management (Member A) */
void     format();
void     install();
uint32_t balloc();
void     bfree(uint32_t block_num);
inode   *ialloc();
void     ifree(uint32_t dinodeid);

/* Layer 3: Inode management (Member B) */
inode   *iget(uint32_t dinodeid);
void     iput(inode *pinode);

/* Layer 5: Directory operations (Member B) */
uint32_t namei(const char *name);
uint16_t iname(const char *name);
void     mkdir(const char *dirname);
void     chdir(const char *dirname);
void     _dir();

/* Layer 4: File operations + Access control (Member C) */
uint32_t access(uint32_t uid, inode *inode, uint16_t mode);
int32_t  creat(uint32_t uid, const char *filename, uint16_t mode);
uint16_t aopen(uint32_t uid, const char *filename, uint16_t openmode);
void     close(uint32_t uid, uint16_t cfd);
void     delete_file(const char *filename);
uint32_t vfs_read(uint32_t fd, char *buf, uint32_t size);
uint32_t vfs_write(uint32_t fd, const char *buf, uint32_t size);

/* Layer 6: User management (Member D) */
int32_t  login(uint16_t uid, const char *passwd);
int32_t  logout(uint16_t uid);
void     halt();

#endif /* FILESYS_H */
