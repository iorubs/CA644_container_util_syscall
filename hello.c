#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/string.h>

asmlinkage long sys_hello(int container_action, char *container_id) {

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/bin:/usr/sbin", NULL };

    char * argv[] = {"/bin/bash", "-c", "command", NULL};

    char dest[50];
    dest[sizeof(dest)] = '\0';
    strcpy(dest, "runc ");

    printk("Container id: %s \n", container_id);

    if (container_action == 1) {
        printk("Running container list.\n");
        strncat(dest, "list > /tmp/ca644_util_log", 50);
        argv[2] = dest;
    }
    else if (container_action == 2) {
        printk("Running container start.\n");
        strncat(dest, "start ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
        argv[2] = dest;
    }
    else if (container_action == 3) {
        printk("Running container delete.\n");
        strncat(dest, "delete ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
        argv[2] = dest;
    }
    else if (container_action == 4) {
        printk("Running container ps.\n");
        strncat(dest, "ps ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " > /tmp/ca644_util_log 2>&1", 50);
        argv[2] = dest;
    }

    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
}
