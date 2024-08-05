#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "driver.h"

/* Utility function to log device status */
void log_device_status(const char *status) {
    printk(KERN_INFO "Device status: %s\n", status);
}

/* Utility function to validate buffer size */
int validate_buffer_size(size_t size) {
    if (size > BUFFER_SIZE) {
        printk(KERN_WARNING "Buffer size %zu exceeds limit\n", size);
        return -EINVAL;
    }
    return 0;
}

/* Utility function to clear the device buffer */
void clear_device_buffer(void) {
    memset(device_buffer, 0, BUFFER_SIZE);
    buffer_size = 0;
    printk(KERN_INFO "Device buffer cleared\n");
}
