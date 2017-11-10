#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(char *container_id,char *container_action) {

    printk("Container Id :  %s\n", container_id);
    printk("Container Action :  %s\n", container_action);

    char * envp[] = { "HOME=/", NULL };
    char * argv[] = { "/bin/bash", "-c", "/bin/ls > /tmp/container_util", NULL};
    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

    return 0;
}
