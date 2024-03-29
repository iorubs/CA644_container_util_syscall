#!/bin/bash

test $EUID -ne 0 &&
{ echo "This script must be run as root" >&2; exit 1; }

apt-get update &&
apt-get upgrade -y &&
apt-get install -y \
    wget \
    make \
    gcc \
    libssl-dev \
    libncursesw5-dev \
    runc

test $? -ne 0 &&
{ echo "Failed to update and install dependencies." >&2 ; exit 1; }

# Download kernel
kernel_major_v="4"
kernel_minor_v="14.2"
kernel_full_v="$kernel_major_v.$kernel_minor_v"

rm -rf /usr/src/linux-$kernel_full_v linux-$kernel_full_v.tar.gz &&
wget https://www.kernel.org/pub/linux/kernel/v$kernel_major_v.x/linux-$kernel_full_v.tar.gz &&
tar -xvf linux-$kernel_full_v.tar.gz -C/usr/src/ &&
rm -rf linux-$kernel_full_v.tar.gz

test $? -ne 0 &&
{ echo "Failed to download/untar linux kernel $kernel_full_v, make sure you picked a valid version." >&2 ; exit 1; }

# Add new system call
mkdir /usr/src/linux-$kernel_full_v/container_util &&
cp container_util.c Makefile /usr/src/linux-$kernel_full_v/container_util/

sed -ri 's/core-y.*kernel.*/& container_util\//' /usr/src/linux-$kernel_full_v/Makefile &&
sed -ri 's/^#endif$/asmlinkage long sys_container_util(void);\n&/' /usr/src/linux-$kernel_full_v/include/linux/syscalls.h

sed -rie 'N;s/([0-9]+).*\n^$/&\1\n/;P;D' /usr/src/linux-$kernel_full_v/arch/x86/entry/syscalls/syscall_64.tbl &&
sys_call_num=$(($(grep -E "^[0-9]+$" /usr/src/linux-$kernel_full_v/arch/x86/entry/syscalls/syscall_64.tbl)+1)) &&
sed -ri "s/^[0-9]+$/$sys_call_num\t64\tcontainer_util\t\t\tsys_container_util/g" /usr/src/linux-$kernel_full_v/arch/x86/entry/syscalls/syscall_64.tbl

# Compile kernel and install kernel modules.
cd /usr/src/linux-$kernel_full_v &&
make menuconfig &&
make -j$(nproc) &&
make modules_install install

test $? -ne 0 &&
{ echo "Unable to compile and install kernel, possibly a dependency issue." >&2; exit 1; }

#Update GRUB boot order.
mkinitramfs -o /boot/initrd.img-$kernel_full_v $kernel_full_v &&
update-grub &&
reboot
