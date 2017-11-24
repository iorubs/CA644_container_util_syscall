#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/string.h>
#include <linux/sched.h>

#TODO: size constants, start and exit fucntions

void filterAction(char* dest, int container_action) {
    strcpy(dest, "runc ");

    if (container_action == 1) {
        printk("Get list of containers.\n");
        strncat(dest, "list", 50);
    }
    else if (container_action == 3) {
        printk("Get container state.\n");
        strncat(dest, "state ", 50);
    }
    else if (container_action == 4) {
        printk("Start container.\n");
        strncat(dest, "start ", 50);
    }
    else if (container_action == 5) {
        printk("List Container services.\n");
        strncat(dest, "ps ", 50);
    }
    else if (container_action == 6) {
        printk("Pause running container.\n");
        strncat(dest, "pause ", 50);
    }
    else if (container_action == 7) {
        printk("Resume paused container.\n");
        strncat(dest, "resume ", 50);
    }
    else if (container_action == 8) {
        printk("Kill container (force stop).\n");
        strncat(dest, "kill ", 50);
    }
    else if (container_action == 9) {
        printk("Delete stopped container.\n");
        strncat(dest, "delete ", 50);
    }
}

asmlinkage long sys_hello(int container_action, char *container_id) {
   printk("System call was initiated by : %s with pid : %i", current->comm,current->pid);

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/bin:/usr/sbin", NULL };

    char dest[50];
    dest[sizeof(dest)] = '\0';

    printk("Container id: %s \n", container_id);

    if (container_action >= 1 && container_action <= 9) {
        filterAction(dest, container_action);
    }
    else {
        printk("Invalid container action.\n");
        return 1;
    }
 
    if(container_action != 1)
        strncat(dest, container_id, 50);

    if(container_action == 8)
        strncat(dest, " KILL", 50);

    if(container_action == 1 || container_action == 3 || container_action == 5)
        strncat(dest, " > /tmp/ca644_util_log 2>&1", 50);
    else
        strncat(dest, " 2> /tmp/ca644_util_log", 50);

    char * argv[] = {"/bin/bash", "-c", dest, NULL};
    int ret_code = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);

    if(ret_code != 0)
        printk("Could not execute container action.\n");
    else
        printk("Container action executed successfully.\n");

    return ret_code;
}
