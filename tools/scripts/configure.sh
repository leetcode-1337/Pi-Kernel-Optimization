#!/bin/bash
echo "Configuring kernel..."

# Apply patches if any
# cd kernel
# patch -p1 < ../patches/custom.patch

# Configure the kernel
cd kernel
make menuconfig

echo "Kernel configuration completed."
