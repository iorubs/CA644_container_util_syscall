#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

Int main() {
    Long int amm = syscall(333);
    printf("Sys call returned %ld\n", amma);
    Return 0;
}
