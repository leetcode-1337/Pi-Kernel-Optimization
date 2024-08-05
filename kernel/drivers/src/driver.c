#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "driver.h"

static int major;
static const char *message = "Hello from the kernel!";
static int device_open = 0;

static int my_open(struct inode *inode, struct file *file) {
    if (device_open) return -EBUSY;
    device_open++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    device_open--;
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    ssize_t bytes_read = strlen(message);
    if (*offset >= bytes_read) return 0;
    if (copy_to_user(buffer, message, bytes_read)) return -EFAULT;
    *offset += bytes_read;
    return bytes_read;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
};

static int __init my_init(void) {
    major = register_chrdev(0, "my_device", &fops);
    if (major < 0) return major;
    printk(KERN_INFO "Registered with major number %d\n", major);
    return 0;
}

static void __exit my_exit(void) {
    unregister_chrdev(major, "my_device");
    printk(KERN_INFO "Unregistered\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("A simple character device driver");
