#include <stdarg.h>
#include "hcc.h"
#include "hcc_libc.h"

#ifndef O_CREAT
#define O_CREAT                00000100        /* not fcntl */
#endif

#ifndef NULL
#define NULL 0
#endif

static int hcc_libc_initalized = 0;

// unistd.h
PHookCallChain access_callchain = NULL;
PHookCallChain open_callchain = NULL;
PHookCallChain system_callchain = NULL;
PHookCallChain readlink_callchain = NULL;
PHookCallChain mkdir_callchain = NULL;
PHookCallChain opendir_callchain = NULL;
PHookCallChain openat_callchain = NULL;
PHookCallChain chdir_callchain = NULL;
PHookCallChain chroot_callchain = NULL;
PHookCallChain unlink_callchain = NULL;
PHookCallChain rmdir_callchain = NULL;
PHookCallChain symlink_callchain = NULL;
PHookCallChain link_callchain = NULL;
PHookCallChain utime_callchain = NULL;
PHookCallChain getlogin_r_callchain = NULL;

int access(const char *path, int mode) {
    access_func_t n_access = HCC_GetNextAddr(access_callchain,NULL);
    return n_access(path, mode);
}

int open(const char *pathname, int flags) {
    open_func_t n_open = HCC_GetNextAddr(open_callchain, NULL);
    return n_open(pathname, flags);
}

int system(const char *command){
    system_func_t n_system = HCC_GetNextAddr(system_callchain,NULL);
    return n_system(command);
}

ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
    readlink_func_t n_readlink = HCC_GetNextAddr(readlink_callchain,NULL);
    return n_readlink(path, buf, bufsiz);
}

int mkdir(const char *path, mode_t mode) {
    mkdir_func_t n_mkdir = HCC_GetNextAddr(mkdir_callchain,NULL);
    return n_mkdir(path, mode);
}

void *opendir(const char *name) {
    opendir_func_t n_opendir = HCC_GetNextAddr(opendir_callchain,NULL);
    return n_opendir(name);
}

int openat(int dirfd, const char *pathname, int flags, ...) {
    va_list args;
    int mode = 0;
    if (flags & O_CREAT) {
        va_start(args, flags);
        mode = va_arg(args, int);
        va_end(args);
    }
    openat_func_t n_openat = HCC_GetNextAddr(openat_callchain,NULL);
    return n_openat(dirfd, pathname, flags, mode);
}

int chdir(const char *path) {
    chdir_func_t n_chdir = HCC_GetNextAddr(chdir_callchain,NULL);
    return n_chdir(path);
}

int chroot(const char *path) {
    chroot_func_t n_chroot = HCC_GetNextAddr(chroot_callchain,NULL);
    return n_chroot(path);
}

int unlink(const char *path) {
    unlink_func_t n_unlink = HCC_GetNextAddr(unlink_callchain,NULL);
    return n_unlink(path);
}

int rmdir(const char *path) {
    rmdir_func_t n_rmdir = HCC_GetNextAddr(rmdir_callchain,NULL);
    return n_rmdir(path);
}

int symlink(const char *target, const char *linkpath) {
  symlink_func_t n_symlink = HCC_GetNextAddr(symlink_callchain,NULL);
    return n_symlink(target, linkpath);
}

int link(const char *oldpath, const char *newpath) {
    link_func_t n_link = HCC_GetNextAddr(link_callchain,NULL);
    return n_link(oldpath, newpath);
}

int utime(const char *filename, void *times) {
    utime_func_t n_utime = HCC_GetNextAddr(utime_callchain,NULL);
    return n_utime(filename, times);
}

int getlogin_r(char *name, size_t namesize) {
    getlogin_r_func_t n_getlogin_r = HCC_GetNextAddr(getlogin_r_callchain, NULL);
    return n_getlogin_r(name, namesize);
}

// sys/stat.h
PHookCallChain lxstat_callchain = NULL;
PHookCallChain xstat_callchain = NULL;
PHookCallChain lxstat64_callchain = NULL;
PHookCallChain xstat64_callchain = NULL;
PHookCallChain rename_callchain = NULL;
PHookCallChain remove_callchain = NULL;
PHookCallChain stat_callchain = NULL;
PHookCallChain lstat_callchain = NULL;
PHookCallChain fstat_callchain = NULL;
PHookCallChain creat_callchain = NULL;
PHookCallChain creat64_callchain = NULL;
PHookCallChain truncate_callchain = NULL;
PHookCallChain ftruncate_callchain = NULL;
PHookCallChain stat64_callchain = NULL;
PHookCallChain lstat64_callchain = NULL;


int __lxstat(int ver, const char *path, void *buf) {
    lxstat_func_t n_lxstat = HCC_GetNextAddr(lxstat_callchain,NULL);
    return n_lxstat(ver, path, buf);
}

int __xstat(int ver, const char *path, void *buf) {
    xstat_func_t n_xstat = HCC_GetNextAddr(xstat_callchain,NULL);
    return n_xstat(ver, path, buf);
}

int __lxstat64(int ver, const char *path, void *buf) {
    lxstat64_func_t n_lxstat = HCC_GetNextAddr(lxstat64_callchain,NULL);
    return n_lxstat(ver, path, buf);
}

