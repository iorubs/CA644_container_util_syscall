#!/bin/bash

test $EUID -ne 0 &&
{ echo "This script must be run as root"; exit 1; }

apt-get install -y \
    wget \
    make \
    gcc \
    libssl-dev

kernel_major_v="4"
kernel_minor_v="13.9"
kernel_full_v="$kernel_major_v.$kernel_minor_v"

rm -rf /usr/src/linux-$kernel_full_v &&
wget https://www.kernel.org/pub/linux/kernel/v$kernel_major_v.x/linux-$kernel_full_v.tar.gz &&
tar -xvf linux-$kernel_full_v.tar.gz -C/usr/src/ &&
rm -rf linux-$kernel_full_v.tar.gz

test $? -ne 0 &&
{ echo "Failled to download/untar linux kernel $kernel_full_v, make sure you picked a valid version."; exit 1; }

mkdir /usr/src/linux-$kernel_full_v/hello &&
cp hello.c Makefile /usr/src/linux-$kernel_full_v/hello/

sed -ri 's/core-y.*kernel.*/& hello\//' /usr/src/linux-$kernel_full_v/Makefile &&
sed -ri 's/^#endif$/asmlinkage long sys_hello(void);\n&/' /usr/src/linux-$kernel_full_v/include/linux/syscalls.h

sed -rie 'N;s/([0-9]+).*\n^$/&\1\n/;P;D' /usr/src/linux-4.13.9/arch/x86/entry/syscalls/syscall_64.tbl

sys_call_num=$(($(grep -E "^[0-9]+$" /usr/src/linux-4.13.9/arch/x86/entry/syscalls/syscall_64.tbl)+1))

sed -ri "s/^[0-9]+$/$sys_call_num\t64\thello\t\t\tsys_hello/g" /usr/src/linux-4.13.9/arch/x86/entry/syscalls/syscall_64.tbl
