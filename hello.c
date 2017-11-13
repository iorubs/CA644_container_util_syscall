#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(int container_action, char *container_id) {

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/bin:/usr/sbin", NULL };

    char * argv[] = {"/bin/bash", "-c", "command", NULL};

    printk("Container id: %s \n", container_id);


    if (container_action == 1) {
        printk("Running container list.\n");
        argv[2] = "runc list > /tmp/ca644_util_log";
    }
    else if (container_action == 2) {
        printk("Running container start.\n");
        argv[2] = "runc start 2> /tmp/ca644_util_log";
    }
    else if (container_action == 3) {
        printk("Running container delete.\n");
        argv[2] = "runc delete test 2> /tmp/ca644_util_log";
    }
    else if (container_action == 4) {
        printk("Running container ps.\n");
        argv[2] = "runc ps test 2>&1 > /tmp/ca644_util_log";
    }

    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
}
