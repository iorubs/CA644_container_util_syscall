#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

static void display_file(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f != NULL) {
        int c;
        while ((c = fgetc(f)) != EOF) {
            putchar(c);
        }
        fclose(f);
    }
}

int manage_container(int i) {
    int manage_choice;
    char container_id[12];
    sprintf(container_id, "%d", i);
    char *container_action_1 = "1";
    char *container_action_2 = "2";
    char *container_action_3 = "3";

    printf("\n --- Manage Container %d --- \n\n",i);
    printf("1. Kill Container\n");
    printf("2. Stop Container\n");
    printf("3. Start Container\n\n");
    printf("Manage Choice : ");
    scanf("%d", &manage_choice);

    if(manage_choice == 1) {
        printf("\nKilling Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_1, container_id);
        return ret_code;
    }
    else if(manage_choice == 2){
        printf("\nStoping Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_2, container_id);
        return ret_code;
    }
    else if(manage_choice == 3){
        printf("\nStarting Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_3, container_id);
        return ret_code;
    }
    else {
        printf("\nInvalid Choice Exiting...\n\n");
        return 0;
    }
}

int create_container() {

    int container_type;

    printf("1. BusyBox Container \n");
    printf("2. Apline Container \n");
    printf("\nChoose Option From Menu Above 1-2: ");
    scanf("%d", &container_type);


    if(container_type == 1) {
        printf("\nCreating BusyBox container...\n\n");
        chdir("cd ca644_alpine");
    }
    else if(container_type == 2) {
        printf("\nCreating new Alpine container...\n\n");
        // container_type = "busybox";
    }
    else {
        printf("\nUnvalid container option\n\n");
        return 1;
    }


    char *arg[] = {"runc", "create", "test", NULL};
    return execvp(arg[0], arg);
}

int main() {
    printf("------------------------------------------\n");
    printf("        Container Util - System Call      \n");
    printf("------------------------------------------\n\n");

    int menu_option;
    int container_id_size = 20;
    char container_id[container_id_size];
    long int ret_code;

    printf("1. List Containers\n");
    printf("2. Start Container\n");
    printf("3. Delete Container\n");
    printf("4. List services inside Container\n");
    printf("5. Create Container\n");
    printf("Choose Option From Menu Above 1-3: ");
    scanf("%d", &menu_option);

    switch(menu_option) {
        case(1):
            printf("\n --- List Containers --- \n\n");
            ret_code = syscall(333, menu_option, NULL);
            display_file("/tmp/ca644_util_log");
            break;
        case(2):
            printf("\n --- Start Container --- \n\n");
            if(fgets(container_id, container_id_size, stdin) != NULL) {
                ret_code = syscall(333, menu_option, container_id);
            }
            break;
        case(3):
            printf("\n --- Delete Container --- \n\n");
            if(fgets(container_id, container_id_size, stdin) != NULL) {
                ret_code = syscall(333, menu_option, container_id);
            }
            break;
        case(4):
            printf("\n --- List services inside container --- \n\n");
            if(fgets(container_id, container_id_size, stdin) != NULL) {
                ret_code = syscall(333, menu_option, container_id);
            }
            break;
        case(5):
            printf("\n --- Create Container --- \n\n");
            ret_code = create_container();
            break;
        default:
            printf("\n Invalid Choice! \n");
    }
}
