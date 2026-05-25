#ifndef FILESYS_H
#define FILESYS_H

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
    unsigned short di_number;   /* link count */
    unsigned short di_mode;     /* type + permissions */
    unsigned short di_uid;      /* owner uid */
    unsigned short di_gid;      /* owner gid */
    unsigned long  di_size;     /* file size in bytes */
    unsigned int   di_addr[NADDR]; /* direct block pointers */
};

/* ====== Forward Declarations ====== */
struct inode;

/* ====== Directory Entry (16 bytes) ====== */
struct direct {
    char         d_name[DIRSIZ]; /* file name */
    unsigned int d_ino;          /* inode number */
};

/* ====== Superblock ====== */
struct filsys {
    unsigned short s_isize;          /* inode area block count */
    unsigned long  s_fsize;          /* data area block count */
    unsigned int   s_nfree;          /* free block count in stack */
    unsigned short s_pfree;          /* free block stack pointer */
    unsigned int   s_free[NICFREE];  /* free block stack */
    unsigned int   s_ninode;         /* free inode count in stack */
    unsigned short s_pinode;         /* free inode stack pointer */
    unsigned int   s_inode[NICINOD]; /* free inode stack */
    unsigned int   s_rinode;         /* remembered inode */
    char           s_fmod;           /* modified flag */
};

/* ====== Password Entry ====== */
struct pwd {
    unsigned short p_uid;
    unsigned short p_gid;
    char           password[PWDSIZ];
};

/* ====== Current Directory ====== */
struct dir {
    struct direct direct[DIRNUM];
    int    size;
};

/* ====== Inode Hash Table Header ====== */
struct hinode {
    inode *i_forw;
};

/* ====== System Open File Table Entry ====== */
struct file {
    char          f_flag;
    unsigned int  f_count;
    inode        *f_inode;
    unsigned long f_off;
};

/* ====== User Structure ====== */
struct user_t {
    unsigned short u_default_mode;
    unsigned short u_uid;
    unsigned short u_gid;
    unsigned short u_ofile[NOFILE];
};

/* ====== Memory Inode (full definition) ====== */
struct inode {
    inode        *i_forw;
    inode        *i_back;
    char          i_flag;
    unsigned int  i_ino;
    unsigned int  i_count;
    unsigned short di_number;
    unsigned short di_mode;
    unsigned short di_uid;
    unsigned short di_gid;
    unsigned short di_size;
    unsigned int   di_addr[NADDR];
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
extern int    g_user_id;

/* ====== Function Declarations ====== */

/* Layer 1-2: Virtual disk + Block management (Member A) */
void          format();
void          install();
unsigned int  balloc();
void          bfree(unsigned int block_num);
inode        *ialloc();
void          ifree(unsigned int dinodeid);

/* Layer 3: Inode management (Member B) */
inode        *iget(unsigned int dinodeid);
void          iput(inode *pinode);

/* Layer 5: Directory operations (Member B) */
unsigned int  namei(const char *name);
unsigned short iname(const char *name);
void          mkdir(const char *dirname);
void          chdir(const char *dirname);
void          _dir();

/* Layer 4: File operations + Access control (Member C) */
unsigned int  access(unsigned int uid, inode *inode, unsigned short mode);
int           creat(unsigned int uid, const char *filename, unsigned short mode);
unsigned short aopen(unsigned int uid, const char *filename, unsigned short openmode);
void          close(unsigned int uid, unsigned short cfd);
void          delete_file(const char *filename);
unsigned int  vfs_read(unsigned int fd, char *buf, unsigned int size);
unsigned int  vfs_write(unsigned int fd, const char *buf, unsigned int size);

/* Layer 6: User management (Member D) */
int           login(unsigned short uid, const char *passwd);
int           logout(unsigned short uid);
void          halt();

#endif /* FILESYS_H */