int __xstat64(int ver, const char *path, void *buf) {
    xstat64_func_t n_xstat = HCC_GetNextAddr(xstat64_callchain,NULL);
    return n_xstat(ver, path, buf);
}

int rename(const char *oldpath, const char *newpath) {
    rename_func_t n_rename = HCC_GetNextAddr(rename_callchain,NULL);
    return n_rename(oldpath, newpath);
}

int remove(const char *path) {
    remove_func_t n_remove = HCC_GetNextAddr(remove_callchain,NULL);
    return n_remove(path);
}

int stat(const char *path, void *buf) {
    stat_func_t n_stat = HCC_GetNextAddr(stat_callchain,NULL);
    return n_stat(path, buf);
}

int lstat(const char *path, void *buf) {
    lstat_func_t n_lstat = HCC_GetNextAddr(lstat_callchain,NULL);
    return n_lstat(path, buf);
}

int fstat(int fd, void *buf) {
    fstat_func_t n_fstat = HCC_GetNextAddr(fstat_callchain,NULL);
    return n_fstat(fd, buf);
}

int creat(const char *path, mode_t mode) {
    creat_func_t n_creat = HCC_GetNextAddr(creat_callchain,NULL);
    return n_creat(path, mode);
}

int creat64(const char *path, mode_t mode) {
    creat64_t n_creat64 = HCC_GetNextAddr(creat64_callchain,NULL);
    return n_creat64(path, mode);
}

int truncate(const char *path, off_t length) {
    truncate_func_t n_truncate = HCC_GetNextAddr(truncate_callchain,NULL);
    return n_truncate(path, length);
}

int ftruncate(int fd, off_t length) {
    ftruncate_func_t n_ftruncate = HCC_GetNextAddr(ftruncate_callchain,NULL);
    return n_ftruncate(fd, length);
}

int __stat64(int ver, const char* path, void* st) {
    stat64_func_t n_stat64 = HCC_GetNextAddr(stat64_callchain, NULL);
    return n_stat64(ver, path,st);
}

int __lstat64(int ver, const char* path, void* st) {
    stat64_func_t n_lstat64 = HCC_GetNextAddr(lstat64_callchain, NULL);
    return n_lstat64(ver, path,st);
}

// stdio.h
PHookCallChain fopen_callchain = NULL;

void *fopen(const char *path, const char *mode) {
    fopen_func_t n_fopen = HCC_GetNextAddr(fopen_callchain,NULL);
    return n_fopen(path, mode);
}

// string.h
PHookCallChain strstr_callchain = NULL;
char* strstr(const char* haystack, const char* needle) {   
    strstr_func_t n_strstr = HCC_GetNextAddr(strstr_callchain, NULL);
    return n_strstr(haystack, needle);
}

// fcntl.h
PHookCallChain open64_callchain = NULL;
PHookCallChain openat64_callchain = NULL;

int open64(const char *path, int oflag, mode_t mode) {
    open64_func_t n_open64 = HCC_GetNextAddr(open64_callchain, NULL);
    return n_open64(path, oflag, mode);
}

int openat64(int dirfd, const char *pathname, int oflag, ...) {
    va_list args;
    va_start(args, oflag);
    mode_t mode = va_arg(args, mode_t);
    va_end(args);

    openat64_func_t n_openat64 = HCC_GetNextAddr(openat64_callchain, NULL);
    return n_openat64(dirfd, pathname, oflag, mode);
}


// sys/statfs.h
PHookCallChain statfs_callchain = NULL;
PHookCallChain fstatfs_callchain = NULL;

int statfs(const char *path, void *buf) {
    statfs_func_t n_statfs = HCC_GetNextAddr(statfs_callchain,NULL);
    return n_statfs(path, buf);
}

int fstatfs(int fd, void *buf) {
    fstatfs_func_t n_fstatfs = HCC_GetNextAddr(fstatfs_callchain,NULL);
    return n_fstatfs(fd, buf);
}

// sys/mount.h
PHookCallChain mount_callchain = NULL;
PHookCallChain umount_callchain = NULL;

int mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data) {
    mount_func_t n_mount = HCC_GetNextAddr(mount_callchain, NULL);
    return n_mount(source, target, filesystemtype, mountflags, data);
}

int umount(const char *target, int flags) {
    unmount_func_t n_umount = HCC_GetNextAddr(umount_callchain, NULL);
    return n_umount(target, flags);
}

// <sys/utsname.h>
PHookCallChain uname_callchain = NULL;

int uname(void *buf) {
    uname_func_t n_uname = HCC_GetNextAddr(uname_callchain, NULL);
    return n_uname(buf);
}

// <pwd.h>
PHookCallChain getpwuid_callchain = NULL;

void *getpwuid(uid_t uid) {
    getpwuid_func_t n_getpwuid = HCC_GetNextAddr(getpwuid_callchain, NULL);
    return n_getpwuid(uid);
}

