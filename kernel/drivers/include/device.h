#ifndef DEVICE_H
#define DEVICE_H

#include <linux/fs.h>      // For file operations

// Function prototypes
int device_open(struct inode *inode, struct file *file);
int device_release(struct inode *inode, struct file *file);
ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset);
ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset);

#endif // DEVICE_H
