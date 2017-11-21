#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/string.h>

asmlinkage long sys_hello(int container_action, char *container_id) {

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/bin:/usr/sbin", NULL };

    char dest[50];
    dest[sizeof(dest)] = '\0';
    strcpy(dest, "runc ");

    printk("Container id: %s \n", container_id);

    if (container_action == 1) {
        printk("Get list of containers.\n");
        strncat(dest, "list > /tmp/ca644_util_log", 50);
    }
    else if (container_action == 3) {
        printk("Get container state.\n");
        strncat(dest, "state ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " > /tmp/ca644_util_log 2>&1", 50);
    }
    else if (container_action == 4) {
        printk("Start container.\n");
        strncat(dest, "start ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
    }
    else if (container_action == 5) {
        printk("List Container services.\n");
        strncat(dest, "ps ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " > /tmp/ca644_util_log 2>&1", 50);
    }
    else if (container_action == 6) {
        printk("Pause running container.\n");
        strncat(dest, "pause ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
    }
    else if (container_action == 7) {
        printk("Resume paused container.\n");
        strncat(dest, "resume ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
    }
    else if (container_action == 8) {
        printk("Kill container (force stop).\n");
        strncat(dest, "kill ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " KILL 2> /tmp/ca644_util_log", 50);
    }
    else if (container_action == 9) {
        printk("Delete stopped container.\n");
        strncat(dest, "delete ", 50);
        strncat(dest, container_id, 50);
        strncat(dest, " 2> /tmp/ca644_util_log", 50);
    }
    else {
        printk("Invalid container action.\n");
        return 1;
    }

    char * argv[] = {"/bin/bash", "-c", dest, NULL};

    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
}
