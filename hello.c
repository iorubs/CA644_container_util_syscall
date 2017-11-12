#include <linux/kernel.h>
#include <linux/kmod.h>

asmlinkage long sys_hello(int container_action, char *action_arg) {

    char * envp[] = {"HOME=/", NULL};
    char * argv[] = {"/bin/bash", "-c", "command", NULL};

    if (container_action == 1) {
        argv[2] = "/bin/runc create test";
    }
    else if (container_action == 2) {
        argv[2] = "/bin/runc list > /tmp/log";
    }
    else if (container_action == 3) {
        argv[2] = "/bin/runc start";
    }
    else if (container_action == 4) {
        argv[2] = "/bin/runc delete test";
    }
    else if (container_action == 6) {
        argv[2] = "/bin/runc ps test > /tmp/log";
    }
    else {
        return 666;
    }


    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

    return 0;
}
