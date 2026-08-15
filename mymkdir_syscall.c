#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

asmlinkage long sys_mymkdir(const char __user *path)
{
    char kpath[256];
    struct path parent;
    struct dentry *dentry;
    int err;

    if (!path)
        return -EINVAL;

    /* copy pathname from user */
    if (strncpy_from_user(kpath, path, sizeof(kpath)) <= 0)
        return -EFAULT;
    kpath[sizeof(kpath)-1] = '\0';

    printk(KERN_INFO "sys_mymkdir called with: %s\n", kpath);

    /* create parent dentry for the new pathname */
    dentry = kern_path_create(AT_FDCWD, kpath, &parent, LOOKUP_DIRECTORY);
    if (IS_ERR(dentry))
        return PTR_ERR(dentry);

    err = vfs_mkdir(parent.dentry->d_inode, dentry, 0777);

    done_path_create(&parent, dentry);

    return err;
}