// <sys/ioctl.h>
PHookCallChain ioctl_callchain = NULL;
int ioctl(int fd, unsigned long request, ...) {
    ioctl_func_t n_ioctl = HCC_GetNextAddr(ioctl_callchain, NULL);
    va_list args;
    va_start(args, request);
    void *arg = va_arg(args, void *);
    va_end(args);
    return n_ioctl(fd, request, arg);
}

// <sys/select.h>
PHookCallChain select_callchain = NULL;

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout){
    select_func_t n_select = HCC_GetNextAddr(select_callchain, NULL);
    return n_select(nfds, readfds, writefds, exceptfds, timeout);
}

// <sys/socket.h>
PHookCallChain recvfrom_callchain = NULL;
PHookCallChain sendto_callchain = NULL;

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, void *src_addr, void *addrlen) {
    recvfrom_func_t n_recvfrom = HCC_GetNextAddr(recvfrom_callchain, NULL);
    return n_recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
}

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, void *dest_addr, unsigned int addrlen) {
    sendto_func_t n_sendto = HCC_GetNextAddr(sendto_callchain, NULL);
    return n_sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}

void hcc_init_libc(void){
    if(hcc_libc_initalized){return;}
    hcc_libc_initalized = 1;
    // unistd.h
    access_callchain = HCC_CreateCallChain("libc.so.6","access");
    open_callchain = HCC_CreateCallChain("libc.so.6","open");
    system_callchain = HCC_CreateCallChain("libc.so.6","system");
    readlink_callchain = HCC_CreateCallChain("libc.so.6","readlink");
    mkdir_callchain = HCC_CreateCallChain("libc.so.6","mkdir");
    opendir_callchain = HCC_CreateCallChain("libc.so.6","opendir");
    openat_callchain = HCC_CreateCallChain("libc.so.6","openat");
    chdir_callchain = HCC_CreateCallChain("libc.so.6","chdir");
    chroot_callchain = HCC_CreateCallChain("libc.so.6","chroot");
    unlink_callchain = HCC_CreateCallChain("libc.so.6","unlink");
    rmdir_callchain = HCC_CreateCallChain("libc.so.6","rmdir");
    symlink_callchain = HCC_CreateCallChain("libc.so.6","symlink");
    link_callchain = HCC_CreateCallChain("libc.so.6","link");
    utime_callchain = HCC_CreateCallChain("libc.so.6","utime");
    getlogin_r_callchain = HCC_CreateCallChain("libc.so.6", "getlogin_r");

    // sys/stat.h
    lxstat_callchain = HCC_CreateCallChain("libc.so.6","__lxstat");
    xstat_callchain = HCC_CreateCallChain("libc.so.6","__xstat");
    lxstat64_callchain = HCC_CreateCallChain("libc.so.6","__lxstat64");
    xstat64_callchain = HCC_CreateCallChain("libc.so.6","__xstat64");    
    rename_callchain = HCC_CreateCallChain("libc.so.6","rename");
    remove_callchain = HCC_CreateCallChain("libc.so.6","remove");
    stat_callchain = HCC_CreateCallChain("libc.so.6","stat");
    lstat_callchain = HCC_CreateCallChain("libc.so.6","lstat");
    fstat_callchain = HCC_CreateCallChain("libc.so.6","fstat");
    creat_callchain = HCC_CreateCallChain("libc.so.6","creat");
    creat64_callchain = HCC_CreateCallChain("libc.so.6","creat64");
    truncate_callchain = HCC_CreateCallChain("libc.so.6","truncate");
    ftruncate_callchain = HCC_CreateCallChain("libc.so.6","ftruncate");
    stat64_callchain = HCC_CreateCallChain("libc.so.6", "stat64");
    lstat64_callchain = HCC_CreateCallChain("libc.so.6", "lstat64");

    // stdio.h
    fopen_callchain = HCC_CreateCallChain("libc.so.6","fopen");

    // string.h
    strstr_callchain = HCC_CreateCallChain("libc.so.6", "strstr");

    // fcntl.h
    open64_callchain = HCC_CreateCallChain("libc.so.6", "open64");
    openat64_callchain = HCC_CreateCallChain("libc.so.6", "openat64");

    // sys/statfs.h
    statfs_callchain = HCC_CreateCallChain("libc.so.6","statfs");
    fstatfs_callchain = HCC_CreateCallChain("libc.so.6","fstatfs");

    // sys/mount.h
    mount_callchain = HCC_CreateCallChain("libc.so.6", "mount");
    umount_callchain = HCC_CreateCallChain("libc.so.6", "umount");

    // <sys/utsname.h>
    uname_callchain = HCC_CreateCallChain("libc.so.6", "uname");

    // <pwd.h>
    getpwuid_callchain = HCC_CreateCallChain("libc.so.6", "getpwuid");

    // <sys/ioctl.h>
    ioctl_callchain = HCC_CreateCallChain("libc.so.6", "ioctl");

    // <sys/select.h>
    select_callchain = HCC_CreateCallChain("libc.so.6", "select");

    // <sys/socket.h>
    recvfrom_callchain = HCC_CreateCallChain("libc.so.6", "recvfrom");
    sendto_callchain = HCC_CreateCallChain("libc.so.6", "sendto");
}