#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(void) {
    printk("Hello world\n");
    char * envp[] = { "HOME=/", NULL };
    // char * argv[] = { "/bin/runc", NULL };

    char * argv[] = { "/bin/bash", "-c", "/bin/ls > /tmp/container_util", NULL};
    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

    return 0;
}
