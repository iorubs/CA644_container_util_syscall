#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(int container_action, char *action_arg) {

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };

    char * argv[] = {"/bin/bash", "-c", "/bin/ls", NULL};

    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    printk("Container Action :  %d\n", container_action);

    if (container_action == 1) {
        printk("Running container create.\n");
        argv[2] = "runc create test 2> /tmp/ca644_util_log";
    }
    else if (container_action == 2) {
        printk("Running container list.\n");
        argv[2] = "runc list 2>&1 > /tmp/ca644_util_log";
    }
    else if (container_action == 3) {
        printk("Running container start.\n");
        argv[2] = "runc start 2> /tmp/ca644_util_log";
    }
    else if (container_action == 4) {
        printk("Running container delete.\n");
        argv[2] = "runc delete test 2> /tmp/ca644_util_log";
    }
    else if (container_action == 5) {
        printk("Running container ps.\n");
        argv[2] = "runc ps test 2>&1 > /tmp/ca644_util_log";
    }
    else {
        return 666;
    }


    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}
