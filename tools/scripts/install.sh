#!/bin/bash
echo "Installing custom kernel..."

# Copy kernel image and modules to boot directory
sudo cp kernel/zImage /boot/kernel7.img
sudo cp -r kernel/modules/ /lib/modules/

# Update bootloader configuration if needed
# sudo update-bootloader

echo "Custom kernel installed successfully."
