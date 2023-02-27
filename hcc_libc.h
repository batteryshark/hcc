#ifndef __HCC_LIBC_H
#define __HCC_LIBC_H

#include <sys/types.h>

#include "hcc.h"

// unistd.h
typedef int (*access_func_t)(const char *, int);
typedef int (*open_func_t)(const char *, int);
typedef int (*system_func_t)(const char *command);
typedef ssize_t (*readlink_func_t)(const char *, char *, size_t);
typedef int (*mkdir_func_t)(const char *, mode_t);
typedef void *(*opendir_func_t)(const char *);
typedef int (*openat_func_t)(int, const char *, int, ...);
typedef int (*chdir_func_t)(const char *);
typedef int (*chroot_func_t)(const char *);
typedef int (*unlink_func_t)(const char *);
typedef int (*rmdir_func_t)(const char *);
typedef int (*symlink_func_t)(const char *, const char *);
typedef int (*link_func_t)(const char *, const char *);
typedef int (*utime_func_t)(const char *, void *);
typedef int (*getlogin_r_func_t)(char *, size_t);
extern PHookCallChain access_callchain;
extern PHookCallChain open_callchain;
extern PHookCallChain system_callchain;
extern PHookCallChain readlink_callchain;
extern PHookCallChain mkdir_callchain;
extern PHookCallChain opendir_callchain;
extern PHookCallChain openat_callchain;
extern PHookCallChain chdir_callchain;
extern PHookCallChain chroot_callchain;
extern PHookCallChain unlink_callchain;
extern PHookCallChain rmdir_callchain;
extern PHookCallChain symlink_callchain;
extern PHookCallChain link_callchain;
extern PHookCallChain utime_callchain;
extern PHookCallChain getlogin_r_callchain;

// sys/stat.h
typedef int (*lxstat_func_t)(int, const char *, void *);
typedef int (*xstat_func_t)(int, const char *, void *);
typedef int (*lxstat64_func_t)(int, const char *, void *);
typedef int (*xstat64_func_t)(int, const char *, void *);
typedef int (*rename_func_t)(const char *, const char *);
typedef int (*remove_func_t)(const char *);
typedef int (*stat_func_t)(const char *, void *);
typedef int (*lstat_func_t)(const char *, void *);
typedef int (*fstat_func_t)(int, void *);
typedef int (*creat_func_t)(const char *, mode_t);
typedef int (*creat64_t)(const char *, mode_t);
typedef int (*truncate_func_t)(const char *, off_t);
typedef int (*ftruncate_func_t)(int, off_t);
typedef int (*stat64_func_t)(int, const char*, void*);
typedef int (*lstat64_func_t)(int, const char*, void*);
extern PHookCallChain lxstat_callchain;
extern PHookCallChain xstat_callchain;
extern PHookCallChain lxstat64_callchain;
extern PHookCallChain xstat64_callchain;
extern PHookCallChain rename_callchain;
extern PHookCallChain remove_callchain;
extern PHookCallChain stat_callchain;
extern PHookCallChain lstat_callchain;
extern PHookCallChain fstat_callchain;
extern PHookCallChain creat_callchain;
extern PHookCallChain creat64_callchain;
extern PHookCallChain truncate_callchain;
extern PHookCallChain ftruncate_callchain;
extern PHookCallChain stat64_callchain;
extern PHookCallChain lstat64_callchain;

// stdio.h
typedef void *(*fopen_func_t)(const char *, const char *);
extern PHookCallChain fopen_callchain;

// string.h
typedef char* (*strstr_func_t)(const char*, const char*);
extern PHookCallChain strstr_callchain;

// fcntl.h
typedef int (*open64_func_t)(const char *, int, ...);
typedef int (*openat64_func_t)(int, const char *, int, ...);
extern PHookCallChain open64_callchain;
extern PHookCallChain openat64_callchain;

// sys/statfs.h
typedef int (*statfs_func_t)(const char *, void *);
typedef int (*fstatfs_func_t)(int, void *);
extern PHookCallChain statfs_callchain;
extern PHookCallChain fstatfs_callchain;

// <sys/mount.h>
typedef int (*mount_func_t)(const char *, const char *, const char *, unsigned long, const void *);
typedef int (*unmount_func_t)(const char *, int);
extern PHookCallChain mount_callchain;
extern PHookCallChain umount_callchain;

// <sys/utsname.h>
typedef int (*uname_func_t)(void *);
extern PHookCallChain uname_callchain;

// <pwd.h>
typedef void *(*getpwuid_func_t)(uid_t);
extern PHookCallChain getpwuid_callchain;

// <sys/ioctl.h>
typedef int (*ioctl_func_t)(int, unsigned long, ...);
extern PHookCallChain ioctl_callchain;

// <sys/select.h>
typedef int (*select_func_t)(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
extern PHookCallChain select_callchain;

// <sys/socket.h>
typedef ssize_t (*recvfrom_func_t)(int sockfd, void *buf, size_t len, int flags, void *src_addr, void *addrlen);
typedef ssize_t (*sendto_func_t)(int sockfd, const void *buf, size_t len, int flags, void *dest_addr, unsigned int addrlen);
extern PHookCallChain recvfrom_callchain;
extern PHookCallChain sendto_callchain;


void hcc_init_libc(void);

#endif