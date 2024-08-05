#!/bin/bash
echo "Measuring boot time..."

# Measure boot time
sudo systemd-analyze > boot_time.txt

echo "Boot time measurement completed."
