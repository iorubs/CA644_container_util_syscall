#include <linux/kernel.h>
#include <linux/kmod.h>
#include <unistd.h>

asmlinkage long sys_hello(int container_action, char *container_id) {

    char * envp[] = {"HOME=/", NULL};
    char * argv[] = {"/bin/bash", "-c", "command", NULL};

    if (container_action == 1) {
        chdir("/tmp/ca644_container_util/ca644_alpine")
        argv[2] = "/usr/sbin/runc run -d test > /tmp/ca644_container_util/log";
    }
    else if (container_action == 2) {
        argv[2] = "/usr/sbin/runc list > /tmp/ca644_container_util/log";
    }
    else if (container_action == 3) {
        argv[2] = "/usr/sbin/runc list > /tmp/ca644_container_util/log";
    }
    else if (container_action == 4) {
        argv[2] = "/usr/sbin/runc list > /tmp/ca644_container_util/log";
    }
    else if (container_action == 6) {
        argv[2] = "/usr/sbin/runc list > /tmp/ca644_container_util/log";
    }
    else {
        return 666;
    }


    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

    return 0;
}
