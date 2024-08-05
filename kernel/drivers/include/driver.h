#ifndef DRIVER_H
#define DRIVER_H

#include <linux/fs.h>      // For file operations
#include <linux/module.h>  // For module initialization and cleanup

// Function prototypes
int register_device(void);
void unregister_device(int major);

#endif // DRIVER_H
