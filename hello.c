#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/string.h>
#include <linux/sched.h>

#define ID_LEN 20
#define COMMAND_LEN 50
#define LIST 1
#define STATE 3
#define START 4
#define PS 5
#define PAUSE 6
#define RESUME 7
#define KILL 8
#define DELETE 9

void filterAction(char* dest, int container_action) {
    strcpy(dest, "runc ");

    if (container_action == LIST) {
        printk("Get list of containers.\n");
        strncat(dest, "list", COMMAND_LEN);
    }
    else if (container_action == STATE) {
        printk("Get container state.\n");
        strncat(dest, "state ", COMMAND_LEN);
    }
    else if (container_action == START) {
        printk("Start container.\n");
        strncat(dest, "start ", COMMAND_LEN);
    }
    else if (container_action == PS) {
        printk("List Container services.\n");
        strncat(dest, "ps ", COMMAND_LEN);
    }
    else if (container_action == PAUSE) {
        printk("Pause running container.\n");
        strncat(dest, "pause ", COMMAND_LEN);
    }
    else if (container_action == RESUME) {
        printk("Resume paused container.\n");
        strncat(dest, "resume ", COMMAND_LEN);
    }
    else if (container_action == KILL) {
        printk("Kill container (force stop).\n");
        strncat(dest, "kill ", COMMAND_LEN);
    }
    else if (container_action == DELETE) {
        printk("Delete stopped container.\n");
        strncat(dest, "delete ", COMMAND_LEN);
    }
}

asmlinkage long sys_hello(int container_action, char *container_id) {

    printk("System call was initiated by : %s with pid : %i", current->comm,current->pid);

    if(strlen(container_id) > ID_LEN || strlen(container_id) <= 0) {
        printk("Container Id Invalid, system call aborted..\n");
        return 1;
    }

    char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PWD=/",
        "PATH=/bin:/usr/sbin", NULL };

    char dest[COMMAND_LEN];
    dest[sizeof(dest)] = '\0';

    printk("Container id: %s \n", container_id);

    if (container_action >= LIST && container_action <= DELETE) {
        filterAction(dest, container_action);
    }
    else {
        printk("Invalid container action.\n");
        return 1;
    }
 
    if(container_action != LIST)
        strncat(dest, container_id, COMMAND_LEN);

    if(container_action == KILL)
        strncat(dest, " KILL", COMMAND_LEN);

    if(container_action == LIST || container_action == STATE || container_action == PS)
        strncat(dest, " > /tmp/ca644_util_log 2>&1", COMMAND_LEN);
    else
        strncat(dest, " 2> /tmp/ca644_util_log", COMMAND_LEN);

    char * argv[] = {"/bin/bash", "-c", dest, NULL};
    int ret_code = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);

    if(ret_code != 0)
        printk("Could not execute container action.\n");
    else
        printk("Container action executed successfully.\n");
    return ret_code;
}
