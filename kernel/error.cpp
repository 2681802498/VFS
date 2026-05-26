/**
 * error.cpp - Error code string conversion
 * Layer 1 utility
 */
#include "filesys.h"

const char *vfs_strerror(int err)
{
    switch (err) {
    case E_VFS_OK:      return "Success";
    case E_VFS_NOENT:   return "No such file or directory";
    case E_VFS_NOSPC:   return "No space left on device";
    case E_VFS_NOPERM:  return "Permission denied";
    case E_VFS_EXIST:   return "File already exists";
    case E_VFS_NOTDIR:  return "Not a directory";
    case E_VFS_ISDIR:   return "Is a directory";
    case E_VFS_NFILE:   return "Too many open files";
    case E_VFS_IO:      return "Input/output error";
    case E_VFS_AUTH:    return "Authentication failure";
    case E_VFS_BUSY:    return "Device or resource busy";
    case E_VFS_INVAL:   return "Invalid argument";
    default:            return "Unknown error";
    }
}
