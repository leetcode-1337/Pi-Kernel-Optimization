#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "driver.h"

#define DEVICE_NAME "my_device"
#define BUFFER_SIZE 1024

static char device_buffer[BUFFER_SIZE];
static int buffer_size = 0;

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "%s: Device opened\n", DEVICE_NAME);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "%s: Device closed\n", DEVICE_NAME);
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    ssize_t bytes_read = 0;

    if (*offset >= buffer_size)
        return 0;

    if (length > buffer_size - *offset)
        length = buffer_size - *offset;

    if (copy_to_user(buffer, device_buffer + *offset, length))
        return -EFAULT;

    *offset += length;
    bytes_read = length;
    printk(KERN_INFO "%s: Read %zu bytes\n", DEVICE_NAME, bytes_read);

    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    ssize_t bytes_written = 0;

    if (*offset >= BUFFER_SIZE)
        return -ENOMEM;

    if (length > BUFFER_SIZE - *offset)
        length = BUFFER_SIZE - *offset;

    if (copy_from_user(device_buffer + *offset, buffer, length))
        return -EFAULT;

    *offset += length;
    buffer_size += length;
    bytes_written = length;
    printk(KERN_INFO "%s: Written %zu bytes\n", DEVICE_NAME, bytes_written);

    return bytes_written;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
};

int register_device(void) {
    int result = register_chrdev(0, DEVICE_NAME, &fops);
    if (result < 0) {
        printk(KERN_ALERT "%s: Failed to register device\n", DEVICE_NAME);
        return result;
    }
    printk(KERN_INFO "%s: Device registered with major number %d\n", DEVICE_NAME, result);
    return result;
}

void unregister_device(int major) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "%s: Device unregistered\n", DEVICE_NAME);
}
