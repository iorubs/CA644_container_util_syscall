#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
    long int ret = syscall(333);
    printf("Sys call returned %ld\n", ret);
    return 0;
}
