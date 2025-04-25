#!/bin/bash

# vars
PASSWORD="dinosaur"

# 64MB for now, need to find way to mass generate dummy files
dd if=/dev/zero of=usb.img bs=1M count=64

# set it up and mount
echo -n "$PASSWORD" | cryptsetup luksFormat usb.img --key-file=-
echo -n "$PASSWORD" | cryptsetup open usb.img secretusb --key-file=-
mkfs.ext4 /dev/mapper/secretusb
mount /dev/mapper/secretusb /mnt/flash

# copy files in
sudo cp -r flash_drive_files/* /mnt/flash/
sudo umount /mnt
sudo cryptsetup close secretusb

# zip it
zip -r lost_usb.zip usb.img
