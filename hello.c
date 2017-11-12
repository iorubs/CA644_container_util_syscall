#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(int container_action, char *action_arg) {

    char * envp[] = {"HOME=/", NULL};
    char * argv[] = {"/bin/bash", "-c", "command", NULL};

    printk("Container Action :  %d\n", container_action);

    if (container_action == 1) {
        printk("Running container create.\n");
        argv[2] = "/bin/runc create test > /tmp/ca644_util_log";
    }
    else if (container_action == 2) {
        printk("Running container list.\n");
        argv[2] = "/bin/runc list > /tmp/ca644_util_log";
    }
    else if (container_action == 3) {
        printk("Running container start.\n");
        argv[2] = "/bin/runc start > /tmp/ca644_util_log";
    }
    else if (container_action == 4) {
        printk("Running container delete.\n");
        argv[2] = "/bin/runc delete test > /tmp/ca644_util_log";
    }
    else if (container_action == 6) {
        printk("Running container ps.\n");
        argv[2] = "/bin/runc ps test > /tmp/ca644_util_log";
    }
    else {
        return 666;
    }


    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
}
